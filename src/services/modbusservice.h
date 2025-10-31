#pragma once

#include <QObject>
#include <QTimer>
#include <QThread>
#include "../interfaces/idatasource.h"
#include "../utils/result.h"

// Forward declare modbus_t to avoid exposing libmodbus in header
typedef struct _modbus modbus_t;

/**
 * @brief Modbus TCP service for reading/writing industrial controllers
 * 
 * This service handles all Modbus TCP communication with industrial controllers.
 * Extracted from GraphsPage to follow Service Layer pattern.
 * 
 * Pattern: Service Layer (RULE-303)
 * Location: src/services/
 * Threading: Runs in separate thread (RULE-501, RULE-503)
 * 
 * Features:
 * - Auto-reconnection with exponential backoff
 * - Thread-safe operation
 * - Error handling and reporting
 * - Configurable retry attempts
 */
class ModbusService : public QObject {
    Q_OBJECT
    
public:
    explicit ModbusService(QObject* parent = nullptr);
    ~ModbusService() override;
    
    // IDataSource interface implementation (inline for simplicity)
    Result<QVariant> read(const QString& tag);
    void startPolling(int intervalMs);
    void stopPolling();
    bool isConnected() const;
    Result<void> connect(const QString& address, int port);
    void disconnect();
    
    /**
     * @brief Read an input register (read-only data from controller)
     * @param address Register address (0-65535)
     * @return Result containing uint16_t value or error
     */
    Result<uint16_t> readInputRegister(int address);
    
    /**
     * @brief Read a holding register (read/write data from controller)
     * @param address Register address (0-65535)
     * @return Result containing uint16_t value or error
     */
    Result<uint16_t> readHoldingRegister(int address);
    
    /**
     * @brief Write a single holding register
     * @param address Register address (0-65535)
     * @param value Value to write (0-65535)
     * @return Result indicating success or failure
     */
    Result<void> writeSingleRegister(int address, uint16_t value);
    
    /**
     * @brief Set maximum reconnection attempts
     */
    void setMaxReconnectAttempts(int attempts) { m_maxReconnectAttempts = attempts; }
    
    /**
     * @brief Enable/disable debug logging
     */
    void setDebugEnabled(bool enabled);

signals:
    /**
     * @brief Emitted when data is successfully read
     * @param tag The data point identifier
     * @param value The read value
     */
    void dataReady(const QString& tag, const QVariant& value);
    
    /**
     * @brief Emitted when an error occurs
     * @param error Error message describing what went wrong
     */
    void errorOccurred(const QString& error);
    
    /**
     * @brief Emitted when connection state changes
     * @param connected True if connected, false if disconnected
     */
    void connectionStateChanged(bool connected);

public slots:
    /**
     * @brief Attempt to reconnect to Modbus controller
     */
    void attemptReconnection();

private slots:
    void onPollTimerTimeout();

private:
    void cleanupModbusContext();
    Result<void> connectInternal();
    
    modbus_t* m_context;
    QTimer* m_pollTimer;
    QThread* m_workerThread;
    
    QString m_address;
    int m_port;
    bool m_connected;
    int m_maxReconnectAttempts;
    bool m_debugEnabled;
    
    // For polling specific tags
    QMap<QString, int> m_tagToAddressMap;  // Map tag names to Modbus addresses
};
