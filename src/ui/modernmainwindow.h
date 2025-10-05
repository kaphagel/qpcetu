#ifndef MODERNMAINWINDOW_H
#define MODERNMAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QProgressBar>
#include <QTimer>
#include <QFrame>
#include <QPushButton>
#include <QTextEdit>
#include <QGroupBox>
#include <QStackedWidget>
#include <QScrollArea>
#include <QPropertyAnimation>
#include <QGraphicsDropShadowEffect>

#include "../udpservice.h"

// Forward declarations for page classes
class DashboardPage;
class GraphsPage;
class SettingsPage;
class UdpResponsePage;
class ControllerCardWidget;

/**
 * @brief Modern Industrial HMI MainWindow with card-based controller interface
 *
 * Features:
 * - Real-time controller discovery and status display
 * - Modern industrial styling with sci-fi aesthetics
 * - Card-based controller layout with live data
 * - System status monitoring and alerts
 * - Responsive design with animations
 */
class ModernMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ModernMainWindow(QWidget *parent = nullptr);
    ~ModernMainWindow();

public slots:
    void navigateToPage(int index);
    void onControllerDiscovered(const QString &ip, const QByteArray &data);
    void onControllerCountChanged(int count);

private slots:
    void updateSystemStatus();
    void updateDateTime();
    void showControllerDetails(const QString &ip);
    void refreshControllers();
    void toggleTheme();
    void onThemeChanged();

protected:
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;

private:
    void setupUI();
    void setupStyling();
    void createHeaderBar();
    void createSystemStatusStrip();
    void createMainContentArea();
    void createControllerGrid();
    void createQuickActionsPanel();
    void createStatusBar();
    void updateControllerGrid();
    void addControllerCard(const QString &ip, const QString &type, const QString &status);
    void animateCardEntry(QWidget *card);

    // Core services
    UdpService *m_udpService;

    // Pages
    DashboardPage *m_dashboardPage;
    GraphsPage *m_graphsPage;
    SettingsPage *m_settingsPage;
    UdpResponsePage *m_udpResponsePage;

    // UI Structure
    QWidget *m_centralWidget;
    QStackedWidget *m_stackedWidget;

    // Header components
    QWidget *m_headerBar;
    QLabel *m_titleLabel;
    QLabel *m_connectionStatusLabel;
    QLabel *m_userLabel;
    QLabel *m_dateTimeLabel;

    // System status strip
    QWidget *m_statusStrip;
    QLabel *m_discoveryStatus;
    QLabel *m_modbusStatus;
    QLabel *m_eventsStatus;
    QLabel *m_dataStatus;

    // Main content area
    QWidget *m_mainContent;
    QScrollArea *m_controllerScrollArea;
    QWidget *m_controllerGridWidget;
    QGridLayout *m_controllerGridLayout;
    QWidget *m_quickActionsPanel;

    // Bottom status bar
    QWidget *m_bottomStatusBar;
    QLabel *m_cpuLabel;
    QLabel *m_memoryLabel;
    QLabel *m_networkLabel;
    QLabel *m_lastUpdateLabel;

    // Controller management
    QList<ControllerCardWidget *> m_controllerCards;
    int m_discoveredControllers;

    // Timers
    QTimer *m_statusTimer;
    QTimer *m_dateTimeTimer;

    // Animation
    QPropertyAnimation *m_cardAnimation;
};

#endif // MODERNMAINWINDOW_H