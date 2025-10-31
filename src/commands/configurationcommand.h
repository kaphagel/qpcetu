#pragma once

#include "../interfaces/icommand.h"
#include <QString>
#include <QVariant>
#include <QMap>
#include <QDateTime>
#include <QUuid>

/**
 * @brief Command for changing system configuration
 * 
 * This command encapsulates configuration changes with undo capability.
 * Used for modifying application settings, controller parameters, display themes, etc.
 * 
 * Pattern: Command Pattern (RULE-203)
 * Location: src/commands/ (RULE-307)
 * 
 * Features:
 * - Undo/Redo: Restores previous configuration on undo
 * - Audit Trail: Tracks who changed what and when
 * - Batch Changes: Can modify multiple configuration keys atomically
 * - Validation: Supports custom validation before applying changes
 * 
 * Example Usage:
 * @code
 * QMap<QString, QVariant> changes;
 * changes["theme"] = "dark";
 * changes["polling_interval"] = 1000;
 * 
 * auto cmd = new ConfigurationCommand(
 *     configService,
 *     changes,
 *     "Configuration Update",
 *     "admin"
 * );
 * cmd->execute();  // Apply changes
 * cmd->undo();     // Restore previous values
 * @endcode
 */
class ConfigurationCommand : public ICommand {
public:
    /**
     * @brief Construct a configuration change command
     * @param changes Map of configuration key -> new value
     * @param description Human-readable description of changes
     * @param userName The username of who issued the command
     */
    ConfigurationCommand(
        const QMap<QString, QVariant>& changes,
        const QString& description,
        const QString& userName
    );
    
    ~ConfigurationCommand() override = default;
    
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
     * @brief Get the configuration changes
     * @return Map of key -> new value
     */
    QMap<QString, QVariant> changes() const { return m_changes; }
    
    /**
     * @brief Get the previous configuration values (for undo)
     * @return Map of key -> old value (valid only after execute())
     */
    QMap<QString, QVariant> previousValues() const { return m_previousValues; }
    
    /**
     * @brief Get the last error message (if any)
     * @return Error message or empty string if no error
     */
    QString lastError() const { return m_lastError; }
    
    /**
     * @brief Set a validation function
     * 
     * The validation function is called before applying changes.
     * Return true if changes are valid, false otherwise.
     * 
     * @param validator Function that validates configuration changes
     */
    void setValidator(std::function<bool(const QMap<QString, QVariant>&)> validator);

private:
    /**
     * @brief Apply configuration changes to QSettings
     * @param values Map of key -> value to apply
     * @return True if successful, false on error
     */
    bool applyConfiguration(const QMap<QString, QVariant>& values);
    
    /**
     * @brief Read current configuration values from QSettings
     * @param keys List of configuration keys to read
     * @return Map of key -> current value
     */
    QMap<QString, QVariant> readConfiguration(const QStringList& keys);
    
    QMap<QString, QVariant> m_changes;          // New configuration values
    QMap<QString, QVariant> m_previousValues;   // Old configuration values (for undo)
    QString m_description;                      // Human-readable description
    QString m_userName;                         // Who issued the command
    QString m_commandId;                        // Unique identifier (UUID)
    QDateTime m_timestamp;                      // When command was created
    bool m_executed;                            // Has execute() been called?
    QString m_lastError;                        // Last error message
    std::function<bool(const QMap<QString, QVariant>&)> m_validator;  // Optional validator
};
