#include "mockindustrialcontroller.h"
#include <QDebug>
#include <QRandomGenerator>

MockIndustrialController::MockIndustrialController(QObject *parent)
    : QObject(parent)
    , m_address("192.168.1.100")
    , m_port(502)
    , m_controllerType("EPIC4")
    , m_version("1.00")
    , m_macAddress("C0-22-F1-41-03-3A")
    , m_failureMode(false)
    , m_connectionDelay(100)
    , m_dataUpdateInterval(1000)
    , m_currentState(IndustrialController::OFFLINE)
    , m_connectionAttempts(0)
    , m_dataRequestCount(0)
{
    // Initialize simulation timers
    m_connectionTimer = new QTimer(this);
    m_connectionTimer->setSingleShot(true);
    connect(m_connectionTimer, &QTimer::timeout, this, &MockIndustrialController::onConnectionTimer);
    
    m_dataUpdateTimer = new QTimer(this);
    connect(m_dataUpdateTimer, &QTimer::timeout, this, &MockIndustrialController::onDataUpdateTimer);
    
    m_heartbeatTimer = new QTimer(this);
    m_heartbeatTimer->setInterval(5000); // 5 second heartbeat
    connect(m_heartbeatTimer, &QTimer::timeout, this, &MockIndustrialController::onHeartbeatTimer);
    
    // Initialize with default test data
    generateTestData();
}

MockIndustrialController::~MockIndustrialController()
{
    // Timers are automatically deleted by parent QObject
}

void MockIndustrialController::setSimulatedAddress(const QString &address)
{
    m_address = address;
}

void MockIndustrialController::setSimulatedPort(quint16 port)
{
    m_port = port;
}

void MockIndustrialController::setSimulatedControllerType(const QString &type)
{
    m_controllerType = type;
}

void MockIndustrialController::setSimulatedVersion(const QString &version)
{
    m_version = version;
}

void MockIndustrialController::setSimulatedMacAddress(const QString &mac)
{
    m_macAddress = mac;
}

void MockIndustrialController::setConnectionDelay(int milliseconds)
{
    m_connectionDelay = milliseconds;
}

void MockIndustrialController::setFailureMode(bool shouldFail)
{
    m_failureMode = shouldFail;
}

void MockIndustrialController::setDataUpdateInterval(int milliseconds)
{
    m_dataUpdateInterval = milliseconds;
    if (m_dataUpdateTimer->isActive()) {
        m_dataUpdateTimer->setInterval(milliseconds);
    }
}

void MockIndustrialController::simulateConnecting()
{
    m_connectionAttempts++;
    updateState(IndustrialController::DISCOVERING);
    
    if (m_failureMode) {
        // Simulate connection failure after delay
        QTimer::singleShot(m_connectionDelay, this, [this]() {
            updateState(IndustrialController::COMM_ERROR);
            emit errorOccurred("Mock connection failure");
        });
    } else {
        // Simulate successful connection after delay
        m_connectionTimer->setInterval(m_connectionDelay);
        m_connectionTimer->start();
    }
}

void MockIndustrialController::simulateConnected()
{
    updateState(IndustrialController::ONLINE);
    m_dataUpdateTimer->setInterval(m_dataUpdateInterval);
    m_dataUpdateTimer->start();
    m_heartbeatTimer->start();
    emit connected();
}

void MockIndustrialController::simulateDisconnected()
{
    updateState(IndustrialController::OFFLINE);
    m_dataUpdateTimer->stop();
    m_heartbeatTimer->stop();
    emit disconnected();
}

void MockIndustrialController::simulateFault(const QString &error)
{
    updateState(IndustrialController::COMM_ERROR);
    m_lastError = error;
    m_dataUpdateTimer->stop();
    m_heartbeatTimer->stop();
    emit errorOccurred(error);
}

void MockIndustrialController::simulateConnectionLoss()
{
    if (m_currentState == IndustrialController::ONLINE) {
        simulateDisconnected();
    }
}

void MockIndustrialController::simulateReconnection()
{
    if (m_currentState == IndustrialController::OFFLINE || 
        m_currentState == IndustrialController::COMM_ERROR) {
        simulateConnecting();
    }
}

void MockIndustrialController::injectTestData(const QVariantMap &data)
{
    m_currentData = data;
    if (m_currentState == IndustrialController::ONLINE) {
        emit dataReceived(data);
    }
}

void MockIndustrialController::injectHeartbeat()
{
    if (m_currentState == IndustrialController::ONLINE) {
        emit heartbeatReceived();
    }
}

void MockIndustrialController::injectFaultCondition(const QString &faultCode)
{
    QVariantMap faultData = m_currentData;
    faultData["fault_code"] = faultCode;
    faultData["fault_active"] = true;
    faultData["timestamp"] = QDateTime::currentDateTime();
    
    emit dataReceived(faultData);
    simulateFault(QString("Fault condition: %1").arg(faultCode));
}

int MockIndustrialController::getConnectionAttempts() const
{
    return m_connectionAttempts;
}

int MockIndustrialController::getDataRequestCount() const
{
    return m_dataRequestCount;
}

QStringList MockIndustrialController::getReceivedCommands() const
{
    return m_receivedCommands;
}

IndustrialController::ConnectionStatus MockIndustrialController::getCurrentState() const
{
    return m_currentState;
}

void MockIndustrialController::resetMock()
{
    m_connectionAttempts = 0;
    m_dataRequestCount = 0;
    m_receivedCommands.clear();
    m_lastError.clear();
    m_failureMode = false;
    
    m_connectionTimer->stop();
    m_dataUpdateTimer->stop();
    m_heartbeatTimer->stop();
    
    updateState(IndustrialController::OFFLINE);
    generateTestData();
}

void MockIndustrialController::onConnectionTimer()
{
    if (!m_failureMode) {
        simulateConnected();
    }
}

void MockIndustrialController::onDataUpdateTimer()
{
    m_dataRequestCount++;
    generateTestData();
    emit dataReceived(m_currentData);
}

void MockIndustrialController::onHeartbeatTimer()
{
    emit heartbeatReceived();
}

void MockIndustrialController::updateState(IndustrialController::ConnectionStatus newState)
{
    if (m_currentState != newState) {
        m_currentState = newState;
        emit stateChanged(newState);
    }
}

void MockIndustrialController::generateTestData()
{
    // Generate realistic industrial test data
    QVariantMap data;
    
    // Basic controller info
    data["controller_type"] = m_controllerType;
    data["version"] = m_version;
    data["address"] = m_address;
    data["port"] = m_port;
    data["mac_address"] = m_macAddress;
    
    // Simulated process data
    auto random = QRandomGenerator::global();
    data["temperature"] = 20.0 + (random->bounded(100) / 10.0); // 20-30°C
    data["pressure"] = 1000.0 + random->bounded(200);           // 1000-1200 kPa
    data["flow_rate"] = 50.0 + (random->bounded(100) / 2.0);   // 50-100 L/min
    data["motor_speed"] = 1500 + random->bounded(500);         // 1500-2000 RPM
    
    // Digital I/O status
    data["pump_running"] = random->bounded(2) == 1;
    data["alarm_active"] = false;
    data["maintenance_required"] = false;
    
    // Timestamps
    data["timestamp"] = QDateTime::currentDateTime();
    data["uptime"] = random->bounded(86400); // Up to 24 hours in seconds
    
    m_currentData = data;
}

#include "mockindustrialcontroller.moc"