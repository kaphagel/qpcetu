#ifndef UDPSERVICE_H
#define UDPSERVICE_H

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QNetworkInterface>

class UdpService : public QObject {
    Q_OBJECT
public:
    explicit UdpService(QObject *parent = nullptr);
    ~UdpService();

    void startBroadcast();
    void stopBroadcast();

signals:
    void moduleDiscovered(const QString &address, const QByteArray &response);

private slots:
    void sendBroadcast();
    void processPendingDatagrams();

private:
    QUdpSocket *m_socket;
    QTimer *m_broadcastTimer;
    QList<QHostAddress> m_broadcastAddresses;
    quint16 m_port = 45454; // Example port
    QByteArray m_message = "Scan Module";
    void updateBroadcastAddresses();
};

#endif // UDPSERVICE_H
