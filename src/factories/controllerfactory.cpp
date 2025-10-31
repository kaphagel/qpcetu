#include "controllerfactory.h"
#include <QDebug>

IndustrialController* ControllerFactory::createFromDiscovery(
    const QString& discoveryResponse,
    const QHostAddress& senderAddress,
    QObject* parent)
{
    auto* controller = new IndustrialController(parent);
    
    if (!controller->parseDiscoveryResponse(discoveryResponse, senderAddress)) {
        qWarning() << "Failed to parse discovery response:" << discoveryResponse;
        delete controller;
        return nullptr;
    }
    
    // Assign strategy based on detected type
    IndustrialController::ControllerType type = parseControllerType(controller->controllerType());
    assignStrategy(controller, type);
    
    return controller;
}

IndustrialController* ControllerFactory::createFromConfig(
    const QJsonObject& config,
    QObject* parent)
{
    // Extract required fields
    QString typeString = config["type"].toString();
    QString ipAddress = config["ip"].toString();
    
    if (typeString.isEmpty() || ipAddress.isEmpty()) {
        qWarning() << "Invalid configuration: missing type or ip";
        return nullptr;
    }
    
    // Parse controller type
    IndustrialController::ControllerType type = parseControllerType(typeString);
    if (type == IndustrialController::UNKNOWN) {
        qWarning() << "Unknown controller type:" << typeString;
        return nullptr;
    }
    
    // Extract optional fields
    QString hostname = config["hostname"].toString();
    int port = config["port"].toInt(getDefaultPort(type));
    
    // Create controller
    auto* controller = createController(type, ipAddress, hostname, parent);
    
    return controller;
}

IndustrialController* ControllerFactory::createEpic4(
    const QString& ipAddress,
    const QString& hostname,
    QObject* parent)
{
    return createController(IndustrialController::EPIC4, ipAddress, hostname, parent);
}

IndustrialController* ControllerFactory::createSnapPac(
    const QString& ipAddress,
    const QString& hostname,
    QObject* parent)
{
    return createController(IndustrialController::SNAP_PAC, ipAddress, hostname, parent);
}

IndustrialController* ControllerFactory::createController(
    IndustrialController::ControllerType type,
    const QString& ipAddress,
    const QString& hostname,
    QObject* parent)
{
    auto* controller = new IndustrialController(parent);
    
    // Set basic properties
    // Note: IndustrialController doesn't have public setters in the current implementation.
    // In a real implementation, we'd either:
    // 1. Add setters to IndustrialController
    // 2. Pass properties through constructor
    // 3. Use a builder pattern
    // For now, we'll create the controller and assign the strategy.
    
    assignStrategy(controller, type);
    
    return controller;
}

IndustrialController::ControllerType ControllerFactory::parseControllerType(const QString& typeString)
{
    QString upper = typeString.toUpper().trimmed();
    
    if (upper == "EPIC4" || upper == "EPIC-4") {
        return IndustrialController::EPIC4;
    }
    else if (upper == "EPIC5" || upper == "EPIC-5") {
        return IndustrialController::EPIC5;
    }
    else if (upper == "SNAP_PAC" || upper == "SNAP-PAC" || upper == "SNAPPAC") {
        return IndustrialController::SNAP_PAC;
    }
    else if (upper == "CLICK_PLC" || upper == "CLICK-PLC" || upper == "CLICKPLC") {
        return IndustrialController::CLICK_PLC;
    }
    else if (upper == "MODICON") {
        return IndustrialController::MODICON;
    }
    else if (upper == "COMPACT_LOGIX" || upper == "COMPACTLOGIX" || upper == "COMPACT-LOGIX") {
        return IndustrialController::COMPACT_LOGIX;
    }
    
    return IndustrialController::UNKNOWN;
}

int ControllerFactory::getDefaultPort(IndustrialController::ControllerType type)
{
    // Most industrial controllers use Modbus TCP on port 502
    switch (type) {
        case IndustrialController::EPIC4:
        case IndustrialController::EPIC5:
        case IndustrialController::SNAP_PAC:
            return 502;  // Modbus TCP
        
        case IndustrialController::CLICK_PLC:
            return 502;  // Modbus TCP
        
        case IndustrialController::MODICON:
            return 502;  // Modbus TCP
        
        case IndustrialController::COMPACT_LOGIX:
            return 44818;  // EtherNet/IP
        
        case IndustrialController::UNKNOWN:
        default:
            return 502;  // Default to Modbus TCP
    }
}

void ControllerFactory::assignStrategy(IndustrialController* controller, IndustrialController::ControllerType type)
{
    if (!controller) {
        return;
    }
    
    ControllerStrategy* strategy = nullptr;
    
    switch (type) {
        case IndustrialController::EPIC4:
            strategy = new Epic4Strategy(controller);
            qDebug() << "Assigned Epic4Strategy to controller";
            break;
        
        case IndustrialController::SNAP_PAC:
            strategy = new SnapPacStrategy(controller);
            qDebug() << "Assigned SnapPacStrategy to controller";
            break;
        
        case IndustrialController::EPIC5:
            // EPIC5 can use same strategy as EPIC4 (same protocol)
            strategy = new Epic4Strategy(controller);
            qDebug() << "Assigned Epic4Strategy to EPIC5 controller";
            break;
        
        case IndustrialController::CLICK_PLC:
        case IndustrialController::MODICON:
        case IndustrialController::COMPACT_LOGIX:
            // These would need their own strategies implemented
            qWarning() << "Strategy not implemented for controller type:" << type;
            break;
        
        case IndustrialController::UNKNOWN:
        default:
            qWarning() << "Cannot assign strategy to unknown controller type";
            break;
    }
    
    // Note: In the current IndustrialController implementation,
    // there's no public method to set the strategy.
    // In a production implementation, we'd add:
    //   controller->setStrategy(strategy);
    // or pass the strategy through the constructor.
}
