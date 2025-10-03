#include "controllerstrategy.h"
#include <QStringList>
#include <QRegularExpression>
#include <QDebug>

// Base ControllerStrategy implementation
ControllerStrategy::ControllerStrategy(QObject *parent)
    : QObject(parent)
{
}

// Epic4Strategy implementation
Epic4Strategy::Epic4Strategy(QObject *parent)
    : ControllerStrategy(parent)
{
}

QStringList Epic4Strategy::supportedOperations() const
{
    return QStringList() << "READ_COILS" << "READ_DISCRETE_INPUTS" 
                        << "READ_HOLDING_REGISTERS" << "READ_INPUT_REGISTERS"
                        << "WRITE_SINGLE_COIL" << "WRITE_SINGLE_REGISTER"
                        << "WRITE_MULTIPLE_COILS" << "WRITE_MULTIPLE_REGISTERS";
}

bool Epic4Strategy::validateConfiguration(const QVariantMap &config) const
{
    // Validate required configuration parameters for EPIC4 controllers
    QStringList required = QStringList() << "ip_address" << "port" << "unit_id";
    
    for (const QString &key : required) {
        if (!config.contains(key) || config.value(key).toString().isEmpty()) {
            return false;
        }
    }
    
    // Validate IP address format
    QString ip = config.value("ip_address").toString();
    QRegularExpression ipRegex("^(?:(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)\\.){3}(?:25[0-5]|2[0-4][0-9]|[01]?[0-9][0-9]?)$");
    if (!ipRegex.match(ip).hasMatch()) {
        return false;
    }
    
    // Validate port range
    bool ok;
    int port = config.value("port").toInt(&ok);
    if (!ok || port < 1 || port > 65535) {
        return false;
    }
    
    return true;
}

QVariantMap Epic4Strategy::parseDiscoveryResponse(const QString &response) const
{
    if (!isValidResponse(response)) {
        return QVariantMap();
    }
    
    return parseKeyValuePairs(response);
}

QString Epic4Strategy::formatWriteRequest(const QString &register_addr, const QVariant &value) const
{
    // Format Modbus TCP write request for EPIC4
    // This would typically be binary data, but showing conceptual format
    return QString("WRITE_REG:%1=%2").arg(register_addr).arg(value.toString());
}

QVariant Epic4Strategy::parseReadResponse(const QString &response) const
{
    // Parse Modbus TCP response for EPIC4
    QRegularExpression responseRegex("READ_RESPONSE:(.+)");
    QRegularExpressionMatch match = responseRegex.match(response);
    
    if (match.hasMatch()) {
        return match.captured(1);
    }
    
    return QVariant();
}

bool Epic4Strategy::isValidResponse(const QString &response) const
{
    // Check if response contains expected EPIC4 discovery format
    return response.contains("Protocol version") && 
           response.contains("FB type") &&
           (response.contains("EPIC4") || response.contains("EPIC5"));
}

QVariantMap Epic4Strategy::parseKeyValuePairs(const QString &response) const
{
    QVariantMap result;
    
    // Split by semicolon and parse key=value pairs
    QStringList pairs = response.split(";", Qt::SkipEmptyParts);
    
    for (const QString &pair : pairs) {
        QStringList keyValue = pair.split("=", Qt::SkipEmptyParts);
        if (keyValue.size() == 2) {
            QString key = keyValue[0].trimmed();
            QString value = keyValue[1].trimmed();
            
            // Map discovery response keys to standardized property names
            if (key == "Protocol version") {
                result["protocol_version"] = value;
            } else if (key == "FB type") {
                result["controller_type"] = value;
            } else if (key == "Module version") {
                result["module_version"] = value;
            } else if (key == "MAC") {
                result["mac_address"] = value;
            } else if (key == "IP") {
                result["ip_address"] = value;
            } else if (key == "SN") {
                result["subnet_mask"] = value;
            } else if (key == "GW") {
                result["gateway"] = value;
            } else if (key == "DHCP") {
                result["dhcp_enabled"] = (value.toLower() == "on");
            } else if (key == "PSWD") {
                result["password_enabled"] = (value.toLower() == "on");
            } else if (key == "HN") {
                result["hostname"] = value;
            } else if (key == "DNS1") {
                result["dns_primary"] = value;
            } else if (key == "DNS2") {
                result["dns_secondary"] = value;
            } else {
                // Store any unknown keys as-is
                result[key.toLower().replace(" ", "_")] = value;
            }
        }
    }
    
    return result;
}

// SnapPacStrategy implementation
SnapPacStrategy::SnapPacStrategy(QObject *parent)
    : ControllerStrategy(parent)
{
}

QStringList SnapPacStrategy::supportedOperations() const
{
    return QStringList() << "READ_TABLE" << "WRITE_TABLE" 
                        << "READ_VARIABLE" << "WRITE_VARIABLE"
                        << "EXECUTE_COMMAND" << "GET_STATUS";
}

bool SnapPacStrategy::validateConfiguration(const QVariantMap &config) const
{
    // SNAP PAC specific validation
    QStringList required = QStringList() << "ip_address" << "port";
    
    for (const QString &key : required) {
        if (!config.contains(key)) {
            return false;
        }
    }
    
    // Default port for SNAP PAC is 2001
    bool ok;
    int port = config.value("port", 2001).toInt(&ok);
    return ok && port > 0 && port <= 65535;
}

QVariantMap SnapPacStrategy::parseDiscoveryResponse(const QString &response) const
{
    if (!isValidResponse(response)) {
        return QVariantMap();
    }
    
    QVariantMap result;
    // SNAP PAC has different discovery response format
    // Implementation would depend on actual SNAP PAC protocol
    result["controller_type"] = "SNAP_PAC";
    result["protocol_version"] = "1.0";
    
    return result;
}

QString SnapPacStrategy::formatWriteRequest(const QString &register_addr, const QVariant &value) const
{
    // SNAP PAC specific write format
    return QString("SNAP_WRITE:%1=%2").arg(register_addr).arg(value.toString());
}

QVariant SnapPacStrategy::parseReadResponse(const QString &response) const
{
    // SNAP PAC specific response parsing
    return QVariant();
}

bool SnapPacStrategy::isValidResponse(const QString &response) const
{
    return response.contains("SNAP") || response.contains("PAC");
}

// ControllerStrategyFactory implementation
ControllerStrategy* ControllerStrategyFactory::createStrategy(IndustrialController::ControllerType type, QObject *parent)
{
    switch (type) {
        case IndustrialController::EPIC4:
        case IndustrialController::EPIC5:
            return new Epic4Strategy(parent);
            
        case IndustrialController::SNAP_PAC:
            return new SnapPacStrategy(parent);
            
        default:
            qWarning() << "Unknown controller type:" << type;
            return nullptr;
    }
}

QStringList ControllerStrategyFactory::supportedTypes()
{
    return QStringList() << "EPIC4" << "EPIC5" << "SNAP_PAC";
}