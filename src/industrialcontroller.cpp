#include "industrialcontroller.h"
#include <QRegularExpression>
#include <QJsonDocument>
#include <QDebug>

IndustrialController::IndustrialController(QObject *parent)
    : QObject(parent), m_controllerType(UNKNOWN), m_dhcpEnabled(false), m_passwordProtected(false), m_status(OFFLINE), m_signalStrength(0), m_timeoutTimer(new QTimer(this))
{
    setupTimeoutTimer();
}

bool IndustrialController::parseDiscoveryResponse(const QString &response, const QHostAddress &sender)
{
    // Parse the discovery response format:
    // "Protocol version = 1.00;FB type = EPIC4;Module version = 1.99;MAC = C0-22-F1-41-03-3A;IP = 192.168.10.243;SN = 255.255.255.0;GW = 192.168.10.1;DHCP = OFF;PSWD = OFF;HN = Andritz;DNS1 = 0.0.0.0;DNS2 = 0.0.0.0;"

    qDebug() << "Parsing controller discovery response:" << response;

    // Split by semicolon and parse key-value pairs
    QStringList pairs = response.split(';', Qt::SkipEmptyParts);
    QHash<QString, QString> data;

    for (const QString &pair : pairs)
    {
        QStringList keyValue = pair.split('=', Qt::SkipEmptyParts);
        if (keyValue.size() == 2)
        {
            QString key = keyValue[0].trimmed();
            QString value = keyValue[1].trimmed();
            data[key] = value;
        }
    }

    // Extract controller information
    if (data.contains("Protocol version"))
    {
        m_protocolVersion = data["Protocol version"];
    }

    if (data.contains("FB type"))
    {
        m_controllerTypeStr = data["FB type"];
        m_controllerType = parseControllerType(m_controllerTypeStr);
    }

    if (data.contains("Module version"))
    {
        m_firmwareVersion = data["Module version"];
    }

    if (data.contains("MAC"))
    {
        m_macAddress = data["MAC"];
    }

    if (data.contains("IP"))
    {
        m_ipAddress = data["IP"];
    }
    else
    {
        // Fallback to sender IP if not provided
        m_ipAddress = sender.toString();
    }

    if (data.contains("SN"))
    {
        m_subnetMask = data["SN"]; // Note: This seems to be subnet mask, not serial number
    }

    if (data.contains("GW"))
    {
        m_gatewayAddress = data["GW"];
    }

    if (data.contains("DHCP"))
    {
        m_dhcpEnabled = (data["DHCP"].toUpper() == "ON");
    }

    if (data.contains("PSWD"))
    {
        m_passwordProtected = (data["PSWD"].toUpper() == "ON");
    }

    if (data.contains("HN"))
    {
        m_hostname = data["HN"];
    }

    if (data.contains("DNS1"))
    {
        m_dns1 = data["DNS1"];
    }

    if (data.contains("DNS2"))
    {
        m_dns2 = data["DNS2"];
    }

    // Update status
    m_discoveredAt = QDateTime::currentDateTime();
    updateLastSeen();
    setStatus(ONLINE);

    // Calculate signal strength (placeholder - could be based on response time)
    m_signalStrength = 85; // Good signal

    qDebug() << "Successfully parsed controller:"
             << "Type:" << m_controllerTypeStr
             << "IP:" << m_ipAddress
             << "MAC:" << m_macAddress
             << "Hostname:" << m_hostname;

    emit controllerChanged();
    emit dataUpdated();

    return true;
}

IndustrialController::ControllerType IndustrialController::parseControllerType(const QString &typeStr)
{
    QString type = typeStr.toUpper();

    if (type.contains("EPIC4"))
        return EPIC4;
    if (type.contains("EPIC5"))
        return EPIC5;
    if (type.contains("SNAP"))
        return SNAP_PAC;
    if (type.contains("CLICK"))
        return CLICK_PLC;
    if (type.contains("MODICON"))
        return MODICON;
    if (type.contains("LOGIX"))
        return COMPACT_LOGIX;

    return UNKNOWN;
}

QString IndustrialController::statusText() const
{
    switch (m_status)
    {
    case OFFLINE:
        return "Offline";
    case DISCOVERING:
        return "Discovering...";
    case ONLINE:
        return "Online";
    case COMM_ERROR:
        return "Error";
    case TIMEOUT:
        return "Timeout";
    default:
        return "Unknown";
    }
}

QString IndustrialController::typeDisplayName() const
{
    switch (m_controllerType)
    {
    case EPIC4:
        return "EPIC4 Controller";
    case EPIC5:
        return "EPIC5 Controller";
    case SNAP_PAC:
        return "SNAP PAC";
    case CLICK_PLC:
        return "Click PLC";
    case MODICON:
        return "Modicon PLC";
    case COMPACT_LOGIX:
        return "CompactLogix";
    case UNKNOWN:
    default:
        return m_controllerTypeStr.isEmpty() ? "Unknown Controller" : m_controllerTypeStr;
    }
}

QJsonObject IndustrialController::toJson() const
{
    QJsonObject obj;
    obj["type"] = m_controllerTypeStr;
    obj["protocolVersion"] = m_protocolVersion;
    obj["firmwareVersion"] = m_firmwareVersion;
    obj["ipAddress"] = m_ipAddress;
    obj["macAddress"] = m_macAddress;
    obj["hostname"] = m_hostname;
    obj["subnetMask"] = m_subnetMask;
    obj["gateway"] = m_gatewayAddress;
    obj["dns1"] = m_dns1;
    obj["dns2"] = m_dns2;
    obj["dhcpEnabled"] = m_dhcpEnabled;
    obj["passwordProtected"] = m_passwordProtected;
    obj["status"] = statusText();
    obj["lastSeen"] = m_lastSeen.toString(Qt::ISODate);
    obj["signalStrength"] = m_signalStrength;
    return obj;
}

void IndustrialController::updateLastSeen()
{
    m_lastSeen = QDateTime::currentDateTime();
    m_timeoutTimer->start(); // Reset timeout timer
    emit statusChanged();
}

void IndustrialController::setStatus(ConnectionStatus status)
{
    if (m_status != status)
    {
        m_status = status;
        emit statusChanged();
    }
}

void IndustrialController::checkTimeout()
{
    // If we haven't seen the controller in 30 seconds, mark as timeout
    if (m_lastSeen.secsTo(QDateTime::currentDateTime()) > 30)
    {
        setStatus(TIMEOUT);
    }
}

void IndustrialController::setupTimeoutTimer()
{
    m_timeoutTimer->setSingleShot(false);
    m_timeoutTimer->setInterval(5000); // Check every 5 seconds
    connect(m_timeoutTimer, &QTimer::timeout, this, &IndustrialController::checkTimeout);
}