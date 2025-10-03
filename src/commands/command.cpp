#include "command.h"
#include <QDebug>

// Base Command implementation
Command::Command(QObject *parent)
    : QObject(parent)
{
}

// ControllerOperationCommand implementation
ControllerOperationCommand::ControllerOperationCommand(const QString &controllerIp, 
                                                     Operation operation,
                                                     QObject *parent)
    : Command(parent)
    , m_controllerIp(controllerIp)
    , m_operation(operation)
    , m_previousState(Stop) // Default previous state
{
}

bool ControllerOperationCommand::execute()
{
    if (m_executed) {
        qWarning() << "Command already executed for controller:" << m_controllerIp;
        return false;
    }
    
    bool success = false;
    
    // Simulate operation execution (in real implementation, this would communicate with the controller)
    switch (m_operation) {
        case Start:
            qDebug() << "Starting controller operations on" << m_controllerIp;
            // TODO: Implement actual controller start command via Modbus/protocol
            success = true;
            m_previousState = Stop; // Assume it was stopped before
            break;
            
        case Stop:
            qDebug() << "Stopping controller operations on" << m_controllerIp;
            // TODO: Implement actual controller stop command
            success = true;
            m_previousState = Start; // Assume it was running before
            break;
            
        case Reset:
            qDebug() << "Resetting controller" << m_controllerIp;
            // TODO: Implement actual controller reset command
            success = true;
            m_previousState = Stop; // Reset typically stops operations
            break;
            
        case Configure:
            qDebug() << "Configuring controller" << m_controllerIp;
            // TODO: Implement actual controller configuration
            success = true;
            // Configuration doesn't change operational state
            break;
    }
    
    if (success) {
        m_executed = true;
        emit executed(true);
        
        // Log the operation for audit trail
        qDebug() << QString("Command executed: %1 on %2").arg(description()).arg(m_controllerIp);
    } else {
        emit executed(false);
        qWarning() << QString("Command failed: %1 on %2").arg(description()).arg(m_controllerIp);
    }
    
    return success;
}

bool ControllerOperationCommand::undo()
{
    if (!m_executed) {
        qWarning() << "Cannot undo command that was not executed for controller:" << m_controllerIp;
        return false;
    }
    
    if (!isReversible()) {
        qWarning() << "Command is not reversible:" << description();
        return false;
    }
    
    bool success = false;
    
    // Execute the reverse operation
    switch (m_operation) {
        case Start:
            // Undo start by stopping
            qDebug() << "Undoing start operation by stopping controller" << m_controllerIp;
            success = true;
            break;
            
        case Stop:
            // Undo stop by starting
            qDebug() << "Undoing stop operation by starting controller" << m_controllerIp;
            success = true;
            break;
            
        case Reset:
            // Reset operations typically cannot be undone
            qWarning() << "Reset operation cannot be undone for controller" << m_controllerIp;
            success = false;
            break;
            
        case Configure:
            // Configuration changes could potentially be undone by restoring previous config
            qDebug() << "Undoing configuration changes for controller" << m_controllerIp;
            success = true;
            break;
    }
    
    if (success) {
        m_executed = false;
        emit undone(true);
        
        qDebug() << QString("Command undone: %1 on %2").arg(description()).arg(m_controllerIp);
    } else {
        emit undone(false);
        qWarning() << QString("Command undo failed: %1 on %2").arg(description()).arg(m_controllerIp);
    }
    
    return success;
}

QString ControllerOperationCommand::description() const
{
    QString operationName;
    switch (m_operation) {
        case Start:
            operationName = "Start Operations";
            break;
        case Stop:
            operationName = "Stop Operations";
            break;
        case Reset:
            operationName = "Reset Controller";
            break;
        case Configure:
            operationName = "Configure Controller";
            break;
    }
    
    return QString("%1 for %2").arg(operationName).arg(m_controllerIp);
}