#include "simpledragdroppage.h"
#include <QDebug>

SimpleDragDropPage::SimpleDragDropPage(QWidget *parent)
    : QWidget(parent), m_mainLayout(nullptr), m_backButton(nullptr), m_titleLabel(nullptr), m_contentLabel(nullptr)
{
    setupUI();
}

SimpleDragDropPage::~SimpleDragDropPage()
{
}

void SimpleDragDropPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(20, 20, 20, 20);
    m_mainLayout->setSpacing(20);

    // Header with back button
    QHBoxLayout *headerLayout = new QHBoxLayout();

    m_backButton = new QPushButton("← Back");
    m_backButton->setFixedSize(100, 30);
    connect(m_backButton, &QPushButton::clicked, this, &SimpleDragDropPage::onBackClicked);

    m_titleLabel = new QLabel("Simple Drag & Drop Interface");
    m_titleLabel->setStyleSheet("font-size: 18px; font-weight: bold; color: #00E5FF;");

    headerLayout->addWidget(m_backButton);
    headerLayout->addWidget(m_titleLabel);
    headerLayout->addStretch();

    // Content area
    m_contentLabel = new QLabel("This is a placeholder for the drag & drop interface.\nFuture implementation will include interactive elements.");
    m_contentLabel->setStyleSheet("font-size: 14px; color: #FFFFFF; padding: 40px; background-color: rgba(45, 45, 45, 0.3); border-radius: 8px;");
    m_contentLabel->setAlignment(Qt::AlignCenter);

    m_mainLayout->addLayout(headerLayout);
    m_mainLayout->addWidget(m_contentLabel);
    m_mainLayout->addStretch();

    // Apply styling
    setStyleSheet(
        "SimpleDragDropPage { background-color: #0F1419; }"
        "QPushButton { background-color: rgba(0, 229, 255, 0.1); border: 1px solid rgba(0, 229, 255, 0.3); border-radius: 6px; color: #00E5FF; font-size: 12px; padding: 6px 12px; }"
        "QPushButton:hover { background-color: rgba(0, 229, 255, 0.2); }");
}

void SimpleDragDropPage::onBackClicked()
{
    qDebug() << "SimpleDragDropPage: Back button clicked";
    emit backRequested();
}