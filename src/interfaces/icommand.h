#pragma once

#include <QString>
#include <QDateTime>

/**
 * @brief Interface for commands (Command Pattern)
 * 
 * Commands encapsulate operations for undo/redo and audit trails.
 * Use this for all write operations in industrial control systems.
 * 
 * Pattern: Command Pattern (RULE-203)
 * Location: src/interfaces/ (RULE-305)
 * 
 * Benefits:
 * - Audit trail: Know who did what and when
 * - Undo/Redo: Operator can reverse mistakes
 * - Batch operations: Record sequence and replay
 * - Security: Track all control actions
 */
class ICommand {
public:
    virtual ~ICommand() = default;
    
    /**
     * @brief Execute the command
     * 
     * This performs the actual operation (e.g., write value to controller).
     * Should be idempotent if possible.
     */
    virtual void execute() = 0;
    
    /**
     * @brief Undo the command
     * 
     * Reverses the operation (e.g., restore previous value).
     * Not all commands can be undone (document this in implementation).
     */
    virtual void undo() = 0;
    
    /**
     * @brief Check if this command can be undone
     * @return True if undo() can be called safely
     */
    virtual bool canUndo() const = 0;
    
    /**
     * @brief Get a human-readable description of the command
     * @return Description string (e.g., "Write 42.5 to Temperature Setpoint")
     */
    virtual QString description() const = 0;
    
    /**
     * @brief Get the timestamp when the command was created
     * @return Timestamp of command creation
     */
    virtual QDateTime timestamp() const = 0;
    
    /**
     * @brief Get the username of who issued the command
     * @return Username (for audit trail)
     */
    virtual QString userName() const = 0;
    
    /**
     * @brief Get the unique identifier for this command
     * @return UUID or unique ID
     */
    virtual QString commandId() const = 0;
};
