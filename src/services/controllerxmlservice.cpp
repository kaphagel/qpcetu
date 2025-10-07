#include "controllerxmlservice.h"
#include <QNetworkRequest>
#include <QDebug>
#include <QRegularExpression>

ControllerXmlService::ControllerXmlService(QObject *parent)
    : QObject(parent)
    , m_networkManager(new QNetworkAccessManager(this))
    , m_refreshTimer(new QTimer(this))
    , m_refreshInterval(5000) // Default 5 seconds
{
    connect(m_refreshTimer, &QTimer::timeout, this, &ControllerXmlService::onAutoRefreshTimeout);
}

ControllerXmlService::~ControllerXmlService()
{
    stopAutoRefresh();
}

void ControllerXmlService::setBaseUrl(const QString &baseUrl)
{
    m_baseUrl = baseUrl;
    if (!m_baseUrl.endsWith('/')) {
        m_baseUrl += '/';
    }
    qDebug() << "ControllerXmlService: Base URL set to" << m_baseUrl;
}

void ControllerXmlService::setRefreshInterval(int intervalMs)
{
    m_refreshInterval = intervalMs;
    if (m_refreshTimer->isActive()) {
        m_refreshTimer->setInterval(m_refreshInterval);
    }
    qDebug() << "ControllerXmlService: Refresh interval set to" << intervalMs << "ms";
}

void ControllerXmlService::fetchXmlFile(const QString &fileName)
{
    if (m_baseUrl.isEmpty()) {
        emit networkError("Base URL not set");
        return;
    }

    QUrl url(m_baseUrl + fileName);
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::UserAgentHeader, "Qt Industrial HMI Client");
    
    qDebug() << "ControllerXmlService: Fetching" << url.toString();
    
    QNetworkReply *reply = m_networkManager->get(request);
    connect(reply, &QNetworkReply::finished, this, &ControllerXmlService::onNetworkReply);
    
    m_currentFileName = fileName;
}

void ControllerXmlService::startAutoRefresh(const QString &fileName)
{
    m_currentFileName = fileName;
    m_refreshTimer->start(m_refreshInterval);
    qDebug() << "ControllerXmlService: Auto-refresh started for" << fileName;
    
    // Fetch immediately
    fetchXmlFile(fileName);
}

void ControllerXmlService::stopAutoRefresh()
{
    m_refreshTimer->stop();
    qDebug() << "ControllerXmlService: Auto-refresh stopped";
}

void ControllerXmlService::onNetworkReply()
{
    QNetworkReply *reply = qobject_cast<QNetworkReply*>(sender());
    if (!reply) return;

    reply->deleteLater();

    if (reply->error() != QNetworkReply::NoError) {
        QString error = QString("Network error: %1").arg(reply->errorString());
        qDebug() << "ControllerXmlService:" << error;
        emit networkError(error);
        return;
    }

    QByteArray xmlData = reply->readAll();
    qDebug() << "ControllerXmlService: Received" << xmlData.size() << "bytes of XML data";

    try {
        parseXmlData(xmlData);
        if (m_refreshTimer->isActive()) {
            emit xmlDataUpdated(m_currentPage);
        } else {
            emit xmlDataReceived(m_currentPage);
        }
    } catch (const std::exception &e) {
        QString error = QString("XML parsing error: %1").arg(e.what());
        qDebug() << "ControllerXmlService:" << error;
        emit parsingError(error);
    }
}

void ControllerXmlService::onAutoRefreshTimeout()
{
    if (!m_currentFileName.isEmpty()) {
        fetchXmlFile(m_currentFileName);
    }
}

void ControllerXmlService::parseXmlData(const QByteArray &xmlData)
{
    QXmlStreamReader reader(xmlData);
    m_currentPage = XmlPage(); // Reset current page

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "unit_page") {
                parseUnitPage(reader);
            }
        }
    }

    if (reader.hasError()) {
        throw std::runtime_error(reader.errorString().toStdString());
    }

    qDebug() << "ControllerXmlService: Parsed page with" << m_currentPage.forms.size() << "forms";
}

void ControllerXmlService::parseUnitPage(QXmlStreamReader &reader)
{
    // Read attributes
    QXmlStreamAttributes attrs = reader.attributes();
    m_currentPage.version = attrs.value("version").toString();

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "hdr") {
                QXmlStreamAttributes hdrAttrs = reader.attributes();
                m_currentPage.title = hdrAttrs.value("title").toString();
            } else if (reader.name() == "frm") {
                XmlForm form;
                parseForm(reader, form);
                if (!form.columns.isEmpty()) {
                    m_currentPage.forms.append(form);
                }
            }
        } else if (token == QXmlStreamReader::EndElement) {
            if (reader.name() == "unit_page") {
                break;
            }
        }
    }
}

void ControllerXmlService::parseForm(QXmlStreamReader &reader, XmlForm &form)
{
    QXmlStreamAttributes attrs = reader.attributes();
    form.type = attrs.value("type").toString();
    form.title = attrs.value("title").toString();

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "col") {
                XmlColumn column;
                parseColumn(reader, column);
                form.columns.append(column);
            }
        } else if (token == QXmlStreamReader::EndElement) {
            if (reader.name() == "frm") {
                break;
            }
        }
    }
}

void ControllerXmlService::parseColumn(QXmlStreamReader &reader, XmlColumn &column)
{
    QXmlStreamAttributes attrs = reader.attributes();
    column.width = attrs.value("width").toString();
    column.title = attrs.value("title").toString();

    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        
        if (token == QXmlStreamReader::StartElement) {
            if (reader.name() == "val") {
                XmlField field;
                parseField(reader, field);
                if (!field.id.isEmpty()) {
                    column.fields.append(field);
                }
            }
        } else if (token == QXmlStreamReader::EndElement) {
            if (reader.name() == "col") {
                break;
            }
        }
    }
}

void ControllerXmlService::parseField(QXmlStreamReader &reader, XmlField &field)
{
    QXmlStreamAttributes attrs = reader.attributes();
    
    field.id = attrs.value("id").toString();
    field.label = attrs.value("label").toString();
    field.var = attrs.value("var").toString();
    field.type = attrs.value("type").toString();
    field.unit = attrs.value("unit").toString();
    field.calc = attrs.value("calc").toString();
    field.hidden = (attrs.value("hidden").toString() == "true");
    field.optds = attrs.value("optds").toString();
    field.optdv = attrs.value("optdv").toString();

    // Skip to end of val element
    while (!reader.atEnd() && !reader.hasError()) {
        QXmlStreamReader::TokenType token = reader.readNext();
        if (token == QXmlStreamReader::EndElement && reader.name() == "val") {
            break;
        }
    }
}

QVariant ControllerXmlService::applyCalculation(const QString &calc, const QVariant &value)
{
    if (calc.isEmpty()) {
        return value;
    }

    // Handle simple calculations like "val/10" or "val==0?val:(val+1)/100"
    QString expression = calc;
    double val = value.toDouble();
    
    // Simple division: "val/10"
    QRegularExpression divRegex(R"(val/(\d+))");
    QRegularExpressionMatch divMatch = divRegex.match(expression);
    if (divMatch.hasMatch()) {
        double divisor = divMatch.captured(1).toDouble();
        return val / divisor;
    }

    // For now, return original value for complex expressions
    return value;
}