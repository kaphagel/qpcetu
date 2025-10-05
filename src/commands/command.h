#ifndef COMMAND_H
#define COMMAND_H

#include <QObject>
#include <QString>

/**
 * @brief Abstract base class for all industrial operations
 *
 * Implements Command pattern for undo/redo functionality
 * and logging of all industrial operations
 */
class Command : public QObject
{
    Q_OBJECT

public:
    explicit Command(QObject *parent = nullptr);
    virtual ~Command() = default;

    virtual bool execute() = 0;
    virtual bool undo() = 0;
    virtual QString description() const = 0;
    virtual bool isReversible() const { return true; }

signals:
    void executed(bool success);
    void undone(bool success);

protected:
    bool m_executed = false;
};

/**
 * @brief Command to start/stop controller operations
 */
class ControllerOperationCommand : public Command
{
    Q_OBJECT

public:
    enum Operation
    {
        Start,
        Stop,
        Reset,
        Configure
    };

    ControllerOperationCommand(const QString &controllerIp,
                               Operation operation,
                               QObject *parent = nullptr);

    bool execute() override;
    bool undo() override;
    QString description() const override;

private:
    QString m_controllerIp;
    Operation m_operation;
    Operation m_previousState;
};

#endif // COMMAND_H