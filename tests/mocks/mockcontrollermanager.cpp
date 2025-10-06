#include "mockcontrollermanager.h"
#include <QDebug>

MockControllerManager::MockControllerManager(QObject *parent)
    : QObject(parent)
    , m_discoveryActive(false)
    , m_networkPartitioned(false)
{
}

MockControllerManager::~MockControllerManager()
{
    clearMockControllers();
}

void MockControllerManager::addMockController(MockIndustrialController *controller)
{
    if (!controller || m_mockControllers.contains(controller)) {
        return;
    }
    
    m_mockControllers.append(controller);
    connectControllerSignals(controller);
}

void MockControllerManager::removeMockController(MockIndustrialController *controller)
{
    if (!controller) {
        return;
    }
    
    disconnectControllerSignals(controller);
    m_mockControllers.removeAll(controller);
}

void MockControllerManager::clearMockControllers()
{
    for (auto *controller : m_mockControllers) {
        disconnectControllerSignals(controller);
    }
    m_mockControllers.clear();
}

void MockControllerManager::simulateDiscovery()
{
    if (m_discoveryActive) {
        return;
    }
    
    m_discoveryActive = true;
    emit discoveryStarted();
    
    // Simulate discovery responses after short delay
    QTimer::singleShot(100, this, [this]() {
        for (auto *controller : m_mockControllers) {
            if (!m_networkPartitioned) {
                QVariantMap info;
                info["type"] = "EPIC4";
                info["version"] = "1.00";
                info["mac"] = "C0-22-F1-41-03-3A";
                
                emit controllerDiscovered("192.168.1.100", info);
            }
        }
        
        m_discoveryActive = false;
        emit discoveryFinished();
    });
}

void MockControllerManager::simulateControllerFailure(const QString &address)
{
    for (auto *controller : m_mockControllers) {
        // In a real implementation, we'd match by actual address
        // For mock, simulate failure on first controller
        controller->simulateFault("Simulated controller failure");
        break;
    }
}

void MockControllerManager::simulateControllerRecovery(const QString &address)
{
    for (auto *controller : m_mockControllers) {
        if (controller->getCurrentState() == IndustrialController::COMM_ERROR) {
            controller->resetMock();
            controller->simulateConnecting();
            break;
        }
    }
}

void MockControllerManager::simulateNetworkPartition()
{
    m_networkPartitioned = true;
    for (auto *controller : m_mockControllers) {
        controller->simulateConnectionLoss();
    }
}

void MockControllerManager::simulateNetworkRestore()
{
    m_networkPartitioned = false;
    for (auto *controller : m_mockControllers) {
        controller->simulateReconnection();
    }
}

int MockControllerManager::getControllerCount() const
{
    return m_mockControllers.size();
}

QStringList MockControllerManager::getControllerAddresses() const
{
    QStringList addresses;
    for (int i = 0; i < m_mockControllers.size(); ++i) {
        addresses.append(QString("192.168.1.%1").arg(100 + i));
    }
    return addresses;
}

MockIndustrialController* MockControllerManager::getMockController(const QString &address) const
{
    // For mock purposes, return controller by index derived from address
    bool ok;
    int index = address.split('.').last().toInt(&ok) - 100;
    if (ok && index >= 0 && index < m_mockControllers.size()) {
        return m_mockControllers.at(index);
    }
    return nullptr;
}

bool MockControllerManager::isDiscoveryActive() const
{
    return m_discoveryActive;
}

void MockControllerManager::resetMock()
{
    m_discoveryActive = false;
    m_networkPartitioned = false;
    for (auto *controller : m_mockControllers) {
        controller->resetMock();
    }
}

void MockControllerManager::onControllerStateChanged(IndustrialController::ConnectionStatus state)
{
    auto *controller = qobject_cast<MockIndustrialController*>(sender());
    if (!controller) {
        return;
    }
    
    // Find controller address (mock implementation)
    int index = m_mockControllers.indexOf(controller);
    QString address = QString("192.168.1.%1").arg(100 + index);
    
    switch (state) {
    case IndustrialController::ONLINE:
        emit controllerConnected(address);
        break;
    case IndustrialController::OFFLINE:
        emit controllerDisconnected(address);
        break;
    case IndustrialController::COMM_ERROR:
        // Error signal will be handled separately
        break;
    default:
        break;
    }
}

void MockControllerManager::onControllerError(const QString &error)
{
    auto *controller = qobject_cast<MockIndustrialController*>(sender());
    if (!controller) {
        return;
    }
    
    // Find controller address (mock implementation)
    int index = m_mockControllers.indexOf(controller);
    QString address = QString("192.168.1.%1").arg(100 + index);
    
    emit controllerError(address, error);
}

void MockControllerManager::connectControllerSignals(MockIndustrialController *controller)
{
    connect(controller, &MockIndustrialController::stateChanged,
            this, &MockControllerManager::onControllerStateChanged);
    connect(controller, &MockIndustrialController::errorOccurred,
            this, &MockControllerManager::onControllerError);
}

void MockControllerManager::disconnectControllerSignals(MockIndustrialController *controller)
{
    disconnect(controller, nullptr, this, nullptr);
}

#include "mockcontrollermanager.moc"