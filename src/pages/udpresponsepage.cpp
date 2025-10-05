// UdpResponsePage implementation
#include "udpresponsepage.h"
#include "../mainwindow.h"
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>
#include <QLabel>
#include <QIcon>

UdpResponsePage::UdpResponsePage(QWidget *parent)
    : QWidget(parent), m_layout(new QVBoxLayout), m_textEdit(new QTextEdit(this))
    {
        QVBoxLayout *mainLayout = new QVBoxLayout;
        mainLayout->setSpacing(16);
        mainLayout->setContentsMargins(16, 16, 16, 16);

        // Top app bar with home button
        QWidget *topBar = new QWidget;
        QHBoxLayout *topLayout = new QHBoxLayout(topBar);
        topLayout->setContentsMargins(0, 0, 0, 0);
        topLayout->setSpacing(0);
        QPushButton *homeBtn = new QPushButton;
        homeBtn->setIcon(QIcon(":/icons/home.svg"));
        homeBtn->setIconSize(QSize(32, 32));
        homeBtn->setFlat(true);
        homeBtn->setStyleSheet("QPushButton { background: transparent; border: none; margin: 0 8px; } QPushButton:pressed { background: #e0e0e0; }");
        topLayout->addWidget(homeBtn, 0, Qt::AlignLeft);
        QLabel *titleLabel = new QLabel("UDP Response");
        titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #007AFF; background: transparent;");
        topLayout->addWidget(titleLabel, 1, Qt::AlignLeft);
        topLayout->addStretch();
        mainLayout->addWidget(topBar);
        mainLayout->addWidget(m_textEdit);
        connect(homeBtn, &QPushButton::clicked, this, [this]() {
            QWidget *mw = this->window();
            if (auto mainWin = qobject_cast<MainWindow*>(mw)) {
                mainWin->navigateToPage(0);
            }
        });
        setLayout(mainLayout);
}

void UdpResponsePage::addResponse(const QString &address, const QByteArray &response)
{
    m_textEdit->append(QString("From %1: %2").arg(address, QString::fromUtf8(response)));
}
