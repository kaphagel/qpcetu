#include <QApplication>
#include <QStyleFactory>
#include <QPalette>
#include <QFont>
#include "mainwindow.h"
#include "udpservice.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
        app.setStyleSheet(R"(
            QPushButton {
                background-color: #23272b;
                color: #e0e0e0;
                border: 1px solid #444;
                border-radius: 2px;
                font-family: 'Segoe UI', 'Arial', sans-serif;
                font-size: 14px;
                font-weight: 500;
                padding: 6px 18px;
                outline: none;
            }
            QPushButton:hover {
                background-color: #2c3136;
                border: 1px solid #666;
            }
            QPushButton:pressed {
                background-color: #1a1d20;
                border: 1px solid #888;
            }
            QPushButton:disabled {
                background-color: #181a1b;
                color: #888;
                border: 1px solid #222;
            }
        )");
    
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
