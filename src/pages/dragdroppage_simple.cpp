#include "dragdroppage_simple.h"
#include <QApplication>
#include <QRandomGenerator>

// SimpleDraggableRectangle Implementation
SimpleDraggableRectangle::SimpleDraggableRectangle(const QString &text, const QColor &color, QWidget *parent)
    : QLabel(parent), m_color(color), m_text(text)
{
    setText(text);
    setFixedSize(120, 80);
    setAlignment(Qt::AlignCenter);
    setStyleSheet(QString("QLabel { "
                          "background-color: %1; "
                          "color: white; "
                          "border: 2px solid #333; "
                          "border-radius: 8px; "
                          "font-weight: bold; "
                          "font-size: 12px; "
                          "}")
                      .arg(color.name()));

    setAttribute(Qt::WA_DeleteOnClose);
}

void SimpleDraggableRectangle::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        m_dragStartPosition = event->pos();
    }
    QLabel::mousePressEvent(event);
}

void SimpleDraggableRectangle::mouseMoveEvent(QMouseEvent *event)
{
    if (!(event->buttons() & Qt::LeftButton))
        return;

    if ((event->pos() - m_dragStartPosition).manhattanLength() < QApplication::startDragDistance())
        return;

    QDrag *drag = new QDrag(this);
    QMimeData *mimeData = new QMimeData;
    mimeData->setText(m_text);
    drag->setMimeData(mimeData);

    // Create a simple pixmap for drag
    QPixmap pixmap(size());
    pixmap.fill(m_color);
    QPainter painter(&pixmap);
    painter.setPen(Qt::white);
    painter.drawText(rect(), Qt::AlignCenter, m_text);
    drag->setPixmap(pixmap);

    Qt::DropAction dropAction = drag->exec(Qt::CopyAction | Qt::MoveAction);
    Q_UNUSED(dropAction)
}

// SimpleDropZone Implementation
SimpleDropZone::SimpleDropZone(const QString &label, QWidget *parent)
    : QFrame(parent), m_label(label), m_hasDroppedItem(false)
{
    setAcceptDrops(true);
    setMinimumSize(300, 200);
    setFrameStyle(QFrame::Box | QFrame::Raised);
    setLineWidth(2);
    setStyleSheet("QFrame { "
                  "background-color: #f0f0f0; "
                  "border: 2px dashed #666; "
                  "border-radius: 10px; "
                  "color: #333; "
                  "}");
}

void SimpleDropZone::clearDroppedItems()
{
    m_hasDroppedItem = false;
    m_lastDroppedText.clear();
    update();
}

void SimpleDropZone::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
        setStyleSheet("QFrame { "
                      "background-color: #e8f5e8; "
                      "border: 2px dashed #4CAF50; "
                      "border-radius: 10px; "
                      "color: #333; "
                      "}");
    }
}

void SimpleDropZone::dragMoveEvent(QDragMoveEvent *event)
{
    if (event->mimeData()->hasText())
    {
        event->acceptProposedAction();
    }
}

void SimpleDropZone::dropEvent(QDropEvent *event)
{
    if (event->mimeData()->hasText())
    {
        m_lastDroppedText = event->mimeData()->text();
        m_lastDroppedPosition = event->pos();
        m_hasDroppedItem = true;

        event->acceptProposedAction();
        update();

        // Reset styling
        setStyleSheet("QFrame { "
                      "background-color: #f0f0f0; "
                      "border: 2px dashed #666; "
                      "border-radius: 10px; "
                      "color: #333; "
                      "}");

        qDebug() << "Dropped" << m_lastDroppedText << "at position" << m_lastDroppedPosition;
    }
}

void SimpleDropZone::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);

    // Draw zone label
    painter.setPen(QColor("#666"));
    painter.setFont(QFont("Arial", 14, QFont::Bold));
    painter.drawText(rect().adjusted(10, 10, -10, -10), Qt::AlignTop | Qt::AlignHCenter, m_label);

    // Draw dropped item if any
    if (m_hasDroppedItem && !m_lastDroppedText.isEmpty())
    {
        painter.setPen(QColor("#333"));
        painter.setFont(QFont("Arial", 10));

        QRect itemRect(m_lastDroppedPosition.x() - 30, m_lastDroppedPosition.y() - 15, 60, 30);
        painter.fillRect(itemRect, QColor("#4CAF50"));
        painter.setPen(Qt::white);
        painter.drawText(itemRect, Qt::AlignCenter, m_lastDroppedText);
    }
    else
    {
        // Draw instructions if no items
        painter.setPen(QColor("#999"));
        painter.setFont(QFont("Arial", 12, QFont::Bold));
        painter.drawText(rect().adjusted(20, 50, -20, -20),
                         Qt::AlignCenter | Qt::TextWordWrap,
                         "Drag and drop rectangles here");
    }
}

// SimpleDragDropPage Implementation
SimpleDragDropPage::SimpleDragDropPage(QWidget *parent)
    : QWidget(parent), m_rectangleCounter(1)
{
    setupUI();
}

void SimpleDragDropPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(20);

    // Toolbar
    m_toolbarLayout = new QHBoxLayout;

    m_backButton = new QPushButton("← Back to Main");
    m_backButton->setIcon(QIcon(":/icons/home.svg"));
    m_backButton->setStyleSheet("QPushButton { "
                                "background: #007AFF; "
                                "color: white; "
                                "border: none; "
                                "padding: 10px 20px; "
                                "border-radius: 8px; "
                                "font-size: 14px; "
                                "font-weight: bold; "
                                "} "
                                "QPushButton:hover { background: #0051D0; } "
                                "QPushButton:pressed { background: #003A9B; }");
    connect(m_backButton, &QPushButton::clicked, this, &SimpleDragDropPage::backRequested);

    m_addRectButton = new QPushButton("+ Add Rectangle");
    m_addRectButton->setStyleSheet("QPushButton { "
                                   "background: #4CAF50; "
                                   "color: white; "
                                   "border: none; "
                                   "padding: 10px 20px; "
                                   "border-radius: 8px; "
                                   "font-size: 14px; "
                                   "font-weight: bold; "
                                   "} "
                                   "QPushButton:hover { background: #45A049; } "
                                   "QPushButton:pressed { background: #3D8B40; }");
    connect(m_addRectButton, &QPushButton::clicked, this, &SimpleDragDropPage::addRectangle);

    m_clearButton = new QPushButton("Clear All");
    m_clearButton->setStyleSheet("QPushButton { "
                                 "background: #FF6B6B; "
                                 "color: white; "
                                 "border: none; "
                                 "padding: 10px 20px; "
                                 "border-radius: 8px; "
                                 "font-size: 14px; "
                                 "font-weight: bold; "
                                 "} "
                                 "QPushButton:hover { background: #FF5252; } "
                                 "QPushButton:pressed { background: #E53935; }");
    connect(m_clearButton, &QPushButton::clicked, this, &SimpleDragDropPage::clearDropZones);

    m_toolbarLayout->addWidget(m_backButton);
    m_toolbarLayout->addStretch();
    m_toolbarLayout->addWidget(m_addRectButton);
    m_toolbarLayout->addWidget(m_clearButton);

    m_mainLayout->addLayout(m_toolbarLayout);

    // Instructions
    QLabel *instructions = new QLabel("Drag & Drop Test Page");
    instructions->setStyleSheet("QLabel { "
                                "font-size: 24px; "
                                "font-weight: bold; "
                                "color: #333; "
                                "margin: 10px 0; "
                                "}");
    instructions->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(instructions);

    QLabel *subInstructions = new QLabel("Click 'Add Rectangle' to create draggable items, then drag them to the drop zones below");
    subInstructions->setStyleSheet("QLabel { "
                                   "font-size: 14px; "
                                   "color: #666; "
                                   "margin-bottom: 20px; "
                                   "}");
    subInstructions->setAlignment(Qt::AlignCenter);
    m_mainLayout->addWidget(subInstructions);

    // Draggables container
    QFrame *draggablesFrame = new QFrame;
    draggablesFrame->setFrameStyle(QFrame::Box | QFrame::Sunken);
    draggablesFrame->setStyleSheet("QFrame { background-color: #f8f8f8; padding: 10px; border-radius: 8px; }");
    m_draggablesLayout = new QHBoxLayout(draggablesFrame);
    m_draggablesLayout->setAlignment(Qt::AlignLeft);

    QLabel *draggablesLabel = new QLabel("Draggable Items:");
    draggablesLabel->setStyleSheet("QLabel { font-weight: bold; margin-right: 20px; }");
    m_draggablesLayout->addWidget(draggablesLabel);
    m_draggablesLayout->addStretch();

    m_mainLayout->addWidget(draggablesFrame);

    // Drop zones
    QLabel *dropZonesLabel = new QLabel("Drop Zones:");
    dropZonesLabel->setStyleSheet("QLabel { font-size: 18px; font-weight: bold; color: #333; margin-top: 20px; }");
    m_mainLayout->addWidget(dropZonesLabel);

    m_dropZonesLayout = new QHBoxLayout;
    m_dropZonesLayout->setSpacing(20);

    m_dropZone1 = new SimpleDropZone("Zone 1");
    m_dropZone2 = new SimpleDropZone("Zone 2");
    m_dropZone3 = new SimpleDropZone("Zone 3");

    m_dropZonesLayout->addWidget(m_dropZone1);
    m_dropZonesLayout->addWidget(m_dropZone2);
    m_dropZonesLayout->addWidget(m_dropZone3);

    m_mainLayout->addLayout(m_dropZonesLayout);
    m_mainLayout->addStretch();
}

void SimpleDragDropPage::addRectangle()
{
    QStringList colors = {"#FF6B6B", "#4ECDC4", "#45B7D1", "#96CEB4", "#FECA57", "#FF9FF3", "#54A0FF"};
    QString rectText = QString("Rect %1").arg(m_rectangleCounter++);
    QColor rectColor(colors[QRandomGenerator::global()->bounded(colors.size())]);

    SimpleDraggableRectangle *rect = new SimpleDraggableRectangle(rectText, rectColor, this);
    m_draggablesLayout->insertWidget(m_draggablesLayout->count() - 1, rect); // Insert before stretch
}

void SimpleDragDropPage::clearDropZones()
{
    m_dropZone1->clearDroppedItems();
    m_dropZone2->clearDroppedItems();
    m_dropZone3->clearDroppedItems();
}