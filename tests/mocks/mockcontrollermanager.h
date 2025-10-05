#ifndef MOCKCONTROLLERMANAGER_H
#define MOCKCONTROLLERMANAGER_H

#include <QObject>
#include <QTimer>
#include "../src/controllermanager.h"
#include "mockindustrialcontroller.h"

/**
 * @brief Mock ControllerManager for testing high-level system behavior
 * 
 * Provides controllable multi-controller scenarios for testing
 * discovery, management, and coordination logic.
 */
class MockControllerManager : public QObject
{
    Q_OBJECT

public:
    explicit MockControllerManager(QObject *parent = nullptr);
    virtual ~MockControllerManager();

    // Mock Configuration
    void addMockController(MockIndustrialController *controller);
    void removeMockController(MockIndustrialController *controller);
    void clearMockControllers();
    
    // Simulation Control
    void simulateDiscovery();
    void simulateControllerFailure(const QString &address);
    void simulateControllerRecovery(const QString &address);
    void simulateNetworkPartition();
    void simulateNetworkRestore();
    
    // Test State Access
    int getControllerCount() const;
    QStringList getControllerAddresses() const;
    MockIndustrialController* getMockController(const QString &address) const;
    bool isDiscoveryActive() const;
    
    // Reset for clean test state
    void resetMock();

signals:
    // Mirror ControllerManager signals
    void controllerDiscovered(const QString &address, const QVariantMap &info);
    void controllerConnected(const QString &address);
    void controllerDisconnected(const QString &address);
    void controllerError(const QString &address, const QString &error);
    void discoveryStarted();
    void discoveryFinished();

private slots:
    void onControllerStateChanged(IndustrialController::State state);
    void onControllerError(const QString &error);

private:
    QList<MockIndustrialController*> m_mockControllers;
    bool m_discoveryActive;
    bool m_networkPartitioned;
    
    void connectControllerSignals(MockIndustrialController *controller);
    void disconnectControllerSignals(MockIndustrialController *controller);
};

#endif // MOCKCONTROLLERMANAGER_H