#pragma once

#include "../interfaces/irepository.h"
#include "../models/datapoint.h"
#include <QSqlDatabase>
#include <QMutex>
#include <QString>

/**
 * @brief SQLite-backed repository for DataPoint persistence
 * 
 * This repository provides persistent storage for historical DataPoints.
 * Uses SQLite for reliable, embeddable database functionality.
 * 
 * Pattern: Repository Pattern (RULE-202)
 * Location: src/repositories/ (RULE-304)
 * 
 * Features:
 * - Persistent storage (survives application restarts)
 * - Thread-safe operations (QMutex)
 * - Query by time range
 * - Query by tag
 * - Automatic table creation
 * - Connection pooling
 * 
 * Database Schema:
 * CREATE TABLE datapoints (
 *   id INTEGER PRIMARY KEY AUTOINCREMENT,
 *   tag TEXT NOT NULL,
 *   value TEXT NOT NULL,
 *   timestamp INTEGER NOT NULL,
 *   quality INTEGER NOT NULL,
 *   INDEX idx_tag (tag),
 *   INDEX idx_timestamp (timestamp)
 * );
 * 
 * Example Usage:
 * @code
 * SqliteRepository repo("industrial_data.db");
 * repo.save(DataPoint("Temperature", 42.5));
 * 
 * auto result = repo.findByTag("Temperature");
 * if (result.isSuccess()) {
 *     for (const auto& point : result.value()) {
 *         qDebug() << point.value();
 *     }
 * }
 * @endcode
 */
class SqliteRepository : public IRepository<DataPoint> {
public:
    /**
     * @brief Construct a SQLite repository
     * @param databasePath Path to SQLite database file (default: "datapoints.db")
     */
    explicit SqliteRepository(const QString& databasePath = "datapoints.db");
    
    ~SqliteRepository() override;
    
    // IRepository interface implementation
    Result<void> save(const DataPoint& entity) override;
    Result<DataPoint> findById(const QString& id) override;
    Result<QList<DataPoint>> findAll() override;
    Result<void> deleteById(const QString& id) override;
    int count() const override;
    Result<void> clear() override;
    
    /**
     * @brief Find data points by tag
     * @param tag The tag identifier
     * @return Result containing list of matching data points
     */
    Result<QList<DataPoint>> findByTag(const QString& tag);
    
    /**
     * @brief Find data points within a time range
     * @param startTime Start of time range (inclusive)
     * @param endTime End of time range (inclusive)
     * @return Result containing list of matching data points
     */
    Result<QList<DataPoint>> findByTimeRange(const QDateTime& startTime, const QDateTime& endTime);
    
    /**
     * @brief Find data points by tag within a time range
     * @param tag The tag identifier
     * @param startTime Start of time range (inclusive)
     * @param endTime End of time range (inclusive)
     * @return Result containing list of matching data points
     */
    Result<QList<DataPoint>> findByTagAndTimeRange(
        const QString& tag,
        const QDateTime& startTime,
        const QDateTime& endTime
    );
    
    /**
     * @brief Get the latest data point for a tag
     * @param tag The tag identifier
     * @return Result containing the most recent data point
     */
    Result<DataPoint> findLatestByTag(const QString& tag);
    
    /**
     * @brief Delete old data points beyond retention period
     * @param retentionDays Number of days to retain (older data is deleted)
     * @return Result indicating success or failure
     */
    Result<void> deleteOlderThan(int retentionDays);
    
    /**
     * @brief Check if database is connected
     * @return True if database is open and ready
     */
    bool isConnected() const;

private:
    /**
     * @brief Initialize database connection and create tables
     * @return True if successful, false on error
     */
    bool initialize();
    
    /**
     * @brief Create database tables if they don't exist
     * @return True if successful, false on error
     */
    bool createTables();
    
    /**
     * @brief Convert DataPoint to database-ready quality integer
     */
    int qualityToInt(DataPoint::Quality quality) const;
    
    /**
     * @brief Convert database quality integer to DataPoint::Quality
     */
    DataPoint::Quality intToQuality(int quality) const;
    
    QString m_databasePath;         // Path to SQLite database file
    QSqlDatabase m_database;        // SQLite database connection
    mutable QMutex m_mutex;         // Thread safety
    QString m_connectionName;       // Unique connection name for Qt SQL
};
