#ifndef MOCKINDUSTRIALCONTROLLER_H
#define MOCKINDUSTRIALCONTROLLER_H

#include <QObject>
#include <QTimer>
#include <QSignalSpy>
#include "../src/industrialcontroller.h"

/**
 * @brief Mock implementation of IndustrialController for testing
 * 
 * Provides controllable behavior for testing controller management,
 * state transitions, and error conditions without real hardware.
 * 
 * Key features:
 * - Simulated connection states and transitions
 * - Configurable response times and error conditions  
 * - Test data injection for validation
 * - Signal verification support
 */
class MockIndustrialController : public QObject
{
    Q_OBJECT

public:
    explicit MockIndustrialController(QObject *parent = nullptr);
    virtual ~MockIndustrialController();

    // Mock Configuration
    void setSimulatedAddress(const QString &address);
    void setSimulatedPort(quint16 port);
    void setSimulatedControllerType(const QString &type);
    void setSimulatedVersion(const QString &version);
    void setSimulatedMacAddress(const QString &mac);
    
    // Mock Behavior Control
    void setConnectionDelay(int milliseconds);
    void setFailureMode(bool shouldFail);
    void setDataUpdateInterval(int milliseconds);
    void simulateConnectionLoss();
    void simulateReconnection();
    
    // Mock Data Injection
    void injectTestData(const QVariantMap &data);
    void injectHeartbeat();
    void injectFaultCondition(const QString &faultCode);
    
    // State Simulation
    void simulateConnecting();
    void simulateConnected();
    void simulateDisconnected();
    void simulateFault(const QString &error);
    
    // Test Verification Helpers
    int getConnectionAttempts() const;
    int getDataRequestCount() const;
    QStringList getReceivedCommands() const;
    IndustrialController::ConnectionStatus getCurrentState() const;
    
    // Reset for clean test state
    void resetMock();

signals:
    // Mirror real controller signals for testing
    void stateChanged(IndustrialController::ConnectionStatus newState);
    void dataReceived(const QVariantMap &data);
    void errorOccurred(const QString &error);
    void connected();
    void disconnected();
    void heartbeatReceived();

private slots:
    void onConnectionTimer();
    void onDataUpdateTimer();
    void onHeartbeatTimer();

private:
    // Mock Configuration
    QString m_address;
    quint16 m_port;
    QString m_controllerType;
    QString m_version;
    QString m_macAddress;
    
    // Mock Behavior
    bool m_failureMode;
    int m_connectionDelay;
    int m_dataUpdateInterval;
    
    // Mock State
    IndustrialController::ConnectionStatus m_currentState;
    QVariantMap m_currentData;
    QString m_lastError;
    
    // Test Tracking
    int m_connectionAttempts;
    int m_dataRequestCount;
    QStringList m_receivedCommands;
    
    // Simulation Timers
    QTimer *m_connectionTimer;
    QTimer *m_dataUpdateTimer;
    QTimer *m_heartbeatTimer;
    
    // Internal helpers
    void updateState(IndustrialController::ConnectionStatus newState);
    void generateTestData();
};

#endif // MOCKINDUSTRIALCONTROLLER_H