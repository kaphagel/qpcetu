#pragma once

#include <QObject>
#include <QVariant>
#include <QString>
#include "../utils/result.h"

/**
 * @brief Interface for data sinks (write operations to external systems)
 * 
 * This interface defines the contract for writing data to external systems.
 * Implementations can be Modbus TCP, UDP, REST API, etc.
 * 
 * Separated from IDataSource for Interface Segregation Principle (ISP).
 * Read-only controllers implement IDataSource only.
 * Read-write controllers implement both IDataSource and IDataSink.
 * 
 * Pattern: Interface Segregation Principle (ISP)
 * Location: src/interfaces/ (RULE-305)
 */
class IDataSink {
public:
    virtual ~IDataSink() = default;
    
    /**
     * @brief Write a single value to a tag/address
     * @param tag The data point identifier (e.g., "Setpoint", "Enable", address "25")
     * @param value The value to write (will be converted to appropriate type)
     * @return Result indicating success or error message
     */
    virtual Result<void> write(const QString& tag, const QVariant& value) = 0;
    
    /**
     * @brief Write multiple values atomically (if supported)
     * @param writes Map of tag -> value pairs
     * @return Result indicating success or error message
     * 
     * Default implementation calls write() for each tag sequentially.
     * Override for protocols that support batch writes (e.g., Modbus Write Multiple).
     */
    virtual Result<void> writeMultiple(const QMap<QString, QVariant>& writes);
};

/**
 * @brief Signal interface for IDataSink (Qt signals require QObject)
 * 
 * Use this for emitting signals from data sinks.
 * Inherit both IDataSink and IDataSinkSignals in concrete implementations.
 */
class IDataSinkSignals : public QObject {
    Q_OBJECT
    
signals:
    /**
     * @brief Emitted when a write operation succeeds
     * @param tag The data point identifier
     * @param value The written value
     */
    void writeSucceeded(const QString& tag, const QVariant& value);
    
    /**
     * @brief Emitted when a write operation fails
     * @param tag The data point identifier
     * @param error Error message describing what went wrong
     */
    void writeFailed(const QString& tag, const QString& error);
    
    /**
     * @brief Emitted when connection state changes
     * @param connected True if connected, false if disconnected
     */
    void connectionChanged(bool connected);
};
