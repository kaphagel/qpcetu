#pragma once

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QXmlStreamReader>
#include <QTimer>
#include <QUrl>
#include <QMap>
#include <QVariant>

/**
 * @brief Service for fetching and parsing XML data from industrial controllers
 * 
 * Generic service that can work with any controller that exposes XML data
 * over HTTP. Handles network requests, XML parsing, and data extraction.
 */
class ControllerXmlService : public QObject
{
    Q_OBJECT

public:
    struct XmlField
    {
        QString id;
        QString label;
        QString var;
        QString type;
        QString unit;
        QString calc;
        QVariant value;
        bool hidden = false;
        QString optds;  // Option display strings
        QString optdv;  // Option display values
    };

    struct XmlColumn
    {
        QString title;
        QString width;
        QList<XmlField> fields;
    };

    struct XmlForm
    {
        QString type;
        QString title;
        QList<XmlColumn> columns;
    };

    struct XmlPage
    {
        QString title;
        QString version;
        QList<XmlForm> forms;
    };

    explicit ControllerXmlService(QObject *parent = nullptr);
    ~ControllerXmlService();

    void setBaseUrl(const QString &baseUrl);
    void setRefreshInterval(int intervalMs);
    
    void fetchXmlFile(const QString &fileName);
    void startAutoRefresh(const QString &fileName);
    void stopAutoRefresh();

    const XmlPage& getCurrentPage() const { return m_currentPage; }

signals:
    void xmlDataReceived(const XmlPage &page);
    void xmlDataUpdated(const XmlPage &page);
    void networkError(const QString &error);
    void parsingError(const QString &error);

private slots:
    void onNetworkReply();
    void onAutoRefreshTimeout();

private:
    void parseXmlData(const QByteArray &xmlData);
    void parseUnitPage(QXmlStreamReader &reader);
    void parseForm(QXmlStreamReader &reader, XmlForm &form);
    void parseColumn(QXmlStreamReader &reader, XmlColumn &column);
    void parseField(QXmlStreamReader &reader, XmlField &field);
    QVariant applyCalculation(const QString &calc, const QVariant &value);

    QNetworkAccessManager *m_networkManager;
    QTimer *m_refreshTimer;
    QString m_baseUrl;
    QString m_currentFileName;
    XmlPage m_currentPage;
    int m_refreshInterval;
};
