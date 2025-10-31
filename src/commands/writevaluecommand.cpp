#include "writevaluecommand.h"

WriteValueCommand::WriteValueCommand(
    IDataSink* dataSink,
    const QString& tag,
    const QVariant& newValue,
    const QString& userName
)
    : m_dataSink(dataSink)
    , m_tag(tag)
    , m_newValue(newValue)
    , m_oldValue()
    , m_userName(userName)
    , m_commandId(QUuid::createUuid().toString())
    , m_timestamp(QDateTime::currentDateTime())
    , m_executed(false)
    , m_canUndo(false)
    , m_lastError("")
{
}

void WriteValueCommand::execute()
{
    if (!m_dataSink) {
        m_lastError = "No data sink available";
        m_canUndo = false;
        return;
    }
    
    // Step 1: Read current value (for undo)
    // Note: We need IDataSource interface for reading.
    // In a real implementation, the data sink might also implement IDataSource,
    // or we could inject both interfaces.
    // For now, we'll assume we can't read the old value, making undo impossible.
    // TODO: Add IDataSource* parameter to constructor for full undo support.
    
    // Step 2: Write new value
    Result<void> result = m_dataSink->write(m_tag, m_newValue);
    
    if (result.isSuccess()) {
        m_executed = true;
        m_lastError = "";
        // Note: Without reading old value, we can't undo.
        // Set m_canUndo to false for safety.
        m_canUndo = false;
    } else {
        m_executed = false;
        m_lastError = result.error();
        m_canUndo = false;
    }
}

void WriteValueCommand::undo()
{
    if (!m_canUndo) {
        m_lastError = "Command cannot be undone (old value not captured)";
        return;
    }
    
    if (!m_dataSink) {
        m_lastError = "No data sink available for undo";
        return;
    }
    
    if (!m_executed) {
        m_lastError = "Command has not been executed yet";
        return;
    }
    
    // Restore old value
    Result<void> result = m_dataSink->write(m_tag, m_oldValue);
    
    if (result.isSuccess()) {
        m_executed = false;
        m_lastError = "";
    } else {
        m_lastError = result.error();
    }
}

bool WriteValueCommand::canUndo() const
{
    return m_canUndo && m_executed;
}

QString WriteValueCommand::description() const
{
    return QString("Write %1 to tag '%2'")
        .arg(m_newValue.toString())
        .arg(m_tag);
}

QDateTime WriteValueCommand::timestamp() const
{
    return m_timestamp;
}

QString WriteValueCommand::userName() const
{
    return m_userName;
}

QString WriteValueCommand::commandId() const
{
    return m_commandId;
}
