// SettingsPage implementation
#include "settingspage.h"
#include <QVBoxLayout>
#include <QLabel>

SettingsPage::SettingsPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("Settings", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    // TODO: Move more settings widgets here from MainWindow

}
