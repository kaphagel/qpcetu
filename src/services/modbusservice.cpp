#include "modbusservice.h"
#include "../../deps/external/libmodbus/src/modbus.h"
#include "../../deps/external/libmodbus/src/modbus-tcp.h"
#include <QDebug>
#include <QThread>
#include <errno.h>

ModbusService::ModbusService(QObject* parent)
    : QObject(parent)
    , m_context(nullptr)
    , m_pollTimer(new QTimer(this))
    , m_workerThread(nullptr)
    , m_address("")
    , m_port(502)
    , m_connected(false)
    , m_maxReconnectAttempts(5)
    , m_debugEnabled(false)
{
    // Connect poll timer
    QObject::connect(m_pollTimer, &QTimer::timeout,
                     this, &ModbusService::onPollTimerTimeout);
}

ModbusService::~ModbusService() {
    disconnect();
    cleanupModbusContext();
}

Result<void> ModbusService::connect(const QString& address, int port) {
    m_address = address;
    m_port = port;
    return connectInternal();
}

Result<void> ModbusService::connectInternal() {
    // Try to connect with retry logic
    int attempt = 0;
    
    while (attempt < m_maxReconnectAttempts) {
        // Create new Modbus context
        m_context = modbus_new_tcp(m_address.toUtf8().constData(), m_port);
        
        if (!m_context) {
            qWarning("Modbus context creation failed (attempt %d/%d)", 
                     attempt + 1, m_maxReconnectAttempts);
            QThread::msleep(1000);
            attempt++;
            continue;
        }
        
        // Enable debug and quirks mode
        if (m_debugEnabled) {
            modbus_set_debug(m_context, TRUE);
        }
        modbus_enable_quirks(m_context, TRUE);
        
        // Attempt connection
        if (modbus_connect(m_context) == -1) {
            qWarning("Modbus connection failed (attempt %d/%d): %s",
                     attempt + 1, m_maxReconnectAttempts, modbus_strerror(errno));
            modbus_free(m_context);
            m_context = nullptr;
            QThread::msleep(1000);
            attempt++;
            continue;
        }
        
        // Success!
        qDebug() << "Modbus connection successful to" << m_address << ":" << m_port;
        m_connected = true;
        emit connectionStateChanged(true);
        return Result<void>::success();
    }
    
    // All attempts failed
    QString errorMsg = QString("Failed to connect to Modbus after %1 attempts").arg(m_maxReconnectAttempts);
    emit errorOccurred(errorMsg);
    return Result<void>::failure(errorMsg);
}

void ModbusService::disconnect() {
    if (m_connected && m_context) {
        modbus_close(m_context);
        m_connected = false;
        emit connectionStateChanged(false);
    }
    cleanupModbusContext();
}

void ModbusService::cleanupModbusContext() {
    if (m_context) {
        modbus_free(m_context);
        m_context = nullptr;
    }
}

bool ModbusService::isConnected() const {
    return m_connected;
}

Result<QVariant> ModbusService::read(const QString& tag) {
    // Look up address for this tag
    if (!m_tagToAddressMap.contains(tag)) {
        return Result<QVariant>::failure(QString("Unknown tag: %1").arg(tag));
    }
    
    int address = m_tagToAddressMap[tag];
    auto result = readInputRegister(address);
    
    if (result.isSuccess()) {
        return Result<QVariant>::success(QVariant(result.value()));
    } else {
        return Result<QVariant>::failure(result.error());
    }
}

Result<uint16_t> ModbusService::readInputRegister(int address) {
    if (!m_connected || !m_context) {
        return Result<uint16_t>::failure("Not connected to Modbus controller");
    }
    
    uint16_t reg[1] = {0};
    int rc = modbus_read_input_registers(m_context, address, 1, reg);
    
    if (rc == 1) {
        // Success
        return Result<uint16_t>::success(reg[0]);
    } else {
        // Handle connection errors
        int err = errno;
        QString errorMsg = QString("Modbus read failed: %1").arg(modbus_strerror(err));
        
        // Check if we need to reconnect
        if (err == ECONNRESET || err == ETIMEDOUT || err == ENOTCONN || err == EBADF) {
            qWarning() << "Connection lost, attempting reconnection...";
            m_connected = false;
            emit connectionStateChanged(false);
            
            // Trigger reconnection attempt
            QMetaObject::invokeMethod(this, "attemptReconnection", Qt::QueuedConnection);
        }
        
        emit errorOccurred(errorMsg);
        return Result<uint16_t>::failure(errorMsg);
    }
}

Result<uint16_t> ModbusService::readHoldingRegister(int address) {
    if (!m_connected || !m_context) {
        return Result<uint16_t>::failure("Not connected to Modbus controller");
    }
    
    uint16_t reg[1] = {0};
    int rc = modbus_read_registers(m_context, address, 1, reg);
    
    if (rc == 1) {
        return Result<uint16_t>::success(reg[0]);
    } else {
        QString errorMsg = QString("Modbus read failed: %1").arg(modbus_strerror(errno));
        emit errorOccurred(errorMsg);
        return Result<uint16_t>::failure(errorMsg);
    }
}

Result<void> ModbusService::writeSingleRegister(int address, uint16_t value) {
    if (!m_connected || !m_context) {
        return Result<void>::failure("Not connected to Modbus controller");
    }
    
    int rc = modbus_write_register(m_context, address, value);
    
    if (rc == 1) {
        return Result<void>::success();
    } else {
        QString errorMsg = QString("Modbus write failed: %1").arg(modbus_strerror(errno));
        emit errorOccurred(errorMsg);
        return Result<void>::failure(errorMsg);
    }
}

void ModbusService::startPolling(int intervalMs) {
    if (!m_pollTimer->isActive()) {
        m_pollTimer->start(intervalMs);
        qDebug() << "Modbus polling started with interval:" << intervalMs << "ms";
    }
}

void ModbusService::stopPolling() {
    if (m_pollTimer->isActive()) {
        m_pollTimer->stop();
        qDebug() << "Modbus polling stopped";
    }
}

void ModbusService::onPollTimerTimeout() {
    // Poll all registered tags
    for (auto it = m_tagToAddressMap.constBegin(); it != m_tagToAddressMap.constEnd(); ++it) {
        const QString& tag = it.key();
        int address = it.value();
        
        auto result = readInputRegister(address);
        if (result.isSuccess()) {
            emit dataReady(tag, QVariant(result.value()));
        }
    }
}

void ModbusService::attemptReconnection() {
    qDebug() << "Attempting Modbus reconnection...";
    
    // Cleanup old context
    cleanupModbusContext();
    
    // Try to reconnect
    auto result = connectInternal();
    
    if (result.isSuccess()) {
        qDebug() << "Modbus reconnection successful";
    } else {
        qWarning() << "Modbus reconnection failed:" << result.error();
    }
}

void ModbusService::setDebugEnabled(bool enabled) {
    m_debugEnabled = enabled;
    if (m_context) {
        modbus_set_debug(m_context, enabled ? TRUE : FALSE);
    }
}
