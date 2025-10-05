#ifndef MOCKUDPSERVICE_H
#define MOCKUDPSERVICE_H

#include <QObject>
#include <QTimer>
#include <QHostAddress>
#include <QNetworkDatagram>
#include "../src/udpservice.h"

/**
 * @brief Mock UDP service for testing network discovery functionality
 * 
 * Simulates UDP broadcast/response behavior without actual network traffic.
 * Allows testing of discovery protocols, response parsing, and error conditions.
 */
class MockUdpService : public QObject
{
    Q_OBJECT

public:
    explicit MockUdpService(QObject *parent = nullptr);
    virtual ~MockUdpService();

    // Mock Configuration
    void setListeningPort(quint16 port);
    void addSimulatedResponse(const QByteArray &response, const QHostAddress &sender = QHostAddress("192.168.1.100"));
    void clearSimulatedResponses();
    void setResponseDelay(int milliseconds);
    void setFailureMode(bool shouldFail);
    
    // Mock Network Operations
    void simulateBroadcast(const QByteArray &data);
    void simulateResponse(const QByteArray &data, const QHostAddress &sender);
    void simulateNetworkError(const QString &error);
    void simulateTimeout();
    
    // Test State Management
    bool isListening() const;
    quint16 getListeningPort() const;
    QByteArray getLastBroadcast() const;
    int getBroadcastCount() const;
    QList<QHostAddress> getDiscoveredHosts() const;
    
    // Reset for clean test state
    void resetMock();

public slots:
    // Simulate UdpService interface
    void startListening();
    void stopListening();
    void sendBroadcast(const QByteArray &data);

signals:
    // Mirror real UdpService signals
    void responseReceived(const QByteArray &data, const QHostAddress &sender);
    void broadcastSent(const QByteArray &data);
    void errorOccurred(const QString &error);
    void listeningStarted(quint16 port);
    void listeningStopped();

private slots:
    void onResponseTimer();

private:
    // Mock Configuration
    quint16 m_listeningPort;
    bool m_isListening;
    bool m_failureMode;
    int m_responseDelay;
    
    // Mock State
    QByteArray m_lastBroadcast;
    int m_broadcastCount;
    QList<QHostAddress> m_discoveredHosts;
    
    // Simulated Responses
    struct SimulatedResponse {
        QByteArray data;
        QHostAddress sender;
    };
    QList<SimulatedResponse> m_simulatedResponses;
    
    // Simulation Timer
    QTimer *m_responseTimer;
    
    // Internal helpers
    void processSimulatedResponses();
};

#endif // MOCKUDPSERVICE_H