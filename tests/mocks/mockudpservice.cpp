#include "mockudpservice.h"
#include <QDebug>

MockUdpService::MockUdpService(QObject *parent)
    : QObject(parent)
    , m_listeningPort(3250)
    , m_isListening(false)
    , m_failureMode(false)
    , m_responseDelay(50)
    , m_broadcastCount(0)
{
    m_responseTimer = new QTimer(this);
    m_responseTimer->setSingleShot(true);
    connect(m_responseTimer, &QTimer::timeout, this, &MockUdpService::onResponseTimer);
    
    // Add default EPIC4 controller response
    QByteArray defaultResponse = 
        "Protocol version = 1.00;"
        "FB type = EPIC4;"
        "Module version = 1.99;"
        "MAC = C0-22-F1-41-03-3A;"
        "IP = 192.168.10.243;"
        "Name = EthernetBrain;"
        "Board SN = 0x12345678;"
        "Opto SN = 0x87654321;"
        "Boot version = 1.2.3;";
    
    addSimulatedResponse(defaultResponse);
}

MockUdpService::~MockUdpService()
{
    // Timer automatically deleted by parent QObject
}

void MockUdpService::setListeningPort(quint16 port)
{
    m_listeningPort = port;
}

void MockUdpService::addSimulatedResponse(const QByteArray &response, const QHostAddress &sender)
{
    SimulatedResponse simResponse;
    simResponse.data = response;
    simResponse.sender = sender;
    m_simulatedResponses.append(simResponse);
}

void MockUdpService::clearSimulatedResponses()
{
    m_simulatedResponses.clear();
}

void MockUdpService::setResponseDelay(int milliseconds)
{
    m_responseDelay = milliseconds;
}

void MockUdpService::setFailureMode(bool shouldFail)
{
    m_failureMode = shouldFail;
}

void MockUdpService::simulateBroadcast(const QByteArray &data)
{
    m_lastBroadcast = data;
    m_broadcastCount++;
    emit broadcastSent(data);
    
    if (!m_failureMode && !m_simulatedResponses.isEmpty()) {
        // Schedule simulated responses
        m_responseTimer->setInterval(m_responseDelay);
        m_responseTimer->start();
    }
}

void MockUdpService::simulateResponse(const QByteArray &data, const QHostAddress &sender)
{
    if (!m_discoveredHosts.contains(sender)) {
        m_discoveredHosts.append(sender);
    }
    emit responseReceived(data, sender);
}

void MockUdpService::simulateNetworkError(const QString &error)
{
    emit errorOccurred(error);
}

void MockUdpService::simulateTimeout()
{
    // Simulate no responses received
    // This is typically handled by caller timeout logic
}

bool MockUdpService::isListening() const
{
    return m_isListening;
}

quint16 MockUdpService::getListeningPort() const
{
    return m_listeningPort;
}

QByteArray MockUdpService::getLastBroadcast() const
{
    return m_lastBroadcast;
}

int MockUdpService::getBroadcastCount() const
{
    return m_broadcastCount;
}

QList<QHostAddress> MockUdpService::getDiscoveredHosts() const
{
    return m_discoveredHosts;
}

void MockUdpService::resetMock()
{
    m_isListening = false;
    m_lastBroadcast.clear();
    m_broadcastCount = 0;
    m_discoveredHosts.clear();
    m_failureMode = false;
    m_responseTimer->stop();
}

void MockUdpService::startListening()
{
    if (m_failureMode) {
        emit errorOccurred("Mock UDP listening failure");
        return;
    }
    
    m_isListening = true;
    emit listeningStarted(m_listeningPort);
}

void MockUdpService::stopListening()
{
    m_isListening = false;
    m_responseTimer->stop();
    emit listeningStopped();
}

void MockUdpService::sendBroadcast(const QByteArray &data)
{
    if (!m_isListening) {
        emit errorOccurred("Cannot broadcast: not listening");
        return;
    }
    
    simulateBroadcast(data);
}

void MockUdpService::onResponseTimer()
{
    processSimulatedResponses();
}

void MockUdpService::processSimulatedResponses()
{
    // Send all configured simulated responses
    for (const auto &response : m_simulatedResponses) {
        simulateResponse(response.data, response.sender);
        
        // Small delay between multiple responses to simulate real network timing
        if (&response != &m_simulatedResponses.last()) {
            QTimer::singleShot(10, this, [this, response]() {
                // Continue processing remaining responses
            });
        }
    }
}

#include "mockudpservice.moc"