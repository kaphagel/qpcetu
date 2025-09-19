#include "animatedprogressbar.h"
#include <QLinearGradient>
#include <QEasingCurve>

AnimatedProgressBar::AnimatedProgressBar(QWidget *parent)
    : QProgressBar(parent)
    , m_animationOffset(0.0)
    , m_targetValue(0)
    , m_valueAnimation(nullptr)
    , m_flowAnimation(nullptr)
{
    setMinimum(0);
    setMaximum(100);
    setTextVisible(false);
    setValue(0); // Ensure initial value is 0
    setupAnimation();
    // Custom styling
    setStyleSheet(R"(
        QProgressBar {
            border: 2px solid #004488;
            border-radius: 5px;
            background-color: #000022;
            height: 16px;
        }
        
        QProgressBar::chunk {
            background-color: transparent;
            border-radius: 3px;
        }
    )");
}

AnimatedProgressBar::~AnimatedProgressBar()
{
    // Stop and delete animations to prevent segfault
    if (m_flowAnimation) {
        m_flowAnimation->stop();
        delete m_flowAnimation;
        m_flowAnimation = nullptr;
    }
    
    if (m_valueAnimation) {
        m_valueAnimation->stop();
        delete m_valueAnimation;
        m_valueAnimation = nullptr;
    }
}

void AnimatedProgressBar::setupAnimation()
{
    // Flow animation for the energy effect
    m_flowAnimation = new QPropertyAnimation(this, "animationOffset", this);
    m_flowAnimation->setDuration(2000);
    m_flowAnimation->setStartValue(0.0);
    m_flowAnimation->setEndValue(1.0);
    m_flowAnimation->setEasingCurve(QEasingCurve::Linear);
    m_flowAnimation->setLoopCount(-1); // Infinite
    m_flowAnimation->start();
}

void AnimatedProgressBar::setValue(int value)
{
    m_targetValue = qBound(0, value, 100);
    
    // Animate the value change smoothly
    if (!m_valueAnimation) {
        m_valueAnimation = new QPropertyAnimation(this, "value", this);
        m_valueAnimation->setDuration(1500);
        m_valueAnimation->setEasingCurve(QEasingCurve::OutCubic);
    }
    
    m_valueAnimation->stop();
    m_valueAnimation->setStartValue(QProgressBar::value());
    m_valueAnimation->setEndValue(m_targetValue);
    m_valueAnimation->start();
}

void AnimatedProgressBar::setAnimationOffset(qreal offset)
{
    m_animationOffset = offset;
    update(); // Trigger repaint
}

void AnimatedProgressBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    QRect barRect = rect().adjusted(2, 2, -2, -2);
    int progressWidth = (barRect.width() * value()) / maximum();
    QRect progressRect = QRect(barRect.x(), barRect.y(), progressWidth, barRect.height());
    
    // Draw background
    painter.fillRect(barRect, QColor(0, 0, 34));
    
    if (progressWidth > 0) {
        // Create animated gradient
        QLinearGradient gradient(progressRect.topLeft(), progressRect.topRight());
        
        qreal offset = m_animationOffset;
        QColor baseColor, lightColor, darkColor;
        
        // Color based on value
        if (value() >= 80) {
            baseColor = QColor(0, 255, 136);  // Green
            lightColor = QColor(136, 255, 200);
            darkColor = QColor(0, 200, 100);
        } else if (value() >= 50) {
            baseColor = QColor(0, 170, 255);  // Blue
            lightColor = QColor(102, 204, 255);
            darkColor = QColor(0, 100, 200);
        } else {
            baseColor = QColor(255, 68, 68);  // Red
            lightColor = QColor(255, 136, 136);
            darkColor = QColor(200, 0, 0);
        }
    
        // Draw border
        QPen borderPen(QColor(0, 68, 136), 2);
        painter.setPen(borderPen);
        painter.drawRect(barRect);
    } // end of paintEvent
}
