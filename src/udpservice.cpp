#include "udpservice.h"
#include <QDebug>

UdpService::UdpService(QObject *parent)
    : QObject(parent), m_socket(new QUdpSocket(this)), m_broadcastTimer(new QTimer(this))
{
    connect(m_broadcastTimer, &QTimer::timeout, this, &UdpService::sendBroadcast);
    connect(m_socket, &QUdpSocket::readyRead, this, &UdpService::processPendingDatagrams);
    updateBroadcastAddresses();
}

UdpService::~UdpService() {}

void UdpService::startBroadcast() {
    m_broadcastTimer->start(1000); // 1 second interval
}

void UdpService::stopBroadcast() {
    m_broadcastTimer->stop();
}

void UdpService::updateBroadcastAddresses() {
    m_broadcastAddresses.clear();
    const auto interfaces = QNetworkInterface::allInterfaces();
    for (const QNetworkInterface &iface : interfaces) {
        if (iface.flags().testFlag(QNetworkInterface::IsUp) &&
            iface.flags().testFlag(QNetworkInterface::IsRunning) &&
            !iface.flags().testFlag(QNetworkInterface::IsLoopBack)) {
            for (const QNetworkAddressEntry &entry : iface.addressEntries()) {
                if (entry.broadcast().isNull()) continue;
                m_broadcastAddresses.append(entry.broadcast());
            }
        }
    }
}

void UdpService::sendBroadcast() {
    for (const QHostAddress &addr : m_broadcastAddresses) {
        m_socket->writeDatagram(m_message, addr, m_port);
    }
}

void UdpService::processPendingDatagrams() {
    while (m_socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(m_socket->pendingDatagramSize());
        QHostAddress sender;
        quint16 senderPort;
        m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
        emit moduleDiscovered(sender.toString(), datagram);
    }
}
