#include "datawidget.h"
#include <QGraphicsDropShadowEffect>
#include <QEasingCurve>
#include <QRandomGenerator>

DataWidget::DataWidget(const QString &title, const QString &unit, QWidget *parent)
    : QWidget(parent)
    , m_title(title)
    , m_unit(unit)
    , m_currentValue(0)
    , m_targetValue(0)
    , m_glowIntensity(0.5)
    , m_valueAnimation(nullptr)
    , m_glowAnimation(nullptr)
{
    setupUI();
    setupStyling();
    startGlowAnimation();
}

DataWidget::~DataWidget()
{
    // Stop and delete animations to prevent segfault
    if (m_glowAnimation) {
        m_glowAnimation->stop();
        delete m_glowAnimation;
        m_glowAnimation = nullptr;
    }
    
    if (m_valueAnimation) {
        m_valueAnimation->stop();
        delete m_valueAnimation;
        m_valueAnimation = nullptr;
    }
}

void DataWidget::setupUI()
{
    setMinimumSize(200, 120);
    setMaximumSize(250, 150);
    
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(5);
    m_layout->setContentsMargins(10, 10, 10, 10);
    
    // Title label
    m_titleLabel = new QLabel(m_title);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setObjectName("dataTitle");
    
    // Value label
    m_valueLabel = new QLabel("0");
    m_valueLabel->setAlignment(Qt::AlignCenter);
    m_valueLabel->setObjectName("dataValue");
    
    // Unit label
    m_unitLabel = new QLabel(m_unit);
    m_unitLabel->setAlignment(Qt::AlignCenter);
    m_unitLabel->setObjectName("dataUnit");
    
    // Progress bar
    m_progressBar = new QProgressBar;
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(0);
    m_progressBar->setTextVisible(false);
    m_progressBar->setObjectName("dataProgress");
    
    m_layout->addWidget(m_titleLabel);
    m_layout->addWidget(m_valueLabel);
    m_layout->addWidget(m_unitLabel);
    m_layout->addWidget(m_progressBar);
    
    // Add glow effect
    m_glowEffect = new QGraphicsDropShadowEffect;
    m_glowEffect->setBlurRadius(15);
    m_glowEffect->setColor(QColor(0, 170, 255, 100));
    m_glowEffect->setOffset(0, 0);
    setGraphicsEffect(m_glowEffect);
}

void DataWidget::setupStyling()
{
    QString styleSheet = R"(
        DataWidget {
            background-color: #001133;
            border: 2px solid #0066cc;
            border-radius: 10px;
        }
        
        QLabel#dataTitle {
            font-size: 12px;
            font-weight: bold;
            color: #88aaff;
            background-color: transparent;
        }
        
        QLabel#dataValue {
            font-size: 24px;
            font-weight: bold;
            color: #00aaff;
            background-color: transparent;
            font-family: 'Courier New', monospace;
        }
        
        QLabel#dataUnit {
            font-size: 10px;
            color: #6699ff;
            background-color: transparent;
        }
        
        QProgressBar#dataProgress {
            border: 1px solid #004488;
            border-radius: 3px;
            background-color: #000022;
            height: 8px;
        }
        
        QProgressBar#dataProgress::chunk {
            background: qlineargradient(x1:0, y1:0, x2:1, y2:0,
                stop:0 #0066cc, stop:0.5 #00aaff, stop:1 #66ccff);
            border-radius: 3px;
        }
    )";
    
    setStyleSheet(styleSheet);
}

void DataWidget::setValue(int value)
{
    m_targetValue = qBound(0, value, 100);
    
    // Use a simple direct update instead of animation to avoid issues
    m_currentValue = m_targetValue;
    updateDisplay();
}

void DataWidget::updateDisplay()
{
    // Simple direct update without animation
    m_currentValue = m_targetValue;
    
    if (m_valueLabel) {
        m_valueLabel->setText(QString::number(m_currentValue));
    }
    if (m_progressBar) {
        m_progressBar->setValue(m_currentValue);
    }
    
    // Change color based on value
    QString color;
    if (m_currentValue >= 80) {
        color = "#00ff88"; // Green for good values
    } else if (m_currentValue >= 50) {
        color = "#00aaff"; // Blue for normal values
    } else if (m_currentValue >= 30) {
        color = "#ffaa00"; // Orange for warning
    } else {
        color = "#ff4444"; // Red for critical
    }
    
    m_valueLabel->setStyleSheet(QString("color: %1;").arg(color));
}

void DataWidget::setGlowIntensity(qreal intensity)
{
    m_glowIntensity = intensity;
    if (m_glowEffect) {
        int alpha = static_cast<int>(intensity * 150);
        m_glowEffect->setColor(QColor(0, 170, 255, alpha));
    }
}

void DataWidget::startGlowAnimation()
{
    m_glowAnimation = new QPropertyAnimation(this, "glowIntensity", this);
    m_glowAnimation->setDuration(3000);
    m_glowAnimation->setStartValue(0.3);
    m_glowAnimation->setEndValue(1.0);
    m_glowAnimation->setEasingCurve(QEasingCurve::InOutSine);
    m_glowAnimation->setLoopCount(-1); // Infinite loop
    m_glowAnimation->start();
}
