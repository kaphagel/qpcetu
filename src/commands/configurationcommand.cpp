#include "configurationcommand.h"
#include <QSettings>

ConfigurationCommand::ConfigurationCommand(
    const QMap<QString, QVariant>& changes,
    const QString& description,
    const QString& userName
)
    : m_changes(changes)
    , m_previousValues()
    , m_description(description)
    , m_userName(userName)
    , m_commandId(QUuid::createUuid().toString())
    , m_timestamp(QDateTime::currentDateTime())
    , m_executed(false)
    , m_lastError("")
    , m_validator(nullptr)
{
}

void ConfigurationCommand::execute()
{
    // Step 1: Validate changes (if validator is set)
    if (m_validator && !m_validator(m_changes)) {
        m_lastError = "Configuration validation failed";
        m_executed = false;
        return;
    }
    
    // Step 2: Read current values for undo
    QStringList keys = m_changes.keys();
    m_previousValues = readConfiguration(keys);
    
    // Step 3: Apply new configuration
    if (!applyConfiguration(m_changes)) {
        m_lastError = "Failed to apply configuration changes";
        m_executed = false;
        return;
    }
    
    // Success
    m_executed = true;
    m_lastError = "";
}

void ConfigurationCommand::undo()
{
    if (!m_executed) {
        m_lastError = "Command has not been executed yet";
        return;
    }
    
    if (m_previousValues.isEmpty()) {
        m_lastError = "No previous configuration to restore";
        return;
    }
    
    // Restore previous configuration
    if (!applyConfiguration(m_previousValues)) {
        m_lastError = "Failed to restore previous configuration";
        return;
    }
    
    // Success
    m_executed = false;
    m_lastError = "";
}

bool ConfigurationCommand::canUndo() const
{
    return m_executed && !m_previousValues.isEmpty();
}

QString ConfigurationCommand::description() const
{
    if (!m_description.isEmpty()) {
        return m_description;
    }
    
    // Generate description from changes
    QStringList changeList;
    for (auto it = m_changes.begin(); it != m_changes.end(); ++it) {
        changeList << QString("%1 = %2").arg(it.key()).arg(it.value().toString());
    }
    
    return QString("Configuration: %1").arg(changeList.join(", "));
}

QDateTime ConfigurationCommand::timestamp() const
{
    return m_timestamp;
}

QString ConfigurationCommand::userName() const
{
    return m_userName;
}

QString ConfigurationCommand::commandId() const
{
    return m_commandId;
}

void ConfigurationCommand::setValidator(std::function<bool(const QMap<QString, QVariant>&)> validator)
{
    m_validator = validator;
}

bool ConfigurationCommand::applyConfiguration(const QMap<QString, QVariant>& values)
{
    QSettings settings;
    
    try {
        for (auto it = values.begin(); it != values.end(); ++it) {
            settings.setValue(it.key(), it.value());
        }
        
        // Ensure settings are written to disk
        settings.sync();
        
        // Check for write errors
        if (settings.status() != QSettings::NoError) {
            m_lastError = "QSettings error occurred during write";
            return false;
        }
        
        return true;
    } catch (...) {
        m_lastError = "Exception occurred while writing settings";
        return false;
    }
}

QMap<QString, QVariant> ConfigurationCommand::readConfiguration(const QStringList& keys)
{
    QSettings settings;
    QMap<QString, QVariant> values;
    
    for (const QString& key : keys) {
        values[key] = settings.value(key);
    }
    
    return values;
}
