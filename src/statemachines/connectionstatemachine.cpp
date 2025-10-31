#include "connectionstatemachine.h"
#include <QDebug>
#include <QFinalState>

ConnectionStateMachine::ConnectionStateMachine(QObject* parent)
    : QObject(parent)
    , m_stateMachine(new QStateMachine(this))
    , m_disconnectedState(nullptr)
    , m_connectingState(nullptr)
    , m_connectedState(nullptr)
    , m_runningState(nullptr)
    , m_faultState(nullptr)
    , m_reconnectingState(nullptr)
    , m_connectTimer(new QTimer(this))
    , m_activityTimer(new QTimer(this))
    , m_reconnectDelayTimer(new QTimer(this))
    , m_currentState(State::Disconnected)
    , m_config()
    , m_targetAddress()
    , m_targetPort(0)
    , m_reconnectAttemptCount(0)
    , m_consecutiveErrorCount(0)
    , m_lastError()
{
    setupStateMachine();
    
    // Configure timers
    m_connectTimer->setSingleShot(true);
    m_activityTimer->setSingleShot(false);
    m_reconnectDelayTimer->setSingleShot(true);
    
    connect(m_connectTimer, &QTimer::timeout, this, &ConnectionStateMachine::onConnectTimeout);
    connect(m_activityTimer, &QTimer::timeout, this, &ConnectionStateMachine::onActivityTimeout);
    connect(m_reconnectDelayTimer, &QTimer::timeout, this, &ConnectionStateMachine::onReconnectDelayTimeout);
    
    qDebug() << "ConnectionStateMachine: Created";
}

ConnectionStateMachine::~ConnectionStateMachine() {
    if (m_stateMachine->isRunning()) {
        m_stateMachine->stop();
    }
    qDebug() << "ConnectionStateMachine: Destroyed";
}

void ConnectionStateMachine::setupStateMachine() {
    // Create states
    m_disconnectedState = new QState(m_stateMachine);
    m_connectingState = new QState(m_stateMachine);
    m_connectedState = new QState(m_stateMachine);
    m_runningState = new QState(m_stateMachine);
    m_faultState = new QState(m_stateMachine);
    m_reconnectingState = new QState(m_stateMachine);
    
    // Set initial state
    m_stateMachine->setInitialState(m_disconnectedState);
    
    // Disconnected state: Entry action
    connect(m_disconnectedState, &QState::entered, this, [this]() {
        qDebug() << "ConnectionStateMachine: Entered DISCONNECTED state";
        transitionToState(State::Disconnected);
        m_connectTimer->stop();
        m_activityTimer->stop();
        resetReconnectAttempts();
        emit disconnected();
    });
    
    // Connecting state: Entry action
    connect(m_connectingState, &QState::entered, this, [this]() {
        qDebug() << "ConnectionStateMachine: Entered CONNECTING state" 
                 << "to" << m_targetAddress << ":" << m_targetPort;
        transitionToState(State::Connecting);
        m_connectTimer->start(m_config.connectTimeoutMs);
        emit connectingStarted(m_targetAddress, m_targetPort);
    });
    
    // Connected state: Entry action
    connect(m_connectedState, &QState::entered, this, [this]() {
        qDebug() << "ConnectionStateMachine: Entered CONNECTED state";
        transitionToState(State::Connected);
        m_connectTimer->stop();
        m_activityTimer->start(m_config.activityTimeoutMs);
        resetErrorCount();
        resetReconnectAttempts();
        emit connected();
    });
    
    // Running state: Entry action
    connect(m_runningState, &QState::entered, this, [this]() {
        qDebug() << "ConnectionStateMachine: Entered RUNNING state";
        transitionToState(State::Running);
        m_activityTimer->start(m_config.activityTimeoutMs);
        emit running();
    });
    
    // Fault state: Entry action
    connect(m_faultState, &QState::entered, this, [this]() {
        qDebug() << "ConnectionStateMachine: Entered FAULT state -" << m_lastError;
        transitionToState(State::Fault);
        m_connectTimer->stop();
        m_activityTimer->stop();
        emit faultOccurred(m_lastError);
    });
    
    // Reconnecting state: Entry action
    connect(m_reconnectingState, &QState::entered, this, [this]() {
        incrementReconnectAttempt();
        qDebug() << "ConnectionStateMachine: Entered RECONNECTING state"
                 << "(attempt" << m_reconnectAttemptCount 
                 << "of" << m_config.maxReconnectAttempts << ")";
        transitionToState(State::Reconnecting);
        m_connectTimer->stop();
        m_activityTimer->stop();
        emit reconnecting(m_reconnectAttemptCount);
        
        // Check if max attempts exceeded
        if (m_config.maxReconnectAttempts > 0 && 
            m_reconnectAttemptCount > m_config.maxReconnectAttempts) {
            qWarning() << "ConnectionStateMachine: Max reconnection attempts exceeded";
            emit reconnectionFailed();
            // Transition to Disconnected
            disconnect();
        } else {
            // Start delay before reconnection
            m_reconnectDelayTimer->start(m_config.reconnectDelayMs);
        }
    });
    
    qDebug() << "ConnectionStateMachine: State machine setup complete";
}

void ConnectionStateMachine::start() {
    if (!m_stateMachine->isRunning()) {
        m_stateMachine->start();
        qDebug() << "ConnectionStateMachine: Started";
    }
}

void ConnectionStateMachine::stop() {
    if (m_stateMachine->isRunning()) {
        m_stateMachine->stop();
        qDebug() << "ConnectionStateMachine: Stopped";
    }
}

QString ConnectionStateMachine::stateString() const {
    switch (m_currentState) {
        case State::Disconnected:   return "Disconnected";
        case State::Connecting:     return "Connecting";
        case State::Connected:      return "Connected";
        case State::Running:        return "Running";
        case State::Fault:          return "Fault";
        case State::Reconnecting:   return "Reconnecting";
        default:                    return "Unknown";
    }
}

void ConnectionStateMachine::setConfig(const Config& config) {
    m_config = config;
    qDebug() << "ConnectionStateMachine: Configuration updated -"
             << "connectTimeout:" << config.connectTimeoutMs << "ms,"
             << "maxReconnectAttempts:" << config.maxReconnectAttempts << ","
             << "reconnectDelay:" << config.reconnectDelayMs << "ms,"
             << "faultThreshold:" << config.faultThreshold << ","
             << "activityTimeout:" << config.activityTimeoutMs << "ms";
}

bool ConnectionStateMachine::isRunning() const {
    return m_stateMachine->isRunning();
}

void ConnectionStateMachine::connectToHost(const QString& address, int port) {
    m_targetAddress = address;
    m_targetPort = port;
    qDebug() << "ConnectionStateMachine: connectToHost() called -" << address << ":" << port;
    
    // Transition from Disconnected or Reconnecting to Connecting
    if (m_currentState == State::Disconnected || m_currentState == State::Reconnecting) {
        m_stateMachine->postEvent(new QEvent(QEvent::User));
        transitionToState(State::Connecting);
    }
}

void ConnectionStateMachine::disconnect() {
    qDebug() << "ConnectionStateMachine: disconnect() called";
    
    // Transition to Disconnected from any state
    m_connectTimer->stop();
    m_activityTimer->stop();
    m_reconnectDelayTimer->stop();
    transitionToState(State::Disconnected);
}

void ConnectionStateMachine::onConnectionSuccess() {
    qDebug() << "ConnectionStateMachine: onConnectionSuccess() called";
    
    // Transition from Connecting to Connected
    if (m_currentState == State::Connecting) {
        transitionToState(State::Connected);
    }
}

void ConnectionStateMachine::onConnectionFailure(const QString& reason) {
    m_lastError = reason;
    qWarning() << "ConnectionStateMachine: onConnectionFailure() -" << reason;
    
    incrementErrorCount();
    
    // Transition from Connecting to Reconnecting or Fault
    if (m_currentState == State::Connecting) {
        if (m_consecutiveErrorCount >= m_config.faultThreshold) {
            transitionToState(State::Fault);
        } else {
            transitionToState(State::Reconnecting);
        }
    }
}

void ConnectionStateMachine::onDataReceived() {
    // Reset activity timer
    m_activityTimer->start(m_config.activityTimeoutMs);
    
    // Transition from Connected to Running (first data received)
    if (m_currentState == State::Connected) {
        transitionToState(State::Running);
    }
    
    // Reset error count on successful data reception
    if (m_currentState == State::Running) {
        resetErrorCount();
    }
}

void ConnectionStateMachine::onNetworkError(const QString& error) {
    m_lastError = error;
    qWarning() << "ConnectionStateMachine: onNetworkError() -" << error;
    
    incrementErrorCount();
    
    // Transition from Running/Connected to Reconnecting or Fault
    if (m_currentState == State::Running || m_currentState == State::Connected) {
        if (m_consecutiveErrorCount >= m_config.faultThreshold) {
            transitionToState(State::Fault);
        } else {
            transitionToState(State::Reconnecting);
        }
    }
}

void ConnectionStateMachine::resetAndReconnect() {
    qDebug() << "ConnectionStateMachine: resetAndReconnect() called";
    resetErrorCount();
    resetReconnectAttempts();
    
    if (m_currentState == State::Fault) {
        transitionToState(State::Reconnecting);
    }
}

void ConnectionStateMachine::onConnectTimeout() {
    qWarning() << "ConnectionStateMachine: Connection timeout after" 
               << m_config.connectTimeoutMs << "ms";
    onConnectionFailure("Connection timeout");
}

void ConnectionStateMachine::onActivityTimeout() {
    qWarning() << "ConnectionStateMachine: Activity timeout after"
               << m_config.activityTimeoutMs << "ms - no data received";
    onNetworkError("Activity timeout - connection may be stale");
}

void ConnectionStateMachine::onReconnectDelayTimeout() {
    qDebug() << "ConnectionStateMachine: Reconnect delay expired, attempting connection";
    // Trigger reconnection
    connectToHost(m_targetAddress, m_targetPort);
}

void ConnectionStateMachine::transitionToState(State newState) {
    State oldState = m_currentState;
    if (oldState != newState) {
        m_currentState = newState;
        emit stateChanged(oldState, newState);
        qDebug() << "ConnectionStateMachine: State transition:" 
                 << stateString() << "->" << stateString();
    }
}

void ConnectionStateMachine::incrementErrorCount() {
    m_consecutiveErrorCount++;
    qDebug() << "ConnectionStateMachine: Error count incremented to" 
             << m_consecutiveErrorCount << "/" << m_config.faultThreshold;
}

void ConnectionStateMachine::resetErrorCount() {
    if (m_consecutiveErrorCount > 0) {
        qDebug() << "ConnectionStateMachine: Error count reset (was" 
                 << m_consecutiveErrorCount << ")";
        m_consecutiveErrorCount = 0;
    }
}

void ConnectionStateMachine::incrementReconnectAttempt() {
    m_reconnectAttemptCount++;
}

void ConnectionStateMachine::resetReconnectAttempts() {
    if (m_reconnectAttemptCount > 0) {
        qDebug() << "ConnectionStateMachine: Reconnect attempts reset (was"
                 << m_reconnectAttemptCount << ")";
        m_reconnectAttemptCount = 0;
    }
}
