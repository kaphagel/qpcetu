#pragma once

#include <QList>
#include <QMutex>
#include <QMutexLocker>
#include "../interfaces/irepository.h"
#include "../models/datapoint.h"

/**
 * @brief Circular buffer repository for efficient real-time data storage
 * 
 * This repository implements a fixed-size circular buffer optimized for
 * high-frequency industrial sensor data. When the buffer is full, the oldest
 * data is automatically overwritten by new data (FIFO behavior).
 * 
 * Features:
 * - Thread-safe operations using QMutex
 * - O(1) insertion complexity
 * - Fixed memory footprint (no dynamic allocation after construction)
 * - Automatic aging-out of old data
 * - Quality-based filtering
 * - Time-range queries
 * 
 * Pattern: Repository (RULE-202)
 * Location: src/repositories/ (RULE-301)
 * 
 * Use Cases:
 * - Real-time graph data buffering
 * - Moving average calculations
 * - Historical data for immediate playback
 * - Quality monitoring (reject Bad/Uncertain samples)
 * 
 * Example:
 * @code
 * auto* repo = new CircularBufferRepository(1000, this); // 1000 samples
 * DataPoint point("EEG", 42.5, QDateTime::currentDateTime());
 * repo->save(point);
 * 
 * // Get last 100 samples
 * auto recent = repo->findRecent(100);
 * 
 * // Get samples from last 5 seconds
 * auto lastFiveSeconds = repo->findByTimeRange(
 *     QDateTime::currentDateTime().addSecs(-5),
 *     QDateTime::currentDateTime()
 * );
 * @endcode
 * 
 * Thread Safety: All public methods are thread-safe.
 */
class CircularBufferRepository : public QObject, public IRepository<DataPoint> {
    Q_OBJECT
    
public:
    /**
     * @brief Create circular buffer repository
     * @param maxSize Maximum number of data points to store
     * @param parent QObject parent
     */
    explicit CircularBufferRepository(int maxSize = 10000, QObject* parent = nullptr);
    ~CircularBufferRepository() override;
    
    // IRepository<DataPoint> interface implementation
    
    /**
     * @brief Save a data point to the buffer
     * @param entity DataPoint to save
     * @return Result<void> Success or error
     * 
     * Complexity: O(1)
     * Thread-safe: Yes
     */
    Result<void> save(const DataPoint& entity) override;
    
    /**
     * @brief Find data point by tag (returns most recent)
     * @param id Tag name (e.g., "EEG", "Temperature")
     * @return Result<DataPoint> The most recent data point with matching tag
     * 
     * Complexity: O(n) where n is buffer size
     * Thread-safe: Yes
     */
    Result<DataPoint> findById(const QString& id) override;
    
    /**
     * @brief Get all data points in buffer
     * @return Result<QList<DataPoint>> All stored data points
     * 
     * Complexity: O(n)
     * Thread-safe: Yes
     */
    Result<QList<DataPoint>> findAll() override;
    
    /**
     * @brief Delete data points by tag
     * @param id Tag name
     * @return Result<void> Success or error
     * 
     * Complexity: O(n)
     * Thread-safe: Yes
     */
    Result<void> deleteById(const QString& id) override;
    
    /**
     * @brief Get number of data points in buffer
     * @return Current count
     * 
     * Complexity: O(1)
     * Thread-safe: Yes
     */
    int count() const override;
    
    /**
     * @brief Clear all data from buffer
     * @return Result<void> Success or error
     * 
     * Complexity: O(1)
     * Thread-safe: Yes
     */
    Result<void> clear() override;
    
    // Additional methods specific to circular buffer
    
    /**
     * @brief Get the most recent N data points
     * @param n Number of recent points to retrieve
     * @return Result<QList<DataPoint>> Most recent points (newest first)
     * 
     * Complexity: O(min(n, bufferSize))
     * Thread-safe: Yes
     */
    Result<QList<DataPoint>> findRecent(int n);
    
    /**
     * @brief Find data points within a time range
     * @param startTime Start of time range (inclusive)
     * @param endTime End of time range (inclusive)
     * @return Result<QList<DataPoint>> Points within time range
     * 
     * Complexity: O(n)
     * Thread-safe: Yes
     */
    Result<QList<DataPoint>> findByTimeRange(const QDateTime& startTime, const QDateTime& endTime);
    
    /**
     * @brief Find data points by tag within time range
     * @param tag Tag name
     * @param startTime Start of time range
     * @param endTime End of time range
     * @return Result<QList<DataPoint>> Matching points
     * 
     * Complexity: O(n)
     * Thread-safe: Yes
     */
    Result<QList<DataPoint>> findByTagAndTimeRange(
        const QString& tag,
        const QDateTime& startTime,
        const QDateTime& endTime
    );
    
    /**
     * @brief Find data points by quality
     * @param quality Quality level to filter by
     * @return Result<QList<DataPoint>> Points with matching quality
     * 
     * Complexity: O(n)
     * Thread-safe: Yes
     */
    Result<QList<DataPoint>> findByQuality(DataPoint::Quality quality);
    
    /**
     * @brief Get maximum buffer size
     */
    int maxSize() const { return m_maxSize; }
    
    /**
     * @brief Check if buffer is full
     */
    bool isFull() const;
    
    /**
     * @brief Get buffer utilization percentage
     * @return Percentage 0.0 to 100.0
     */
    double utilizationPercent() const;
    
    /**
     * @brief Get oldest data point timestamp
     * @return Result<QDateTime> Timestamp of oldest point, or error if empty
     */
    Result<QDateTime> oldestTimestamp() const;
    
    /**
     * @brief Get newest data point timestamp
     * @return Result<QDateTime> Timestamp of newest point, or error if empty
     */
    Result<QDateTime> newestTimestamp() const;

signals:
    /**
     * @brief Emitted when a new data point is saved
     * @param dataPoint The saved data point
     */
    void dataSaved(const DataPoint& dataPoint);
    
    /**
     * @brief Emitted when buffer is full and old data is overwritten
     * @param overwrittenPoint The data point that was overwritten
     */
    void dataOverwritten(const DataPoint& overwrittenPoint);
    
    /**
     * @brief Emitted when buffer is cleared
     */
    void bufferCleared();

private:
    QList<DataPoint> m_buffer;       ///< Circular buffer storage
    int m_maxSize;                   ///< Maximum buffer capacity
    int m_writeIndex;                ///< Current write position
    int m_currentCount;              ///< Current number of valid entries
    mutable QMutex m_mutex;          ///< Thread safety mutex
};
