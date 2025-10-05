#include "controllermanager.h"
#include <QDebug>

ControllerManager::ControllerManager(QObject *parent)
    : QAbstractListModel(parent), m_cleanupTimer(new QTimer(this))
{
    setupCleanupTimer();
}

int ControllerManager::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_controllers.size();
}

QVariant ControllerManager::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= m_controllers.size())
    {
        return QVariant();
    }

    IndustrialController *controller = m_controllers.at(index.row());

    switch (role)
    {
    case ControllerRole:
        return QVariant::fromValue(controller);
    case TypeRole:
        return controller->typeDisplayName();
    case IpAddressRole:
        return controller->ipAddress();
    case HostnameRole:
        return controller->hostname();
    case StatusRole:
        return controller->statusText();
    case LastSeenRole:
        return controller->lastSeen();
    case SignalStrengthRole:
        return controller->signalStrength();
    default:
        return QVariant();
    }
}

QHash<int, QByteArray> ControllerManager::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ControllerRole] = "controller";
    roles[TypeRole] = "type";
    roles[IpAddressRole] = "ipAddress";
    roles[HostnameRole] = "hostname";
    roles[StatusRole] = "status";
    roles[LastSeenRole] = "lastSeen";
    roles[SignalStrengthRole] = "signalStrength";
    return roles;
}

IndustrialController *ControllerManager::addOrUpdateController(const QString &response, const QHostAddress &sender)
{
    // Create temporary controller to parse the response
    IndustrialController tempController;
    if (!tempController.parseDiscoveryResponse(response, sender))
    {
        qWarning() << "Failed to parse controller response:" << response;
        return nullptr;
    }

    QString ipAddress = tempController.ipAddress();
    QString macAddress = tempController.macAddress();

    // Check if controller already exists (by IP or MAC)
    IndustrialController *existingController = nullptr;

    if (!ipAddress.isEmpty() && m_controllersByIp.contains(ipAddress))
    {
        existingController = m_controllersByIp[ipAddress];
    }
    else if (!macAddress.isEmpty() && m_controllersByMac.contains(macAddress))
    {
        existingController = m_controllersByMac[macAddress];
    }

    if (existingController)
    {
        // Update existing controller
        qDebug() << "Updating existing controller:" << ipAddress;
        existingController->parseDiscoveryResponse(response, sender);

        int index = findControllerIndex(existingController);
        if (index >= 0)
        {
            emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        }

        emit controllerUpdated(existingController);
        emit statusChanged();
        return existingController;
    }

    // Create new controller
    IndustrialController *newController = new IndustrialController(this);
    newController->parseDiscoveryResponse(response, sender);

    // Connect signals
    connect(newController, &IndustrialController::controllerChanged,
            this, &ControllerManager::onControllerDataUpdated);
    connect(newController, &IndustrialController::statusChanged,
            this, &ControllerManager::statusChanged);
    connect(newController, &IndustrialController::dataUpdated,
            this, &ControllerManager::onControllerDataUpdated);

    // Add to lists and maps
    beginInsertRows(QModelIndex(), m_controllers.size(), m_controllers.size());
    m_controllers.append(newController);

    if (!ipAddress.isEmpty())
    {
        m_controllersByIp[ipAddress] = newController;
    }
    if (!macAddress.isEmpty())
    {
        m_controllersByMac[macAddress] = newController;
    }

    endInsertRows();

    qDebug() << "Added new controller:" << newController->typeDisplayName()
             << "at" << ipAddress << "(" << macAddress << ")";

    emit controllerAdded(newController);
    emit controllerCountChanged();
    emit statusChanged();

    return newController;
}

IndustrialController *ControllerManager::getController(const QString &ipAddress) const
{
    return m_controllersByIp.value(ipAddress, nullptr);
}

IndustrialController *ControllerManager::getControllerByMac(const QString &macAddress) const
{
    return m_controllersByMac.value(macAddress, nullptr);
}

QList<IndustrialController *> ControllerManager::getControllersByType(IndustrialController::ControllerType type) const
{
    QList<IndustrialController *> result;
    for (IndustrialController *controller : m_controllers)
    {
        if (controller->controllerType() == type)
        {
            result.append(controller);
        }
    }
    return result;
}

int ControllerManager::onlineCount() const
{
    int count = 0;
    for (const IndustrialController *controller : m_controllers)
    {
        if (controller->isOnline())
        {
            count++;
        }
    }
    return count;
}

int ControllerManager::getCountByType(IndustrialController::ControllerType type) const
{
    int count = 0;
    for (const IndustrialController *controller : m_controllers)
    {
        if (controller->controllerType() == type)
        {
            count++;
        }
    }
    return count;
}

void ControllerManager::removeOfflineControllers()
{
    for (int i = m_controllers.size() - 1; i >= 0; --i)
    {
        IndustrialController *controller = m_controllers[i];
        if (!controller->isOnline())
        {
            beginRemoveRows(QModelIndex(), i, i);

            // Remove from maps
            m_controllersByIp.remove(controller->ipAddress());
            m_controllersByMac.remove(controller->macAddress());

            // Remove from list
            m_controllers.removeAt(i);

            endRemoveRows();

            emit controllerRemoved(controller);
            controller->deleteLater();
        }
    }

    emit controllerCountChanged();
    emit statusChanged();
}

void ControllerManager::clearAll()
{
    beginResetModel();

    for (IndustrialController *controller : m_controllers)
    {
        controller->deleteLater();
    }

    m_controllers.clear();
    m_controllersByIp.clear();
    m_controllersByMac.clear();

    endResetModel();

    emit controllerCountChanged();
    emit statusChanged();
}

void ControllerManager::onControllerDataUpdated()
{
    IndustrialController *controller = qobject_cast<IndustrialController *>(sender());
    if (controller)
    {
        int index = findControllerIndex(controller);
        if (index >= 0)
        {
            emit dataChanged(createIndex(index, 0), createIndex(index, 0));
        }
    }
}

void ControllerManager::performPeriodicCleanup()
{
    // Check for timed-out controllers
    for (IndustrialController *controller : m_controllers)
    {
        controller->checkTimeout();
    }

    // Optionally remove offline controllers after a longer period
    // removeOfflineControllers();
}

void ControllerManager::setupCleanupTimer()
{
    m_cleanupTimer->setInterval(10000); // Check every 10 seconds
    m_cleanupTimer->setSingleShot(false);
    connect(m_cleanupTimer, &QTimer::timeout, this, &ControllerManager::performPeriodicCleanup);
    m_cleanupTimer->start();
}

int ControllerManager::findControllerIndex(IndustrialController *controller) const
{
    return m_controllers.indexOf(controller);
}