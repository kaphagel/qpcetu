#ifndef DASHBOARDPAGE_H
#define DASHBOARDPAGE_H
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
class DataWidget;
class AnimatedProgressBar;
class GraphWidget;

class DashboardPage : public QWidget {
    Q_OBJECT
public:
    explicit DashboardPage(QWidget *parent = nullptr);

    // Methods to update dashboard data
    void updateData();
    void updateSystemStatus();
    void simulateAlert();

private:
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

    // Graph widgets
    GraphWidget *m_energyGraph;
    GraphWidget *m_shieldGraph;
    GraphWidget *m_systemGraph;
    GraphWidget *m_networkGraph;
    GraphWidget *m_thrusterGraph;
    GraphWidget *m_sensorGraph;

    // Data
    int m_alertLevel = 0;
    bool m_systemOnline = true;

    void createStatusPanel(QVBoxLayout *mainVLayout);
    void createDataPanels(QGridLayout *mainLayout);
    void createSystemPanel(QGridLayout *mainLayout);
    void createControlPanel(QGridLayout *mainLayout);
    void createGraphPanels(QGridLayout *mainLayout);
};
#endif // DASHBOARDPAGE_H
