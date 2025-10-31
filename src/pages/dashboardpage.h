#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QGridLayout>
#include "../viewmodels/dashboardviewmodel.h"

class DataWidget;
class AnimatedProgressBar;
class GraphWidget;

class DashboardPage : public QWidget {
    Q_OBJECT
public:
    explicit DashboardPage(QWidget *parent = nullptr);
    ~DashboardPage() override;

private slots:
    // ViewModel signal handlers
    void onEnergyCoreUpdated(int value);
    void onShieldMatrixUpdated(int value);
    void onEngineThrustUpdated(int value);
    void onWeaponArrayUpdated(int value);
    void onSystemParametersUpdated(const DashboardViewModel::SystemParameters& params);
    void onNavigationDataUpdated(const DashboardViewModel::NavigationData& data);
    void onSystemStatusChanged(DashboardViewModel::SystemStatus status, const QString& message);
    void onTimeUpdated(const QString& timestamp);
    void onAlertGenerated(const QString& message);
    void onConnectionStatusChanged(bool connected, const QString& message);

private:
    void setupUI();
    void connectSignals();
    void setupEEGLayout();
    QWidget *createTopBar();
    QWidget *createGraphArea();
    QWidget *createDataWidgetRow();
    QWidget *createBottomBar();
    void createStatusPanel(QVBoxLayout *mainVLayout);
    void createDataPanels(QGridLayout *mainLayout);
    void createSystemPanel(QGridLayout *mainLayout);
    void createControlPanel(QGridLayout *mainLayout);
    void createGraphPanels(QGridLayout *mainLayout);

private:
    // ViewModel (business logic)
    DashboardViewModel* m_viewModel;
    
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
};
