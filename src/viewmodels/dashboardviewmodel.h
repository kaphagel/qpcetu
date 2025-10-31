#pragma once

#include <QObject>
#include <QTimer>
#include <QString>
#include <QDateTime>

/**
 * @brief ViewModel for Dashboard page - handles business logic for system monitoring
 * 
 * This ViewModel contains all business logic for the Dashboard page, including:
 * - System status monitoring
 * - Simulated data generation (energy, shields, engines, weapons)
 * - Navigation data (coordinates, velocity, altitude)
 * - System parameters (power, coolant, fuel)
 * - Alert/log message generation
 * - Time updates
 * 
 * Pattern: MVVM (Model-View-ViewModel) - RULE-200
 * Location: src/viewmodels/ (RULE-301)
 * 
 * The View (DashboardPage) connects to this ViewModel's signals for UI updates.
 * This separation allows testing without UI and reusing logic across platforms.
 */
class DashboardViewModel : public QObject {
    Q_OBJECT
    
public:
    /**
     * @brief System status states
     */
    enum class SystemStatus {
        Online,
        Warning,
        Critical,
        Offline
    };
    Q_ENUM(SystemStatus)
    
    /**
     * @brief Navigation data structure
     */
    struct NavigationData {
        int x = 0;
        int y = 0;
        int z = 0;
        double velocity = 0.0;  ///< Speed of light (C)
        int altitude = 0;       ///< Kilometers
    };
    
    /**
     * @brief System parameters structure
     */
    struct SystemParameters {
        int powerDistribution = 0;  ///< Percentage 0-100
        int coolantLevel = 0;       ///< Percentage 0-100
        int fuelReserves = 0;       ///< Percentage 0-100
    };
    
    explicit DashboardViewModel(QObject* parent = nullptr);
    ~DashboardViewModel() override;
    
    /**
     * @brief Start automatic data updates
     * @param intervalMs Update interval in milliseconds
     */
    void startUpdates(int intervalMs = 1000);
    
    /**
     * @brief Stop automatic data updates
     */
    void stopUpdates();
    
    /**
     * @brief Check if updates are running
     */
    bool isUpdating() const { return m_isUpdating; }
    
    /**
     * @brief Manually trigger data update
     */
    void updateData();
    
    /**
     * @brief Manually trigger system status update
     */
    void updateSystemStatus();
    
    /**
     * @brief Manually trigger alert generation
     */
    void generateAlert();
    
    /**
     * @brief Get current system status
     */
    SystemStatus currentSystemStatus() const { return m_systemStatus; }
    
    /**
     * @brief Get current navigation data
     */
    NavigationData navigationData() const { return m_navigationData; }
    
    /**
     * @brief Get current system parameters
     */
    SystemParameters systemParameters() const { return m_systemParameters; }
    
    /**
     * @brief Get energy core value
     */
    int energyCore() const { return m_energyCore; }
    
    /**
     * @brief Get shield matrix value
     */
    int shieldMatrix() const { return m_shieldMatrix; }
    
    /**
     * @brief Get engine thrust value
     */
    int engineThrust() const { return m_engineThrust; }
    
    /**
     * @brief Get weapon array status
     */
    int weaponArray() const { return m_weaponArray; }

signals:
    /**
     * @brief Emitted when energy core value changes
     * @param value New value in MW
     */
    void energyCoreUpdated(int value);
    
    /**
     * @brief Emitted when shield matrix value changes
     * @param value New value in percentage
     */
    void shieldMatrixUpdated(int value);
    
    /**
     * @brief Emitted when engine thrust value changes
     * @param value New value in KN
     */
    void engineThrustUpdated(int value);
    
    /**
     * @brief Emitted when weapon array status changes
     * @param value Ready status percentage
     */
    void weaponArrayUpdated(int value);
    
    /**
     * @brief Emitted when system parameters change
     * @param params New system parameters
     */
    void systemParametersUpdated(const SystemParameters& params);
    
    /**
     * @brief Emitted when navigation data changes
     * @param data New navigation data
     */
    void navigationDataUpdated(const NavigationData& data);
    
    /**
     * @brief Emitted when system status changes
     * @param status New system status
     * @param message Status message (e.g., "SYSTEM ONLINE")
     */
    void systemStatusChanged(SystemStatus status, const QString& message);
    
    /**
     * @brief Emitted when current time updates
     * @param timestamp Current date/time string
     */
    void timeUpdated(const QString& timestamp);
    
    /**
     * @brief Emitted when a new alert/log message is generated
     * @param message Alert message with timestamp
     */
    void alertGenerated(const QString& message);
    
    /**
     * @brief Emitted when connection status changes
     * @param connected True if quantum link is active
     * @param message Status message (e.g., "QUANTUM LINK: ACTIVE")
     */
    void connectionStatusChanged(bool connected, const QString& message);

private slots:
    void onUpdateTimer();

private:
    void generateRandomData();
    void generateRandomSystemParameters();
    void generateRandomNavigationData();
    void checkSystemStatus();
    QString generateRandomAlert();
    
    QTimer* m_updateTimer;
    bool m_isUpdating;
    
    // Current state
    SystemStatus m_systemStatus;
    NavigationData m_navigationData;
    SystemParameters m_systemParameters;
    
    // Sensor values
    int m_energyCore;
    int m_shieldMatrix;
    int m_engineThrust;
    int m_weaponArray;
    
    // Connection state
    bool m_connectionActive;
};
