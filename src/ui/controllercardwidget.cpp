#include "controllercardwidget.h"
#include <QPainter>
#include <QPainterPath>
#include <QDateTime>
#include <QDebug>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

ControllerCardWidget::ControllerCardWidget(const QString &controllerType,
                                           const QString &ipAddress,
                                           QWidget *parent)
    : QWidget(parent), m_controllerType(controllerType), m_ipAddress(ipAddress), m_status(Disconnected), m_statusColor(QColor(100, 100, 100)), m_temperature(0.0), m_powerConsumption(0.0), m_connectionQuality(0), m_lastSeen(QDateTime::currentDateTime()), m_isHovered(false), m_pulseValue(0)
{
    setupUI();
    setupStyling();
    updateStatusIndicator();

    // Setup pulse animation for active controllers
    m_pulseTimer = new QTimer(this);
    connect(m_pulseTimer, &QTimer::timeout, this, &ControllerCardWidget::updatePulseAnimation);

    m_pulseAnimation = new QPropertyAnimation(this, "statusColor", this);
    m_pulseAnimation->setDuration(2000);
    m_pulseAnimation->setLoopCount(-1);

    setFixedSize(320, 220); // Increased from 280x180 for touch
    updateLastSeen();
}

void ControllerCardWidget::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(16, 16, 16, 16); // Increased margins for touch
    m_mainLayout->setSpacing(12);                     // Increased spacing for touch

    // Header with icon, type, and status
    m_headerLayout = new QHBoxLayout();
    m_headerLayout->setSpacing(12); // Increased spacing for touch

    m_iconLabel = new QLabel();
    m_iconLabel->setFixedSize(40, 40); // Increased from 32x32 for touch
    m_iconLabel->setAlignment(Qt::AlignCenter);
    m_iconLabel->setStyleSheet(
        "QLabel { "
        "  font-size: 22px; " // Increased from 18px
        "  color: #00E5FF; "
        "  background-color: rgba(0, 229, 255, 0.1); "
        "  border: 1px solid #00E5FF; "
        "  border-radius: 16px; "
        "}");
    m_iconLabel->setText(getControllerIcon());

    m_typeLabel = new QLabel(m_controllerType);
    m_typeLabel->setStyleSheet(
        "QLabel { "
        "  font-size: 14px; "
        "  font-weight: bold; "
        "  color: #FFFFFF; "
        "}");

    m_statusIndicator = new QLabel();
    m_statusIndicator->setFixedSize(16, 16); // Increased from 12x12 for touch
    m_statusIndicator->setStyleSheet(
        "QLabel { "
        "  border-radius: 8px; " // Updated radius
        "  background-color: #666666; "
        "}");

    m_headerLayout->addWidget(m_iconLabel);
    m_headerLayout->addWidget(m_typeLabel);
    m_headerLayout->addStretch();
    m_headerLayout->addWidget(m_statusIndicator);

    // IP Address
    m_ipLabel = new QLabel(m_ipAddress);
    m_ipLabel->setStyleSheet(
        "QLabel { "
        "  font-size: 12px; "
        "  color: #B0BEC5; "
        "  font-family: 'Courier New', monospace; "
        "}");

    // Metrics section
    m_metricsLayout = new QHBoxLayout();
    m_metricsLayout->setSpacing(12);

    // Temperature
    QVBoxLayout *tempLayout = new QVBoxLayout();
    tempLayout->setSpacing(4); // Increased spacing for touch
    QLabel *tempTitle = new QLabel("🌡️ TEMP");
    tempTitle->setStyleSheet("QLabel { font-size: 12px; color: #78909C; }"); // Increased from 9px
    m_temperatureLabel = new QLabel("--°C");
    m_temperatureLabel->setStyleSheet("QLabel { font-size: 16px; color: #FFFFFF; font-weight: bold; }"); // Increased from 12px
    tempLayout->addWidget(tempTitle);
    tempLayout->addWidget(m_temperatureLabel);

    // Power
    QVBoxLayout *powerLayout = new QVBoxLayout();
    powerLayout->setSpacing(4); // Increased spacing for touch
    QLabel *powerTitle = new QLabel("⚡ POWER");
    powerTitle->setStyleSheet("QLabel { font-size: 12px; color: #78909C; }"); // Increased from 9px
    m_powerLabel = new QLabel("-- kW");
    m_powerLabel->setStyleSheet("QLabel { font-size: 16px; color: #FFFFFF; font-weight: bold; }"); // Increased from 12px
    powerLayout->addWidget(powerTitle);
    powerLayout->addWidget(m_powerLabel);

    // Connection Quality
    QVBoxLayout *connLayout = new QVBoxLayout();
    connLayout->setSpacing(4); // Increased spacing for touch
    QLabel *connTitle = new QLabel("📶 SIGNAL");
    connTitle->setStyleSheet("QLabel { font-size: 12px; color: #78909C; }"); // Increased from 9px
    m_connectionBar = new QProgressBar();
    m_connectionBar->setFixedHeight(12); // Increased from 8px for touch
    m_connectionBar->setRange(0, 100);
    m_connectionBar->setValue(0);
    m_connectionBar->setStyleSheet(
        "QProgressBar { "
        "  border: 1px solid #37474F; "
        "  border-radius: 4px; "
        "  background-color: #263238; "
        "} "
        "QProgressBar::chunk { "
        "  background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, "
        "    stop:0 #4CAF50, stop:0.7 #8BC34A, stop:1 #CDDC39); "
        "  border-radius: 3px; "
        "}");
    connLayout->addWidget(connTitle);
    connLayout->addWidget(m_connectionBar);

    m_metricsLayout->addLayout(tempLayout);
    m_metricsLayout->addLayout(powerLayout);
    m_metricsLayout->addLayout(connLayout);

    // Last seen
    m_lastSeenLabel = new QLabel();
    m_lastSeenLabel->setStyleSheet(
        "QLabel { "
        "  font-size: 13px; " // Increased from 10px for touch
        "  color: #607D8B; "
        "}");

    // Action buttons
    m_actionsLayout = new QHBoxLayout();
    m_actionsLayout->setSpacing(12); // Increased spacing for touch

    m_configureButton = new QPushButton("⚙️");
    m_configureButton->setFixedSize(36, 36); // Increased from 24x24 for touch
    m_configureButton->setToolTip("Configure Controller");
    m_configureButton->setStyleSheet(
        "QPushButton { "
        "  background-color: rgba(0, 229, 255, 0.1); "
        "  border: 1px solid #00E5FF; "
        "  border-radius: 18px; " // Updated radius
        "  color: #00E5FF; "
        "  font-size: 16px; " // Increased from 12px
        "} "
        "QPushButton:hover { "
        "  background-color: rgba(0, 229, 255, 0.2); "
        "} "
        "QPushButton:pressed { "
        "  background-color: rgba(0, 229, 255, 0.3); "
        "  border: 2px solid #00E5FF; " // Touch feedback
        "}");

    m_diagnosticsButton = new QPushButton("🔧");
    m_diagnosticsButton->setFixedSize(36, 36); // Increased from 24x24 for touch
    m_diagnosticsButton->setToolTip("Run Diagnostics");
    m_diagnosticsButton->setStyleSheet(m_configureButton->styleSheet());

    connect(m_configureButton, &QPushButton::clicked, this, &ControllerCardWidget::onConfigureClicked);
    connect(m_diagnosticsButton, &QPushButton::clicked, this, &ControllerCardWidget::onDiagnosticsClicked);

    m_actionsLayout->addStretch();
    m_actionsLayout->addWidget(m_configureButton);
    m_actionsLayout->addWidget(m_diagnosticsButton);

    // Add all layouts to main
    m_mainLayout->addLayout(m_headerLayout);
    m_mainLayout->addWidget(m_ipLabel);
    m_mainLayout->addSpacing(4);
    m_mainLayout->addLayout(m_metricsLayout);
    m_mainLayout->addWidget(m_lastSeenLabel);
    m_mainLayout->addLayout(m_actionsLayout);
}

void ControllerCardWidget::setupStyling()
{
    setStyleSheet(
        "ControllerCardWidget { "
        "  background-color: qlineargradient(x1:0, y1:0, x2:0, y2:1, "
        "    stop:0 #2D2D2D, stop:1 #1A1A1A); "
        "  border: 1px solid #37474F; "
        "  border-radius: 8px; "
        "}");

    // Add subtle shadow effect
    m_shadowEffect = new QGraphicsDropShadowEffect(this);
    m_shadowEffect->setBlurRadius(10);
    m_shadowEffect->setColor(QColor(0, 0, 0, 50));
    m_shadowEffect->setOffset(2, 2);
    setGraphicsEffect(m_shadowEffect);
}

void ControllerCardWidget::setStatus(ControllerStatus status)
{
    if (m_status != status)
    {
        m_status = status;
        updateStatusIndicator();
        animateStatusChange();
        updateLastSeen();

        // Start/stop pulse animation based on status
        if (status == Running || status == Connected)
        {
            m_pulseTimer->start(100);
        }
        else
        {
            m_pulseTimer->stop();
        }
    }
}

void ControllerCardWidget::setStatusColor(const QColor &color)
{
    m_statusColor = color;
    update();
}

void ControllerCardWidget::setTemperature(double temp)
{
    m_temperature = temp;
    m_temperatureLabel->setText(QString("%1°C").arg(temp, 0, 'f', 1));

    // Color code temperature
    if (temp > 80)
    {
        m_temperatureLabel->setStyleSheet("QLabel { color: #F44336; font-weight: bold; }");
    }
    else if (temp > 60)
    {
        m_temperatureLabel->setStyleSheet("QLabel { color: #FF9800; font-weight: bold; }");
    }
    else
    {
        m_temperatureLabel->setStyleSheet("QLabel { color: #4CAF50; font-weight: bold; }");
    }
}

void ControllerCardWidget::setPowerConsumption(double power)
{
    m_powerConsumption = power;
    m_powerLabel->setText(QString("%1 kW").arg(power, 0, 'f', 1));
}

void ControllerCardWidget::setConnectionQuality(int quality)
{
    m_connectionQuality = quality;
    m_connectionBar->setValue(quality);
}

void ControllerCardWidget::updateLastSeen()
{
    m_lastSeen = QDateTime::currentDateTime();
    m_lastSeenLabel->setText(QString("Last seen: %1").arg(m_lastSeen.toString("hh:mm:ss")));
}

void ControllerCardWidget::updateStatusIndicator()
{
    QColor color = getStatusColor();
    m_statusIndicator->setStyleSheet(
        QString("QLabel { "
                "  border-radius: 6px; "
                "  background-color: %1; "
                "}")
            .arg(color.name()));

    // Update icon color based on status
    QString iconColor = (m_status == Running || m_status == Connected) ? "#4CAF50" : "#78909C";
    m_iconLabel->setStyleSheet(
        QString("QLabel { "
                "  font-size: 18px; "
                "  color: %1; "
                "  background-color: rgba(0, 229, 255, 0.1); "
                "  border: 1px solid %1; "
                "  border-radius: 16px; "
                "}")
            .arg(iconColor));
}

void ControllerCardWidget::animateStatusChange()
{
    // Animate the status indicator with a pulse effect
    QColor startColor = getStatusColor();
    QColor endColor = startColor.lighter(150);

    m_pulseAnimation->setStartValue(startColor);
    m_pulseAnimation->setEndValue(endColor);
    m_pulseAnimation->start();
}

void ControllerCardWidget::updatePulseAnimation()
{
    m_pulseValue = (m_pulseValue + 5) % 100;
    if (m_status == Running || m_status == Connected)
    {
        int alpha = 100 + (sin(m_pulseValue * M_PI / 50.0) * 50);
        QColor pulseColor = getStatusColor();
        pulseColor.setAlpha(alpha);
        m_statusIndicator->setStyleSheet(
            QString("QLabel { "
                    "  border-radius: 6px; "
                    "  background-color: %1; "
                    "}")
                .arg(pulseColor.name()));
    }
}

QString ControllerCardWidget::getStatusText() const
{
    switch (m_status)
    {
    case Disconnected:
        return "Disconnected";
    case Connecting:
        return "Connecting";
    case Connected:
        return "Connected";
    case Running:
        return "Running";
    case Warning:
        return "Warning";
    case Error:
        return "Error";
    default:
        return "Unknown";
    }
}

QColor ControllerCardWidget::getStatusColor() const
{
    switch (m_status)
    {
    case Disconnected:
        return QColor(97, 97, 97); // Gray
    case Connecting:
        return QColor(255, 193, 7); // Amber
    case Connected:
        return QColor(76, 175, 80); // Green
    case Running:
        return QColor(76, 175, 80); // Green
    case Warning:
        return QColor(255, 152, 0); // Orange
    case Error:
        return QColor(244, 67, 54); // Red
    default:
        return QColor(97, 97, 97);
    }
}

QString ControllerCardWidget::getControllerIcon() const
{
    if (m_controllerType.contains("EPIC", Qt::CaseInsensitive))
    {
        return "🔷";
    }
    else if (m_controllerType.contains("SNAP", Qt::CaseInsensitive))
    {
        return "🔸";
    }
    else
    {
        return "🎛️";
    }
}

void ControllerCardWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw card background with gradient
    QPainterPath path;
    path.addRoundedRect(rect().adjusted(1, 1, -1, -1), 8, 8);

    QLinearGradient gradient(0, 0, 0, height());
    if (m_isHovered)
    {
        gradient.setColorAt(0, QColor(50, 50, 50));
        gradient.setColorAt(1, QColor(30, 30, 30));
    }
    else
    {
        gradient.setColorAt(0, QColor(45, 45, 45));
        gradient.setColorAt(1, QColor(26, 26, 26));
    }

    painter.fillPath(path, gradient);

    // Draw border
    QPen borderPen(QColor(55, 71, 79), 1);
    painter.setPen(borderPen);
    painter.drawPath(path);

    // Draw status accent line at top
    QColor accentColor = getStatusColor();
    QPen accentPen(accentColor, 3);
    painter.setPen(accentPen);
    painter.drawLine(8, 3, width() - 8, 3);
}

void ControllerCardWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        emit cardClicked(m_ipAddress);
    }
    QWidget::mousePressEvent(event);
}

void ControllerCardWidget::enterEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_isHovered = true;
    update();
}

void ControllerCardWidget::leaveEvent(QEvent *event)
{
    Q_UNUSED(event)
    m_isHovered = false;
    update();
}

void ControllerCardWidget::onConfigureClicked()
{
    emit configureRequested(m_ipAddress);
}

void ControllerCardWidget::onDiagnosticsClicked()
{
    emit diagnosticsRequested(m_ipAddress);
}