#pragma once

#include <QObject>
#include <QDateTime>
#include <QQueue>
#include <QTimer>
#include <QMutex>

/**
 * @brief Industrial event types with priorities
 */
class IndustrialEvent
{
public:
    enum EventType
    {
        Info,
        Warning,
        Alarm,
        Critical,
        SystemEvent
    };

    enum EventCategory
    {
        Communication,
        Process,
        Safety,
        Maintenance,
        User
    };

    IndustrialEvent(EventType type, EventCategory category,
                    const QString &source, const QString &message);

    EventType type() const { return m_type; }
    EventCategory category() const { return m_category; }
    QString source() const { return m_source; }
    QString message() const { return m_message; }
    QDateTime timestamp() const { return m_timestamp; }
    quint64 eventId() const { return m_eventId; }
    bool isAcknowledged() const { return m_acknowledged; }

    void acknowledge(const QString &user = QString());
    QString acknowledgedBy() const { return m_acknowledgedBy; }
    QDateTime acknowledgedAt() const { return m_acknowledgedAt; }

private:
    static quint64 s_nextEventId;

    quint64 m_eventId;
    EventType m_type;
    EventCategory m_category;
    QString m_source;
    QString m_message;
    QDateTime m_timestamp;
    bool m_acknowledged;
    QString m_acknowledgedBy;
    QDateTime m_acknowledgedAt;
};

/**
 * @brief Central event manager for industrial HMI
 *
 * Manages alarms, events, and notifications with priority queuing
 */
class IndustrialEventManager : public QObject
{
    Q_OBJECT

public:
    explicit IndustrialEventManager(QObject *parent = nullptr);

    // Event management
    void addEvent(const IndustrialEvent &event);
    void acknowledgeEvent(quint64 eventId, const QString &user = QString());
    void acknowledgeAllEvents(const QString &user = QString());

    // Event retrieval
    QList<IndustrialEvent> getEvents(IndustrialEvent::EventType minType = IndustrialEvent::Info) const;
    QList<IndustrialEvent> getUnacknowledgedEvents() const;
    QList<IndustrialEvent> getEventsBySource(const QString &source) const;
    QList<IndustrialEvent> getEventsByCategory(IndustrialEvent::EventCategory category) const;

    // Statistics
    int totalEventCount() const;
    int unacknowledgedCount() const;
    int alarmCount() const;
    int criticalCount() const;

    // Configuration
    void setMaxEvents(int maxEvents);
    void setAutoAcknowledgeTimeout(int seconds);

public slots:
    void onControllerConnected(const QString &controllerIp);
    void onControllerDisconnected(const QString &controllerIp);
    void onControllerFault(const QString &controllerIp, const QString &error);
    void onDataValueChanged(const QString &source, const QString &tag, const QVariant &value);

signals:
    void eventAdded(const IndustrialEvent &event);
    void eventAcknowledged(quint64 eventId);
    void alarmStateChanged(bool hasUnacknowledgedAlarms);
    void criticalAlarmRaised(const IndustrialEvent &event);

private slots:
    void processEventQueue();
    void checkAutoAcknowledge();

private:
    void pruneOldEvents();
    bool shouldRaiseAlarm(const QString &source, const QString &tag, const QVariant &value);

    QList<IndustrialEvent> m_events;
    QQueue<IndustrialEvent> m_eventQueue;
    QTimer *m_processTimer;
    QTimer *m_autoAckTimer;
    QMutex m_eventsMutex;

    int m_maxEvents;
    int m_autoAckTimeout;
    QMap<QString, QVariant> m_lastValues;      // For change detection
    QMap<QString, QDateTime> m_lastAlarmTimes; // Alarm debouncing
};
