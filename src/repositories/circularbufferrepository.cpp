#include "circularbufferrepository.h"
#include <QDebug>
#include <algorithm>

CircularBufferRepository::CircularBufferRepository(int maxSize, QObject* parent)
    : QObject(parent)
    , m_buffer()
    , m_maxSize(maxSize)
    , m_writeIndex(0)
    , m_currentCount(0)
    , m_mutex()
{
    // Pre-allocate buffer to avoid dynamic reallocation
    m_buffer.reserve(maxSize);
    qDebug() << "CircularBufferRepository: Created with max size" << maxSize;
}

CircularBufferRepository::~CircularBufferRepository() {
    qDebug() << "CircularBufferRepository: Destroyed with" << m_currentCount << "entries";
}

Result<void> CircularBufferRepository::save(const DataPoint& entity) {
    QMutexLocker locker(&m_mutex);
    
    if (!entity.isValid()) {
        return Result<void>::failure("Cannot save invalid DataPoint");
    }
    
    // Check if we're overwriting old data
    bool willOverwrite = (m_currentCount == m_maxSize);
    DataPoint overwrittenPoint;
    
    if (willOverwrite) {
        overwrittenPoint = m_buffer[m_writeIndex];
    }
    
    // Insert or overwrite
    if (m_currentCount < m_maxSize) {
        m_buffer.append(entity);
        m_currentCount++;
    } else {
        m_buffer[m_writeIndex] = entity;
    }
    
    // Advance write index (circular)
    m_writeIndex = (m_writeIndex + 1) % m_maxSize;
    
    // Emit signals outside mutex lock
    locker.unlock();
    
    emit dataSaved(entity);
    
    if (willOverwrite) {
        emit dataOverwritten(overwrittenPoint);
    }
    
    return Result<void>::success();
}

Result<DataPoint> CircularBufferRepository::findById(const QString& id) {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<DataPoint>::failure("Buffer is empty");
    }
    
    // Search backwards from newest to oldest to find most recent match
    for (int i = m_currentCount - 1; i >= 0; --i) {
        int index = (m_writeIndex - 1 - i + m_maxSize) % m_maxSize;
        if (m_buffer[index].tag() == id) {
            return Result<DataPoint>::success(m_buffer[index]);
        }
    }
    
    return Result<DataPoint>::failure(QString("No DataPoint found with tag: %1").arg(id));
}

Result<QList<DataPoint>> CircularBufferRepository::findAll() {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QList<DataPoint>>::success(QList<DataPoint>());
    }
    
    QList<DataPoint> result;
    result.reserve(m_currentCount);
    
    // Return in chronological order (oldest to newest)
    if (m_currentCount < m_maxSize) {
        // Buffer not full yet - simple case
        result = m_buffer;
    } else {
        // Buffer is full - need to unwrap circular order
        for (int i = 0; i < m_currentCount; ++i) {
            int index = (m_writeIndex + i) % m_maxSize;
            result.append(m_buffer[index]);
        }
    }
    
    return Result<QList<DataPoint>>::success(result);
}

Result<void> CircularBufferRepository::deleteById(const QString& id) {
    QMutexLocker locker(&m_mutex);
    
    int removedCount = 0;
    
    // Remove all matching entries
    for (int i = m_currentCount - 1; i >= 0; --i) {
        int index = (m_writeIndex - 1 - i + m_maxSize) % m_maxSize;
        if (m_buffer[index].tag() == id) {
            m_buffer.removeAt(index);
            removedCount++;
            m_currentCount--;
            
            // Adjust write index if we removed before it
            if (index < m_writeIndex) {
                m_writeIndex--;
            }
        }
    }
    
    if (removedCount == 0) {
        return Result<void>::failure(QString("No DataPoint found with tag: %1").arg(id));
    }
    
    qDebug() << "CircularBufferRepository: Deleted" << removedCount 
             << "entries with tag" << id;
    
    return Result<void>::success();
}

int CircularBufferRepository::count() const {
    QMutexLocker locker(&m_mutex);
    return m_currentCount;
}

Result<void> CircularBufferRepository::clear() {
    QMutexLocker locker(&m_mutex);
    
    m_buffer.clear();
    m_buffer.reserve(m_maxSize);
    m_writeIndex = 0;
    m_currentCount = 0;
    
    locker.unlock();
    
    emit bufferCleared();
    
    qDebug() << "CircularBufferRepository: Buffer cleared";
    return Result<void>::success();
}

Result<QList<DataPoint>> CircularBufferRepository::findRecent(int n) {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QList<DataPoint>>::success(QList<DataPoint>());
    }
    
    int actualCount = qMin(n, m_currentCount);
    QList<DataPoint> result;
    result.reserve(actualCount);
    
    // Get most recent N points (newest first)
    for (int i = 0; i < actualCount; ++i) {
        int index = (m_writeIndex - 1 - i + m_maxSize) % m_maxSize;
        result.append(m_buffer[index]);
    }
    
    return Result<QList<DataPoint>>::success(result);
}

Result<QList<DataPoint>> CircularBufferRepository::findByTimeRange(
    const QDateTime& startTime,
    const QDateTime& endTime)
{
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QList<DataPoint>>::success(QList<DataPoint>());
    }
    
    QList<DataPoint> result;
    
    // Search all entries
    for (int i = 0; i < m_currentCount; ++i) {
        int index = (m_writeIndex + i) % m_maxSize;
        const DataPoint& point = m_buffer[index];
        
        if (point.timestamp() >= startTime && point.timestamp() <= endTime) {
            result.append(point);
        }
    }
    
    return Result<QList<DataPoint>>::success(result);
}

Result<QList<DataPoint>> CircularBufferRepository::findByTagAndTimeRange(
    const QString& tag,
    const QDateTime& startTime,
    const QDateTime& endTime)
{
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QList<DataPoint>>::success(QList<DataPoint>());
    }
    
    QList<DataPoint> result;
    
    // Search all entries
    for (int i = 0; i < m_currentCount; ++i) {
        int index = (m_writeIndex + i) % m_maxSize;
        const DataPoint& point = m_buffer[index];
        
        if (point.tag() == tag &&
            point.timestamp() >= startTime &&
            point.timestamp() <= endTime) {
            result.append(point);
        }
    }
    
    return Result<QList<DataPoint>>::success(result);
}

Result<QList<DataPoint>> CircularBufferRepository::findByQuality(DataPoint::Quality quality) {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QList<DataPoint>>::success(QList<DataPoint>());
    }
    
    QList<DataPoint> result;
    
    // Search all entries
    for (int i = 0; i < m_currentCount; ++i) {
        int index = (m_writeIndex + i) % m_maxSize;
        const DataPoint& point = m_buffer[index];
        
        if (point.quality() == quality) {
            result.append(point);
        }
    }
    
    return Result<QList<DataPoint>>::success(result);
}

bool CircularBufferRepository::isFull() const {
    QMutexLocker locker(&m_mutex);
    return m_currentCount == m_maxSize;
}

double CircularBufferRepository::utilizationPercent() const {
    QMutexLocker locker(&m_mutex);
    if (m_maxSize == 0) return 0.0;
    return (static_cast<double>(m_currentCount) / m_maxSize) * 100.0;
}

Result<QDateTime> CircularBufferRepository::oldestTimestamp() const {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QDateTime>::failure("Buffer is empty");
    }
    
    int oldestIndex = (m_writeIndex) % m_maxSize;
    if (m_currentCount < m_maxSize) {
        oldestIndex = 0;
    }
    
    return Result<QDateTime>::success(m_buffer[oldestIndex].timestamp());
}

Result<QDateTime> CircularBufferRepository::newestTimestamp() const {
    QMutexLocker locker(&m_mutex);
    
    if (m_currentCount == 0) {
        return Result<QDateTime>::failure("Buffer is empty");
    }
    
    int newestIndex = (m_writeIndex - 1 + m_maxSize) % m_maxSize;
    return Result<QDateTime>::success(m_buffer[newestIndex].timestamp());
}
