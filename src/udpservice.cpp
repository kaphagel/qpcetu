#include "udpservice.h"
#include <QDebug>

#include "udpservice.h"
#include <QDebug>
#include <QNetworkDatagram>

UdpService::UdpService(QObject *parent)
    : QObject(parent), m_socket(new QUdpSocket(this)), m_broadcastTimer(new QTimer(this)), m_controllerManager(new ControllerManager(this))
{
    connect(m_broadcastTimer, &QTimer::timeout, this, &UdpService::sendBroadcast);
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpService::processPendingDatagrams);

    // Connect controller manager signals
    connect(m_controllerManager, &ControllerManager::controllerCountChanged,
            this, &UdpService::controllersChanged);
    connect(m_controllerManager, &ControllerManager::controllerAdded,
            this, &UdpService::controllerDiscovered);

    updateBroadcastAddresses();
}

UdpService::~UdpService() {}

int UdpService::discoveredControllers() const
{
    return m_controllerManager->controllerCount();
}

void UdpService::startBroadcast()
{
    qDebug() << "Starting UDP broadcast service - interval: 1000ms, port:" << m_port << ", message:" << m_message;

    // Bind socket to listen for responses
    if (!m_socket->bind(QHostAddress::Any, m_port))
    {
        qDebug() << "Failed to bind UDP socket to port" << m_port << "- Error:" << m_socket->errorString();
    }
    else
    {
        qDebug() << "UDP socket successfully bound to port" << m_port << "for listening";
    }

    updateBroadcastAddresses();
    qDebug() << "Found" << m_broadcastAddresses.size() << "broadcast addresses:" << m_broadcastAddresses;

    // Debug: Show local IP addresses that will be filtered out
    qDebug() << "Local IP addresses (will be filtered from responses):";
    const auto interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &iface : interfaces)
    {
        if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
            iface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (const QNetworkAddressEntry &entry : iface.addressEntries())
            {
                qDebug() << "  - Local IP:" << entry.ip().toString() << "(will also filter ::ffff:" + entry.ip().toString() + ")";
            }
        }
    }

    qDebug() << "UDP service is now listening for responses on port" << m_port;
    m_broadcastTimer->start(1000); // 1 second interval
}

void UdpService::stopBroadcast()
{
    m_broadcastTimer->stop();
}

void UdpService::updateBroadcastAddresses()
{
    m_broadcastAddresses.clear();
    const auto interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &iface : interfaces)
    {
        if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
            iface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
        {
            for (const QNetworkAddressEntry &entry : iface.addressEntries())
            {
                if (entry.broadcast().isNull())
                    continue;
                m_broadcastAddresses.append(entry.broadcast());
            }
        }
    }
}

void UdpService::sendBroadcast()
{
    static int broadcastCount = 0;
    broadcastCount++;

    qDebug() << "Sending UDP broadcast:" << m_message << "to" << m_broadcastAddresses.size() << "addresses on port" << m_port;
    for (const QHostAddress &addr : m_broadcastAddresses)
    {
        qint64 sent = m_socket->writeDatagram(m_message, addr, m_port);
        qDebug() << "  -> Sent to" << addr.toString() << ":" << m_port << "(" << sent << "bytes)";
    }

    // Every 10th broadcast, show listening status
    if (broadcastCount % 10 == 0)
    {
        qDebug() << "📡 Listening status: Socket state =" << m_socket->state()
                 << ", Local port =" << m_socket->localPort()
                 << ", Has pending =" << m_socket->hasPendingDatagrams();
    }
}

void UdpService::processPendingDatagrams()
{
    qDebug() << "Processing incoming UDP datagrams...";
    while (m_socket->hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);

        // Filter out our own IP address to avoid seeing our own broadcasts
        bool isOwnMessage = false;
        QString senderStr = sender.toString();

        // Check if this is from our own network interface
        const auto interfaces = QNetworkInterface::allInterfaces();
        for (const QNetworkInterface &iface : interfaces)
        {
            if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
                iface.flags().testFlag(QNetworkInterface::IsRunning) &&
                !iface.flags().testFlag(QNetworkInterface::IsLoopBack))
            {
                for (const QNetworkAddressEntry &entry : iface.addressEntries())
                {
                    QString localAddr = entry.ip().toString();
                    // Check both direct IP and IPv6-mapped IPv4 format
                    if (senderStr == localAddr || senderStr == ("::ffff:" + localAddr))
                    {
                        isOwnMessage = true;
                        break;
                    }
                }
                if (isOwnMessage)
                    break;
            }
        }

        if (isOwnMessage)
        {
            qDebug() << "🔄 Ignoring own message from" << senderStr << ":" << senderPort << "- Data:" << datagram;
        }
        else
        {
            qDebug() << "🎯 External UDP message from" << senderStr << ":" << senderPort << "- Data:" << datagram;

            // Try to parse as industrial controller discovery response
            QString response = QString::fromUtf8(datagram);
            if (response.contains("Protocol version") && response.contains("FB type"))
            {
                qDebug() << "📡 Industrial controller discovery response detected";
                IndustrialController *controller = m_controllerManager->addOrUpdateController(response, sender);
                if (controller)
                {
                    qDebug() << "✅ Controller parsed:" << controller->typeDisplayName()
                             << "at" << controller->ipAddress();
                }
            }
            else
            {
                qDebug() << "📦 Generic UDP response - not a recognized controller format";
            }

            // Still emit the original signal for compatibility
            emit moduleDiscovered(senderStr, datagram);
        }
    }
}
