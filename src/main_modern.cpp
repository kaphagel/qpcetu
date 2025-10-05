#include <QApplication>
#include <QDebug>
#include "ui/modernmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    qDebug() << "Starting Modern SciFi Data Screen...";

    // Set application properties
    app.setApplicationName("SciFi Data Screen");
    app.setApplicationVersion("2.0.0");
    app.setOrganizationName("Quantum Tactical Processing");

    // Create and show the modern main window
    ModernMainWindow window;
    window.show();

    qDebug() << "Modern HMI interface initialized successfully";

    return app.exec();
}