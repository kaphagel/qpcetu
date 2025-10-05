// GraphsPage implementation
#include "graphspage.h"
#include "../graphwidget.h"
#include "../mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QThread>

GraphsPage::GraphsPage(QWidget *parent) : QWidget(parent) {
    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->setSpacing(4);
    mainLayout->setContentsMargins(8, 8, 8, 8);

    // Create 4 graphs for 2x2 grid
    m_eegGraph = new GraphWidget("EEG Waveform", GraphWidget::SineWave, this);
    m_eegGraph->setRange(0, 120);
    m_eegGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_eegGraph, 0, 0);

    m_graph2 = new GraphWidget("Shield Harmonics", GraphWidget::RandomData, this);
    m_graph2->setRange(20, 100);
    m_graph2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_graph2, 0, 1);

    m_graph3 = new GraphWidget("System Status", GraphWidget::StepFunction, this);
    m_graph3->setRange(0, 100);
    m_graph3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_graph3, 1, 0);

    m_graph4 = new GraphWidget("Network Traffic", GraphWidget::PulseWave, this);
    m_graph4->setRange(0, 100);
    m_graph4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    mainLayout->addWidget(m_graph4, 1, 1);

    this->setLayout(mainLayout);

    // Modbus TCP setup
    int maxAttempts = 5;
    int attempt = 0;
    while (attempt < maxAttempts) {
        m_modbusCtx = modbus_new_tcp("192.168.10.243", 502);
        if (m_modbusCtx) {
            modbus_set_debug(m_modbusCtx, TRUE);
            modbus_enable_quirks(m_modbusCtx, TRUE);
            if (modbus_connect(m_modbusCtx) == -1) {
                qWarning("Modbus connection failed (attempt %d): %s", attempt+1, modbus_strerror(errno));
                modbus_free(m_modbusCtx);
                m_modbusCtx = nullptr;
                QThread::msleep(1000); // Wait 1s before retry
            } else {
                qWarning("Modbus connection succeeded (attempt %d)", attempt+1);
                break;
            }
        } else {
            qWarning("Modbus context creation failed (attempt %d)", attempt+1);
            QThread::msleep(1000);
        }
        ++attempt;
    }

    // Timer for polling EEG value
    m_pollTimer = new QTimer(this);
    connect(m_pollTimer, &QTimer::timeout, this, &GraphsPage::pollEEG);
    m_pollTimer->start(1000); // 1 second interval

    this->setLayout(mainLayout);
}

void GraphsPage::pollEEG() {
    if (!m_modbusCtx) return;
    uint16_t reg[1] = {0};
    int rc = modbus_read_input_registers(m_modbusCtx, 25, 1, reg); // Input register 25 (decimal)
    if (rc == 1) {
        qreal scaledValue = reg[0] / 10.0;
        m_eegGraph->addDataPoint(scaledValue);
    } else {
        int err = errno;
        // Attempt to fully reset and robustly reconnect Modbus context if connection error
        if (err == ECONNRESET || err == ETIMEDOUT || err == ENOTCONN || err == EBADF) {
            qWarning("Attempting full Modbus context reset and robust reconnect...");
            if (m_modbusCtx) {
                modbus_close(m_modbusCtx);
                modbus_free(m_modbusCtx);
                m_modbusCtx = nullptr;
            }
            int maxAttempts = 5;
            int attempt = 0;
            while (attempt < maxAttempts) {
                m_modbusCtx = modbus_new_tcp("192.168.10.243", 502);
                if (m_modbusCtx) {
                    modbus_set_debug(m_modbusCtx, TRUE);
                    modbus_enable_quirks(m_modbusCtx, TRUE);
                    if (modbus_connect(m_modbusCtx) == -1) {
                        qWarning("Modbus reconnect failed (attempt %d): %s", attempt+1, modbus_strerror(errno));
                        modbus_free(m_modbusCtx);
                        m_modbusCtx = nullptr;
                        QThread::msleep(1000); // Wait 1s before retry
                    } else {
                        qWarning("Modbus reconnect succeeded (attempt %d)", attempt+1);
                        break;
                    }
                } else {
                    qWarning("Modbus context creation failed (attempt %d)", attempt+1);
                    QThread::msleep(1000);
                }
                ++attempt;
            }
        }
    }
}
