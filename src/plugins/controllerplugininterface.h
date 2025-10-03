#ifndef CONTROLLERPLUGININTERFACE_H
#define CONTROLLERPLUGININTERFACE_H

#include <QObject>
#include <QVariantMap>
#include "../industrialcontroller.h"

/**
 * @brief Plugin interface for adding new controller types
 * 
 * Allows extending the HMI with new controller protocols without
 * modifying the core application
 */
class ControllerPluginInterface
{
public:
    virtual ~ControllerPluginInterface() = default;

    // Plugin identification
    virtual QString pluginName() const = 0;
    virtual QString pluginVersion() const = 0;
    virtual QString pluginDescription() const = 0;
    virtual QStringList supportedControllerTypes() const = 0;

    // Controller factory
    virtual IndustrialController* createController(const QString &type, 
                                                  const QString &ip,
                                                  QObject *parent = nullptr) = 0;

    // Discovery support
    virtual bool supportsDiscovery(const QString &type) const = 0;
    virtual QString discoveryMessage(const QString &type) const = 0;
    virtual int discoveryPort(const QString &type) const = 0;
    virtual bool parseDiscoveryResponse(const QString &response, 
                                      QString &controllerType,
                                      QVariantMap &properties) const = 0;

    // Configuration UI
    virtual QWidget* createConfigurationWidget(const QString &type, QWidget *parent = nullptr) const = 0;
    virtual QStringList requiredSettings(const QString &type) const = 0;
    virtual bool validateSettings(const QString &type, const QVariantMap &settings) const = 0;

    // Protocol support
    virtual QStringList supportedProtocols(const QString &type) const = 0;
    virtual int defaultPort(const QString &type) const = 0;
    virtual int connectionTimeout(const QString &type) const = 0;
};

Q_DECLARE_INTERFACE(ControllerPluginInterface, "com.yourcompany.ControllerPluginInterface/1.0")

/**
 * @brief Plugin manager for loading and managing controller plugins
 */
class ControllerPluginManager : public QObject
{
    Q_OBJECT

public:
    explicit ControllerPluginManager(QObject *parent = nullptr);
    ~ControllerPluginManager();

    bool loadPluginsFromDirectory(const QString &directory);
    bool loadPlugin(const QString &filePath);
    void unloadAllPlugins();

    QStringList availablePlugins() const;
    QStringList supportedControllerTypes() const;
    ControllerPluginInterface* getPlugin(const QString &controllerType) const;

    // Factory methods using plugins
    IndustrialController* createController(const QString &type, const QString &ip) const;
    QWidget* createConfigWidget(const QString &type, QWidget *parent = nullptr) const;

signals:
    void pluginLoaded(const QString &pluginName);
    void pluginUnloaded(const QString &pluginName);
    void pluginError(const QString &error);

private:
    struct PluginInfo {
        QPluginLoader *loader;
        ControllerPluginInterface *interface;
        QString filePath;
    };

    QMap<QString, PluginInfo> m_plugins;
    QMap<QString, ControllerPluginInterface*> m_typeToPlugin;
};

/**
 * @brief Base class for creating controller plugins
 */
class BaseControllerPlugin : public QObject, public ControllerPluginInterface
{
    Q_OBJECT
    Q_INTERFACES(ControllerPluginInterface)

public:
    explicit BaseControllerPlugin(QObject *parent = nullptr);

protected:
    // Helper methods for plugin implementers
    QVariantMap parseKeyValueResponse(const QString &response, 
                                    const QString &separator = ";",
                                    const QString &keyValueSeparator = "=") const;
    bool isValidIpAddress(const QString &ip) const;
    bool isValidMacAddress(const QString &mac) const;
};

#endif // CONTROLLERPLUGININTERFACE_H