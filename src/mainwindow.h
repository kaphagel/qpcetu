#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QRandomGenerator>
#include <QFrame>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QStackedWidget>

class DataWidget;
class AnimatedProgressBar;
class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void updateData();
    void updateSystemStatus();
    void simulateAlert();

private:
    void setupUI();
    void setupStyling();
    void createStatusPanel();
    void createDataPanels();
    void createGraphPanels();
    void createSystemPanel();
    void createControlPanel();

    // Multi-page navigation demo
    void setupPages();
    void setupBreadcrumbs(const QStringList &crumbs, int activeIndex);
    void navigateToPage(int index);

    // UI Components
    QWidget *m_centralWidget;
    QStackedWidget *m_stackedWidget;
    QWidget *m_breadcrumbBar;
    QHBoxLayout *m_breadcrumbLayout;
    QGridLayout *m_mainLayout;

    // Status indicators
    QLabel *m_statusLabel;
    QLabel *m_timeLabel;
    QLabel *m_connectionStatus;

    // Data panels
    DataWidget *m_energyWidget;
    DataWidget *m_shieldWidget;
    DataWidget *m_engineWidget;
    DataWidget *m_weaponWidget;

    // Progress bars
    AnimatedProgressBar *m_powerBar;
    AnimatedProgressBar *m_coolantBar;
    AnimatedProgressBar *m_fuelBar;

    // System info
    QTextEdit *m_logDisplay;
    QLabel *m_coordinates;
    QLabel *m_velocity;
    QLabel *m_altitude;

    // Control buttons
    QPushButton *m_engageBtn;
    QPushButton *m_alertBtn;
    QPushButton *m_scanBtn;

    // Timers
    QTimer *m_updateTimer;
    QTimer *m_statusTimer;
    QTimer *m_alertTimer;

    // Graph widgets
    GraphWidget *m_energyGraph;
    GraphWidget *m_shieldGraph;
    GraphWidget *m_systemGraph;
    GraphWidget *m_networkGraph;
    GraphWidget *m_thrusterGraph;
    GraphWidget *m_sensorGraph;

    // Data
    int m_alertLevel;
    bool m_systemOnline;
};

#endif // MAINWINDOW_H
