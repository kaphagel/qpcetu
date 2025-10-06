#include <QtTest/QtTest>
#include <QSignalSpy>
#include "../src/controllermanager.h"
#include "../src/udpservice.h"
#include "../mocks/mockcontrollermanager.h"
#include "../mocks/mockudpservice.h"
#include "../mocks/mockindustrialcontroller.h"

/**
 * @brief Integration tests for UDP discovery and controller management
 * 
 * Tests the complete discovery workflow from UDP broadcast through
 * controller registration and management.
 */
class TestUdpIntegration : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase();
    void init();
    void cleanup();

    // Discovery Integration Tests
    void testCompleteDiscoveryWorkflow();
    void testMultipleControllerDiscovery();
    void testDiscoveryWithFailures();
    void testRepeatedDiscovery();

    // Controller Registration Tests
    void testControllerRegistration();
    void testDuplicateControllerHandling();
    void testControllerDeregistration();

    // Network Integration Tests
    void testNetworkPartitionRecovery();
    void testDiscoveryUnderLoad();
    void testConcurrentDiscoveryRequests();

    // Error Handling Integration
    void testDiscoveryErrorRecovery();
    void testPartialDiscoveryFailure();
    void testControllerConnectionFailures();

private:
    MockControllerManager *m_mockManager;
    MockUdpService *m_mockUdpService;
    QList<MockIndustrialController*> m_mockControllers;
    
    void setupMultipleControllers(int count);
    void waitForSignal(QObject *sender, const char *signal, int timeout = 5000);
};

void TestUdpIntegration::initTestCase()
{
    qDebug() << "Starting UDP Integration tests...";
}

void TestUdpIntegration::cleanupTestCase()
{
    qDebug() << "UDP Integration tests completed.";
}

void TestUdpIntegration::init()
{
    m_mockManager = new MockControllerManager(this);
    m_mockUdpService = new MockUdpService(this);
    
    // Connect manager and UDP service signals for integration testing
    connect(m_mockUdpService, &MockUdpService::responseReceived,
            this, [this](const QByteArray &data, const QHostAddress &sender) {
        // Simulate controller manager processing UDP responses
        QVariantMap info;
        QString dataStr = QString::fromUtf8(data);
        
        if (dataStr.contains("FB type = EPIC4")) {
            info["type"] = "EPIC4";
        } else if (dataStr.contains("FB type = SNAP_PAC")) {
            info["type"] = "SNAP_PAC";
        }
        
        if (dataStr.contains("Module version =")) {
            int start = dataStr.indexOf("Module version = ") + 17;
            int end = dataStr.indexOf(";", start);
            if (end > start) {
                info["version"] = dataStr.mid(start, end - start);
            }
        }
        
        emit m_mockManager->controllerDiscovered(sender.toString(), info);
    });
}

void TestUdpIntegration::cleanup()
{
    // Clean up mock controllers
    for (auto *controller : m_mockControllers) {
        delete controller;
    }
    m_mockControllers.clear();
    
    if (m_mockManager) {
        m_mockManager->resetMock();
        delete m_mockManager;
        m_mockManager = nullptr;
    }
    
    if (m_mockUdpService) {
        m_mockUdpService->resetMock();
        delete m_mockUdpService;
        m_mockUdpService = nullptr;
    }
}

void TestUdpIntegration::testCompleteDiscoveryWorkflow()
{
    QSignalSpy discoveryStartedSpy(m_mockManager, &MockControllerManager::discoveryStarted);
    QSignalSpy discoveryFinishedSpy(m_mockManager, &MockControllerManager::discoveryFinished);
    QSignalSpy controllerDiscoveredSpy(m_mockManager, &MockControllerManager::controllerDiscovered);
    QSignalSpy broadcastSpy(m_mockUdpService, &MockUdpService::broadcastSent);
    QSignalSpy responseSpy(m_mockUdpService, &MockUdpService::responseReceived);
    
    // Setup: Start UDP service
    m_mockUdpService->startListening();
    QVERIFY(m_mockUdpService->isListening());
    
    // Step 1: Start discovery
    m_mockManager->simulateDiscovery();
    QCOMPARE(discoveryStartedSpy.count(), 1);
    
    // Step 2: Simulate UDP broadcast
    m_mockUdpService->sendBroadcast("Module Scan");
    QCOMPARE(broadcastSpy.count(), 1);
    
    // Step 3: Wait for responses and controller discovery
    waitForSignal(m_mockUdpService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    waitForSignal(m_mockManager, SIGNAL(discoveryFinished()));
    
    // Verify complete workflow
    QCOMPARE(responseSpy.count(), 1);
    QCOMPARE(controllerDiscoveredSpy.count(), 1);
    QCOMPARE(discoveryFinishedSpy.count(), 1);
    
    // Verify discovered controller information
    QVariantList discoveredArgs = controllerDiscoveredSpy.at(0);
    QString address = discoveredArgs.at(0).toString();
    QVariantMap info = discoveredArgs.at(1).toMap();
    
    QVERIFY(!address.isEmpty());
    QVERIFY(info.contains("type"));
}

void TestUdpIntegration::testMultipleControllerDiscovery()
{
    setupMultipleControllers(3);
    
    QSignalSpy controllerDiscoveredSpy(m_mockManager, &MockControllerManager::controllerDiscovered);
    QSignalSpy responseSpy(m_mockUdpService, &MockUdpService::responseReceived);
    
    // Add multiple controller responses
    m_mockUdpService->addSimulatedResponse(
        "Protocol version = 1.00;FB type = EPIC4;IP = 192.168.1.100;",
        QHostAddress("192.168.1.100"));
    m_mockUdpService->addSimulatedResponse(
        "Protocol version = 1.00;FB type = EPIC4;IP = 192.168.1.101;",
        QHostAddress("192.168.1.101"));
    m_mockUdpService->addSimulatedResponse(
        "Protocol version = 1.00;FB type = SNAP_PAC;IP = 192.168.1.102;",
        QHostAddress("192.168.1.102"));
    
    // Start discovery
    m_mockUdpService->startListening();
    m_mockManager->simulateDiscovery();
    m_mockUdpService->sendBroadcast("Module Scan");
    
    // Wait for all responses
    QTest::qWait(500);
    
    // Should discover multiple controllers
    QVERIFY(responseSpy.count() >= 3);
    QVERIFY(controllerDiscoveredSpy.count() >= 3);
    QCOMPARE(m_mockUdpService->getDiscoveredHosts().size(), 3);
}

void TestUdpIntegration::testDiscoveryWithFailures()
{
    QSignalSpy errorSpy(m_mockUdpService, &MockUdpService::errorOccurred);
    QSignalSpy discoveryFinishedSpy(m_mockManager, &MockControllerManager::discoveryFinished);
    
    // Simulate UDP service failure
    m_mockUdpService->setFailureMode(true);
    m_mockUdpService->startListening();
    
    QCOMPARE(errorSpy.count(), 1);
    QVERIFY(!m_mockUdpService->isListening());
    
    // Discovery should handle UDP failure gracefully
    m_mockManager->simulateDiscovery();
    waitForSignal(m_mockManager, SIGNAL(discoveryFinished()));
    
    QCOMPARE(discoveryFinishedSpy.count(), 1);
}

void TestUdpIntegration::testRepeatedDiscovery()
{
    QSignalSpy discoveryStartedSpy(m_mockManager, &MockControllerManager::discoveryStarted);
    QSignalSpy discoveryFinishedSpy(m_mockManager, &MockControllerManager::discoveryFinished);
    QSignalSpy broadcastSpy(m_mockUdpService, &MockUdpService::broadcastSent);
    
    m_mockUdpService->startListening();
    
    // Perform multiple discovery cycles
    for (int i = 0; i < 3; ++i) {
        m_mockManager->simulateDiscovery();
        waitForSignal(m_mockManager, SIGNAL(discoveryFinished()));
        
        m_mockUdpService->sendBroadcast("Module Scan");
        QTest::qWait(100); // Small delay between cycles
    }
    
    QCOMPARE(discoveryStartedSpy.count(), 3);
    QCOMPARE(discoveryFinishedSpy.count(), 3);
    QCOMPARE(broadcastSpy.count(), 3);
}

void TestUdpIntegration::testControllerRegistration()
{
    QSignalSpy controllerDiscoveredSpy(m_mockManager, &MockControllerManager::controllerDiscovered);
    
    // Setup controller
    auto *controller = new MockIndustrialController(this);
    controller->setSimulatedAddress("192.168.1.100");
    controller->setSimulatedControllerType("EPIC4");
    m_mockControllers.append(controller);
    m_mockManager->addMockController(controller);
    
    // Start discovery and trigger controller response
    m_mockUdpService->startListening();
    m_mockManager->simulateDiscovery();
    m_mockUdpService->sendBroadcast("Module Scan");
    
    waitForSignal(m_mockUdpService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    
    // Verify controller is registered
    QCOMPARE(m_mockManager->getControllerCount(), 1);
    QVERIFY(m_mockManager->getControllerAddresses().contains("192.168.1.100"));
}

void TestUdpIntegration::testDuplicateControllerHandling()
{
    setupMultipleControllers(1);
    
    QSignalSpy controllerDiscoveredSpy(m_mockManager, &MockControllerManager::controllerDiscovered);
    
    m_mockUdpService->startListening();
    
    // Discover same controller multiple times
    for (int i = 0; i < 3; ++i) {
        m_mockManager->simulateDiscovery();
        m_mockUdpService->sendBroadcast("Module Scan");
        waitForSignal(m_mockUdpService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
        QTest::qWait(50);
    }
    
    // Should handle duplicates appropriately
    QVERIFY(controllerDiscoveredSpy.count() >= 3);
    QCOMPARE(m_mockManager->getControllerCount(), 1); // Only one unique controller
}

void TestUdpIntegration::testControllerDeregistration()
{
    setupMultipleControllers(2);
    
    QCOMPARE(m_mockManager->getControllerCount(), 2);
    
    // Remove one controller
    auto *controller = m_mockControllers.takeFirst();
    m_mockManager->removeMockController(controller);
    delete controller;
    
    QCOMPARE(m_mockManager->getControllerCount(), 1);
}

void TestUdpIntegration::testNetworkPartitionRecovery()
{
    setupMultipleControllers(2);
    
    QSignalSpy disconnectedSpy(m_mockManager, &MockControllerManager::controllerDisconnected);
    QSignalSpy connectedSpy(m_mockManager, &MockControllerManager::controllerConnected);
    
    // Simulate all controllers connected
    for (auto *controller : m_mockControllers) {
        controller->simulateConnected();
    }
    
    // Simulate network partition
    m_mockManager->simulateNetworkPartition();
    
    // All controllers should disconnect
    QTest::qWait(100);
    QVERIFY(disconnectedSpy.count() >= 2);
    
    // Simulate network recovery
    m_mockManager->simulateNetworkRestore();
    
    // Controllers should reconnect
    QTest::qWait(200);
    QVERIFY(connectedSpy.count() >= 2);
}

void TestUdpIntegration::testDiscoveryUnderLoad()
{
    setupMultipleControllers(10);
    
    QSignalSpy responseSpy(m_mockUdpService, &MockUdpService::responseReceived);
    QSignalSpy broadcastSpy(m_mockUdpService, &MockUdpService::broadcastSent);
    
    // Add many simulated responses
    for (int i = 0; i < 10; ++i) {
        QString response = QString("Protocol version = 1.00;FB type = EPIC4;IP = 192.168.1.%1;").arg(100 + i);
        m_mockUdpService->addSimulatedResponse(response.toUtf8(), QHostAddress(QString("192.168.1.%1").arg(100 + i)));
    }
    
    m_mockUdpService->startListening();
    
    // Send multiple rapid broadcasts
    for (int i = 0; i < 5; ++i) {
        m_mockUdpService->sendBroadcast("Module Scan");
        QTest::qWait(10);
    }
    
    // Should handle high load
    QCOMPARE(broadcastSpy.count(), 5);
    QTest::qWait(1000); // Allow all responses to arrive
    QVERIFY(responseSpy.count() >= 5);
}

void TestUdpIntegration::testConcurrentDiscoveryRequests()
{
    QSignalSpy discoveryStartedSpy(m_mockManager, &MockControllerManager::discoveryStarted);
    QSignalSpy discoveryFinishedSpy(m_mockManager, &MockControllerManager::discoveryFinished);
    
    m_mockUdpService->startListening();
    
    // Start multiple discovery operations concurrently
    m_mockManager->simulateDiscovery();
    m_mockManager->simulateDiscovery(); // Second call while first is active
    m_mockManager->simulateDiscovery(); // Third call
    
    // Wait for all to complete
    QTest::qWait(500);
    
    // Should handle concurrent requests appropriately
    QVERIFY(discoveryStartedSpy.count() >= 1);
    QVERIFY(discoveryFinishedSpy.count() >= 1);
}

void TestUdpIntegration::testDiscoveryErrorRecovery()
{
    QSignalSpy errorSpy(m_mockUdpService, &MockUdpService::errorOccurred);
    QSignalSpy discoveryFinishedSpy(m_mockManager, &MockControllerManager::discoveryFinished);
    
    // Start with failure mode
    m_mockUdpService->setFailureMode(true);
    m_mockUdpService->startListening();
    QCOMPARE(errorSpy.count(), 1);
    
    // Try discovery during failure
    m_mockManager->simulateDiscovery();
    waitForSignal(m_mockManager, SIGNAL(discoveryFinished()));
    
    // Recovery: disable failure mode and retry
    m_mockUdpService->setFailureMode(false);
    m_mockUdpService->resetMock();
    m_mockUdpService->startListening();
    QVERIFY(m_mockUdpService->isListening());
    
    // Discovery should now work
    m_mockManager->simulateDiscovery();
    m_mockUdpService->sendBroadcast("Module Scan");
    waitForSignal(m_mockManager, SIGNAL(discoveryFinished()));
    
    QVERIFY(discoveryFinishedSpy.count() >= 2);
}

void TestUdpIntegration::testPartialDiscoveryFailure()
{
    setupMultipleControllers(3);
    
    QSignalSpy responseSpy(m_mockUdpService, &MockUdpService::responseReceived);
    QSignalSpy controllerDiscoveredSpy(m_mockManager, &MockControllerManager::controllerDiscovered);
    
    // Add mix of valid and invalid responses
    m_mockUdpService->addSimulatedResponse(
        "Protocol version = 1.00;FB type = EPIC4;IP = 192.168.1.100;");
    m_mockUdpService->addSimulatedResponse(
        "Invalid response data");
    m_mockUdpService->addSimulatedResponse(
        "Protocol version = 1.00;FB type = SNAP_PAC;IP = 192.168.1.102;");
    
    m_mockUdpService->startListening();
    m_mockManager->simulateDiscovery();
    m_mockUdpService->sendBroadcast("Module Scan");
    
    QTest::qWait(300);
    
    // Should receive all responses, but only valid ones trigger discovery
    QCOMPARE(responseSpy.count(), 3);
    QCOMPARE(controllerDiscoveredSpy.count(), 2); // Only 2 valid responses
}

void TestUdpIntegration::testControllerConnectionFailures()
{
    setupMultipleControllers(2);
    
    QSignalSpy errorSpy(m_mockManager, &MockControllerManager::controllerError);
    
    // Set one controller to fail
    m_mockControllers[0]->setFailureMode(true);
    
    // Attempt connections
    for (auto *controller : m_mockControllers) {
        controller->simulateConnecting();
    }
    
    QTest::qWait(200);
    
    // Should receive error for failing controller
    QVERIFY(errorSpy.count() >= 1);
    
    // Other controller should work
    QCOMPARE(m_mockControllers[1]->getCurrentState(), IndustrialController::ONLINE);
}

void TestUdpIntegration::setupMultipleControllers(int count)
{
    for (int i = 0; i < count; ++i) {
        auto *controller = new MockIndustrialController(this);
        controller->setSimulatedAddress(QString("192.168.1.%1").arg(100 + i));
        controller->setSimulatedControllerType("EPIC4");
        m_mockControllers.append(controller);
        m_mockManager->addMockController(controller);
    }
}

void TestUdpIntegration::waitForSignal(QObject *sender, const char *signal, int timeout)
{
    QSignalSpy spy(sender, signal);
    QVERIFY(spy.wait(timeout));
}

QTEST_MAIN(TestUdpIntegration)
#include "test_udp_integration.moc"