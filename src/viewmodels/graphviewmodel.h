#pragma once

#include <QObject>
#include <QTimer>
#include "../models/datapoint.h"

// Forward declaration
class ModbusService;

/**
 * @brief ViewModel for Graphs page - handles business logic for data visualization
 * 
 * This ViewModel contains all business logic for the Graphs page, including:
 * - Data acquisition from Modbus service
 * - Data transformation (e.g., scaling EEG values by /10)
 * - Polling management
 * - Error handling
 * 
 * Pattern: MVVM (Model-View-ViewModel) - RULE-200
 * Location: src/viewmodels/ (RULE-301)
 * 
 * The View (GraphsPage) connects to this ViewModel's signals for UI updates.
 * This separation allows testing without UI and reusing logic across platforms.
 */
class GraphViewModel : public QObject {
    Q_OBJECT
    
public:
    explicit GraphViewModel(ModbusService* modbusService, QObject* parent = nullptr);
    ~GraphViewModel() override;
    
    /**
     * @brief Start polling EEG data from controller
     * @param intervalMs Polling interval in milliseconds
     */
    void startPolling(int intervalMs = 1000);
    
    /**
     * @brief Stop polling data
     */
    void stopPolling();
    
    /**
     * @brief Check if currently polling
     */
    bool isPolling() const;
    
    /**
     * @brief Get the current EEG value
     */
    double currentEegValue() const { return m_currentEegValue; }
    
    /**
     * @brief Get the last data point
     */
    DataPoint lastDataPoint() const { return m_lastDataPoint; }

signals:
    /**
     * @brief Emitted when EEG data is updated
     * @param value The scaled EEG value (divided by 10)
     */
    void eegDataUpdated(double value);
    
    /**
     * @brief Emitted when a new data point is available
     * @param dataPoint The complete data point with timestamp and quality
     */
    void dataPointReceived(const DataPoint& dataPoint);
    
    /**
     * @brief Emitted when an error occurs
     * @param error Error message describing what went wrong
     */
    void errorOccurred(const QString& error);
    
    /**
     * @brief Emitted when connection state changes
     * @param connected True if connected to data source
     */
    void connectionStateChanged(bool connected);

private slots:
    void onDataSourceDataReady(const QString& tag, const QVariant& value);
    void onDataSourceError(const QString& error);
    void onDataSourceConnectionChanged(bool connected);

private:
    /**
     * @brief Scale raw EEG value (divide by 10)
     */
    double scaleEegValue(uint16_t rawValue) const;
    
    ModbusService* m_modbusService;
    double m_currentEegValue;
    DataPoint m_lastDataPoint;
    bool m_isPolling;
};
