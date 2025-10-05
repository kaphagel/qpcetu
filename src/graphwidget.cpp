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

    m_maxDataPoints = 120; // Reasonable default for visible graph

    // Initialize graph parameters
    setupUI();
}

GraphWidget::~GraphWidget()
{
}

void GraphWidget::setupUI()
{
    setMinimumSize(400, 300);
    setMaximumSize(QWIDGETSIZE_MAX, QWIDGETSIZE_MAX);
    
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
    qDebug() << "addDataPoint:" << value;
    int bufferSize = width() > 0 && m_stepSize > 0 ? (width() - 20) / m_stepSize : m_maxDataPoints;
    if (m_dataPoints.size() < bufferSize) {
        m_dataPoints.append(value);
        m_bufferHead = m_dataPoints.size() - 1;
    } else {
        m_bufferHead = (m_bufferHead + 1) % bufferSize;
        m_dataPoints[m_bufferHead] = value;
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

    // Draw vertical axis with scale
    QPen axisPen(Qt::white, 2);
    painter.setPen(axisPen);
    painter.drawLine(graphRect.left(), graphRect.top(), graphRect.left(), graphRect.bottom());
    int numTicks = 5;
    QFont tickFont = painter.font();
    tickFont.setPointSize(10);
    painter.setFont(tickFont);
    for (int i = 0; i <= numTicks; ++i) {
        qreal value = m_minValue + (m_maxValue - m_minValue) * (1.0 - i / (qreal)numTicks);
        int y = graphRect.top() + (graphRect.height() * i) / numTicks;
        painter.drawLine(graphRect.left() - 10, y, graphRect.left(), y);
        painter.setPen(Qt::white);
        QFont tickFont = painter.font();
        tickFont.setPointSize(14);
        painter.setFont(tickFont);
        painter.drawText(5, y - 12, 50, 24, Qt::AlignLeft | Qt::AlignVCenter, QString::number((int)value));
        painter.setPen(axisPen);
    }

    // Draw graph data
    drawGraph(painter, graphRect);

    // Show current value label
    if (!m_dataPoints.isEmpty()) {
        qreal lastValue = m_dataPoints.last();
        QString valueLabel = QString("Value: %1").arg(lastValue, 0, 'f', 1);
        QFont valueFont = painter.font();
        valueFont.setBold(true);
        valueFont.setPointSize(12);
        painter.setFont(valueFont);
        painter.setPen(Qt::yellow);
        painter.drawText(graphRect.right() - 120, graphRect.top() + 10, 110, 24, Qt::AlignRight | Qt::AlignVCenter, valueLabel);
    }
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
    if (m_dataPoints.isEmpty())
        return;

    int bufferSize = graphRect.width() / m_stepSize;
    qreal valueRange = qMax(1.0, m_maxValue - m_minValue);

    int N = m_dataPoints.size();
    int startIdx = (N > bufferSize) ? (m_bufferHead + 1) % N : 0;

    // Marker X position
    int markerX = graphRect.left() + (m_bufferHead % bufferSize) * m_stepSize;

    // Clear a narrow strip ahead of the marker
    int eraseWidth = m_stepSize + 2;
    int eraseX = markerX + 1;
    if (eraseX + eraseWidth > graphRect.right())
        eraseX -= graphRect.width(); // wrap
    painter.save();
    painter.setCompositionMode(QPainter::CompositionMode_Source);
    painter.fillRect(QRect(eraseX, graphRect.top(), eraseWidth, graphRect.height()), palette().color(QPalette::Window));
    painter.restore();

    // Draw all segments except those crossing the cleared strip
    QPen corePen(m_graphColor.lighter(120), 1);
    painter.setPen(corePen);

    QPointF prevPoint;
    bool hasPrev = false;

    for (int i = 0; i < qMin(bufferSize, N); ++i)
    {
        int bufIdx = (startIdx + i) % N;
        qreal normalizedValue = (m_dataPoints[bufIdx] - m_minValue) / valueRange;
        normalizedValue = qBound(0.0, normalizedValue, 1.0);
        qreal y = graphRect.bottom() - normalizedValue * graphRect.height();
        int x = graphRect.left() + i * m_stepSize;

        QPointF currentPoint(x, y);

        if (hasPrev)
        {
            // Skip line if it crosses cleared area
            if (!((prevPoint.x() < eraseX + eraseWidth && prevPoint.x() > eraseX) ||
                  (currentPoint.x() < eraseX + eraseWidth && currentPoint.x() > eraseX)))
            {
                painter.drawLine(prevPoint, currentPoint);
            }
        }

        prevPoint = currentPoint;
        hasPrev = true;
    }

  // Draw vertical marker as a subtle dotted line
QPen scanPen(m_graphColor.lighter(150), 1); // lighter color, thinner
scanPen.setStyle(Qt::DotLine);              // dotted line
scanPen.setColor(QColor(m_graphColor.red(), m_graphColor.green(), m_graphColor.blue(), 120)); // semi-transparent
painter.setPen(scanPen);
painter.drawLine(QPointF(markerX, graphRect.top()), QPointF(markerX, graphRect.bottom()));
}
