# CODE TEMPLATES

**Purpose**: Copy-paste code templates for AI agents. Reduce generation errors.  
**Last Updated**: October 30, 2025

---

## Template Index

1. [Qt Widget Page (Full Page UI)](#template-qt-widget-page)
2. [Qt Widget Component (Reusable Widget)](#template-qt-widget-component)
3. [ViewModel (Business Logic)](#template-viewmodel)
4. [Service (External System Integration)](#template-service)
5. [Repository (Data Persistence)](#template-repository)
6. [Domain Model (Pure C++)](#template-domain-model)
7. [Strategy (Communication Protocol)](#template-strategy)
8. [Command (Industrial Operation)](#template-command)
9. [Interface (Abstract Base Class)](#template-interface)

---

## Template: Qt Widget Page

**Use When**: Creating a new full-page UI component  
**Location**: `src/views/pages/[name]page.h` and `src/views/pages/[name]page.cpp`  
**Pattern**: MVVM (View + ViewModel)

### Header File: `[name]page.h`

```cpp
#pragma once
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>

class [Name]ViewModel;
class ThemeManager;

class [Name]Page : public QWidget {
    Q_OBJECT

public:
    explicit [Name]Page(QWidget* parent = nullptr);
    ~[Name]Page() override;

private slots:
    void onDataUpdated();
    void onErrorOccurred(const QString& message);
    void onRefreshClicked();

private:
    void setupUI();
    void connectSignals();
    void applyTheme();

    // ViewModel (business logic)
    [Name]ViewModel* m_viewModel;
    
    // UI Components
    QVBoxLayout* m_mainLayout;
    QLabel* m_titleLabel;
    QPushButton* m_refreshButton;
    
    // Services
    ThemeManager* m_themeManager;
};
```

### Implementation File: `[name]page.cpp`

```cpp
#include "[name]page.h"
#include "viewmodels/[name]viewmodel.h"
#include "ui/thememanager.h"
#include <QMessageBox>

[Name]Page::[Name]Page(QWidget* parent)
    : QWidget(parent)
    , m_viewModel(new [Name]ViewModel(this))
    , m_mainLayout(new QVBoxLayout(this))
    , m_titleLabel(new QLabel("[Name] Page", this))
    , m_refreshButton(new QPushButton("Refresh", this))
    , m_themeManager(ThemeManager::instance())
{
    setupUI();
    connectSignals();
    applyTheme();
}

[Name]Page::~[Name]Page() {
    // Qt parent-child relationship handles cleanup
}

void [Name]Page::setupUI() {
    // Apply 8pt grid spacing (RULE-073)
    m_mainLayout->setContentsMargins(16, 16, 16, 16);
    m_mainLayout->setSpacing(16);
    
    // Title label (22px font - RULE-060)
    QFont titleFont = m_titleLabel->font();
    titleFont.setPointSize(22);
    titleFont.setBold(true);
    m_titleLabel->setFont(titleFont);
    
    // Refresh button (60x60px minimum - RULE-050)
    m_refreshButton->setMinimumSize(60, 60);
    
    // Layout assembly
    m_mainLayout->addWidget(m_titleLabel);
    m_mainLayout->addWidget(m_refreshButton);
    m_mainLayout->addStretch();
    
    setLayout(m_mainLayout);
}

void [Name]Page::connectSignals() {
    // ViewModel → View
    connect(m_viewModel, &[Name]ViewModel::dataUpdated,
            this, &[Name]Page::onDataUpdated);
    connect(m_viewModel, &[Name]ViewModel::errorOccurred,
            this, &[Name]Page::onErrorOccurred);
    
    // View → ViewModel
    connect(m_refreshButton, &QPushButton::clicked,
            this, &[Name]Page::onRefreshClicked);
    
    // Theme changes
    connect(m_themeManager, &ThemeManager::themeChanged,
            this, &[Name]Page::applyTheme);
}

void [Name]Page::applyTheme() {
    // Use ThemeManager for colors (RULE-070)
    QString bgColor = m_themeManager->backgroundColor().name();
    QString textColor = m_themeManager->textColor().name();
    QString primaryColor = m_themeManager->primaryColor().name();
    
    setStyleSheet(QString(
        "QWidget { background-color: %1; color: %2; }"
        "QPushButton { "
        "  background-color: %3; "
        "  color: white; "
        "  border: none; "
        "  border-radius: 8px; "
        "  font-size: 16px; "
        "}"
        "QPushButton:hover { opacity: 0.8; }"
    ).arg(bgColor, textColor, primaryColor));
}

void [Name]Page::onDataUpdated() {
    // Update UI with new data from ViewModel
}

void [Name]Page::onErrorOccurred(const QString& message) {
    QMessageBox::warning(this, "Error", message);
}

void [Name]Page::onRefreshClicked() {
    m_viewModel->refresh();
}
```

---

## Template: Qt Widget Component

**Use When**: Creating a reusable widget (not a full page)  
**Location**: `src/views/widgets/[name]widget.h` and `src/views/widgets/[name]widget.cpp`

### Header File: `[name]widget.h`

```cpp
#pragma once
#include <QWidget>
#include <QLabel>
#include <QPushButton>

class [Name]Widget : public QWidget {
    Q_OBJECT

public:
    explicit [Name]Widget(QWidget* parent = nullptr);
    ~[Name]Widget() override;
    
    // Public API
    void setData(const QString& data);
    QString data() const;

signals:
    void clicked();
    void dataChanged(const QString& newData);

private:
    void setupUI();
    
    QLabel* m_dataLabel;
    QPushButton* m_actionButton;
    QString m_data;
};
```

---

## Template: ViewModel

**Use When**: Creating business logic for a UI component  
**Location**: `src/viewmodels/[name]viewmodel.h` and `src/viewmodels/[name]viewmodel.cpp`  
**Pattern**: MVVM pattern (business logic layer)

### Header File: `[name]viewmodel.h`

```cpp
#pragma once
#include <QObject>
#include <QString>
#include <QTimer>

class IDataSource;  // Interface dependency (RULE-113)

class [Name]ViewModel : public QObject {
    Q_OBJECT

public:
    explicit [Name]ViewModel(QObject* parent = nullptr);
    ~[Name]ViewModel() override;
    
    // Public API for View
    void refresh();
    void setDataSource(IDataSource* dataSource);
    
    // Data accessors
    QString currentValue() const { return m_currentValue; }

signals:
    void dataUpdated();
    void errorOccurred(const QString& message);
    void valueChanged(const QString& newValue);

public slots:
    void onDataSourceUpdated();

private:
    void fetchData();
    
    IDataSource* m_dataSource;
    QTimer* m_updateTimer;
    QString m_currentValue;
    bool m_isLoading;
};
```

### Implementation File: `[name]viewmodel.cpp`

```cpp
#include "[name]viewmodel.h"
#include "interfaces/IDataSource.h"

[Name]ViewModel::[Name]ViewModel(QObject* parent)
    : QObject(parent)
    , m_dataSource(nullptr)
    , m_updateTimer(new QTimer(this))
    , m_currentValue("")
    , m_isLoading(false)
{
    // Setup periodic updates (1 second interval)
    m_updateTimer->setInterval(1000);
    connect(m_updateTimer, &QTimer::timeout,
            this, &[Name]ViewModel::fetchData);
    m_updateTimer->start();
}

[Name]ViewModel::~[Name]ViewModel() {
    // Qt parent-child handles cleanup
}

void [Name]ViewModel::refresh() {
    fetchData();
}

void [Name]ViewModel::setDataSource(IDataSource* dataSource) {
    m_dataSource = dataSource;
    
    if (m_dataSource) {
        connect(m_dataSource, &IDataSource::dataReady,
                this, &[Name]ViewModel::onDataSourceUpdated);
    }
}

void [Name]ViewModel::fetchData() {
    if (!m_dataSource || m_isLoading) {
        return;
    }
    
    m_isLoading = true;
    // Fetch data from data source
    // Emit signals based on results
    m_isLoading = false;
}

void [Name]ViewModel::onDataSourceUpdated() {
    fetchData();
    emit dataUpdated();
}
```

---

## Template: Service

**Use When**: Integrating with external systems (Modbus, UDP, Database)  
**Location**: `src/services/[name]service.h` and `src/services/[name]service.cpp`  
**Pattern**: Service layer (external system integration)

### Header File: `[name]service.h`

```cpp
#pragma once
#include <QObject>
#include <QThread>

class [Name]Service : public QObject {
    Q_OBJECT

public:
    explicit [Name]Service(QObject* parent = nullptr);
    ~[Name]Service() override;
    
    void start();
    void stop();
    bool isRunning() const { return m_isRunning; }

signals:
    void started();
    void stopped();
    void dataReceived(const QVariant& data);
    void errorOccurred(const QString& error);

private slots:
    void doWork();

private:
    void connectToExternalSystem();
    void disconnectFromExternalSystem();
    
    QThread* m_workerThread;
    bool m_isRunning;
};
```

---

## Template: Repository

**Use When**: Implementing data persistence (database, file, memory)  
**Location**: `src/repositories/[name]repository.h` and `src/repositories/[name]repository.cpp`  
**Pattern**: Repository pattern (data persistence abstraction)

### Header File: `[name]repository.h`

```cpp
#pragma once
#include "interfaces/IRepository.h"
#include <QList>
#include <QString>

template<typename T>
class [Name]Repository : public IRepository<T> {
public:
    [Name]Repository();
    ~[Name]Repository() override;
    
    // IRepository interface implementation
    void save(const T& entity) override;
    T findById(const QString& id) override;
    QList<T> findAll() override;
    void deleteById(const QString& id) override;
    
private:
    QList<T> m_data;
};
```

---

## Template: Domain Model

**Use When**: Creating a data structure (pure C++, no Qt)  
**Location**: `src/models/[name].h` and `src/models/[name].cpp`  
**Pattern**: Domain model (pure C++, no Qt dependencies - RULE-102)

### Header File: `[name].h`

```cpp
#pragma once
#include <string>
#include <chrono>

class [Name] {
public:
    [Name]();
    [Name](const std::string& id, const std::string& name);
    ~[Name]();
    
    // Getters
    std::string id() const { return m_id; }
    std::string name() const { return m_name; }
    std::chrono::system_clock::time_point timestamp() const { return m_timestamp; }
    
    // Setters
    void setId(const std::string& id) { m_id = id; }
    void setName(const std::string& name) { m_name = name; }

private:
    std::string m_id;
    std::string m_name;
    std::chrono::system_clock::time_point m_timestamp;
};
```

---

## Template: Strategy

**Use When**: Implementing a new communication protocol  
**Location**: `src/strategies/[name]strategy.h` and `src/strategies/[name]strategy.cpp`  
**Pattern**: Strategy pattern (interchangeable algorithms)

### Header File: `[name]strategy.h`

```cpp
#pragma once
#include "interfaces/ICommunicationStrategy.h"

class [Name]Strategy : public ICommunicationStrategy {
public:
    [Name]Strategy();
    ~[Name]Strategy() override;
    
    // ICommunicationStrategy interface
    Result<QVariant> read(const QString& tag) override;
    Result<bool> write(const QString& tag, const QVariant& value) override;
    void connect(const QString& address, int port) override;
    void disconnect() override;
    bool isConnected() const override;

private:
    bool m_connected;
    QString m_address;
    int m_port;
};
```

---

## Template: Command

**Use When**: Implementing an industrial operation (undo/redo, audit trail)  
**Location**: `src/commands/[name]command.h` and `src/commands/[name]command.cpp`  
**Pattern**: Command pattern (encapsulate operations)

### Header File: `[name]command.h`

```cpp
#pragma once
#include "interfaces/ICommand.h"
#include <QDateTime>

class [Name]Command : public ICommand {
public:
    [Name]Command(const QString& target, const QVariant& value);
    ~[Name]Command() override;
    
    // ICommand interface
    void execute() override;
    void undo() override;
    QString description() const override;
    QDateTime timestamp() const override;

private:
    QString m_target;
    QVariant m_newValue;
    QVariant m_oldValue;
    QDateTime m_timestamp;
};
```

---

## Template: Interface

**Use When**: Defining a contract for dependency injection  
**Location**: `src/interfaces/I[Name].h` (header only)  
**Pattern**: Interface Segregation Principle (ISP)

### Header File: `I[Name].h`

```cpp
#pragma once
#include <QObject>
#include <QVariant>

class I[Name] {
public:
    virtual ~I[Name]() = default;
    
    // Pure virtual methods
    virtual void doSomething() = 0;
    virtual QVariant getData() const = 0;
    virtual bool setData(const QVariant& data) = 0;
};

// If Qt signals/slots needed, use separate interface
class I[Name]Signals : public QObject {
    Q_OBJECT
signals:
    void dataChanged(const QVariant& newData);
    void errorOccurred(const QString& error);
};
```

---

## Usage Instructions for AI Agents

### Step 1: Identify Component Type
- Full-page UI → Use **Qt Widget Page** template
- Reusable UI component → Use **Qt Widget Component** template
- Business logic → Use **ViewModel** template
- External system → Use **Service** template
- Data storage → Use **Repository** template
- Data structure → Use **Domain Model** template
- New protocol → Use **Strategy** template
- Industrial operation → Use **Command** template
- Abstraction → Use **Interface** template

### Step 2: Copy Template
- Copy entire template code
- Replace `[Name]` with actual class name (PascalCase)
- Replace `[name]` with actual file name (kebab-case)

### Step 3: Verify Against RULES.md
- Check file location (RULE-300 to RULE-310)
- Check naming conventions (RULE-010 to RULE-042)
- Check UI constraints if applicable (RULE-050 to RULE-073)
- Check pattern usage (RULE-200 to RULE-205)

### Step 4: Run VALIDATION.md Checklist
- Complete pre-commit checklist
- Verify all MUST/NEVER rules followed

---

**Last Updated**: October 30, 2025  
**Version**: 1.0 (AI-First Documentation)  
**Purpose**: Copy-paste code templates for AI agent code generation
