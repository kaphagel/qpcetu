#include <QApplication>
#include <QDebug>
#include <QLibraryInfo>
#include <QDir>
#include "ui/modernmainwindow.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    // Ensure Qt can find plugins on Linux
    QString pluginPath = QLibraryInfo::location(QLibraryInfo::PluginsPath);
    qDebug() << "Qt Plugin Path:" << pluginPath;
    app.addLibraryPath(pluginPath);
    
    // Also try the standard system Qt plugin path
    app.addLibraryPath("/usr/lib/x86_64-linux-gnu/qt5/plugins");

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