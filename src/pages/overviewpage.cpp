#include "overviewpage.h"
#include <QFont>
#include <QSizePolicy>

OverviewPage::OverviewPage(QWidget *parent)
    : QWidget(parent)
{
    m_gridLayout = new QGridLayout(this);
    m_gridLayout->setSpacing(32);
    m_gridLayout->setContentsMargins(40, 40, 40, 40);

    struct IconInfo
    {
        QString label;
        QString iconPath;
    } icons[] = {
        {"Dashboard", ":/icons/dashboard.svg"},
        {"Graphs", ":/icons/graphs.svg"},
        {"Settings", ":/icons/settings.svg"},
        {"UDP", ":/icons/udp.svg"},
        {"Drag & Drop", ":/icons/dragdrop.svg"}};

    QFont labelFont("San Francisco", 16, QFont::Medium);

    for (int i = 0; i < 5; ++i)
    {
        QPushButton *iconBtn = new QPushButton;
        iconBtn->setIcon(QIcon(icons[i].iconPath));
        iconBtn->setIconSize(QSize(80, 80));
        iconBtn->setFixedSize(100, 100);
        iconBtn->setFlat(true);
        iconBtn->setStyleSheet("QPushButton { background: #f8f8f8; border-radius: 24px; border: none; } QPushButton:pressed { background: #e0e0e0; }");
        iconBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        connect(iconBtn, &QPushButton::clicked, this, [this, i]()
                { emit iconClicked(i); });

        QLabel *label = new QLabel(icons[i].label);
        label->setAlignment(Qt::AlignCenter);
        label->setFont(labelFont);
        label->setStyleSheet("color: #222; background: transparent; margin-top: 8px;");
        QWidget *iconWidget = new QWidget;
        QVBoxLayout *vbox = new QVBoxLayout(iconWidget);
        vbox->setSpacing(8);
        vbox->setContentsMargins(0, 0, 0, 0);
        vbox->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
        vbox->addWidget(iconBtn, 0, Qt::AlignHCenter);
        vbox->addWidget(label, 0, Qt::AlignHCenter);

        // Arrange in 3 columns, 2 rows (with 5th item in center of second row)
        if (i < 3)
        {
            m_gridLayout->addWidget(iconWidget, 0, i, Qt::AlignHCenter | Qt::AlignVCenter);
        }
        else
        {
            // Second row - center the remaining items
            int col = (i - 3) + 1; // Start from column 1 for 4th item, column 2 for 5th item
            m_gridLayout->addWidget(iconWidget, 1, col, Qt::AlignHCenter | Qt::AlignVCenter);
        }
    }
    setStyleSheet("background: #f0f0f0;");
}
