#ifndef ANIMATEDPROGRESSBAR_H
#define ANIMATEDPROGRESSBAR_H

#include <QProgressBar>
#include <QPropertyAnimation>
#include <QTimer>
#include <QPainter>
#include <QStyleOptionProgressBar>

class AnimatedProgressBar : public QProgressBar
{
    Q_OBJECT
    Q_PROPERTY(qreal animationOffset READ animationOffset WRITE setAnimationOffset)

public:
    explicit AnimatedProgressBar(QWidget *parent = nullptr);
    ~AnimatedProgressBar();
    
    qreal animationOffset() const { return m_animationOffset; }
    void setAnimationOffset(qreal offset);

public slots:
    void setValue(int value);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    void setupAnimation();
    
    qreal m_animationOffset;
    int m_targetValue;
    QPropertyAnimation *m_valueAnimation;
    QPropertyAnimation *m_flowAnimation;
};

#endif // ANIMATEDPROGRESSBAR_H
