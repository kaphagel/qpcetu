#pragma once

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QFrame>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QDrag>
#include <QMouseEvent>
#include <QPainter>
#include <QApplication>
#include <QDebug>

// Simple draggable rectangle widget
class SimpleDraggableRectangle : public QLabel
{
    Q_OBJECT

public:
    SimpleDraggableRectangle(const QString &text, const QColor &color, QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QPoint m_dragStartPosition;
    QColor m_color;
    QString m_text;
};

// Simple drop zone
class SimpleDropZone : public QFrame
{
    Q_OBJECT

public:
    SimpleDropZone(const QString &label, QWidget *parent = nullptr);
    void clearDroppedItems();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dragMoveEvent(QDragMoveEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void paintEvent(QPaintEvent *event) override;

private:
    QString m_label;
    QString m_lastDroppedText; // Store only the last dropped item
    QPoint m_lastDroppedPosition;
    bool m_hasDroppedItem;
};

// Main drag and drop page
class SimpleDragDropPage : public QWidget
{
    Q_OBJECT

public:
    SimpleDragDropPage(QWidget *parent = nullptr);

signals:
    void backRequested();

private slots:
    void addRectangle();
    void clearDropZones();

private:
    void setupUI();

    // UI Components
    QVBoxLayout *m_mainLayout;
    QHBoxLayout *m_toolbarLayout;
    QHBoxLayout *m_draggablesLayout;
    QHBoxLayout *m_dropZonesLayout;

    QPushButton *m_backButton;
    QPushButton *m_addRectButton;
    QPushButton *m_clearButton;

    SimpleDropZone *m_dropZone1;
    SimpleDropZone *m_dropZone2;
    SimpleDropZone *m_dropZone3;

    int m_rectangleCounter;
};
