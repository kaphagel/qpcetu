#pragma once

#include <QObject>
#include <QVariantMap>
#include "../industrialcontroller.h"

/**
 * @brief Abstract strategy for controller-specific operations
 *
 * Different controller types require different protocols and data formats
 */
class ControllerStrategy : public QObject
{
    Q_OBJECT

public:
    explicit ControllerStrategy(QObject *parent = nullptr);
    virtual ~ControllerStrategy() = default;

    virtual QString protocolName() const = 0;
    virtual QStringList supportedOperations() const = 0;
    virtual bool validateConfiguration(const QVariantMap &config) const = 0;

    // Data operations
    virtual QVariantMap parseDiscoveryResponse(const QString &response) const = 0;
    virtual QString formatWriteRequest(const QString &register_addr, const QVariant &value) const = 0;
    virtual QVariant parseReadResponse(const QString &response) const = 0;

    // Connection management
    virtual int defaultPort() const = 0;
    virtual int heartbeatInterval() const = 0;
    virtual QString heartbeatMessage() const = 0;

signals:
    void dataReceived(const QVariantMap &data);
    void errorOccurred(const QString &error);

protected:
    virtual bool isValidResponse(const QString &response) const = 0;
};

/**
 * @brief Strategy for EPIC4/EPIC5 controllers (Opto22)
 */
class Epic4Strategy : public ControllerStrategy
{
    Q_OBJECT

public:
    explicit Epic4Strategy(QObject *parent = nullptr);

    QString protocolName() const override { return "EPIC4/EPIC5"; }
    QStringList supportedOperations() const override;
    bool validateConfiguration(const QVariantMap &config) const override;

    QVariantMap parseDiscoveryResponse(const QString &response) const override;
    QString formatWriteRequest(const QString &register_addr, const QVariant &value) const override;
    QVariant parseReadResponse(const QString &response) const override;

    int defaultPort() const override { return 502; }        // Modbus TCP
    int heartbeatInterval() const override { return 5000; } // 5 seconds
    QString heartbeatMessage() const override { return "Module Scan"; }

protected:
    bool isValidResponse(const QString &response) const override;

private:
    QVariantMap parseKeyValuePairs(const QString &response) const;
};

/**
 * @brief Strategy for SNAP PAC controllers
 */
class SnapPacStrategy : public ControllerStrategy
{
    Q_OBJECT

public:
    explicit SnapPacStrategy(QObject *parent = nullptr);

    QString protocolName() const override { return "SNAP_PAC"; }
    QStringList supportedOperations() const override;
    bool validateConfiguration(const QVariantMap &config) const override;

    QVariantMap parseDiscoveryResponse(const QString &response) const override;
    QString formatWriteRequest(const QString &register_addr, const QVariant &value) const override;
    QVariant parseReadResponse(const QString &response) const override;

    int defaultPort() const override { return 2001; }       // SNAP protocol
    int heartbeatInterval() const override { return 3000; } // 3 seconds
    QString heartbeatMessage() const override { return "SNAP_PING"; }

protected:
    bool isValidResponse(const QString &response) const override;
};

/**
 * @brief Factory for creating appropriate strategies
 */
class ControllerStrategyFactory
{
public:
    static ControllerStrategy *createStrategy(IndustrialController::ControllerType type, QObject *parent = nullptr);
    static QStringList supportedTypes();
};
