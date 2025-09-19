#include <QCoreApplication>
#include <QUdpSocket>
#include <QTimer>
#include <QRandomGenerator>
#include <QDateTime>
#include <QDebug>

class MockUdpService : public QObject {
    Q_OBJECT
public:
    MockUdpService(quint16 port, QObject *parent = nullptr)
        : QObject(parent), m_port(port) {
        m_socket = new QUdpSocket(this);
        if (!m_socket->bind(QHostAddress::Any, m_port)) {
            qWarning() << "Failed to bind UDP socket on port" << m_port;
            QCoreApplication::quit();
        }
        connect(m_socket, &QUdpSocket::readyRead, this, &MockUdpService::processPendingDatagrams);
        qDebug() << "MockUdpService listening on port" << m_port;
    }

private slots:
    void processPendingDatagrams() {
        while (m_socket->hasPendingDatagrams()) {
            QByteArray datagram;
            datagram.resize(m_socket->pendingDatagramSize());
            QHostAddress sender;
            quint16 senderPort;
            m_socket->readDatagram(datagram.data(), datagram.size(), &sender, &senderPort);
            qDebug() << "Received UDP message from" << sender.toString() << ":" << senderPort << ":" << datagram;
            // Generate random response
            QByteArray response = generateRandomResponse();
            m_socket->writeDatagram(response, sender, senderPort);
            qDebug() << "Sent response:" << response;
        }
    }

    QByteArray generateRandomResponse() {
        QString msg = QString("MockResponse_%1").arg(QRandomGenerator::global()->generate());
        return msg.toUtf8();
    }

private:
    QUdpSocket *m_socket;
    quint16 m_port;
};

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);
    quint16 port = 45454; // Change to match your application's UDP port
    MockUdpService service(port);
    return app.exec();
}

#include "mockudpservice.moc"
