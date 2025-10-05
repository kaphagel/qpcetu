// SettingsPage implementation
#include "settingspage.h"
#include "../mainwindow.h"
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QIcon>

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent) {
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
    QLabel *titleLabel = new QLabel("Settings");
    titleLabel->setStyleSheet("font-size: 22px; font-weight: bold; color: #FF9500; background: transparent;");
    topLayout->addWidget(titleLabel, 1, Qt::AlignLeft);
    topLayout->addStretch();
    mainLayout->addWidget(topBar);
    connect(homeBtn, &QPushButton::clicked, this, [this]() {
        QWidget *mw = this->window();
        if (auto mainWin = qobject_cast<MainWindow*>(mw)) {
            mainWin->navigateToPage(0);
        }
    });
    this->setLayout(mainLayout);
    // TODO: Move more settings widgets here from MainWindow

}
