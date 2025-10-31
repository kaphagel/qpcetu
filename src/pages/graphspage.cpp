#include "graphspage.h"
#include "../graphwidget.h"
#include "../viewmodels/graphviewmodel.h"
#include "../services/modbusservice.h"
#include "../ui/thememanager.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDebug>

GraphsPage::GraphsPage(QWidget* parent) 
    : QWidget(parent)
    , m_viewModel(nullptr)
    , m_modbusService(new ModbusService(this))
    , m_eegGraph(nullptr)
    , m_graph2(nullptr)
    , m_graph3(nullptr)
    , m_graph4(nullptr)
    , m_mainLayout(nullptr)
    , m_themeManager(ThemeManager::instance())
{
    setupUI();
    
    // Create ViewModel with ModbusService
    m_viewModel = new GraphViewModel(m_modbusService, this);
    
    connectSignals();
    
    // Connect to Modbus controller
    auto connectResult = m_modbusService->connect("192.168.10.243", 502);
    if (connectResult.isSuccess()) {
        qDebug() << "GraphsPage: Successfully connected to Modbus controller";
        
        // Start polling EEG data (1 second interval)
        m_viewModel->startPolling(1000);
    } else {
        qWarning() << "GraphsPage: Failed to connect to Modbus:" << connectResult.error();
    }
    
    applyTheme();
}

GraphsPage::~GraphsPage() {
    // Qt parent-child relationship handles cleanup
    if (m_viewModel) {
        m_viewModel->stopPolling();
    }
}

void GraphsPage::setupUI() {
    // Create main layout
    QGridLayout* gridLayout = new QGridLayout;
    gridLayout->setSpacing(4);
    gridLayout->setContentsMargins(8, 8, 8, 8);

    // Create 4 graphs for 2x2 grid
    m_eegGraph = new GraphWidget("EEG Waveform", GraphWidget::SineWave, this);
    m_eegGraph->setRange(0, 120);
    m_eegGraph->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(m_eegGraph, 0, 0);

    m_graph2 = new GraphWidget("Shield Harmonics", GraphWidget::RandomData, this);
    m_graph2->setRange(20, 100);
    m_graph2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(m_graph2, 0, 1);

    m_graph3 = new GraphWidget("System Status", GraphWidget::StepFunction, this);
    m_graph3->setRange(0, 100);
    m_graph3->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(m_graph3, 1, 0);

    m_graph4 = new GraphWidget("Network Traffic", GraphWidget::PulseWave, this);
    m_graph4->setRange(0, 100);
    m_graph4->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    gridLayout->addWidget(m_graph4, 1, 1);

    setLayout(gridLayout);
}

void GraphsPage::connectSignals() {
    // ViewModel → View connections
    connect(m_viewModel, &GraphViewModel::eegDataUpdated,
            this, &GraphsPage::onEegDataUpdated);
    connect(m_viewModel, &GraphViewModel::errorOccurred,
            this, &GraphsPage::onErrorOccurred);
    connect(m_viewModel, &GraphViewModel::connectionStateChanged,
            this, &GraphsPage::onConnectionStateChanged);
    
    // Theme changes
    connect(m_themeManager, &ThemeManager::themeChanged,
            this, &GraphsPage::applyTheme);
}

void GraphsPage::applyTheme() {
    // Use ThemeManager for colors (RULE-070)
    QString bgColor = m_themeManager->color(ThemeManager::MainBackground).name();
    QString textColor = m_themeManager->color(ThemeManager::PrimaryText).name();
    
    setStyleSheet(QString(
        "QWidget { background-color: %1; color: %2; }"
    ).arg(bgColor, textColor));
}

void GraphsPage::onEegDataUpdated(double value) {
    // Update EEG graph with new data
    if (m_eegGraph) {
        m_eegGraph->addDataPoint(value);
    }
}

void GraphsPage::onErrorOccurred(const QString& error) {
    qWarning() << "GraphsPage: Error occurred:" << error;
    // Could show error in UI status bar or message box
    // For now, just log it
}

void GraphsPage::onConnectionStateChanged(bool connected) {
    qDebug() << "GraphsPage: Connection state changed:" << connected;
    // Could update UI to show connection status
}
