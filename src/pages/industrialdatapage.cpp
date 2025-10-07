#include "industrialdatapage.h"
#include "../ui/thememanager.h"
#include <QSplitter>
#include <QDebug>
#include <QTime>

IndustrialDataPage::IndustrialDataPage(QWidget *parent)
    : QWidget(parent)
    , m_mainLayout(nullptr)
    , m_scrollArea(nullptr)
    , m_contentWidget(nullptr)
    , m_contentLayout(nullptr)
    , m_titleLabel(nullptr)
    , m_statusLabel(nullptr)
    , m_xmlService(nullptr)
    , m_virtualKeyboard(nullptr)
    , m_isInitialized(false)
{
    // Initialize virtual keyboard for touch screen input FIRST
    m_virtualKeyboard = new VirtualKeyboard(this);
    
    setupUI();
    
    // Create XML service
    m_xmlService = new ControllerXmlService(this);
    connect(m_xmlService, &ControllerXmlService::xmlDataReceived,
            this, &IndustrialDataPage::onXmlDataReceived);
    connect(m_xmlService, &ControllerXmlService::xmlDataUpdated,
            this, &IndustrialDataPage::onXmlDataUpdated);
    connect(m_xmlService, &ControllerXmlService::networkError,
            this, &IndustrialDataPage::onNetworkError);
    connect(m_xmlService, &ControllerXmlService::parsingError,
            this, &IndustrialDataPage::onParsingError);
}

IndustrialDataPage::~IndustrialDataPage()
{
    if (m_xmlService) {
        m_xmlService->stopAutoRefresh();
    }
}

void IndustrialDataPage::setupUI()
{
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(16, 16, 16, 16);
    m_mainLayout->setSpacing(16);

    // Title label
    m_titleLabel = new QLabel("Industrial Controller Data");
    m_titleLabel->setObjectName("pageTitle");
    applyCleanStyling(m_titleLabel, "title");
    m_mainLayout->addWidget(m_titleLabel);

    // Status label
    m_statusLabel = new QLabel("Connecting to controller...");
    m_statusLabel->setObjectName("statusLabel");
    applyCleanStyling(m_statusLabel, "status");
    m_mainLayout->addWidget(m_statusLabel);

    // Scroll area for content
    m_scrollArea = new QScrollArea();
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setFrameStyle(QFrame::NoFrame);
    applyCleanStyling(m_scrollArea, "scrollArea");

    // Content widget
    m_contentWidget = new QWidget();
    m_contentLayout = new QVBoxLayout(m_contentWidget);
    m_contentLayout->setContentsMargins(0, 0, 0, 0);
    m_contentLayout->setSpacing(16);

    m_scrollArea->setWidget(m_contentWidget);
    m_mainLayout->addWidget(m_scrollArea);

    // Add virtual keyboard at bottom - initially hidden
    m_mainLayout->addWidget(m_virtualKeyboard);

    setLayout(m_mainLayout);
}

void IndustrialDataPage::setControllerUrl(const QString &baseUrl)
{
    if (m_xmlService) {
        m_xmlService->setBaseUrl(baseUrl);
        m_statusLabel->setText("Controller URL set: " + baseUrl);
    }
}

void IndustrialDataPage::loadXmlFile(const QString &fileName)
{
    if (!m_xmlService) {
        m_statusLabel->setText("Error: XML service not initialized");
        return;
    }

    m_statusLabel->setText("Loading " + fileName + "...");
    m_xmlService->fetchXmlFile(fileName);
}

void IndustrialDataPage::onXmlDataReceived(const ControllerXmlService::XmlPage &page)
{
    qDebug() << "IndustrialDataPage: Received XML data for page:" << page.title;
    
    m_statusLabel->setText("Connected - Data loaded successfully");
    clearLayout();
    createPageLayout(page);
    m_isInitialized = true;

    // Start auto-refresh for live updates
    m_xmlService->startAutoRefresh("unit/p_operation.xml");
}

void IndustrialDataPage::onXmlDataUpdated(const ControllerXmlService::XmlPage &page)
{
    if (m_isInitialized) {
        updateFieldValues(page);
        m_statusLabel->setText("Live data - Last update: " + QTime::currentTime().toString());
    }
}

void IndustrialDataPage::onNetworkError(const QString &error)
{
    m_statusLabel->setText("Network Error: " + error);
    qDebug() << "IndustrialDataPage: Network error:" << error;
}

void IndustrialDataPage::onParsingError(const QString &error)
{
    m_statusLabel->setText("Data Error: " + error);
    qDebug() << "IndustrialDataPage: Parsing error:" << error;
}

void IndustrialDataPage::clearLayout()
{
    if (!m_contentLayout) return;

    while (QLayoutItem *item = m_contentLayout->takeAt(0)) {
        if (QWidget *widget = item->widget()) {
            widget->deleteLater();
        }
        delete item;
    }
    m_fieldWidgets.clear();
}

void IndustrialDataPage::createPageLayout(const ControllerXmlService::XmlPage &page)
{
    // Update title
    if (!page.title.isEmpty()) {
        m_titleLabel->setText("Controller: " + page.title.toUpper());
    }

    // Create forms
    for (const auto &form : page.forms) {
        if (form.type == "cnt" && !form.columns.isEmpty()) {
            createFormWidget(form);
        } else if (form.type == "sub" && !form.title.isEmpty()) {
            // Create sub-header
            QLabel *subHeader = new QLabel(form.title.toUpper());
            subHeader->setObjectName("subHeader");
            applyCleanStyling(subHeader, "subheader");
            m_contentLayout->addWidget(subHeader);
        }
    }

    m_contentLayout->addStretch();
}

void IndustrialDataPage::createFormWidget(const ControllerXmlService::XmlForm &form)
{
    // Create vertical layout for list-style display
    QVBoxLayout *formLayout = new QVBoxLayout();
    formLayout->setSpacing(8);
    formLayout->setContentsMargins(16, 16, 16, 16);

    // Extract all fields from all columns into a single list with group headers
    QList<QPair<QString, ControllerXmlService::XmlField>> allFields;
    
    for (const auto &column : form.columns) {
        QString groupName = column.title.isEmpty() ? "General" : column.title;
        
        for (const auto &field : column.fields) {
            if (!field.hidden && !field.id.isEmpty()) {
                allFields.append(qMakePair(groupName, field));
            }
        }
    }

    // Create list widget with group headers
    QString currentGroup = "";
    for (const auto &fieldPair : allFields) {
        const QString &groupName = fieldPair.first;
        const ControllerXmlService::XmlField &field = fieldPair.second;
        
        // Add group header if this is a new group
        if (groupName != currentGroup) {
            if (!currentGroup.isEmpty()) {
                // Add some spacing between groups
                QFrame *spacer = new QFrame();
                spacer->setFixedHeight(12);
                formLayout->addWidget(spacer);
            }
            
            QLabel *groupHeader = new QLabel("📋 " + groupName.toUpper());
            applyCleanStyling(groupHeader, "groupHeader");
            formLayout->addWidget(groupHeader);
            
            currentGroup = groupName;
        }
        
        // Create field widget
        QWidget *fieldWidget = createListFieldWidget(field);
        if (fieldWidget) {
            formLayout->addWidget(fieldWidget);
            m_fieldWidgets[field.id] = fieldWidget;
        }
    }

    // Add stretch to fill remaining space
    formLayout->addStretch();

    // Create container widget
    QWidget *formWidget = new QWidget();
    formWidget->setLayout(formLayout);
    applyCleanStyling(formWidget, "form");

    m_contentLayout->addWidget(formWidget);
}

QWidget* IndustrialDataPage::createColumnWidget(const ControllerXmlService::XmlColumn &column)
{
    QGroupBox *groupBox = new QGroupBox();
    if (!column.title.isEmpty()) {
        groupBox->setTitle(column.title.toUpper());
    }
    
    QVBoxLayout *columnLayout = new QVBoxLayout(groupBox);
    columnLayout->setSpacing(12);
    columnLayout->setContentsMargins(12, 16, 12, 12);

    // Parse width percentage
    int widthPercent = 30; // Default
    if (!column.width.isEmpty()) {
        QString widthStr = column.width;
        widthStr.remove('%');
        widthPercent = widthStr.toInt();
    }

    // Create fields
    for (const auto &field : column.fields) {
        if (!field.hidden && !field.id.isEmpty()) {
            QWidget *fieldWidget = createFieldWidget(field);
            if (fieldWidget) {
                columnLayout->addWidget(fieldWidget);
                m_fieldWidgets[field.id] = fieldWidget;
            }
        }
    }

    columnLayout->addStretch();
    
    // Set size policy based on width
    groupBox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);
    applyCleanStyling(groupBox, "column");

    return groupBox;
}

QWidget* IndustrialDataPage::createFieldWidget(const ControllerXmlService::XmlField &field)
{
    QWidget *fieldContainer = new QWidget();
    QHBoxLayout *fieldLayout = new QHBoxLayout(fieldContainer);
    fieldLayout->setContentsMargins(0, 0, 0, 0);
    fieldLayout->setSpacing(8);

    // Label
    QLabel *label = new QLabel(field.label);
    label->setMinimumWidth(120);
    label->setWordWrap(true);
    applyCleanStyling(label, "fieldLabel");
    fieldLayout->addWidget(label);

    // Value widget
    QWidget *valueWidget = nullptr;
    
    if (field.type == "drp") {
        // Dropdown
        QComboBox *combo = new QComboBox();
        if (!field.optds.isEmpty()) {
            QStringList options = field.optds.split(',');
            combo->addItems(options);
        }
        applyCleanStyling(combo, "fieldCombo");
        valueWidget = combo;
    } else if (field.type == "btn") {
        // Button
        QPushButton *button = new QPushButton("Execute");
        applyCleanStyling(button, "fieldButton");
        valueWidget = button;
    } else {
        // Read-only value
        QLineEdit *lineEdit = new QLineEdit();
        lineEdit->setReadOnly(true);
        lineEdit->setText("--");
        applyCleanStyling(lineEdit, "fieldValue");
        valueWidget = lineEdit;
    }

    fieldLayout->addWidget(valueWidget);

    // Unit label
    if (!field.unit.isEmpty()) {
        QLabel *unitLabel = new QLabel(field.unit);
        applyCleanStyling(unitLabel, "fieldUnit");
        fieldLayout->addWidget(unitLabel);
    }

    fieldLayout->addStretch();
    
    applyCleanStyling(fieldContainer, "fieldContainer");
    return fieldContainer;
}

QWidget* IndustrialDataPage::createListFieldWidget(const ControllerXmlService::XmlField &field)
{
    QWidget *fieldContainer = new QWidget();
    QHBoxLayout *fieldLayout = new QHBoxLayout(fieldContainer);
    fieldLayout->setContentsMargins(8, 4, 8, 4);
    fieldLayout->setSpacing(12);

    // Label (compact width for list view)
    QLabel *label = new QLabel(field.label);
    label->setMinimumWidth(150);
    label->setMaximumWidth(200);
    label->setWordWrap(false);
    label->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Preferred);
    applyCleanStyling(label, "listFieldLabel");
    fieldLayout->addWidget(label);

    // Value widget (more compact for list view)
    QWidget *valueWidget = nullptr;
    
    if (field.type == "drp") {
        // Dropdown (compact)
        QComboBox *combo = new QComboBox();
        combo->setMinimumWidth(150);
        combo->setMaximumWidth(250);
        if (!field.optds.isEmpty()) {
            QStringList options = field.optds.split(',');
            combo->addItems(options);
        }
        applyCleanStyling(combo, "listFieldCombo");
        valueWidget = combo;
    } else if (field.type == "btn") {
        // Button (compact)
        QPushButton *button = new QPushButton("Execute");
        button->setMinimumWidth(100);
        button->setMaximumWidth(150);
        applyCleanStyling(button, "listFieldButton");
        valueWidget = button;
    } else {
        // Text input field - determine if it should be editable
        QLineEdit *lineEdit = new QLineEdit();
        
        // Make field editable if it has a variable name (likely an input field)
        // or if it's not just a display value
        bool isInputField = !field.var.isEmpty() || 
                           field.label.contains("Set", Qt::CaseInsensitive) ||
                           field.label.contains("Input", Qt::CaseInsensitive) ||
                           field.label.contains("Target", Qt::CaseInsensitive) ||
                           field.label.contains("Command", Qt::CaseInsensitive);
        
        lineEdit->setReadOnly(!isInputField);
        
        if (isInputField) {
            lineEdit->setText("0"); // Default input value
            lineEdit->setPlaceholderText("Enter value...");
        } else {
            lineEdit->setText("--"); // Display value placeholder
        }
        
        lineEdit->setMinimumWidth(100);
        lineEdit->setMaximumWidth(200);
        applyCleanStyling(lineEdit, isInputField ? "listFieldInput" : "listFieldValue");
        
        // Install virtual keyboard for editable input fields
        if (isInputField && m_virtualKeyboard) {
            m_virtualKeyboard->installInputEventFilter(lineEdit);
        }
        
        valueWidget = lineEdit;
    }

    fieldLayout->addWidget(valueWidget);

    // Unit label (compact)
    if (!field.unit.isEmpty()) {
        QLabel *unitLabel = new QLabel(field.unit);
        unitLabel->setMinimumWidth(30);
        unitLabel->setMaximumWidth(80);
        applyCleanStyling(unitLabel, "listFieldUnit");
        fieldLayout->addWidget(unitLabel);
    }

    // Field ID as help text (if different from label)
    if (!field.id.isEmpty() && field.id != field.label) {
        QLabel *idLabel = new QLabel("[" + field.id + "]");
        idLabel->setStyleSheet("color: gray; font-style: italic; font-size: 11px;");
        fieldLayout->addWidget(idLabel);
    }

    fieldLayout->addStretch();
    
    applyCleanStyling(fieldContainer, "listFieldContainer");
    return fieldContainer;
}

void IndustrialDataPage::applyCleanStyling(QWidget *widget, const QString &widgetType)
{
    ThemeManager *tm = ThemeManager::instance();
    
    if (widgetType == "title") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  font-size: 24px; "
            "  font-weight: bold; "
            "  color: %1; "
            "  padding: 8px 0px; "
            "}"
        ).arg(tm->colorString(ThemeManager::PrimaryText)));
        
    } else if (widgetType == "subheader") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  font-size: 18px; "
            "  font-weight: 600; "
            "  color: %1; "
            "  padding: 12px 0px 8px 0px; "
            "  border-bottom: 1px solid %2; "
            "}"
        ).arg(tm->colorString(ThemeManager::PrimaryText))
         .arg(tm->colorString(ThemeManager::SecondaryText)));
        
    } else if (widgetType == "column") {
        widget->setStyleSheet(QString(
            "QGroupBox { "
            "  background-color: %1; "
            "  border: none; "
            "  border-radius: 8px; "
            "  font-weight: 600; "
            "  color: %2; "
            "  padding-top: 16px; "
            "}"
            "QGroupBox::title { "
            "  subcontrol-origin: margin; "
            "  left: 12px; "
            "  padding: 0 8px 0 8px; "
            "}"
        ).arg(tm->colorString(ThemeManager::CardBackground))
         .arg(tm->colorString(ThemeManager::PrimaryText)));
         
    } else if (widgetType == "fieldLabel") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  color: %1; "
            "  font-size: 14px; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryText)));
        
    } else if (widgetType == "fieldValue") {
        widget->setStyleSheet(QString(
            "QLineEdit { "
            "  background-color: %1; "
            "  border: none; "
            "  border-radius: 4px; "
            "  padding: 8px; "
            "  color: %2; "
            "  font-weight: 500; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryBackground))
         .arg(tm->colorString(ThemeManager::PrimaryText)));
         
    } else if (widgetType == "groupHeader") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  font-size: 16px; "
            "  font-weight: 700; "
            "  color: %1; "
            "  padding: 12px 8px 6px 8px; "
            "  background-color: %2; "
            "  border-radius: 6px; "
            "  margin: 4px 0px; "
            "}"
        ).arg(tm->colorString(ThemeManager::PrimaryText))
         .arg(tm->colorString(ThemeManager::SecondaryBackground)));
         
    } else if (widgetType == "listFieldLabel") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  color: %1; "
            "  font-size: 14px; "
            "  font-weight: 500; "
            "  padding: 4px 8px; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryText)));
        
    } else if (widgetType == "listFieldValue") {
        widget->setStyleSheet(QString(
            "QLineEdit { "
            "  background-color: %1; "
            "  border: 1px solid %2; "
            "  border-radius: 4px; "
            "  padding: 6px 8px; "
            "  color: %3; "
            "  font-weight: 500; "
            "  font-size: 14px; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryBackground))
         .arg(tm->colorString(ThemeManager::BorderColor))
         .arg(tm->colorString(ThemeManager::PrimaryText)));
         
    } else if (widgetType == "listFieldInput") {
        widget->setStyleSheet(QString(
            "QLineEdit { "
            "  background-color: %1; "
            "  border: 2px solid %2; "
            "  border-radius: 4px; "
            "  padding: 6px 8px; "
            "  color: %3; "
            "  font-weight: 600; "
            "  font-size: 14px; "
            "}"
            "QLineEdit:focus { "
            "  border: 2px solid %4; "
            "  background-color: %5; "
            "}"
            "QLineEdit:hover { "
            "  border: 2px solid %6; "
            "}"
        ).arg(tm->colorString(ThemeManager::MainBackground))
         .arg(tm->colorString(ThemeManager::ButtonBackground))
         .arg(tm->colorString(ThemeManager::PrimaryText))
         .arg(tm->colorString(ThemeManager::ButtonHover))
         .arg(tm->colorString(ThemeManager::SecondaryBackground))
         .arg(tm->colorString(ThemeManager::ButtonHover)));
         
    } else if (widgetType == "listFieldCombo") {
        widget->setStyleSheet(QString(
            "QComboBox { "
            "  background-color: %1; "
            "  border: 1px solid %2; "
            "  border-radius: 4px; "
            "  padding: 6px 8px; "
            "  color: %3; "
            "  font-size: 14px; "
            "}"
            "QComboBox::drop-down { "
            "  border: none; "
            "}"
            "QComboBox::down-arrow { "
            "  width: 12px; "
            "  height: 12px; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryBackground))
         .arg(tm->colorString(ThemeManager::BorderColor))
         .arg(tm->colorString(ThemeManager::PrimaryText)));
         
    } else if (widgetType == "listFieldButton") {
        widget->setStyleSheet(QString(
            "QPushButton { "
            "  background-color: %1; "
            "  border: none; "
            "  border-radius: 4px; "
            "  padding: 8px 16px; "
            "  color: white; "
            "  font-weight: 600; "
            "  font-size: 14px; "
            "}"
            "QPushButton:hover { "
            "  background-color: %2; "
            "}"
            "QPushButton:pressed { "
            "  background-color: %3; "
            "}"
        ).arg(tm->colorString(ThemeManager::ButtonBackground))
         .arg(tm->colorString(ThemeManager::ButtonHover))
         .arg(tm->colorString(ThemeManager::ButtonPressed)));
         
    } else if (widgetType == "listFieldUnit") {
        widget->setStyleSheet(QString(
            "QLabel { "
            "  color: %1; "
            "  font-size: 12px; "
            "  font-style: italic; "
            "  padding: 4px; "
            "}"
        ).arg(tm->colorString(ThemeManager::SecondaryText)));
        
    } else if (widgetType == "listFieldContainer") {
        widget->setStyleSheet(QString(
            "QWidget { "
            "  background-color: %1; "
            "  border-radius: 6px; "
            "  margin: 2px 0px; "
            "}"
            "QWidget:hover { "
            "  background-color: %2; "
            "}"
        ).arg(tm->colorString(ThemeManager::MainBackground))
         .arg(tm->colorString(ThemeManager::SecondaryBackground)));
    }
}

void IndustrialDataPage::updateFieldValues(const ControllerXmlService::XmlPage &page)
{
    // This would update live values when we have actual data
    // For now, just update timestamp
    qDebug() << "IndustrialDataPage: Updating field values";
}