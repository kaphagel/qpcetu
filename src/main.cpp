#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include "mainwindow.h"
#include "udpservice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    
    // Set application properties
    app.setApplicationName("Sci-Fi Data Screen");
    app.setApplicationVersion("1.0");
    app.setOrganizationName("Futuristic Systems");
    
    // Set a modern font
    QFont font("Consolas", 10);
    if (!font.exactMatch()) {
        font = QFont("Courier New", 10);
    }
    app.setFont(font);
    
    // Create and show the main window maximized
    MainWindow window;
    window.showMaximized();
    
    // Optionally, start on UDP page for demo:
    // window.navigateToPage(3); // 3 = UDP response page
    
    return app.exec();
}
