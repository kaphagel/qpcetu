# Industrial HMI Architecture Guide

**Project:** Qt5 C++ Industrial Touch Screen HMI  
**Version:** 1.0  
**Last Updated:** October 30, 2025

---

## Table of Contents

1. [Executive Summary](#executive-summary)
2. [Architectural Principles](#architectural-principles)
3. [Design Patterns](#design-patterns)
4. [Technology Stack](#technology-stack)
5. [System Architecture](#system-architecture)
6. [Directory Structure](#directory-structure)
7. [Coding Standards](#coding-standards)
8. [Testing Strategy](#testing-strategy)
9. [Deployment Strategy](#deployment-strategy)

---

## Executive Summary

This industrial HMI application is built with **Qt5 Widgets and C++** for real-time industrial control and monitoring. The architecture follows **SOLID principles** and **Clean Architecture** patterns to ensure maintainability, testability, and extensibility for 24/7 industrial operations.

### Key Design Goals

- ✅ **Reliability**: Zero-crash operation for 24/7 industrial use
- ✅ **Maintainability**: Easy to fix bugs without breaking existing features
- ✅ **Extensibility**: Add new controller types without modifying core code
- ✅ **Testability**: Comprehensive testing without requiring physical hardware
- ✅ **Performance**: Real-time responsiveness with 60fps UI updates
- ✅ **Compliance**: Audit trails and validation for industrial standards (FDA 21 CFR Part 11, ISO)

---

## Architectural Principles

### 1. SOLID Principles (Mandatory)

#### **Single Responsibility Principle (SRP)**
- Each class has ONE reason to change
- UI classes handle ONLY presentation
- ViewModels handle ONLY business logic
- Services handle ONLY one domain concern

**Example:**
```cpp
// ❌ WRONG - Multiple responsibilities
class GraphsPage : public QWidget {
    void updateUI();
    void readModbusData();      // Should be in service
    void saveToDatabase();      // Should be in repository
    void validateData();        // Should be in validator
};

// ✅ CORRECT - Single responsibility
class GraphsPage : public QWidget {
    void updateUI();  // ONLY UI updates
private:
    GraphViewModel* m_viewModel;  // Delegates business logic
};
```

#### **Open/Closed Principle (OCP)**
- Open for extension, closed for modification
- Use Strategy Pattern for protocols
- Use Plugin System for new controllers

**Example:**
```cpp
// ✅ Adding new protocol requires NO modification to existing code
class IControllerCommunication {
public:
    virtual ~IControllerCommunication() = default;
    virtual Result<QVariant> read(const QString& tag) = 0;
};

class ModbusTcpCommunication : public IControllerCommunication { };
class UdpCommunication : public IControllerCommunication { };
class NewProtocolCommunication : public IControllerCommunication { };  // Just add!
```

#### **Liskov Substitution Principle (LSP)**
- Derived classes must be substitutable for base classes
- Maintain honest contracts
- No unexpected exceptions in overrides

**Example:**
```cpp
// ✅ All repositories are interchangeable
IDataRepository* repo = new SqliteRepository();
repo = new InMemoryRepository();  // Swap without breaking code
repo = new TimeSeriesRepository();  // All work the same way
```

#### **Interface Segregation Principle (ISP)**
- Clients shouldn't depend on interfaces they don't use
- Small, focused interfaces

**Example:**
```cpp
// ✅ Split large interfaces into role-based interfaces
class IReadable { virtual QVariant read(const QString& tag) = 0; };
class IWritable { virtual bool write(const QString& tag, const QVariant& value) = 0; };
class IConfigurable { virtual void configure(const QVariantMap& config) = 0; };

// Controller implements only what it needs
class ReadOnlyController : public IReadable { };
class FullController : public IReadable, public IWritable, public IConfigurable { };
```

#### **Dependency Inversion Principle (DIP)**
- Depend on abstractions, not concretions
- Use dependency injection

**Example:**
```cpp
// ✅ Depend on interface, inject via constructor
class GraphsPage : public QWidget {
public:
    GraphsPage(IDataSource* dataSource, QWidget* parent)
        : QWidget(parent), m_dataSource(dataSource) {
    }
private:
    IDataSource* m_dataSource;  // Interface, not concrete class
};
```

---

### 2. Clean Architecture (Layered)

```
┌─────────────────────────────────────────────────────┐
│  Presentation Layer (Qt Widgets)                    │
│  - Pages, Widgets, Dialogs                          │
│  - Pure UI code only                                │
│  - Depends on: Application Layer                    │
├─────────────────────────────────────────────────────┤
│  Application Layer (ViewModels)                     │
│  - Business logic                                   │
│  - Use cases                                        │
│  - Depends on: Domain Layer + Infrastructure        │
├─────────────────────────────────────────────────────┤
│  Domain Layer (Models)                              │
│  - Pure business objects                            │
│  - No dependencies (Qt or external libraries)       │
│  - Independent, reusable                            │
├─────────────────────────────────────────────────────┤
│  Infrastructure Layer (Services, Repositories)      │
│  - External services (Modbus, UDP, Database)        │
│  - Implements interfaces defined in Domain          │
│  - Depends on: Domain Layer                         │
└─────────────────────────────────────────────────────┘
```

**Dependency Rule:** Dependencies flow INWARD only. Inner layers never depend on outer layers.

---

## Design Patterns

### Primary Patterns (Must Use)

#### 1. **Model-View-ViewModel (MVVM)**
**Purpose:** Separate UI from business logic

```cpp
// Model: Pure data
class DataPoint {
    QDateTime timestamp;
    QString tag;
    double value;
};

// ViewModel: Business logic + Qt signals
class GraphViewModel : public QObject {
    Q_OBJECT
signals:
    void dataPointAdded(const DataPoint& point);
public:
    void addDataPoint(const DataPoint& point);
private:
    QVector<DataPoint> m_dataPoints;
};

// View: Pure UI
class GraphsPage : public QWidget {
    GraphsPage(GraphViewModel* viewModel);
};
```

#### 2. **Strategy Pattern**
**Purpose:** Interchangeable communication protocols

```cpp
class ICommunicationStrategy {
public:
    virtual ~ICommunicationStrategy() = default;
    virtual Result<QVariant> read(const QString& tag) = 0;
    virtual Result<bool> write(const QString& tag, const QVariant& value) = 0;
};

class ModbusTcpStrategy : public ICommunicationStrategy { };
class UdpStrategy : public ICommunicationStrategy { };
```

#### 3. **Repository Pattern**
**Purpose:** Abstract data persistence

```cpp
class IDataRepository {
public:
    virtual ~IDataRepository() = default;
    virtual void save(const DataPoint& point) = 0;
    virtual QVector<DataPoint> query(const QueryCriteria& criteria) = 0;
};

class SqliteRepository : public IDataRepository { };
class CircularBufferRepository : public IDataRepository { };
```

#### 4. **Observer Pattern**
**Purpose:** Event-driven communication (via Qt signals/slots)

```cpp
class EventManager : public QObject {
    Q_OBJECT
signals:
    void alarmRaised(const Alarm& alarm);
    void dataUpdated(const QString& tag, double value);
    void connectionStateChanged(ConnectionState state);
};
```

#### 5. **Command Pattern**
**Purpose:** Audit trails and undo/redo

```cpp
class ICommand {
public:
    virtual ~ICommand() = default;
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual QString description() const = 0;
    virtual QDateTime timestamp() const = 0;
};

class WriteValueCommand : public ICommand {
    // Implements write with undo support
};
```

#### 6. **State Machine Pattern**
**Purpose:** Connection lifecycle management

```cpp
enum class ConnectionState {
    Disconnected,
    Connecting,
    Connected,
    Running,
    Fault,
    Reconnecting
};

// Use Qt State Machine Framework
QStateMachine* createConnectionStateMachine();
```

#### 7. **Factory Pattern**
**Purpose:** Centralized object creation

```cpp
class ControllerFactory {
public:
    static std::unique_ptr<IController> create(
        const QString& type, 
        const QVariantMap& config
    );
};
```

#### 8. **Singleton Pattern** (Use Sparingly)
**Purpose:** Global services only

```cpp
// ✅ Appropriate for:
ThemeManager::instance()
LogManager::instance()
EventManager::instance()

// ❌ NOT appropriate for:
Controllers, Repositories, ViewModels
```

---

## Technology Stack

### Core Technologies

| **Category** | **Choice** | **Version** | **Rationale** |
|-------------|-----------|------------|---------------|
| **Language** | C++ | C++17 | Modern features, industrial-grade performance |
| **UI Framework** | Qt5 Widgets | 5.15+ | Touch-optimized, cross-platform, mature |
| **Build System** | CMake | 3.16+ | Industry standard, cross-platform |
| **Testing** | Qt Test | 5.15+ | Native Qt integration |
| **Database** | SQLite | 3.x | Embedded, reliable, zero-config |
| **Protocols** | libmodbus | 3.1.x | Industry-standard Modbus TCP |
| **Version Control** | Git | 2.x | Standard for collaboration |

### Architecture Decisions

| **Decision** | **Choice** | **Alternatives Rejected** |
|-------------|-----------|---------------------------|
| **Concurrency** | Qt Threads + Signals/Slots | ❌ Async/await, Actor model |
| **Error Handling** | Result Type + Error Signals | ❌ Exceptions, Return codes |
| **State Management** | Qt State Machine | ❌ Manual flags, Redux |
| **Data Flow** | Observer (Signals/Slots) | ❌ Pull-based polling |
| **Persistence** | SQLite + Circular Buffer | ❌ All in-memory, PostgreSQL |
| **Logging** | Structured JSON | ❌ Plain text, Binary |
| **Configuration** | JSON + QSettings | ❌ XML, Binary |
| **Deployment** | Qt Installer + Delta Updates | ❌ Manual copy, Full reinstall |
| **Security** | RBAC + Audit Logs | ❌ No security, Complex PKI |
| **Plugins** | Qt Plugin System | ❌ Custom loader, No plugins |

---

## System Architecture

### High-Level Component Diagram

```
┌─────────────────────────────────────────────────────────────┐
│                      ModernMainWindow                       │
│  (Presentation Layer - Qt Widgets)                          │
│                                                             │
│  ┌──────────┐  ┌──────────┐  ┌──────────┐  ┌──────────┐   │
│  │Overview  │  │Dashboard │  │  Graphs  │  │Settings  │   │
│  │  Page    │  │   Page   │  │   Page   │  │   Page   │   │
│  └────┬─────┘  └────┬─────┘  └────┬─────┘  └────┬─────┘   │
└───────┼────────────┼─────────────┼─────────────┼──────────┘
        │            │             │             │
        └────────────┴─────────────┴─────────────┘
                     │
        ┌────────────┴────────────┐
        │                         │
┌───────▼─────────┐    ┌─────────▼────────┐
│   ViewModels    │    │  Navigation      │
│ (Application)   │    │    Manager       │
│                 │    │                  │
│ • GraphViewModel│    │ • PageId enum    │
│ • MainViewModel │    │ • History stack  │
└───────┬─────────┘    └──────────────────┘
        │
┌───────▼──────────────────────────────────────────┐
│           Domain Layer (Models)                  │
│                                                  │
│  DataPoint, Controller, Alarm, Configuration    │
│  (Pure C++, no Qt dependencies)                  │
└───────┬──────────────────────────────────────────┘
        │
┌───────▼──────────────────────────────────────────┐
│      Infrastructure Layer (Services)             │
│                                                  │
│  ┌──────────────┐  ┌──────────────┐             │
│  │ UdpService   │  │ModbusService │             │
│  └──────────────┘  └──────────────┘             │
│                                                  │
│  ┌──────────────┐  ┌──────────────┐             │
│  │DataRepository│  │EventManager  │             │
│  └──────────────┘  └──────────────┘             │
└──────────────────────────────────────────────────┘
```

### Data Flow Architecture

```
┌─────────────┐
│  Modbus TCP │ (192.168.10.243:502)
└──────┬──────┘
       │
       ▼
┌─────────────────┐
│ ModbusService   │ (Worker Thread)
│ (IDataSource)   │
└──────┬──────────┘
       │ Signal: dataReceived(tag, value)
       ▼
┌─────────────────┐
│ GraphViewModel  │ (Main Thread)
│ (Business Logic)│
└──────┬──────────┘
       │ Signal: displayValueChanged(value)
       ▼
┌─────────────────┐
│  GraphsPage     │ (Main Thread)
│  (UI Update)    │
└─────────────────┘
```

---

## Directory Structure

```
project-root/
├── .github/
│   └── instructions/
│       └── instructions.instructions.md   # Build instructions, AI coding rules
│
├── docs/                                  # 📚 Documentation
│   ├── ARCHITECTURE.md                    # This file
│   ├── DESIGN_PATTERNS.md                 # Pattern catalog
│   ├── CODING_STANDARDS.md                # Code style guide
│   ├── API_REFERENCE.md                   # Interface documentation
│   └── DEPLOYMENT.md                      # Deployment guide
│
├── src/                                   # 💻 Source code
│   ├── interfaces/                        # 🔌 Core abstractions (ISP)
│   │   ├── IDataSource.h
│   │   ├── IDataSink.h
│   │   ├── ICommunicationStrategy.h
│   │   ├── IRepository.h
│   │   └── IController.h
│   │
│   ├── models/                            # 📊 Domain models (pure C++)
│   │   ├── datapoint.h/cpp
│   │   ├── controller.h/cpp
│   │   ├── alarm.h/cpp
│   │   └── configuration.h/cpp
│   │
│   ├── viewmodels/                        # 🎯 Business logic (MVVM)
│   │   ├── mainviewmodel.h/cpp
│   │   ├── graphviewmodel.h/cpp
│   │   └── controllerlistviewmodel.h/cpp
│   │
│   ├── views/                             # 🎨 UI components
│   │   ├── pages/
│   │   │   ├── overviewpage.h/cpp
│   │   │   ├── graphspage.h/cpp
│   │   │   ├── dashboardpage.h/cpp
│   │   │   └── settingspage.h/cpp
│   │   ├── widgets/
│   │   │   ├── controllercardwidget.h/cpp
│   │   │   └── graphwidget.h/cpp
│   │   └── dialogs/
│   │       └── configurationdialog.h/cpp
│   │
│   ├── services/                          # ⚙️ Infrastructure services
│   │   ├── udpservice.h/cpp
│   │   ├── modbusservice.h/cpp
│   │   ├── alarmservice.h/cpp
│   │   └── loggerservice.h/cpp
│   │
│   ├── repositories/                      # 💾 Data persistence
│   │   ├── datarepository.h/cpp
│   │   ├── sqliterepository.h/cpp
│   │   ├── circularbufferrepository.h/cpp
│   │   └── configurationrepository.h/cpp
│   │
│   ├── strategies/                        # 🔄 Strategy pattern
│   │   ├── communicationstrategy.h
│   │   ├── modbustcpstrategy.h/cpp
│   │   ├── udpstrategy.h/cpp
│   │   └── restapistrategy.h/cpp
│   │
│   ├── commands/                          # 📝 Command pattern
│   │   ├── command.h
│   │   ├── writevaluecommand.h/cpp
│   │   └── configurationcommand.h/cpp
│   │
│   ├── statemachines/                     # 🎰 State management
│   │   ├── connectionstatemachine.h/cpp
│   │   └── applicationstatemachine.h/cpp
│   │
│   ├── factories/                         # 🏭 Object creation
│   │   ├── controllerfactory.h/cpp
│   │   └── pagefactory.h/cpp
│   │
│   ├── events/                            # 📢 Event system
│   │   ├── eventmanager.h/cpp
│   │   └── event.h
│   │
│   ├── plugins/                           # 🔌 Plugin system
│   │   ├── controllerplugininterface.h
│   │   └── controllerpluginmanager.cpp
│   │
│   ├── ui/                                # 🎨 UI framework
│   │   ├── modernmainwindow.h/cpp
│   │   ├── thememanager.h/cpp
│   │   ├── hamburgermenu.h/cpp
│   │   └── virtualkeyboard.h/cpp
│   │
│   ├── navigation/                        # 🧭 Navigation system
│   │   ├── navigationmanager.h/cpp
│   │   └── breadcrumbwidget.h/cpp
│   │
│   └── utils/                             # 🛠️ Utilities
│       ├── result.h                       # Result<T> for error handling
│       ├── logger.h/cpp
│       └── validator.h/cpp
│
├── tests/                                 # 🧪 Test suite
│   ├── unit/
│   ├── integration/
│   └── e2e/
│
├── resources/                             # 📦 Application resources
│   ├── icons/
│   ├── themes/
│   └── overview.qrc
│
├── scripts/                               # 🚀 Build scripts
│   ├── build-linux.sh
│   ├── build-windows.sh
│   └── build-all.sh
│
├── CMakeLists.txt                         # Build configuration
└── README.md                              # Project overview
```

---

## Coding Standards

### File Naming Conventions

```cpp
// Headers: lowercase with .h extension
datasource.h
modbusservice.h

// Implementation: lowercase with .cpp extension
datasource.cpp
modbusservice.cpp

// Interfaces: prefix with 'I'
IDataSource.h
IController.h

// One class per file (exception: small helper structs)
```

### Code Style

```cpp
// Class names: PascalCase
class GraphViewModel { };

// Method names: camelCase
void updateData();
void processAlarm();

// Member variables: m_ prefix + camelCase
private:
    IDataSource* m_dataSource;
    QTimer* m_updateTimer;

// Constants: UPPER_SNAKE_CASE
const int MAX_BUFFER_SIZE = 1000;

// Namespaces: lowercase
namespace industrial::hmi { }

// Always use:
- #pragma once (not include guards)
- Auto for complex types
- nullptr (not NULL)
- override keyword

// Always separate .h and .cpp files
// Header: Declaration only
// CPP: Implementation only
```

### Qt-Specific Guidelines

```cpp
// Use Qt naming for Qt-specific code
class ModernMainWindow : public QMainWindow {
    Q_OBJECT  // Required for signals/slots

public:
    explicit ModernMainWindow(QWidget* parent = nullptr);
    
signals:
    void dataUpdated(const QString& tag, double value);
    
public slots:
    void onDataReceived();
    
private:
    QTimer* m_timer;  // Qt classes use m_ prefix too
};

// Always use:
- signals/slots (not callbacks)
- QSharedPointer/QScopedPointer for Qt objects
- QString, QDateTime (not std::string, time_t)
```

---

## Testing Strategy

### Testing Pyramid

```
      /\
     /E2E\        ← 10%: Full UI automation (slow)
    /──────\
   /  Integ  \    ← 20%: Service integration tests
  /──────────\
 /    Unit    \   ← 70%: Fast unit tests
/──────────────\
```

### Unit Testing (70%)

```cpp
// Test ViewModels and Models (no UI)
class GraphViewModelTest : public QObject {
    Q_OBJECT
    
private slots:
    void testAddDataPoint() {
        // Arrange
        GraphViewModel viewModel;
        DataPoint point("TAG1", 25.3, QDateTime::currentDateTime());
        
        // Act
        viewModel.addDataPoint(point);
        
        // Assert
        QCOMPARE(viewModel.dataPointCount(), 1);
        QCOMPARE(viewModel.lastValue(), 25.3);
    }
    
    void testDataSourceIntegration() {
        // Use mock data source
        MockDataSource mockSource;
        mockSource.setReturnValue("TAG1", 42.0);
        
        GraphViewModel viewModel(&mockSource);
        viewModel.refreshData();
        
        QCOMPARE(viewModel.lastValue(), 42.0);
    }
};
```

### Integration Testing (20%)

```cpp
// Test service interactions (no UI, but real services)
class ModbusServiceTest : public QObject {
    Q_OBJECT
    
private slots:
    void testRealModbusConnection() {
        ModbusService service("127.0.0.1", 502);  // Test server
        
        Result<QVariant> result = service.read("TAG1");
        
        QVERIFY(result.isSuccess());
        QVERIFY(result.value().toDouble() > 0);
    }
};
```

### E2E Testing (10%)

```cpp
// Test full application flow
void testCompleteWorkflow() {
    ModernMainWindow window;
    window.show();
    
    // Navigate to graphs page
    QTest::mouseClick(window.hamburgerButton(), Qt::LeftButton);
    QTest::mouseClick(window.graphsMenuItem(), Qt::LeftButton);
    
    // Wait for data update
    QTest::qWait(2000);
    
    // Verify graph updated
    QVERIFY(window.graphsPage()->hasData());
}
```

---

## Deployment Strategy

### Build Process

```bash
# Linux native build
cd scripts && ./build-linux.sh

# Windows cross-compilation (MXE)
cd scripts && ./build-windows.sh

# Build all platforms
cd scripts && ./build-all.sh
```

### Deployment Artifacts

```
Linux:
├── bin/ModernSciFiHMI (823KB)
├── Required Qt5 libraries (system)
└── Configuration files

Windows:
├── bin/ModernSciFiHMI.exe (49MB, fully static)
├── No external dependencies
└── Configuration files
```

### Update Strategy

1. **Delta Updates**: Only changed files downloaded
2. **Rollback**: Previous version kept for safety
3. **Zero-Downtime**: Update during maintenance window
4. **Validation**: Checksum verification before deployment

---

## References

- [SOLID Principles](https://en.wikipedia.org/wiki/SOLID)
- [Clean Architecture](https://blog.cleancoder.com/uncle-bob/2012/08/13/the-clean-architecture.html)
- [Qt Documentation](https://doc.qt.io/qt-5/)
- [Design Patterns (GoF)](https://en.wikipedia.org/wiki/Design_Patterns)
- [Industrial HMI Best Practices](https://www.automationworld.com/factory/hmi-scada)

---

**Document Version:** 1.0  
**Maintained By:** Development Team  
**Review Cycle:** Quarterly
