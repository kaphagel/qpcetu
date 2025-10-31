#pragma once

#include <QObject>
#include <QVariant>
#include <QString>
#include "../utils/result.h"

/**
 * @brief Interface for data sources (Modbus, UDP, REST, etc.)
 * 
 * This interface defines the contract for reading data from external systems.
 * Implementations can be Modbus TCP, UDP, REST API, XML, etc.
 * 
 * Use this interface for dependency injection in ViewModels.
 * 
 * Pattern: Interface Segregation Principle (ISP)
 * Location: src/interfaces/ (RULE-305)
 */
class IDataSource {
public:
    virtual ~IDataSource() = default;
    
    /**
     * @brief Read a single value by tag/address
     * @param tag The data point identifier (e.g., "EEG", "Temperature", address "25")
     * @return Result containing the value or error message
     */
    virtual Result<QVariant> read(const QString& tag) = 0;
    
    /**
     * @brief Start continuous polling for data
     * @param intervalMs Polling interval in milliseconds
     */
    virtual void startPolling(int intervalMs) = 0;
    
    /**
     * @brief Stop continuous polling
     */
    virtual void stopPolling() = 0;
    
    /**
     * @brief Check if data source is currently connected
     */
    virtual bool isConnected() const = 0;
    
    /**
     * @brief Connect to the data source
     * @param address IP address or URL
     * @param port Port number (if applicable)
     * @return Result indicating success or failure
     */
    virtual Result<void> connect(const QString& address, int port) = 0;
    
    /**
     * @brief Disconnect from the data source
     */
    virtual void disconnect() = 0;
};

/**
 * @brief Signal interface for IDataSource (Qt signals require QObject)
 * 
 * Use this for emitting signals from data sources.
 * Inherit both IDataSource and IDataSourceSignals in concrete implementations.
 */
class IDataSourceSignals : public QObject {
    Q_OBJECT
    
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
};
