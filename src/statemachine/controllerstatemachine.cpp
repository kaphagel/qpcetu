#include "controllerstatemachine.h"
#include <QDebug>
#include <QSignalTransition>
#include <QEventTransition>

ControllerStateMachine::ControllerStateMachine(const QString &controllerIp, QObject *parent)
    : QObject(parent)
    , m_stateMachine(new QStateMachine(this))
    , m_heartbeatTimer(new QTimer(this))
    , m_controllerIp(controllerIp)
    , m_currentState(Disconnected)
{
    // Setup heartbeat timer
    m_heartbeatTimer->setInterval(5000); // 5 second heartbeat
    m_heartbeatTimer->setSingleShot(false);
    connect(m_heartbeatTimer, &QTimer::timeout, this, &ControllerStateMachine::checkHeartbeat);
    
    setupStateMachine();
    setupTransitions();
    
    m_stateMachine->start();
}

ControllerStateMachine::ControllerState ControllerStateMachine::currentState() const
{
    return m_currentState;
}

void ControllerStateMachine::start()
{
    m_stateMachine->start();
}

void ControllerStateMachine::stop()
{
    m_heartbeatTimer->stop();
    m_stateMachine->stop();
}

void ControllerStateMachine::connectToController()
{
    qDebug() << "Initiating connection to controller:" << m_controllerIp;
    
    // In real implementation, this would start the actual connection process
    // For now, simulate successful connection after a delay
    QTimer::singleShot(2000, this, &ControllerStateMachine::connectionEstablished);
}

void ControllerStateMachine::startOperation()
{
    if (m_currentState == Connected) {
        qDebug() << "Starting operations on controller:" << m_controllerIp;
        emit operationStarted();
    } else {
        qWarning() << "Cannot start operations - controller not connected:" << m_controllerIp;
    }
}

void ControllerStateMachine::stopOperation()
{
    if (m_currentState == Running) {
        qDebug() << "Stopping operations on controller:" << m_controllerIp;
        emit operationStopped();
    }
}

void ControllerStateMachine::enterMaintenance()
{
    if (m_currentState == Connected || m_currentState == Running) {
        qDebug() << "Entering maintenance mode for controller:" << m_controllerIp;
        emit maintenanceRequired();
    }
}

void ControllerStateMachine::clearFault()
{
    if (m_currentState == Fault) {
        qDebug() << "Clearing fault for controller:" << m_controllerIp;
        // Attempt to reconnect after fault is cleared
        connectToController();
    }
}

void ControllerStateMachine::handleCommunicationLoss()
{
    qWarning() << "Communication lost with controller:" << m_controllerIp;
    emit faultDetected("Communication timeout");
}

void ControllerStateMachine::onStateEntered()
{
    QState *state = qobject_cast<QState*>(sender());
    if (!state) return;
    
    // Update current state based on which state was entered
    if (state == m_disconnectedState) {
        m_currentState = Disconnected;
        m_heartbeatTimer->stop();
        qDebug() << "Controller" << m_controllerIp << "entered Disconnected state";
    } else if (state == m_connectingState) {
        m_currentState = Connecting;
        qDebug() << "Controller" << m_controllerIp << "entered Connecting state";
    } else if (state == m_connectedState) {
        m_currentState = Connected;
        m_heartbeatTimer->start();
        qDebug() << "Controller" << m_controllerIp << "entered Connected state";
    } else if (state == m_runningState) {
        m_currentState = Running;
        qDebug() << "Controller" << m_controllerIp << "entered Running state";
    } else if (state == m_faultState) {
        m_currentState = Fault;
        m_heartbeatTimer->stop();
        qDebug() << "Controller" << m_controllerIp << "entered Fault state";
    } else if (state == m_maintenanceState) {
        m_currentState = Maintenance;
        qDebug() << "Controller" << m_controllerIp << "entered Maintenance state";
    } else if (state == m_stoppingState) {
        m_currentState = Stopping;
        qDebug() << "Controller" << m_controllerIp << "entered Stopping state";
    }
    
    emit stateChanged(m_currentState);
}

void ControllerStateMachine::onStateExited()
{
    QState *state = qobject_cast<QState*>(sender());
    if (state) {
        qDebug() << "Controller" << m_controllerIp << "exited state";
    }
}

void ControllerStateMachine::checkHeartbeat()
{
    // In real implementation, this would send a heartbeat request
    // and check for response. For simulation, randomly trigger faults
    static int heartbeatCount = 0;
    heartbeatCount++;
    
    // Simulate occasional communication issues for testing
    if (heartbeatCount % 20 == 0) { // Every 20th heartbeat
        qDebug() << "Simulating communication issue for controller:" << m_controllerIp;
        handleCommunicationLoss();
    } else {
        qDebug() << "Heartbeat OK for controller:" << m_controllerIp;
    }
}

void ControllerStateMachine::setupStateMachine()
{
    // Create states
    m_disconnectedState = new QState(m_stateMachine);
    m_connectingState = new QState(m_stateMachine);
    m_connectedState = new QState(m_stateMachine);
    m_runningState = new QState(m_stateMachine);
    m_faultState = new QState(m_stateMachine);
    m_maintenanceState = new QState(m_stateMachine);
    m_stoppingState = new QState(m_stateMachine);
    
    // Set initial state
    m_stateMachine->setInitialState(m_disconnectedState);
    
    // Connect state entry/exit signals
    connect(m_disconnectedState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_connectingState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_connectedState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_runningState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_faultState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_maintenanceState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    connect(m_stoppingState, &QState::entered, this, &ControllerStateMachine::onStateEntered);
    
    connect(m_disconnectedState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_connectingState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_connectedState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_runningState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_faultState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_maintenanceState, &QState::exited, this, &ControllerStateMachine::onStateExited);
    connect(m_stoppingState, &QState::exited, this, &ControllerStateMachine::onStateExited);
}

void ControllerStateMachine::setupTransitions()
{
    // Disconnected -> Connecting (on connectToController signal)
    QSignalTransition *startConnecting = m_disconnectedState->addTransition(this, &ControllerStateMachine::connectToController, m_connectingState);
    
    // Connecting -> Connected (on connectionEstablished signal)
    QSignalTransition *connected = m_connectingState->addTransition(this, &ControllerStateMachine::connectionEstablished, m_connectedState);
    
    // Connecting -> Fault (on timeout or connection failure)
    QSignalTransition *connectFault = m_connectingState->addTransition(this, &ControllerStateMachine::faultDetected, m_faultState);
    
    // Connected -> Running (on operationStarted signal)
    QSignalTransition *startRunning = m_connectedState->addTransition(this, &ControllerStateMachine::operationStarted, m_runningState);
    
    // Connected -> Maintenance (on maintenanceRequired signal)
    QSignalTransition *enterMaintenance = m_connectedState->addTransition(this, &ControllerStateMachine::maintenanceRequired, m_maintenanceState);
    
    // Connected -> Fault (on communication loss)
    QSignalTransition *connectedFault = m_connectedState->addTransition(this, &ControllerStateMachine::faultDetected, m_faultState);
    
    // Running -> Stopping (on operationStopped signal)
    QSignalTransition *stopOperations = m_runningState->addTransition(this, &ControllerStateMachine::operationStopped, m_stoppingState);
    
    // Running -> Fault (on communication loss)
    QSignalTransition *runningFault = m_runningState->addTransition(this, &ControllerStateMachine::faultDetected, m_faultState);
    
    // Running -> Maintenance (on maintenanceRequired signal)
    QSignalTransition *runningMaintenance = m_runningState->addTransition(this, &ControllerStateMachine::maintenanceRequired, m_maintenanceState);
    
    // Stopping -> Connected (automatic transition after stop completes)
    QTimer *stopTimer = new QTimer(this);
    stopTimer->setSingleShot(true);
    stopTimer->setInterval(1000); // 1 second stop delay
    connect(m_stoppingState, &QState::entered, stopTimer, QOverload<>::of(&QTimer::start));
    QSignalTransition *stopComplete = m_stoppingState->addTransition(stopTimer, &QTimer::timeout, m_connectedState);
    
    // Maintenance -> Connected (when maintenance is complete)
    // This would typically be triggered by an external event or command
    
    // Fault -> Disconnected (when fault is cleared or connection is reset)
    QSignalTransition *faultToDisconnected = m_faultState->addTransition(this, &ControllerStateMachine::connectToController, m_disconnectedState);
    
    // Any state -> Disconnected (emergency disconnect)
    // This could be added for all states if needed
}