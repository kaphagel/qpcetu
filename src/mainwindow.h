#pragma once

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

#include "udpservice.h"

// Forward declarations for page classes
class DashboardPage;
class GraphsPage;
class SettingsPage;
class UdpResponsePage;
class OverviewPage; // Added forward declaration for OverviewPage
class SimpleDragDropPage;

class DataWidget;
class AnimatedProgressBar;
class GraphWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void navigateToPage(int index);

private slots:
    void updateData();
    void updateSystemStatus();
    void simulateAlert();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    // Main pages for QStackedWidget
    OverviewPage *overviewPage;
    DashboardPage *dashboardPage;
    GraphsPage *graphsPage;
    SettingsPage *settingsPage;
    SimpleDragDropPage *dragDropPage;
    void setupUI();
    void setupStyling();
    void createStatusPanel();
    void createDataPanels();
    void createGraphPanels();
    void createSystemPanel();
    void createControlPanel();
    void setupPages();
    void setupBreadcrumbs(const QStringList &crumbs, int activeIndex);

    // UDP Service and Response Page
    UdpService *m_udpService;
    UdpResponsePage *m_udpResponsePage;

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
};
