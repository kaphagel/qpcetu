#ifndef DATAREPOSITORY_H
#define DATAREPOSITORY_H

#include <QObject>
#include <QSqlDatabase>
#include <QDateTime>
#include <QVariantMap>

/**
 * @brief Data point for historical trending
 */
struct DataPoint
{
    QString source;
    QString tag;
    QVariant value;
    QDateTime timestamp;
    int quality; // 0=Bad, 1=Uncertain, 2=Good
};

/**
 * @brief Repository pattern for industrial data persistence
 *
 * Handles historical data, configurations, and event logging
 */
class DataRepository : public QObject
{
    Q_OBJECT

public:
    explicit DataRepository(const QString &databasePath = QString(), QObject *parent = nullptr);
    ~DataRepository();

    bool initialize();
    bool isConnected() const;

    // Historical data
    bool insertDataPoint(const DataPoint &point);
    bool insertDataPoints(const QList<DataPoint> &points);
    QList<DataPoint> getHistoricalData(const QString &source, const QString &tag,
                                       const QDateTime &startTime, const QDateTime &endTime) const;
    QList<DataPoint> getLatestData(const QString &source, int count = 100) const;

    // Configuration management
    bool saveControllerConfig(const QString &controllerIp, const QVariantMap &config);
    QVariantMap loadControllerConfig(const QString &controllerIp) const;
    QStringList getConfiguredControllers() const;

    // Event logging
    bool logEvent(const QString &type, const QString &source,
                  const QString &message, const QDateTime &timestamp = QDateTime::currentDateTime());
    QList<QVariantMap> getEvents(const QDateTime &startTime, const QDateTime &endTime,
                                 const QString &source = QString()) const;

    // Maintenance
    bool cleanupOldData(const QDateTime &cutoffTime);
    qint64 getDatabaseSize() const;
    bool vacuum();

public slots:
    void onDataReceived(const QString &source, const QString &tag, const QVariant &value);
    void onEventOccurred(const QString &type, const QString &source, const QString &message);

signals:
    void dataInserted(const DataPoint &point);
    void databaseError(const QString &error);

private:
    bool createTables();
    bool executeSql(const QString &query, const QVariantMap &bindings = QVariantMap()) const;
    QList<QVariantMap> executeQuery(const QString &query, const QVariantMap &bindings = QVariantMap()) const;

    QSqlDatabase m_database;
    QString m_databasePath;
    bool m_initialized;

    mutable QMutex m_dbMutex;
};

/**
 * @brief High-performance circular buffer for real-time data
 *
 * Used for live trending while repository handles historical storage
 */
class CircularDataBuffer : public QObject
{
    Q_OBJECT

public:
    explicit CircularDataBuffer(int maxSize = 10000, QObject *parent = nullptr);

    void addDataPoint(const DataPoint &point);
    QList<DataPoint> getData(int count = -1) const; // -1 = all data
    QList<DataPoint> getDataRange(const QDateTime &start, const QDateTime &end) const;

    void clear();
    int size() const;
    int maxSize() const;
    void setMaxSize(int maxSize);

signals:
    void dataAdded(const DataPoint &point);
    void bufferFull();

private:
    QList<DataPoint> m_buffer;
    int m_maxSize;
    int m_currentIndex;
    mutable QMutex m_bufferMutex;
};

#endif // DATAREPOSITORY_H