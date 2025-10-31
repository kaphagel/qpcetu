#include "sqliterepository.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>
#include <QMutexLocker>
#include <QUuid>
#include <QDebug>

SqliteRepository::SqliteRepository(const QString& databasePath)
    : m_databasePath(databasePath)
    , m_mutex()
    , m_connectionName(QUuid::createUuid().toString())
{
    initialize();
}

SqliteRepository::~SqliteRepository()
{
    if (m_database.isOpen()) {
        m_database.close();
    }
    QSqlDatabase::removeDatabase(m_connectionName);
}

bool SqliteRepository::initialize()
{
    QMutexLocker locker(&m_mutex);
    
    // Create database connection with unique name
    m_database = QSqlDatabase::addDatabase("QSQLITE", m_connectionName);
    m_database.setDatabaseName(m_databasePath);
    
    if (!m_database.open()) {
        qWarning() << "Failed to open database:" << m_database.lastError().text();
        return false;
    }
    
    return createTables();
}

bool SqliteRepository::createTables()
{
    QSqlQuery query(m_database);
    
    QString createTableSQL = R"(
        CREATE TABLE IF NOT EXISTS datapoints (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            tag TEXT NOT NULL,
            value TEXT NOT NULL,
            timestamp INTEGER NOT NULL,
            quality INTEGER NOT NULL
        )
    )";
    
    if (!query.exec(createTableSQL)) {
        qWarning() << "Failed to create datapoints table:" << query.lastError().text();
        return false;
    }
    
    // Create indices for performance
    query.exec("CREATE INDEX IF NOT EXISTS idx_tag ON datapoints(tag)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_timestamp ON datapoints(timestamp)");
    query.exec("CREATE INDEX IF NOT EXISTS idx_tag_timestamp ON datapoints(tag, timestamp)");
    
    return true;
}

Result<void> SqliteRepository::save(const DataPoint& entity)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare(R"(
        INSERT INTO datapoints (tag, value, timestamp, quality)
        VALUES (:tag, :value, :timestamp, :quality)
    )");
    
    query.bindValue(":tag", entity.tag());
    query.bindValue(":value", entity.value().toString());
    query.bindValue(":timestamp", entity.timestamp().toSecsSinceEpoch());
    query.bindValue(":quality", qualityToInt(entity.quality()));
    
    if (!query.exec()) {
        return Result<void>::failure(query.lastError().text());
    }
    
    return Result<void>::success();
}

Result<DataPoint> SqliteRepository::findById(const QString& id)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare("SELECT tag, value, timestamp, quality FROM datapoints WHERE id = :id");
    query.bindValue(":id", id.toInt());
    
    if (!query.exec()) {
        return Result<DataPoint>::failure(query.lastError().text());
    }
    
    if (!query.next()) {
        return Result<DataPoint>::failure("DataPoint not found with id: " + id);
    }
    
    QString tag = query.value(0).toString();
    QVariant value = query.value(1);
    QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
    DataPoint::Quality quality = intToQuality(query.value(3).toInt());
    
    return Result<DataPoint>::success(DataPoint(tag, value, timestamp, quality));
}

Result<QList<DataPoint>> SqliteRepository::findAll()
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare("SELECT tag, value, timestamp, quality FROM datapoints ORDER BY timestamp DESC");
    
    if (!query.exec()) {
        return Result<QList<DataPoint>>::failure(query.lastError().text());
    }
    
    QList<DataPoint> dataPoints;
    while (query.next()) {
        QString tag = query.value(0).toString();
        QVariant value = query.value(1);
        QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
        DataPoint::Quality quality = intToQuality(query.value(3).toInt());
        
        dataPoints.append(DataPoint(tag, value, timestamp, quality));
    }
    
    return Result<QList<DataPoint>>::success(dataPoints);
}

Result<void> SqliteRepository::deleteById(const QString& id)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM datapoints WHERE id = :id");
    query.bindValue(":id", id.toInt());
    
    if (!query.exec()) {
        return Result<void>::failure(query.lastError().text());
    }
    
    return Result<void>::success();
}

int SqliteRepository::count() const
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare("SELECT COUNT(*) FROM datapoints");
    
    if (!query.exec() || !query.next()) {
        return 0;
    }
    
    return query.value(0).toInt();
}

Result<void> SqliteRepository::clear()
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    if (!query.exec("DELETE FROM datapoints")) {
        return Result<void>::failure(query.lastError().text());
    }
    
    return Result<void>::success();
}

Result<QList<DataPoint>> SqliteRepository::findByTag(const QString& tag)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare("SELECT tag, value, timestamp, quality FROM datapoints WHERE tag = :tag ORDER BY timestamp DESC");
    query.bindValue(":tag", tag);
    
    if (!query.exec()) {
        return Result<QList<DataPoint>>::failure(query.lastError().text());
    }
    
    QList<DataPoint> dataPoints;
    while (query.next()) {
        QString resultTag = query.value(0).toString();
        QVariant value = query.value(1);
        QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
        DataPoint::Quality quality = intToQuality(query.value(3).toInt());
        
        dataPoints.append(DataPoint(resultTag, value, timestamp, quality));
    }
    
    return Result<QList<DataPoint>>::success(dataPoints);
}

Result<QList<DataPoint>> SqliteRepository::findByTimeRange(const QDateTime& startTime, const QDateTime& endTime)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare(R"(
        SELECT tag, value, timestamp, quality 
        FROM datapoints 
        WHERE timestamp >= :start AND timestamp <= :end 
        ORDER BY timestamp DESC
    )");
    query.bindValue(":start", startTime.toSecsSinceEpoch());
    query.bindValue(":end", endTime.toSecsSinceEpoch());
    
    if (!query.exec()) {
        return Result<QList<DataPoint>>::failure(query.lastError().text());
    }
    
    QList<DataPoint> dataPoints;
    while (query.next()) {
        QString tag = query.value(0).toString();
        QVariant value = query.value(1);
        QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
        DataPoint::Quality quality = intToQuality(query.value(3).toInt());
        
        dataPoints.append(DataPoint(tag, value, timestamp, quality));
    }
    
    return Result<QList<DataPoint>>::success(dataPoints);
}

Result<QList<DataPoint>> SqliteRepository::findByTagAndTimeRange(
    const QString& tag,
    const QDateTime& startTime,
    const QDateTime& endTime)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare(R"(
        SELECT tag, value, timestamp, quality 
        FROM datapoints 
        WHERE tag = :tag AND timestamp >= :start AND timestamp <= :end 
        ORDER BY timestamp DESC
    )");
    query.bindValue(":tag", tag);
    query.bindValue(":start", startTime.toSecsSinceEpoch());
    query.bindValue(":end", endTime.toSecsSinceEpoch());
    
    if (!query.exec()) {
        return Result<QList<DataPoint>>::failure(query.lastError().text());
    }
    
    QList<DataPoint> dataPoints;
    while (query.next()) {
        QString resultTag = query.value(0).toString();
        QVariant value = query.value(1);
        QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
        DataPoint::Quality quality = intToQuality(query.value(3).toInt());
        
        dataPoints.append(DataPoint(resultTag, value, timestamp, quality));
    }
    
    return Result<QList<DataPoint>>::success(dataPoints);
}

Result<DataPoint> SqliteRepository::findLatestByTag(const QString& tag)
{
    QMutexLocker locker(&m_mutex);
    
    QSqlQuery query(m_database);
    query.prepare(R"(
        SELECT tag, value, timestamp, quality 
        FROM datapoints 
        WHERE tag = :tag 
        ORDER BY timestamp DESC 
        LIMIT 1
    )");
    query.bindValue(":tag", tag);
    
    if (!query.exec()) {
        return Result<DataPoint>::failure(query.lastError().text());
    }
    
    if (!query.next()) {
        return Result<DataPoint>::failure("No data points found for tag: " + tag);
    }
    
    QString resultTag = query.value(0).toString();
    QVariant value = query.value(1);
    QDateTime timestamp = QDateTime::fromSecsSinceEpoch(query.value(2).toLongLong());
    DataPoint::Quality quality = intToQuality(query.value(3).toInt());
    
    return Result<DataPoint>::success(DataPoint(resultTag, value, timestamp, quality));
}

Result<void> SqliteRepository::deleteOlderThan(int retentionDays)
{
    QMutexLocker locker(&m_mutex);
    
    QDateTime cutoffDate = QDateTime::currentDateTime().addDays(-retentionDays);
    
    QSqlQuery query(m_database);
    query.prepare("DELETE FROM datapoints WHERE timestamp < :cutoff");
    query.bindValue(":cutoff", cutoffDate.toSecsSinceEpoch());
    
    if (!query.exec()) {
        return Result<void>::failure(query.lastError().text());
    }
    
    return Result<void>::success();
}

bool SqliteRepository::isConnected() const
{
    return m_database.isOpen();
}

int SqliteRepository::qualityToInt(DataPoint::Quality quality) const
{
    return static_cast<int>(quality);
}

DataPoint::Quality SqliteRepository::intToQuality(int quality) const
{
    return static_cast<DataPoint::Quality>(quality);
}
