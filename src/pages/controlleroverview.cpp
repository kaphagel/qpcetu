#include "controlleroverview.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QMouseEvent>
#include <QDebug>

ControllerOverview::ControllerOverview(ControllerManager *controllerManager, QWidget *parent)
    : QWidget(parent), m_controllerManager(controllerManager), m_refreshTimer(new QTimer(this))
{
    setupUI();

    // Connect controller manager signals
    connect(m_controllerManager, &ControllerManager::controllerAdded,
            this, &ControllerOverview::onControllerAdded);
    connect(m_controllerManager, &ControllerManager::controllerRemoved,
            this, &ControllerOverview::onControllerRemoved);
    connect(m_controllerManager, &ControllerManager::controllerUpdated,
            this, &ControllerOverview::onControllerUpdated);
    connect(m_controllerManager, &ControllerManager::statusChanged,
            this, &ControllerOverview::updateSummary);

    // Setup refresh timer
    m_refreshTimer->setInterval(5000); // Refresh every 5 seconds
    m_refreshTimer->setSingleShot(false);
    connect(m_refreshTimer, &QTimer::timeout, this, &ControllerOverview::updateSummary);
    m_refreshTimer->start();

    // Initial load
    refreshControllers();
}

void ControllerOverview::setupUI()
{
    setStyleSheet(R"(
        QWidget {
            background-color: #0a0a0a;
            color: #00ff41;
            font-family: 'Courier New', monospace;
        }
        QLabel {
            color: #00ff41;
        }
        QScrollArea {
            border: 2px solid #00ff41;
            border-radius: 8px;
            background-color: #0a0a0a;
        }
    )");

    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Summary label
    m_summaryLabel = new QLabel("Industrial Controller Overview");
    m_summaryLabel->setStyleSheet("font-size: 18px; font-weight: bold; margin: 10px;");
    m_summaryLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(m_summaryLabel);

    // Scroll area for controllers
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);

    m_contentWidget = new QWidget();
    m_gridLayout = new QGridLayout(m_contentWidget);
    m_gridLayout->setSpacing(15);
    m_gridLayout->setContentsMargins(15, 15, 15, 15);

    m_scrollArea->setWidget(m_contentWidget);
    mainLayout->addWidget(m_scrollArea);

    updateSummary();
}

void ControllerOverview::refreshControllers()
{
    // Clear existing widgets
    for (auto it = m_controllerWidgets.begin(); it != m_controllerWidgets.end(); ++it)
    {
        it.value()->deleteLater();
    }
    m_controllerWidgets.clear();

    // Add current controllers
    for (int i = 0; i < m_controllerManager->rowCount(); ++i)
    {
        QModelIndex index = m_controllerManager->index(i, 0);
        IndustrialController *controller = qvariant_cast<IndustrialController *>(
            m_controllerManager->data(index, ControllerManager::ControllerRole));

        if (controller)
        {
            onControllerAdded(controller);
        }
    }

    updateSummary();
}

void ControllerOverview::onControllerAdded(IndustrialController *controller)
{
    if (m_controllerWidgets.contains(controller))
    {
        return; // Already added
    }

    ControllerFaceplate *faceplate = new ControllerFaceplate(controller, this);
    connect(faceplate, &ControllerFaceplate::controllerSelected,
            [this](IndustrialController *ctrl)
            {
                qDebug() << "Controller selected:" << ctrl->typeDisplayName() << ctrl->ipAddress();
                // TODO: Open controller-specific HMI page
            });

    // Add to grid layout
    int row = m_controllerWidgets.size() / 3; // 3 columns
    int col = m_controllerWidgets.size() % 3;
    m_gridLayout->addWidget(faceplate, row, col);

    m_controllerWidgets[controller] = faceplate;
    updateSummary();
}

void ControllerOverview::onControllerRemoved(IndustrialController *controller)
{
    removeControllerWidget(controller);
    updateSummary();
}

void ControllerOverview::onControllerUpdated(IndustrialController *controller)
{
    // The faceplate will update itself via signals
    updateSummary();
}

void ControllerOverview::removeControllerWidget(IndustrialController *controller)
{
    if (m_controllerWidgets.contains(controller))
    {
        QWidget *widget = m_controllerWidgets.take(controller);
        m_gridLayout->removeWidget(widget);
        widget->deleteLater();
    }
}

void ControllerOverview::updateSummary()
{
    int total = m_controllerManager->controllerCount();
    int online = m_controllerManager->onlineCount();

    QString summaryText = QString("Industrial Controller Overview - %1 Controllers (%2 Online)")
                              .arg(total)
                              .arg(online);
    m_summaryLabel->setText(summaryText);
}

QString ControllerOverview::getStatusColor(IndustrialController::ConnectionStatus status)
{
    switch (status)
    {
    case IndustrialController::ONLINE:
        return "#00ff41";
    case IndustrialController::OFFLINE:
        return "#ff4444";
    case IndustrialController::TIMEOUT:
        return "#ffaa00";
    case IndustrialController::COMM_ERROR:
        return "#ff0000";
    case IndustrialController::DISCOVERING:
        return "#44aaff";
    default:
        return "#888888";
    }
}

QString ControllerOverview::getTypeIcon(IndustrialController::ControllerType type)
{
    switch (type)
    {
    case IndustrialController::EPIC4:
        return "🏭";
    case IndustrialController::EPIC5:
        return "🏭";
    case IndustrialController::SNAP_PAC:
        return "📡";
    case IndustrialController::CLICK_PLC:
        return "⚡";
    case IndustrialController::MODICON:
        return "🔧";
    case IndustrialController::COMPACT_LOGIX:
        return "⚙️";
    default:
        return "❓";
    }
}

// ControllerFaceplate implementation

ControllerFaceplate::ControllerFaceplate(IndustrialController *controller, QWidget *parent)
    : QWidget(parent), m_controller(controller)
{
    setupUI();
    setupConnections();
    updateDisplay();
}

void ControllerFaceplate::setupUI()
{
    setFixedSize(280, 200);
    setStyleSheet(R"(
        ControllerFaceplate {
            background-color: #1a1a1a;
            border: 2px solid #00ff41;
            border-radius: 10px;
            margin: 5px;
        }
        ControllerFaceplate:hover {
            background-color: #2a2a2a;
            border-color: #44ff44;
        }
        QLabel {
            color: #00ff41;
            background-color: transparent;
            font-family: 'Courier New', monospace;
        }
    )");

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->setSpacing(8);
    layout->setContentsMargins(15, 15, 15, 15);

    // Type and status header
    QHBoxLayout *headerLayout = new QHBoxLayout();
    m_typeLabel = new QLabel();
    m_typeLabel->setStyleSheet("font-size: 14px; font-weight: bold;");
    m_statusLabel = new QLabel();
    m_statusLabel->setAlignment(Qt::AlignRight);
    headerLayout->addWidget(m_typeLabel);
    headerLayout->addWidget(m_statusLabel);
    layout->addLayout(headerLayout);

    // IP Address
    m_ipLabel = new QLabel();
    m_ipLabel->setStyleSheet("font-size: 12px; color: #88ff88;");
    layout->addWidget(m_ipLabel);

    // Hostname
    m_hostnameLabel = new QLabel();
    m_hostnameLabel->setStyleSheet("font-size: 11px; color: #aaaaaa;");
    layout->addWidget(m_hostnameLabel);

    // Last seen
    m_lastSeenLabel = new QLabel();
    m_lastSeenLabel->setStyleSheet("font-size: 10px; color: #888888;");
    layout->addWidget(m_lastSeenLabel);

    // Signal strength
    m_signalLabel = new QLabel();
    m_signalLabel->setStyleSheet("font-size: 10px; color: #666666;");
    layout->addWidget(m_signalLabel);

    setCursor(Qt::PointingHandCursor);
}

void ControllerFaceplate::setupConnections()
{
    connect(m_controller, &IndustrialController::controllerChanged,
            this, &ControllerFaceplate::updateDisplay);
    connect(m_controller, &IndustrialController::statusChanged,
            this, &ControllerFaceplate::updateDisplay);
    connect(m_controller, &IndustrialController::dataUpdated,
            this, &ControllerFaceplate::updateDisplay);
}

void ControllerFaceplate::updateDisplay()
{
    m_typeLabel->setText(m_controller->typeDisplayName());

    QString statusText = m_controller->statusText();
    QString statusColor = "#00ff41";
    if (!m_controller->isOnline())
    {
        statusColor = "#ff4444";
    }
    m_statusLabel->setText(statusText);
    m_statusLabel->setStyleSheet(QString("color: %1; font-size: 11px;").arg(statusColor));

    m_ipLabel->setText(QString("IP: %1").arg(m_controller->ipAddress()));

    QString hostname = m_controller->hostname();
    if (hostname.isEmpty())
    {
        hostname = "No hostname";
    }
    m_hostnameLabel->setText(QString("Host: %1").arg(hostname));

    QString lastSeen = m_controller->lastSeen().toString("hh:mm:ss");
    m_lastSeenLabel->setText(QString("Last seen: %1").arg(lastSeen));

    QString signalText = QString("Signal: %1%").arg(m_controller->signalStrength());
    m_signalLabel->setText(signalText);
}

void ControllerFaceplate::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit controllerSelected(m_controller);
    }
    QWidget::mousePressEvent(event);
}

void ControllerFaceplate::enterEvent(QEvent *event)
{
    setStyleSheet(styleSheet() + "\nControllerFaceplate { background-color: #2a2a2a; }");
    QWidget::enterEvent(event);
}

void ControllerFaceplate::leaveEvent(QEvent *event)
{
    setStyleSheet(styleSheet().replace("background-color: #2a2a2a;", "background-color: #1a1a1a;"));
    QWidget::leaveEvent(event);
}

void ControllerFaceplate::onControllerClicked()
{
    emit controllerSelected(m_controller);
}