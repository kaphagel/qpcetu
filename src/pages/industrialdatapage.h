#ifndef INDUSTRIALDATAPAGE_H
#define INDUSTRIALDATAPAGE_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <QGroupBox>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include "../services/controllerxmlservice.h"
#include "../ui/virtualkeyboard.h"

/**
 * @brief Page for displaying industrial controller XML data in Qt widgets
 * 
 * Creates a Qt widget interface equivalent to the original web interface
 * by transforming XML data using the same logic as the XSLT file.
 */
class IndustrialDataPage : public QWidget
{
    Q_OBJECT

public:
    explicit IndustrialDataPage(QWidget *parent = nullptr);
    ~IndustrialDataPage();

    void setControllerUrl(const QString &baseUrl);
    void loadXmlFile(const QString &fileName);

private slots:
    void onXmlDataReceived(const ControllerXmlService::XmlPage &page);
    void onXmlDataUpdated(const ControllerXmlService::XmlPage &page);
    void onNetworkError(const QString &error);
    void onParsingError(const QString &error);

private:
    void setupUI();
    void clearLayout();
    void createPageLayout(const ControllerXmlService::XmlPage &page);
    void createFormWidget(const ControllerXmlService::XmlForm &form);
    QWidget* createColumnWidget(const ControllerXmlService::XmlColumn &column);
    QWidget* createFieldWidget(const ControllerXmlService::XmlField &field);
    QWidget* createListFieldWidget(const ControllerXmlService::XmlField &field);
    
    void applyCleanStyling(QWidget *widget, const QString &widgetType);
    void updateFieldValues(const ControllerXmlService::XmlPage &page);

    QVBoxLayout *m_mainLayout;
    QScrollArea *m_scrollArea;
    QWidget *m_contentWidget;
    QVBoxLayout *m_contentLayout;
    QLabel *m_titleLabel;
    QLabel *m_statusLabel;

    ControllerXmlService *m_xmlService;
    QMap<QString, QWidget*> m_fieldWidgets; // Maps field ID to widget for updates
    VirtualKeyboard *m_virtualKeyboard;     // Touch screen virtual keyboard
    
    bool m_isInitialized;
};

#endif // INDUSTRIALDATAPAGE_H