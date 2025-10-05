#include <QtTest/QtTest>
#include <QSignalSpy>
#include <QHostAddress>
#include "../src/udpservice.h"
#include "../mocks/mockudpservice.h"

/**
 * @brief Unit tests for UDP discovery service functionality
 * 
 * Tests network discovery protocols, response handling, and error conditions.
 */
class TestUdpService : public QObject
{
    Q_OBJECT

private slots:
    void initTestCase();
    void cleanupTestCase(); 
    void init();
    void cleanup();

    // Core UDP Functionality
    void testListeningStartStop();
    void testBroadcastSending();
    void testResponseReceiving();
    void testMultipleResponses();

    // Discovery Protocol Tests
    void testControllerDiscovery();
    void testProtocolParsing();
    void testInvalidResponses();
    void testTimeoutHandling();

    // Network Error Tests
    void testNetworkFailure();
    void testPortConflicts();
    void testPermissionErrors();

    // Performance Tests
    void testHighFrequencyBroadcasts();
    void testLargeResponseHandling();
    void testConcurrentOperations();

private:
    MockUdpService *m_mockService;
    
    void waitForSignal(QObject *sender, const char *signal, int timeout = 5000);
};

void TestUdpService::initTestCase()
{
    qDebug() << "Starting UdpService unit tests...";
}

void TestUdpService::cleanupTestCase()
{
    qDebug() << "UdpService unit tests completed.";
}

void TestUdpService::init()
{
    m_mockService = new MockUdpService(this);
}

void TestUdpService::cleanup()
{
    if (m_mockService) {
        m_mockService->resetMock();
        delete m_mockService;
        m_mockService = nullptr;
    }
}

void TestUdpService::testListeningStartStop()
{
    QSignalSpy startSpy(m_mockService, &MockUdpService::listeningStarted);
    QSignalSpy stopSpy(m_mockService, &MockUdpService::listeningStopped);
    
    // Test start listening
    QVERIFY(!m_mockService->isListening());
    m_mockService->startListening();
    
    QVERIFY(m_mockService->isListening());
    QCOMPARE(startSpy.count(), 1);
    QCOMPARE(startSpy.at(0).at(0).toUInt(), 3250u);
    
    // Test stop listening
    m_mockService->stopListening();
    QVERIFY(!m_mockService->isListening());
    QCOMPARE(stopSpy.count(), 1);
}

void TestUdpService::testBroadcastSending()
{
    QSignalSpy broadcastSpy(m_mockService, &MockUdpService::broadcastSent);
    
    m_mockService->startListening();
    
    QByteArray testData = "Module Scan";
    m_mockService->sendBroadcast(testData);
    
    QCOMPARE(broadcastSpy.count(), 1);
    QCOMPARE(m_mockService->getLastBroadcast(), testData);
    QCOMPARE(m_mockService->getBroadcastCount(), 1);
}

void TestUdpService::testResponseReceiving()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    m_mockService->startListening();
    
    // Send broadcast and expect responses
    m_mockService->sendBroadcast("Module Scan");
    
    // Wait for simulated responses
    waitForSignal(m_mockService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    
    QVERIFY(responseSpy.count() > 0);
    QVERIFY(!m_mockService->getDiscoveredHosts().isEmpty());
}

void TestUdpService::testMultipleResponses()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    // Add multiple simulated controllers
    QByteArray response1 = "Protocol version = 1.00;FB type = EPIC4;IP = 192.168.1.100;";
    QByteArray response2 = "Protocol version = 1.00;FB type = SNAP_PAC;IP = 192.168.1.101;";
    
    m_mockService->addSimulatedResponse(response1, QHostAddress("192.168.1.100"));
    m_mockService->addSimulatedResponse(response2, QHostAddress("192.168.1.101"));
    
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    // Should receive multiple responses
    QTest::qWait(200); // Allow time for all responses
    QVERIFY(responseSpy.count() >= 2);
    QCOMPARE(m_mockService->getDiscoveredHosts().size(), 2);
}

void TestUdpService::testControllerDiscovery()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    waitForSignal(m_mockService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    
    // Verify response contains expected controller information
    QByteArray response = responseSpy.at(0).at(0).toByteArray();
    QString responseStr = QString::fromUtf8(response);
    
    QVERIFY(responseStr.contains("Protocol version"));
    QVERIFY(responseStr.contains("FB type"));
    QVERIFY(responseStr.contains("IP"));
}

void TestUdpService::testProtocolParsing()
{
    // Test parsing of EPIC4 controller response
    QByteArray epic4Response = 
        "Protocol version = 1.00;"
        "FB type = EPIC4;"
        "Module version = 1.99;"
        "MAC = C0-22-F1-41-03-3A;"
        "IP = 192.168.10.243;"
        "Name = EthernetBrain;";
    
    m_mockService->clearSimulatedResponses();
    m_mockService->addSimulatedResponse(epic4Response);
    
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    waitForSignal(m_mockService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    
    QByteArray received = responseSpy.at(0).at(0).toByteArray();
    QString receivedStr = QString::fromUtf8(received);
    
    QVERIFY(receivedStr.contains("EPIC4"));
    QVERIFY(receivedStr.contains("1.99"));
    QVERIFY(receivedStr.contains("C0-22-F1-41-03-3A"));
}

void TestUdpService::testInvalidResponses()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    QSignalSpy errorSpy(m_mockService, &MockUdpService::errorOccurred);
    
    // Add malformed response
    QByteArray malformedResponse = "Invalid response format";
    m_mockService->clearSimulatedResponses();
    m_mockService->addSimulatedResponse(malformedResponse);
    
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    // Should still receive the response (parsing validation is in controller logic)
    waitForSignal(m_mockService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    QCOMPARE(responseSpy.count(), 1);
    
    // UDP service doesn't validate content, just transports data
    QByteArray received = responseSpy.at(0).at(0).toByteArray();
    QCOMPARE(received, malformedResponse);
}

void TestUdpService::testTimeoutHandling()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    // Clear responses to simulate no controllers responding
    m_mockService->clearSimulatedResponses();
    
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    // Wait longer than response delay
    QTest::qWait(500);
    
    // Should have no responses
    QCOMPARE(responseSpy.count(), 0);
    QVERIFY(m_mockService->getDiscoveredHosts().isEmpty());
}

void TestUdpService::testNetworkFailure()
{
    QSignalSpy errorSpy(m_mockService, &MockUdpService::errorOccurred);
    
    m_mockService->setFailureMode(true);
    m_mockService->startListening();
    
    QCOMPARE(errorSpy.count(), 1);
    QVERIFY(!m_mockService->isListening());
    
    QString error = errorSpy.at(0).at(0).toString();
    QVERIFY(error.contains("failure"));
}

void TestUdpService::testPortConflicts()
{
    // Test with different port
    m_mockService->setListeningPort(8080);
    QCOMPARE(m_mockService->getListeningPort(), 8080);
    
    QSignalSpy startSpy(m_mockService, &MockUdpService::listeningStarted);
    m_mockService->startListening();
    
    QCOMPARE(startSpy.count(), 1);
    QCOMPARE(startSpy.at(0).at(0).toUInt(), 8080u);
}

void TestUdpService::testPermissionErrors()
{
    QSignalSpy errorSpy(m_mockService, &MockUdpService::errorOccurred);
    
    // Simulate permission error with privileged port
    m_mockService->setListeningPort(80);
    m_mockService->setFailureMode(true);
    m_mockService->startListening();
    
    QVERIFY(errorSpy.count() > 0);
}

void TestUdpService::testHighFrequencyBroadcasts()
{
    QSignalSpy broadcastSpy(m_mockService, &MockUdpService::broadcastSent);
    
    m_mockService->startListening();
    
    // Send multiple broadcasts rapidly
    for (int i = 0; i < 10; ++i) {
        m_mockService->sendBroadcast(QString("Scan %1").arg(i).toUtf8());
    }
    
    QCOMPARE(broadcastSpy.count(), 10);
    QCOMPARE(m_mockService->getBroadcastCount(), 10);
}

void TestUdpService::testLargeResponseHandling()
{
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    // Create large response (simulating detailed controller info)
    QByteArray largeResponse;
    for (int i = 0; i < 100; ++i) {
        largeResponse.append(QString("Field%1 = Value%1;").arg(i));
    }
    
    m_mockService->clearSimulatedResponses();
    m_mockService->addSimulatedResponse(largeResponse);
    
    m_mockService->startListening();
    m_mockService->sendBroadcast("Module Scan");
    
    waitForSignal(m_mockService, SIGNAL(responseReceived(QByteArray,QHostAddress)));
    
    QByteArray received = responseSpy.at(0).at(0).toByteArray();
    QCOMPARE(received.size(), largeResponse.size());
    QCOMPARE(received, largeResponse);
}

void TestUdpService::testConcurrentOperations()
{
    QSignalSpy broadcastSpy(m_mockService, &MockUdpService::broadcastSent);
    QSignalSpy responseSpy(m_mockService, &MockUdpService::responseReceived);
    
    m_mockService->startListening();
    
    // Simulate concurrent broadcasts and responses
    for (int i = 0; i < 5; ++i) {
        m_mockService->sendBroadcast(QString("Concurrent %1").arg(i).toUtf8());
        
        // Add small delay between broadcasts
        QTest::qWait(10);
    }
    
    QCOMPARE(broadcastSpy.count(), 5);
    
    // Should handle concurrent operations without error
    QVERIFY(m_mockService->isListening());
}

void TestUdpService::waitForSignal(QObject *sender, const char *signal, int timeout)
{
    QSignalSpy spy(sender, signal);
    QVERIFY(spy.wait(timeout));
}

QTEST_MAIN(TestUdpService)
#include "test_udpservice.moc"