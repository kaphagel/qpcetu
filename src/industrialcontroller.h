#ifndef INDUSTRIALCONTROLLER_H
#define INDUSTRIALCONTROLLER_H

#include <QObject>
#include <QString>
#include <QHostAddress>
#include <QDateTime>
#include <QJsonObject>
#include <QTimer>

/**
 * @brief Represents a discovered industrial controller with its properties and status
 *
 * Parses UDP discovery responses and maintains controller state for HMI display
 */
class IndustrialController : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString controllerType READ controllerType NOTIFY controllerChanged)
    Q_PROPERTY(QString ipAddress READ ipAddress NOTIFY controllerChanged)
    Q_PROPERTY(QString macAddress READ macAddress NOTIFY controllerChanged)
    Q_PROPERTY(QString hostname READ hostname NOTIFY controllerChanged)
    Q_PROPERTY(QString firmwareVersion READ firmwareVersion NOTIFY controllerChanged)
    Q_PROPERTY(bool isOnline READ isOnline NOTIFY statusChanged)
    Q_PROPERTY(int signalStrength READ signalStrength NOTIFY statusChanged)

public:
    enum ControllerType
    {
        UNKNOWN = 0,
        EPIC4,
        EPIC5,
        SNAP_PAC,
        CLICK_PLC,
        MODICON,
        COMPACT_LOGIX
    };
    Q_ENUM(ControllerType)

    enum ConnectionStatus
    {
        OFFLINE = 0,
        DISCOVERING,
        ONLINE,
        COMM_ERROR, // Changed from ERROR to avoid Windows macro conflict
        TIMEOUT
    };
    Q_ENUM(ConnectionStatus)

    explicit IndustrialController(QObject *parent = nullptr);

    // Parse UDP discovery response
    bool parseDiscoveryResponse(const QString &response, const QHostAddress &sender);

    // Getters
    QString controllerType() const { return m_controllerTypeStr; }
    QString ipAddress() const { return m_ipAddress; }
    QString macAddress() const { return m_macAddress; }
    QString hostname() const { return m_hostname; }
    QString firmwareVersion() const { return m_firmwareVersion; }
    QString serialNumber() const { return m_serialNumber; }
    QString gatewayAddress() const { return m_gatewayAddress; }
    bool isDhcpEnabled() const { return m_dhcpEnabled; }
    bool isPasswordProtected() const { return m_passwordProtected; }
    QString dns1() const { return m_dns1; }
    QString dns2() const { return m_dns2; }

    bool isOnline() const { return m_status == ONLINE; }
    ConnectionStatus status() const { return m_status; }
    QDateTime lastSeen() const { return m_lastSeen; }
    int signalStrength() const { return m_signalStrength; }

    // For HMI display
    QString statusText() const;
    QString typeDisplayName() const;
    QJsonObject toJson() const;

public slots:
    void updateLastSeen();
    void setStatus(ConnectionStatus status);
    void checkTimeout();

signals:
    void controllerChanged();
    void statusChanged();
    void dataUpdated();

private:
    // Controller identification
    ControllerType m_controllerType;
    QString m_controllerTypeStr;
    QString m_protocolVersion;
    QString m_firmwareVersion;
    QString m_macAddress;
    QString m_serialNumber;

    // Network configuration
    QString m_ipAddress;
    QString m_subnetMask;
    QString m_gatewayAddress;
    QString m_dns1;
    QString m_dns2;
    bool m_dhcpEnabled;
    bool m_passwordProtected;
    QString m_hostname;

    // Status and monitoring
    ConnectionStatus m_status;
    QDateTime m_lastSeen;
    QDateTime m_discoveredAt;
    int m_signalStrength;
    QTimer *m_timeoutTimer;

    // Helper methods
    ControllerType parseControllerType(const QString &typeStr);
    void setupTimeoutTimer();
};

#endif // INDUSTRIALCONTROLLER_H