#pragma once

#include <QWidget>
#include <QTimer>
#include <QPainter>
#include <QVector>
#include <QRandomGenerator>
#include <QLabel>
#include <QVBoxLayout>
#include <cmath>

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    enum GraphType {
        SineWave,
        RandomData,
        StepFunction,
        PulseWave
    };

    explicit GraphWidget(const QString &title, GraphType type, QWidget *parent = nullptr);
    ~GraphWidget();

    void addDataPoint(qreal value);
    void setColor(const QColor &color);
    void setRange(qreal min, qreal max);
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_title;
    void setupUI();
    void drawGrid(QPainter &painter, const QRect &graphRect);
    void drawGraph(QPainter &painter, const QRect &graphRect);
    qreal generateNextValue();
    QVector<qreal> m_dataPoints;
    int m_maxDataPoints;
    int m_bufferHead = -1;
    QColor m_graphColor;
    QColor m_gridColor;
    QVBoxLayout *m_layout;
    QLabel *m_titleLabel;
    qreal m_minValue = 0;
    qreal m_maxValue = 100;
    GraphType m_graphType;
    int m_stepSize = 24; // Increased step size (pixels)
public:
    void setStepSize(int step) { m_stepSize = step; update(); }
    // ...existing code...
    
};
