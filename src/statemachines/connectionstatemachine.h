#pragma once

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QTimer>
#include <QString>

/**
 * @brief State machine for managing network connection lifecycle
 * 
 * This state machine implements robust connection management with automatic
 * reconnection, timeout handling, and fault recovery for industrial control systems.
 * 
 * State Diagram:
 * 
 *   [Disconnected] ──connect()──> [Connecting] ──success──> [Connected]
 *        ↑                             │                         │
 *        │                             │ timeout/error           │
 *        │                             └─────────────────────────┘
 *        │                                                        │
 *        │                                              dataReady │
 *        │                                                        ↓
 *        │                                                   [Running]
 *        │                                                        │
 *        │                                              networkError
 *        │                                                        ↓
 *        │                                                    [Fault]
 *        │                                                        │
 *        │                                          canReconnect? │
 *        │                                                        ↓
 *        └────disconnect()─────────────────────────────────[Reconnecting]
 * 
 * Pattern: State Machine (RULE-204)
 * Location: src/statemachines/ (RULE-302)
 * 
 * Usage:
 * @code
 * auto* stateMachine = new ConnectionStateMachine(this);
 * connect(stateMachine, &ConnectionStateMachine::stateChanged, 
 *         this, &MyClass::onConnectionStateChanged);
 * stateMachine->start();
 * stateMachine->connectToHost("192.168.10.243", 502);
 * @endcode
 * 
 * Thread Safety: All methods are thread-safe and can be called from any thread.
 * Qt will automatically marshal signals to the correct thread.
 */
class ConnectionStateMachine : public QObject {
    Q_OBJECT
    
public:
    /**
     * @brief Connection states
     */
    enum class State {
        Disconnected,   ///< Not connected, idle
        Connecting,     ///< Attempting connection
        Connected,      ///< Connection established, not yet transmitting
        Running,        ///< Connection active, data flowing
        Fault,          ///< Error condition detected
        Reconnecting    ///< Attempting automatic reconnection
    };
    Q_ENUM(State)
    
    /**
     * @brief Configuration for state machine behavior
     */
    struct Config {
        int connectTimeoutMs = 5000;        ///< Timeout for connection attempt
        int maxReconnectAttempts = 5;       ///< Maximum reconnection attempts (-1 = unlimited)
        int reconnectDelayMs = 1000;        ///< Delay between reconnection attempts
        int faultThreshold = 3;             ///< Number of consecutive errors before entering Fault state
        int activityTimeoutMs = 30000;      ///< Time without data before considering connection stale
    };
    
    explicit ConnectionStateMachine(QObject* parent = nullptr);
    ~ConnectionStateMachine() override;
    
    /**
     * @brief Start the state machine
     * Initial state: Disconnected
     */
    void start();
    
    /**
     * @brief Stop the state machine
     */
    void stop();
    
    /**
     * @brief Get current state
     */
    State currentState() const { return m_currentState; }
    
    /**
     * @brief Get state as human-readable string
     */
    QString stateString() const;
    
    /**
     * @brief Configure state machine behavior
     */
    void setConfig(const Config& config);
    
    /**
     * @brief Get current configuration
     */
    Config config() const { return m_config; }
    
    /**
     * @brief Check if state machine is running
     */
    bool isRunning() const;
    
    /**
     * @brief Get number of reconnection attempts made
     */
    int reconnectAttemptCount() const { return m_reconnectAttemptCount; }
    
    /**
     * @brief Get number of consecutive errors
     */
    int consecutiveErrorCount() const { return m_consecutiveErrorCount; }

public slots:
    /**
     * @brief Trigger connection attempt
     * @param address Host address (IP or hostname)
     * @param port Port number
     */
    void connectToHost(const QString& address, int port);
    
    /**
     * @brief Trigger disconnection
     */
    void disconnect();
    
    /**
     * @brief Signal successful connection
     * Call this when connection is established
     */
    void onConnectionSuccess();
    
    /**
     * @brief Signal connection failure
     * @param reason Error message describing failure
     */
    void onConnectionFailure(const QString& reason);
    
    /**
     * @brief Signal data received (connection is alive)
     * Call this when data is successfully received
     */
    void onDataReceived();
    
    /**
     * @brief Signal network error occurred
     * @param error Error message
     */
    void onNetworkError(const QString& error);
    
    /**
     * @brief Reset error counters and attempt reconnection
     */
    void resetAndReconnect();

signals:
    /**
     * @brief Emitted when state changes
     * @param oldState Previous state
     * @param newState Current state
     */
    void stateChanged(ConnectionStateMachine::State oldState, ConnectionStateMachine::State newState);
    
    /**
     * @brief Emitted when entering Connecting state
     * @param address Host address
     * @param port Port number
     */
    void connectingStarted(const QString& address, int port);
    
    /**
     * @brief Emitted when entering Connected state
     */
    void connected();
    
    /**
     * @brief Emitted when entering Running state
     */
    void running();
    
    /**
     * @brief Emitted when entering Fault state
     * @param reason Error description
     */
    void faultOccurred(const QString& reason);
    
    /**
     * @brief Emitted when entering Reconnecting state
     * @param attemptNumber Current reconnection attempt number (1-based)
     */
    void reconnecting(int attemptNumber);
    
    /**
     * @brief Emitted when entering Disconnected state
     */
    void disconnected();
    
    /**
     * @brief Emitted when maximum reconnection attempts exceeded
     */
    void reconnectionFailed();

private slots:
    void onConnectTimeout();
    void onActivityTimeout();
    void onReconnectDelayTimeout();

private:
    void setupStateMachine();
    void transitionToState(State newState);
    void incrementErrorCount();
    void resetErrorCount();
    void incrementReconnectAttempt();
    void resetReconnectAttempts();
    
    QStateMachine* m_stateMachine;
    
    // States
    QState* m_disconnectedState;
    QState* m_connectingState;
    QState* m_connectedState;
    QState* m_runningState;
    QState* m_faultState;
    QState* m_reconnectingState;
    
    // Timers
    QTimer* m_connectTimer;
    QTimer* m_activityTimer;
    QTimer* m_reconnectDelayTimer;
    
    // State tracking
    State m_currentState;
    
    // Configuration
    Config m_config;
    
    // Runtime data
    QString m_targetAddress;
    int m_targetPort;
    int m_reconnectAttemptCount;
    int m_consecutiveErrorCount;
    QString m_lastError;
};
