#include "graphviewmodel.h"
#include "../services/modbusservice.h"
#include <QDebug>

GraphViewModel::GraphViewModel(ModbusService* modbusService, QObject* parent)
    : QObject(parent)
    , m_modbusService(modbusService)
    , m_currentEegValue(0.0)
    , m_lastDataPoint()
    , m_isPolling(false)
{
    if (!m_modbusService) {
        qWarning() << "GraphViewModel: modbusService is nullptr!";
        return;
    }
    
    // Connect to Modbus service signals
    connect(m_modbusService, &ModbusService::dataReady,
            this, &GraphViewModel::onDataSourceDataReady);
    connect(m_modbusService, &ModbusService::errorOccurred,
            this, &GraphViewModel::onDataSourceError);
    connect(m_modbusService, &ModbusService::connectionStateChanged,
            this, &GraphViewModel::onDataSourceConnectionChanged);
}

GraphViewModel::~GraphViewModel() {
    stopPolling();
}

void GraphViewModel::startPolling(int intervalMs) {
    if (m_modbusService && !m_isPolling) {
        m_modbusService->startPolling(intervalMs);
        m_isPolling = true;
        qDebug() << "GraphViewModel: Started polling with interval" << intervalMs << "ms";
    }
}

void GraphViewModel::stopPolling() {
    if (m_modbusService && m_isPolling) {
        m_modbusService->stopPolling();
        m_isPolling = false;
        qDebug() << "GraphViewModel: Stopped polling";
    }
}

bool GraphViewModel::isPolling() const {
    return m_isPolling;
}

void GraphViewModel::onDataSourceDataReady(const QString& tag, const QVariant& value) {
    // Check if this is EEG data (could be expanded to handle other tags)
    if (tag == "EEG" || tag == "25") {  // Tag "25" is the Modbus address
        // Get raw value and scale it
        uint16_t rawValue = value.toUInt();
        double scaledValue = scaleEegValue(rawValue);
        
        // Update current value
        m_currentEegValue = scaledValue;
        
        // Create data point
        m_lastDataPoint = DataPoint(tag, scaledValue);
        
        // Emit signals
        emit eegDataUpdated(scaledValue);
        emit dataPointReceived(m_lastDataPoint);
        
        qDebug() << "GraphViewModel: EEG data updated -" 
                 << "Raw:" << rawValue 
                 << "Scaled:" << scaledValue;
    }
}

void GraphViewModel::onDataSourceError(const QString& error) {
    qWarning() << "GraphViewModel: Data source error:" << error;
    emit errorOccurred(error);
}

void GraphViewModel::onDataSourceConnectionChanged(bool connected) {
    qDebug() << "GraphViewModel: Connection state changed:" << connected;
    emit connectionStateChanged(connected);
}

double GraphViewModel::scaleEegValue(uint16_t rawValue) const {
    // Scale EEG value by dividing by 10
    // This is the business logic rule for EEG data
    return rawValue / 10.0;
}
