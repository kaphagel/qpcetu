#ifndef CONTROLLERSTATEMACHINE_H
#define CONTROLLERSTATEMACHINE_H

#include <QObject>
#include <QStateMachine>
#include <QState>
#include <QTimer>

/**
 * @brief State machine for managing industrial controller lifecycle
 * 
 * Handles: Disconnected -> Connecting -> Connected -> Running -> Fault -> Maintenance
 */
class ControllerStateMachine : public QObject
{
    Q_OBJECT

public:
    enum ControllerState {
        Disconnected,
        Connecting,
        Connected,
        Running,
        Fault,
        Maintenance,
        Stopping
    };
    Q_ENUM(ControllerState)

    explicit ControllerStateMachine(const QString &controllerIp, QObject *parent = nullptr);
    
    ControllerState currentState() const;
    void start();
    void stop();

public slots:
    void connectToController();
    void startOperation();
    void stopOperation();
    void enterMaintenance();
    void clearFault();
    void handleCommunicationLoss();

signals:
    void stateChanged(ControllerState newState);
    void connectionEstablished();
    void operationStarted();
    void operationStopped();
    void faultDetected(const QString &error);
    void maintenanceRequired();

private slots:
    void onStateEntered();
    void onStateExited();
    void checkHeartbeat();

private:
    void setupStateMachine();
    void setupTransitions();
    
    QStateMachine *m_stateMachine;
    QState *m_disconnectedState;
    QState *m_connectingState;
    QState *m_connectedState;
    QState *m_runningState;
    QState *m_faultState;
    QState *m_maintenanceState;
    QState *m_stoppingState;
    
    QTimer *m_heartbeatTimer;
    QString m_controllerIp;
    ControllerState m_currentState;
};

#endif // CONTROLLERSTATEMACHINE_H