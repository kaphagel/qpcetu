#pragma once

#include <QWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QPropertyAnimation>
#include <QGraphicsEffect>

class DataWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(qreal glowIntensity READ glowIntensity WRITE setGlowIntensity)

public:
    explicit DataWidget(const QString &title, const QString &unit, QWidget *parent = nullptr);
    ~DataWidget();
    
    void setValue(int value);
    int value() const { return m_currentValue; }
    
    qreal glowIntensity() const { return m_glowIntensity; }
    void setGlowIntensity(qreal intensity);

private slots:
    void updateDisplay();

private:
    void setupUI();
    void setupStyling();
    void startGlowAnimation();
    
    QString m_title;
    QString m_unit;
    int m_currentValue;
    int m_targetValue;
    qreal m_glowIntensity;
    
    QLabel *m_titleLabel;
    QLabel *m_valueLabel;
    QLabel *m_unitLabel;
    QProgressBar *m_progressBar;
    QVBoxLayout *m_layout;
    
    QPropertyAnimation *m_glowAnimation;
    QPropertyAnimation *m_valueAnimation;
    QGraphicsDropShadowEffect *m_glowEffect;
};
