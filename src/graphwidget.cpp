#include "graphwidget.h"
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

GraphWidget::GraphWidget(const QString &title, GraphType graphType, QWidget *parent)
    : QWidget(parent), m_title(title), m_graphType(graphType)
{
    setMinimumSize(200, 150);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    
    // Initialize graph parameters
    setupUI();
    
    // Timer for data updates
    m_updateTimer = new QTimer(this);
    connect(m_updateTimer, &QTimer::timeout, this, &GraphWidget::generateData);
    m_updateTimer->start(100); // Update every 100ms for smooth animation
    
    // Initialize with some data
    for (int i = 0; i < 50; ++i) {
        m_dataPoints.append(generateInitialValue());
    }
}

GraphWidget::~GraphWidget()
{
    if (m_updateTimer) {
        m_updateTimer->stop();
        delete m_updateTimer;
        m_updateTimer = nullptr;
    }
}

void GraphWidget::setupUI()
{
    setMinimumSize(300, 150);
    setMaximumSize(400, 200);
    
    // Initialize sci-fi themed colors based on graph type
    switch (m_graphType) {
        case SineWave:
            m_graphColor = QColor(0, 255, 255); // Bright cyan for energy
            break;
        case RandomData:
            m_graphColor = QColor(255, 140, 0); // Bright orange for shield harmonics
            break;
        case StepFunction:
            m_graphColor = QColor(0, 255, 127); // Bright green/teal for system status
            break;
        case PulseWave:
            m_graphColor = QColor(255, 20, 60); // Bright red/pink for network traffic
            break;
    }
    
    m_gridColor = QColor(40, 80, 120, 80);  // Semi-transparent blue grid
    
    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(2);
    m_layout->setContentsMargins(5, 5, 5, 5);
    
    // Futuristic title label with bright colors
    m_titleLabel = new QLabel(m_title);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(QString(R"(
        QLabel {
            color: %1;
            font-family: 'Courier New', monospace;
            font-weight: bold;
            font-size: 11px;
            background-color: transparent;
            border: none;
            padding: 2px;
        }
    )").arg(m_graphColor.name()));
    
    m_layout->addWidget(m_titleLabel);
    m_layout->addStretch(); // Graph area takes remaining space
    
    // Dark sci-fi background
    setAutoFillBackground(true);
    QPalette pal = palette();
    pal.setColor(QPalette::Window, QColor(8, 12, 20)); // Very dark navy
    setPalette(pal);
    
    // Add subtle glow effect to the entire widget
    QGraphicsDropShadowEffect *glowEffect = new QGraphicsDropShadowEffect;
    glowEffect->setColor(QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 60));
    glowEffect->setBlurRadius(15);
    glowEffect->setOffset(0, 0);
    setGraphicsEffect(glowEffect);
}

void GraphWidget::addDataPoint(qreal value)
{
    m_dataPoints.append(qBound(m_minValue, value, m_maxValue));
    
    // Keep only the last N data points for performance
    if (m_dataPoints.size() > m_maxDataPoints) {
        m_dataPoints.removeFirst();
    }
    
    update(); // Trigger repaint
}

void GraphWidget::setColor(const QColor &color)
{
    m_graphColor = color;
    update();
}

void GraphWidget::setRange(qreal min, qreal max)
{
    m_minValue = min;
    m_maxValue = max;
    update();
}

void GraphWidget::generateData()
{
    qreal newValue = generateNextValue();
    addDataPoint(newValue);
    m_time += 0.1;
}

qreal GraphWidget::generateInitialValue()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    
    switch (m_graphType) {
        case SineWave:
            return m_offset + (rng->bounded(20) - 10); // Start near center with some variation
            
        case RandomData:
            return m_minValue + rng->bounded(int(m_maxValue - m_minValue)); // Random starting point
            
        case StepFunction:
            return m_minValue + rng->bounded(int(m_maxValue - m_minValue)); // Random starting level
            
        case PulseWave:
            return rng->bounded(2) ? m_maxValue * 0.8 : m_minValue + 20; // Start high or low
    }
    
    return m_offset;
}

qreal GraphWidget::generateNextValue()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    
    switch (m_graphType) {
        case SineWave:
            return m_offset + m_amplitude * std::sin(m_frequency * m_time);
            
        case RandomData:
            // More dramatic random walk
            m_lastValue += (rng->bounded(40) - 20) * 1.5; // Larger changes: ±30
            m_lastValue = qBound(m_minValue, m_lastValue, m_maxValue);
            return m_lastValue;
            
        case StepFunction:
            // Step function that changes more frequently
            if (rng->bounded(100) < 8) { // 8% chance to change (was 3%)
                m_lastValue = m_minValue + rng->bounded(int(m_maxValue - m_minValue));
            }
            return m_lastValue;
            
        case PulseWave:
            // Square wave with clearer transitions
            return (int(m_time * 1.5) % 8 < 4) ? m_maxValue * 0.9 : m_minValue + 10;
    }
    
    return m_offset;
}

void GraphWidget::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event)
    
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    
    // Calculate graph area (leave space for title)
    QRect graphRect = rect().adjusted(10, 25, -10, -10);
    
    if (graphRect.width() < 50 || graphRect.height() < 50) {
        return; // Too small to draw
    }
    
    // Draw grid
    drawGrid(painter, graphRect);
    
    // Draw graph data
    drawGraph(painter, graphRect);
}

void GraphWidget::drawGrid(QPainter &painter, const QRect &graphRect)
{
    // Draw futuristic hexagonal grid pattern
    QPen gridPen(m_gridColor, 1);
    gridPen.setStyle(Qt::SolidLine);
    painter.setPen(gridPen);
    
    // Main grid lines with glow effect
    QPen mainGridPen(QColor(m_gridColor.red(), m_gridColor.green(), m_gridColor.blue(), 120), 1);
    painter.setPen(mainGridPen);
    
    // Vertical scan lines
    int verticalLines = 12;
    for (int i = 0; i <= verticalLines; ++i) {
        int x = graphRect.left() + (graphRect.width() * i) / verticalLines;
        painter.drawLine(x, graphRect.top(), x, graphRect.bottom());
    }
    
    // Horizontal scan lines
    int horizontalLines = 8;
    for (int i = 0; i <= horizontalLines; ++i) {
        int y = graphRect.top() + (graphRect.height() * i) / horizontalLines;
        painter.drawLine(graphRect.left(), y, graphRect.right(), y);
    }
    
    // Add futuristic corner brackets
    QPen bracketPen(m_graphColor, 2);
    painter.setPen(bracketPen);
    
    int bracketSize = 15;
    // Top-left bracket
    painter.drawLine(graphRect.left(), graphRect.top() + bracketSize, 
                    graphRect.left(), graphRect.top());
    painter.drawLine(graphRect.left(), graphRect.top(), 
                    graphRect.left() + bracketSize, graphRect.top());
    
    // Top-right bracket
    painter.drawLine(graphRect.right() - bracketSize, graphRect.top(), 
                    graphRect.right(), graphRect.top());
    painter.drawLine(graphRect.right(), graphRect.top(), 
                    graphRect.right(), graphRect.top() + bracketSize);
    
    // Bottom-left bracket
    painter.drawLine(graphRect.left(), graphRect.bottom() - bracketSize, 
                    graphRect.left(), graphRect.bottom());
    painter.drawLine(graphRect.left(), graphRect.bottom(), 
                    graphRect.left() + bracketSize, graphRect.bottom());
    
    // Bottom-right bracket
    painter.drawLine(graphRect.right() - bracketSize, graphRect.bottom(), 
                    graphRect.right(), graphRect.bottom());
    painter.drawLine(graphRect.right(), graphRect.bottom(), 
                    graphRect.right(), graphRect.bottom() - bracketSize);
    
    // Add subtle hexagonal pattern overlay
    QPen hexPen(QColor(m_gridColor.red(), m_gridColor.green(), m_gridColor.blue(), 40), 1);
    painter.setPen(hexPen);
    
    int hexSize = 20;
    for (int x = graphRect.left(); x < graphRect.right(); x += hexSize * 1.5) {
        for (int y = graphRect.top(); y < graphRect.bottom(); y += hexSize) {
            // Draw small hexagon
            QPolygonF hexagon;
            for (int i = 0; i < 6; ++i) {
                qreal angle = i * M_PI / 3.0;
                hexagon << QPointF(x + hexSize/3 * cos(angle), y + hexSize/3 * sin(angle));
            }
            painter.drawPolygon(hexagon);
        }
    }
}

void GraphWidget::drawGraph(QPainter &painter, const QRect &graphRect)
{
    if (m_dataPoints.size() < 2) {
        return;
    }
    
    // Calculate data points
    QVector<QPointF> points;
    qreal xStep = qreal(graphRect.width()) / qMax(1, m_dataPoints.size() - 1);
    qreal valueRange = qMax(1.0, m_maxValue - m_minValue);
    
    for (int i = 0; i < m_dataPoints.size(); ++i) {
        qreal x = graphRect.left() + i * xStep;
        qreal normalizedValue = (m_dataPoints[i] - m_minValue) / valueRange;
        normalizedValue = qBound(0.0, normalizedValue, 1.0);
        qreal y = graphRect.bottom() - (normalizedValue * graphRect.height());
        points.append(QPointF(x, y));
    }
    
    // ENHANCED GLOW EFFECT - Multiple layers
    // Outer glow (widest, most transparent)
    for (int glow = 8; glow >= 1; --glow) {
        QPen glowPen(m_graphColor, glow);
        int alpha = 255 / (glow + 1); // More dramatic falloff
        glowPen.setColor(QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), alpha));
        painter.setPen(glowPen);
        
        for (int i = 1; i < points.size(); ++i) {
            painter.drawLine(points[i-1], points[i]);
        }
    }
    
    // Core line (brightest)
    QPen corePen(m_graphColor.lighter(120), 1);
    painter.setPen(corePen);
    for (int i = 1; i < points.size(); ++i) {
        painter.drawLine(points[i-1], points[i]);
    }
    
    // Add energy particles/sparks at data points
    painter.setBrush(m_graphColor);
    painter.setPen(QPen(m_graphColor.lighter(150), 1));
    
    // Draw glowing data points (last 15 points)
    int startPoint = qMax(0, points.size() - 15);
    for (int i = startPoint; i < points.size(); ++i) {
        // Outer glow circle
        painter.setBrush(QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 60));
        painter.drawEllipse(points[i], 4, 4);
        
        // Inner bright core
        painter.setBrush(m_graphColor);
        painter.drawEllipse(points[i], 2, 2);
    }
    
    // Add scan line effect (moving vertical line)
    static qreal scanPosition = 0.0;
    scanPosition += 2.0;
    if (scanPosition > graphRect.width()) scanPosition = 0.0;
    
    QPen scanPen(QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 100), 2);
    painter.setPen(scanPen);
    qreal scanX = graphRect.left() + scanPosition;
    painter.drawLine(QPointF(scanX, graphRect.top()), QPointF(scanX, graphRect.bottom()));
    
    // Add subtle gradient fill under the curve
    if (points.size() > 2) {
        QPolygonF fillArea;
        fillArea << QPointF(graphRect.left(), graphRect.bottom()); // Start at bottom-left
        
        // Add all the data points
        for (const QPointF &point : points) {
            fillArea << point;
        }
        
        fillArea << QPointF(graphRect.right(), graphRect.bottom()); // End at bottom-right
        
        // Create gradient fill
        QLinearGradient gradient(graphRect.topLeft(), graphRect.bottomLeft());
        gradient.setColorAt(0.0, QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 40));
        gradient.setColorAt(1.0, QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 5));
        
        painter.setBrush(QBrush(gradient));
        painter.setPen(Qt::NoPen);
        painter.drawPolygon(fillArea);
    }
}
