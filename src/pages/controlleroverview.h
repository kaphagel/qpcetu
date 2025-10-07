#ifndef CONTROLLEROVERVIEW_H
#define CONTROLLEROVERVIEW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QScrollArea>
#include <QTimer>
#include <QPushButton>
#include "../controllermanager.h"
#include "../industrialcontroller.h"

/**
 * @brief Overview page showing all discovered industrial controllers
 *
 * Displays controller "faceplates" with status and key information
 */
class ControllerOverview : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerOverview(ControllerManager *controllerManager, QWidget *parent = nullptr);

public slots:
    void refreshControllers();
    void onControllerAdded(IndustrialController *controller);
    void onControllerRemoved(IndustrialController *controller);
    void onControllerUpdated(IndustrialController *controller);
    void onToolButtonClicked(const QString &ipAddress);

signals:
    void navigateToIndustrialPage(const QString &ipAddress);

private:
    ControllerManager *m_controllerManager;
    QScrollArea *m_scrollArea;
    QWidget *m_contentWidget;
    QGridLayout *m_gridLayout;
    QLabel *m_summaryLabel;
    QTimer *m_refreshTimer;

    QHash<IndustrialController *, QWidget *> m_controllerWidgets;

    void setupUI();
    void updateSummary();
    QWidget *createControllerFaceplate(IndustrialController *controller);
    void removeControllerWidget(IndustrialController *controller);
    QString getStatusColor(IndustrialController::ConnectionStatus status);
    QString getTypeIcon(IndustrialController::ControllerType type);
};

/**
 * @brief Individual controller faceplate widget
 */
class ControllerFaceplate : public QWidget
{
    Q_OBJECT

public:
    explicit ControllerFaceplate(IndustrialController *controller, QWidget *parent = nullptr);

public slots:
    void updateDisplay();
    void onControllerClicked();
    void onToolButtonClicked();

signals:
    void controllerSelected(IndustrialController *controller);
    void toolButtonClicked(const QString &ipAddress);

private:
    IndustrialController *m_controller;
    QLabel *m_typeLabel;
    QLabel *m_statusLabel;
    QLabel *m_ipLabel;
    QLabel *m_hostnameLabel;
    QLabel *m_lastSeenLabel;
    QLabel *m_signalLabel;
    QPushButton *m_toolButton;

    void setupUI();
    void setupConnections();
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;
};

#endif // CONTROLLEROVERVIEW_H