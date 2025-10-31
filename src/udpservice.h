#pragma once

#include <QObject>
#include <QUdpSocket>
#include <QTimer>
#include <QNetworkInterface>
#include <QHostAddress>
#include "controllermanager.h"

class UdpService : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int discoveredControllers READ discoveredControllers NOTIFY controllersChanged)
    Q_PROPERTY(ControllerManager *controllerManager READ controllerManager CONSTANT)

public:
    explicit UdpService(QObject *parent = nullptr);
    ~UdpService();

    void startBroadcast();
    void stopBroadcast();

    // Getters
    int discoveredControllers() const;
    ControllerManager *controllerManager() const { return m_controllerManager; }

signals:
    void moduleDiscovered(const QString &address, const QByteArray &response);
    void controllerDiscovered(IndustrialController *controller);
    void controllersChanged();

private slots:
    void sendBroadcast();
    void processPendingDatagrams();

private:
    QUdpSocket *m_socket;
    QTimer *m_broadcastTimer;
    QList<QHostAddress> m_broadcastAddresses;
    ControllerManager *m_controllerManager;
    quint16 m_port = 3250; // Industrial module discovery port
    QByteArray m_message = "Module Scan";
    void updateBroadcastAddresses();
};
