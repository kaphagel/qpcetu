#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

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

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void generateData();

private:
    void setupUI();
    void drawGrid(QPainter &painter, const QRect &graphRect);
    void drawGraph(QPainter &painter, const QRect &graphRect);
    qreal generateNextValue();
    qreal generateInitialValue();
    
    QString m_title;
    GraphType m_graphType;
    QVector<qreal> m_dataPoints;
    QColor m_graphColor;
    QColor m_gridColor;
    qreal m_minValue;
    qreal m_maxValue;
    int m_maxDataPoints;
    
    QTimer *m_updateTimer;
    QLabel *m_titleLabel;
    QVBoxLayout *m_layout;
    
    // Graph generation state
    qreal m_time;
    qreal m_lastValue;
    qreal m_amplitude;
    qreal m_frequency;
    qreal m_offset;
};

#endif // GRAPHWIDGET_H
