#pragma once

#include <QString>
#include <QDateTime>
#include <QVariant>

/**
 * @brief Domain model for a single data point
 * 
 * Pure C++ data structure with no Qt dependencies (except Qt types for convenience).
 * Represents a single measurement or reading from an industrial controller.
 * 
 * Pattern: Domain Model (RULE-102 - pure C++)
 * Location: src/models/ (RULE-300)
 */
class DataPoint {
public:
    /**
     * @brief Quality enumeration for data validity
     */
    enum class Quality {
        Good,           // Data is valid and reliable
        Uncertain,      // Data may be unreliable
        Bad,            // Data is invalid (sensor error, out of range, etc.)
        Stale           // Data is old (not updated recently)
    };
    
    /**
     * @brief Default constructor
     */
    DataPoint() 
        : m_tag("")
        , m_value(0.0)
        , m_timestamp(QDateTime::currentDateTime())
        , m_quality(Quality::Good)
    {}
    
    /**
     * @brief Construct a data point with all values
     */
    DataPoint(const QString& tag, const QVariant& value, const QDateTime& timestamp, Quality quality = Quality::Good)
        : m_tag(tag)
        , m_value(value)
        , m_timestamp(timestamp)
        , m_quality(quality)
    {}
    
    /**
     * @brief Construct a data point with current timestamp
     */
    DataPoint(const QString& tag, const QVariant& value)
        : m_tag(tag)
        , m_value(value)
        , m_timestamp(QDateTime::currentDateTime())
        , m_quality(Quality::Good)
    {}
    
    // Getters
    QString tag() const { return m_tag; }
    QVariant value() const { return m_value; }
    QDateTime timestamp() const { return m_timestamp; }
    Quality quality() const { return m_quality; }
    
    // Setters
    void setTag(const QString& tag) { m_tag = tag; }
    void setValue(const QVariant& value) { m_value = value; }
    void setTimestamp(const QDateTime& timestamp) { m_timestamp = timestamp; }
    void setQuality(Quality quality) { m_quality = quality; }
    
    /**
     * @brief Check if data point is valid
     */
    bool isValid() const {
        return m_quality == Quality::Good && !m_tag.isEmpty();
    }
    
    /**
     * @brief Get the value as double (convenience method)
     */
    double toDouble() const {
        return m_value.toDouble();
    }
    
    /**
     * @brief Get the value as string (convenience method)
     */
    QString toString() const {
        return m_value.toString();
    }

private:
    QString m_tag;              // Identifier (e.g., "EEG", "Temperature", "Pressure")
    QVariant m_value;           // Value (can be int, double, string, bool, etc.)
    QDateTime m_timestamp;      // When the reading was taken
    Quality m_quality;          // Data quality indicator
};
