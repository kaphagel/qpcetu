#pragma once

#include "../interfaces/icommand.h"
#include "../interfaces/idatasink.h"
#include <QString>
#include <QVariant>
#include <QDateTime>
#include <QUuid>

/**
 * @brief Command for writing a value to a data point
 * 
 * This command encapsulates a write operation with undo capability.
 * Used for industrial control operations requiring audit trails.
 * 
 * Pattern: Command Pattern (RULE-203)
 * Location: src/commands/ (RULE-307)
 * 
 * Features:
 * - Undo/Redo: Restores previous value on undo
 * - Audit Trail: Tracks who, what, when
 * - Error Handling: Returns Result<void> for failures
 * 
 * Example Usage:
 * @code
 * auto cmd = new WriteValueCommand(
 *     dataSink,
 *     "Temperature_Setpoint",
 *     42.5,
 *     "operator1"
 * );
 * cmd->execute();  // Write 42.5
 * cmd->undo();     // Restore previous value
 * @endcode
 */
class WriteValueCommand : public ICommand {
public:
    /**
     * @brief Construct a write value command
     * @param dataSink The data sink to write to (injected dependency)
     * @param tag The data point identifier
     * @param newValue The new value to write
     * @param userName The username of who issued the command
     */
    WriteValueCommand(
        IDataSink* dataSink,
        const QString& tag,
        const QVariant& newValue,
        const QString& userName
    );
    
    ~WriteValueCommand() override = default;
    
    // ICommand interface implementation
    void execute() override;
    void undo() override;
    bool canUndo() const override;
    QString description() const override;
    QDateTime timestamp() const override;
    QString userName() const override;
    QString commandId() const override;
    
    /**
     * @brief Check if the command has been executed
     * @return True if execute() has been called successfully
     */
    bool isExecuted() const { return m_executed; }
    
    /**
     * @brief Get the tag this command operates on
     * @return The data point identifier
     */
    QString tag() const { return m_tag; }
    
    /**
     * @brief Get the new value to be written
     * @return The new value
     */
    QVariant newValue() const { return m_newValue; }
    
    /**
     * @brief Get the previous value (for undo)
     * @return The old value (valid only after execute())
     */
    QVariant oldValue() const { return m_oldValue; }
    
    /**
     * @brief Get the last error message (if any)
     * @return Error message or empty string if no error
     */
    QString lastError() const { return m_lastError; }

private:
    IDataSink* m_dataSink;          // Data sink for write operations (NOT owned)
    QString m_tag;                  // Data point identifier
    QVariant m_newValue;            // Value to write
    QVariant m_oldValue;            // Previous value (for undo)
    QString m_userName;             // Who issued the command
    QString m_commandId;            // Unique identifier (UUID)
    QDateTime m_timestamp;          // When command was created
    bool m_executed;                // Has execute() been called?
    bool m_canUndo;                 // Can this command be undone?
    QString m_lastError;            // Last error message
};
