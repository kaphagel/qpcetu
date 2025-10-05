#ifndef CONTROLLERMANAGER_H
#define CONTROLLERMANAGER_H

#include <QObject>
#include <QAbstractListModel>
#include <QTimer>
#include <QHash>
#include "industrialcontroller.h"

/**
 * @brief Manages multiple discovered industrial controllers
 *
 * Provides a model for Qt views and handles controller lifecycle
 */
class ControllerManager : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(int controllerCount READ controllerCount NOTIFY controllerCountChanged)
    Q_PROPERTY(int onlineCount READ onlineCount NOTIFY statusChanged)

public:
    enum Roles
    {
        ControllerRole = Qt::UserRole + 1,
        TypeRole,
        IpAddressRole,
        HostnameRole,
        StatusRole,
        LastSeenRole,
        SignalStrengthRole
    };

    explicit ControllerManager(QObject *parent = nullptr);

    // QAbstractListModel interface
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QHash<int, QByteArray> roleNames() const override;

    // Controller management
    Q_INVOKABLE IndustrialController *addOrUpdateController(const QString &response, const QHostAddress &sender);
    Q_INVOKABLE IndustrialController *getController(const QString &ipAddress) const;
    Q_INVOKABLE IndustrialController *getControllerByMac(const QString &macAddress) const;
    Q_INVOKABLE QList<IndustrialController *> getControllersByType(IndustrialController::ControllerType type) const;

    // Statistics
    int controllerCount() const { return m_controllers.size(); }
    int onlineCount() const;
    Q_INVOKABLE int getCountByType(IndustrialController::ControllerType type) const;

    // Cleanup
    Q_INVOKABLE void removeOfflineControllers();
    Q_INVOKABLE void clearAll();

public slots:
    void onControllerDataUpdated();
    void performPeriodicCleanup();

signals:
    void controllerCountChanged();
    void statusChanged();
    void controllerAdded(IndustrialController *controller);
    void controllerRemoved(IndustrialController *controller);
    void controllerUpdated(IndustrialController *controller);

private:
    QList<IndustrialController *> m_controllers;
    QHash<QString, IndustrialController *> m_controllersByIp;
    QHash<QString, IndustrialController *> m_controllersByMac;
    QTimer *m_cleanupTimer;

    void setupCleanupTimer();
    int findControllerIndex(IndustrialController *controller) const;
};

#endif // CONTROLLERMANAGER_H