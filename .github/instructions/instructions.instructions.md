---
applyTo: '**'
---

# Project Context

This project is a real-time data v## AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs for C++ components.
- ✅ Cr---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don't introduce non-Qt GUI frameworks.  
- ❌ Don't mix UI with business logic.

---

# Industrial HMI Architecture

## System Overview

```
┌─────────────────────────────────────────────────────────────┐
│                    QML Presentation Layer                   │
│  ┌─────────────────┐ ┌─────────────────┐ ┌───────────────┐ │
│  │  Main Dashboard │ │ Controller Pages│ │ Alarm Summary │ │
│  │  (Overview)     │ │ (Type-specific) │ │ (Events)      │ │
│  └─────────────────┘ └─────────────────┘ └───────────────┘ │
└─────────────────────────────────────────────────────────────┘
                               │
┌─────────────────────────────────────────────────────────────┐
│                     C++ Business Logic                      │
│                                                             │
│  ┌─────────────────┐ ┌─────────────────┐ ┌───────────────┐ │
│  │ ControllerManager│ │ EventManager   │ │ CommandManager│ │
│  │   (MVVM Model)  │ │  (Observer)    │ │  (Command)    │ │
│  └─────────────────┘ └─────────────────┘ └───────────────┘ │
│                                                             │
│  ┌─────────────────┐ ┌─────────────────┐ ┌───────────────┐ │
│  │ StateMachine    │ │ Strategy Factory│ │ Plugin Manager│ │
│  │  (State)        │ │  (Strategy)     │ │  (Plugin)     │ │
│  └─────────────────┘ └─────────────────┘ └───────────────┘ │
└─────────────────────────────────────────────────────────────┘
                               │
┌─────────────────────────────────────────────────────────────┐
│                    Infrastructure Layer                     │
│                                                             │
│  ┌─────────────────┐ ┌─────────────────┐ ┌───────────────┐ │
│  │   UdpService    │ │  DataRepository │ │ CircularBuffer│ │
│  │  (Discovery)    │ │  (Repository)   │ │  (Real-time)  │ │
│  └─────────────────┘ └─────────────────┘ └───────────────┘ │
└─────────────────────────────────────────────────────────────┘
```

## Directory Structure

```
src/
├── commands/           # Command Pattern implementations
│   ├── command.h/cpp
│   └── controlleroperationcommand.h/cpp
├── statemachine/       # State Machine Pattern
│   └── controllerstatemachine.h/cpp
├── strategies/         # Strategy Pattern for protocols
│   ├── controllerstrategy.h/cpp
│   ├── epic4strategy.h/cpp
│   └── snappacstrategy.h/cpp
├── events/            # Observer Pattern + Event System
│   └── industrialeventmanager.h/cpp
├── data/              # Repository Pattern
│   ├── datarepository.h/cpp
│   └── circulardatabuffer.h/cpp
├── plugins/           # Plugin Architecture
│   ├── controllerplugininterface.h
│   └── controllerpluginmanager.cpp
├── pages/             # QML Page ViewModels
└── core/              # Core models and services
```

## Implementation Priority

1. **Phase 1**: Core Patterns
   - Strategy Pattern for controller protocols
   - State Machine for connection management
   - Command Pattern for operations

2. **Phase 2**: Data Management
   - Repository Pattern for persistence
   - Event System for alarms
   - Circular Buffer for real-time data

3. **Phase 3**: Extensibility
   - Plugin Architecture
   - QML Integration
   - Testing Frameworkesponding `.qml` files for UI components.
- ✅ Use **Q_PROPERTY** for data binding between C++ and QML.
- ✅ Implement **real-time updates** with proper signal/slot connections.
- ✅ Use **Canvas** or custom painting for graph rendering.
- ✅ Follow **architectural patterns**: Strategy, State Machine, Command, Observer, Repository, Plugin.
- ✅ Ensure **thread safety** in multi-threaded components.
- ✅ Implement **proper error handling** with industrial robustness.
- ✅ Use **smart pointers** for memory management.
- ✅ Document all **public interfaces** with Doxygen comments.
- ❌ Don't mix UI logic in C++ backend classes.
- ❌ Don't create blocking operations in main thread.
- ❌ Don't forget to register C++ types for QML usage.
- ❌ Don't implement direct network calls in UI components.
- ❌ Don't bypass the established architectural patterns.on desktop application built with **Qt5 and QML**.  
It uses Qt Quick for modern UI, C++ backend for data processing, and Modbus TCP for real-time data acquisition.

## High-Level Goals
- Create a modern QML-based user interface with sci-fi aesthetics.
- Implement real-time data visualization with 4 graphs in 2x2 layout.
- Integrate Modbus TCP client for industrial data acquisition.
- Ensure cross-platform compatibility (Linux, Windows, macOS).
- Follow enterprise-grade architecture patterns for industrial HMI systems.

## Architecture Patterns
This project follows proven design patterns for industrial HMI applications:

### 1. **MVVM (Model-View-ViewModel)**
- **QML Views**: UI presentation layer
- **C++ ViewModels**: Business logic and data transformation
- **C++ Models**: Data management (ControllerManager, etc.)

### 2. **Strategy Pattern** (`src/strategies/`)
- **ControllerStrategy**: Abstract base for protocol handling
- **Epic4Strategy**: EPIC4/EPIC5 Opto22 controllers
- **SnapPacStrategy**: SNAP PAC controllers
- **StrategyFactory**: Creates appropriate strategy based on controller type

### 3. **State Machine Pattern** (`src/statemachine/`)
- **ControllerStateMachine**: Manages controller lifecycle
- **States**: Disconnected → Connecting → Connected → Running → Fault → Maintenance
- **Thread-safe transitions** with proper error handling

### 4. **Command Pattern** (`src/commands/`)
- **Command**: Abstract base for all industrial operations
- **ControllerOperationCommand**: Start/Stop/Reset/Configure operations
- **Undo/Redo support** for critical operations
- **Operation logging** for audit trails

### 5. **Observer Pattern + Event System** (`src/events/`)
- **IndustrialEventManager**: Central event hub for alarms and notifications
- **Event prioritization**: Info → Warning → Alarm → Critical
- **Acknowledgment system** with user tracking
- **Real-time event propagation** to QML

### 6. **Repository Pattern** (`src/data/`)
- **DataRepository**: SQLite-based historical data storage
- **CircularDataBuffer**: High-performance real-time data buffer
- **Configuration persistence** for controller settings
- **Event logging** with search and filtering

### 7. **Plugin Architecture** (`src/plugins/`)
- **ControllerPluginInterface**: Standard interface for new controller types
- **PluginManager**: Dynamic loading of controller protocols
- **Extensibility** without modifying core application
- **Customer-specific protocols** via plugins

## Workflow
1. **Define core patterns and interfaces first** (Strategy, Command, Repository).
2. **Implement controller-specific strategies** for each protocol type.
3. **Build state machines** for robust connection management.
4. **Create event system** for industrial alarms and notifications.
5. **Implement data persistence** with repository pattern.
6. **Build QML UI** on top of well-defined C++ ViewModels.
7. Write **comprehensive tests** for each architectural component.

## Documentation
- Document all public classes and methods with **Doxygen-style comments**.
- Document **QML components** with clear property descriptions.
- Keep diagrams (if needed) in **Mermaid or PlantUML**, with modern syntax.
- Main spec lives in Markdown — YAML configs can be derived if structured input is needed.

---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs for C++ components.
- ✅ Create corresponding `.qml` files for UI components.
- ✅ Use **Q_PROPERTY** for data binding between C++ and QML.
- ✅ Implement **real-time updates** with proper signal/slot connections.
- ✅ Use **Canvas** or custom painting for graph rendering.
- ❌ Don't mix UI logic in C++ backend classes.
- ❌ Don't create blocking operations in main thread.
- ❌ Don't forget to register C++ types for QML usage.

## High-Level Goals
- Create a modern QML-based user interface with sci-fi aesthetics.
- Implement real-time data visualization with 4 graphs in 2x2 layout.
- Integrate Modbus TCP client for industrial data acquisition.
- Ensure cross-platform compatibility (Linux, Windows, macOS).
- Follow MVVM pattern for QML/C++ integration.

---

# AI Coding Guidelines

## General
- Always write **modern C++ (C++17)** when possible.
- Prefer **RAII** (Resource Acquisition Is Initialization) for resource management.
- Use **smart pointers (std::unique_ptr, std::shared_ptr)** instead of raw new/delete.
- Keep headers and implementation files **separated** (`.h` and `.cpp`).
- Keep classes **focused and under ~500 lines** — split if needed.

## Qt5 QML Specific Guidelines
- Use **QML for UI** and **C++ for backend logic**.
- Implement **MVVM pattern**: QML Views, C++ ViewModels, C++ Models.
- Use **Q_PROPERTY** for QML-C++ data binding.
- Use **Q_INVOKABLE** for methods called from QML.
- Register C++ types with **qmlRegisterType** for QML usage.
- Use **QQmlApplicationEngine** for QML application loading.
- Prefer **QtQuick.Controls** for standard UI components.

## Architecture Guidelines
- Follow **Strategy Pattern** for controller-specific protocols.
- Use **State Machine Pattern** for connection lifecycle management.
- Implement **Command Pattern** for industrial operations with undo/redo.
- Use **Observer Pattern** for real-time event propagation.
- Apply **Repository Pattern** for data persistence and historical storage.
- Design for **Plugin Architecture** to support future controller types.
- Ensure **thread safety** in all real-time components.
- Implement **proper error handling** with industrial-grade robustness.

## Real-Time Data Guidelines
- Use **circular buffers** for efficient data storage.
- Implement **QTimer** for periodic data updates.
- Use **Canvas** or **custom QQuickPaintedItem** for graph rendering.
- Ensure **smooth 60fps** rendering with efficient drawing.
- Handle **large datasets** without memory leaks.

## Modbus TCP Guidelines
- Use **libmodbus** for Modbus TCP communication.
- Implement **robust error handling** and auto-reconnection.
- Use **separate thread** for network operations if needed.
- Apply **data scaling and validation** before display.
- Provide **connection status feedback** to UI.  

## Workflow
1. **Define core classes and interfaces first** (data models, services).  
2. **Build UI components on top**, wiring them with signals/slots.  
3. Write **unit tests** for logic-heavy classes (non-UI) using `QTest`.  
4. Keep build portable with **CMake** or **qmake** (depending on project setup).  

## Documentation
- Document all public classes and methods with **Doxygen-style comments**.  
- Keep diagrams (if needed) in **Mermaid or PlantUML**, with modern syntax.  
- Main spec lives in Markdown — YAML configs can be derived if structured input is needed.  

---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don’t introduce non-Qt GUI frameworks.  
- ❌ Don’t mix UI with business logic.  
