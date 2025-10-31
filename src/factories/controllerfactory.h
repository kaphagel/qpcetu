#pragma once

#include "../industrialcontroller.h"
#include "../strategies/controllerstrategy.h"
#include <QString>
#include <QHostAddress>
#include <QJsonObject>
#include <memory>

/**
 * @brief Factory for creating Industrial Controller instances
 * 
 * Centralized controller creation with appropriate strategy assignment.
 * Supports multiple controller types (EPIC4, SNAP_PAC, etc.) with type detection.
 * 
 * Pattern: Factory Pattern (RULE-309)
 * Location: src/factories/ (RULE-309)
 * 
 * Benefits:
 * - Centralized creation logic
 * - Automatic strategy assignment based on type
 * - Consistent initialization
 * - Easy to extend with new controller types
 * - Testable without physical hardware
 * 
 * Example Usage:
 * @code
 * // Create from UDP discovery response
 * auto controller = ControllerFactory::createFromDiscovery(
 *     udpResponse,
 *     senderAddress
 * );
 * 
 * // Create from JSON configuration
 * QJsonObject config;
 * config["type"] = "EPIC4";
 * config["ip"] = "192.168.1.100";
 * auto controller = ControllerFactory::createFromConfig(config);
 * 
 * // Create specific type
 * auto controller = ControllerFactory::createEpic4(
 *     "192.168.1.100",
 *     "EPIC-001"
 * );
 * @endcode
 */
class ControllerFactory {
public:
    /**
     * @brief Create controller from UDP discovery response
     * @param discoveryResponse Raw UDP response string
     * @param senderAddress IP address of sender
     * @return Pointer to created controller or nullptr on failure
     */
    static IndustrialController* createFromDiscovery(
        const QString& discoveryResponse,
        const QHostAddress& senderAddress,
        QObject* parent = nullptr
    );
    
    /**
     * @brief Create controller from JSON configuration
     * @param config JSON object with controller properties
     * @return Pointer to created controller or nullptr on failure
     * 
     * Expected JSON format:
     * {
     *   "type": "EPIC4",        // Controller type string
     *   "ip": "192.168.1.100",  // IP address
     *   "hostname": "EPIC-001", // Optional hostname
     *   "port": 502             // Optional Modbus port (default: 502)
     * }
     */
    static IndustrialController* createFromConfig(
        const QJsonObject& config,
        QObject* parent = nullptr
    );
    
    /**
     * @brief Create EPIC4 controller
     * @param ipAddress IP address
     * @param hostname Optional hostname
     * @return Pointer to created EPIC4 controller
     */
    static IndustrialController* createEpic4(
        const QString& ipAddress,
        const QString& hostname = "",
        QObject* parent = nullptr
    );
    
    /**
     * @brief Create SNAP-PAC controller
     * @param ipAddress IP address
     * @param hostname Optional hostname
     * @return Pointer to created SNAP-PAC controller
     */
    static IndustrialController* createSnapPac(
        const QString& ipAddress,
        const QString& hostname = "",
        QObject* parent = nullptr
    );
    
    /**
     * @brief Create controller of specified type
     * @param type Controller type enum
     * @param ipAddress IP address
     * @param hostname Optional hostname
     * @return Pointer to created controller or nullptr for unsupported types
     */
    static IndustrialController* createController(
        IndustrialController::ControllerType type,
        const QString& ipAddress,
        const QString& hostname = "",
        QObject* parent = nullptr
    );
    
    /**
     * @brief Parse controller type from string
     * @param typeString Type as string (e.g., "EPIC4", "SNAP-PAC")
     * @return ControllerType enum value
     */
    static IndustrialController::ControllerType parseControllerType(const QString& typeString);
    
    /**
     * @brief Get default Modbus port for controller type
     * @param type Controller type
     * @return Default port number (typically 502 for Modbus TCP)
     */
    static int getDefaultPort(IndustrialController::ControllerType type);

private:
    /**
     * @brief Assign appropriate strategy to controller
     * @param controller The controller to configure
     * @param type Controller type
     */
    static void assignStrategy(IndustrialController* controller, IndustrialController::ControllerType type);
    
    // Factory is static-only, no instances
    ControllerFactory() = delete;
    ~ControllerFactory() = delete;
    ControllerFactory(const ControllerFactory&) = delete;
    ControllerFactory& operator=(const ControllerFactory&) = delete;
};
