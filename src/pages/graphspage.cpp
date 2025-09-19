// GraphsPage implementation
#include "graphspage.h"
#include <QVBoxLayout>
#include <QLabel>

GraphsPage::GraphsPage(QWidget *parent) : QWidget(parent) {
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *title = new QLabel("Graphs", this);
    title->setAlignment(Qt::AlignCenter);
    layout->addWidget(title);
    // TODO: Move more graphs widgets here from MainWindow
}
