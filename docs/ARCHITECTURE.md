# Industrial HMI Application

## Architecture Overview

This industrial HMI (Human-Machine Interface) application follows enterprise-grade design patterns for robust, scalable industrial automation systems.

## Design Patterns Implemented

### 1. **Strategy Pattern** (`src/strategies/`)
Handles different controller protocols with pluggable strategies:
- **Epic4Strategy**: EPIC4/EPIC5 Opto22 controllers with Modbus TCP
- **SnapPacStrategy**: SNAP PAC controllers with custom protocol
- **ControllerStrategyFactory**: Creates appropriate strategy based on controller type

**Usage Example:**
```cpp
ControllerStrategy* strategy = ControllerStrategyFactory::createStrategy(IndustrialController::EPIC4);
QVariantMap data = strategy->parseDiscoveryResponse("Protocol version = 1.00;FB type = EPIC4;...");
```

### 2. **Command Pattern** (`src/commands/`)
Encapsulates industrial operations with undo/redo support:
- **Command**: Abstract base for all operations
- **ControllerOperationCommand**: Start/Stop/Reset/Configure operations
- **Audit logging** for all industrial operations

**Usage Example:**
```cpp
auto command = new ControllerOperationCommand("192.168.1.100", ControllerOperationCommand::Start);
if (command->execute()) {
    qDebug() << "Operation successful";
    // Later: command->undo() if needed
}
```

### 3. **State Machine Pattern** (`src/statemachine/`)
Manages controller connection lifecycle with proper state transitions:
- **States**: Disconnected → Connecting → Connected → Running → Fault → Maintenance
- **Thread-safe state transitions**
- **Automatic heartbeat monitoring**

**Usage Example:**
```cpp
auto stateMachine = new ControllerStateMachine("192.168.1.100");
connect(stateMachine, &ControllerStateMachine::stateChanged, 
        this, &MyClass::onControllerStateChanged);
stateMachine->connectToController();
```

### 4. **MVVM (Model-View-ViewModel)**
- **QML Views**: UI presentation layer
- **C++ ViewModels**: Business logic (ControllerManager, etc.)
- **C++ Models**: Data management with Qt's model/view framework

### 5. **Observer Pattern + Event System** (`src/events/`)
Real-time event propagation for industrial alarms:
- **IndustrialEventManager**: Central event hub
- **Event prioritization**: Info → Warning → Alarm → Critical
- **Acknowledgment system** with user tracking

### 6. **Repository Pattern** (`src/data/`)
Data persistence and historical storage:
- **DataRepository**: SQLite-based historical data
- **CircularDataBuffer**: High-performance real-time buffer
- **Configuration management**

### 7. **Plugin Architecture** (`src/plugins/`)
Extensible controller support without core modifications:
- **ControllerPluginInterface**: Standard interface
- **Dynamic plugin loading**
- **Customer-specific protocols**

## Project Structure

```
src/
├── commands/              # Command Pattern
│   ├── command.h/cpp
│   └── controlleroperationcommand.h/cpp
├── statemachine/          # State Machine Pattern
│   └── controllerstatemachine.h/cpp
├── strategies/            # Strategy Pattern
│   ├── controllerstrategy.h/cpp
│   ├── epic4strategy.h/cpp
│   └── snappacstrategy.h/cpp
├── events/               # Observer + Event System
│   └── industrialeventmanager.h/cpp
├── data/                 # Repository Pattern
│   ├── datarepository.h/cpp
│   └── circulardatabuffer.h/cpp
├── plugins/              # Plugin Architecture
│   ├── controllerplugininterface.h
│   └── controllerpluginmanager.cpp
├── pages/                # QML Page ViewModels
│   └── controlleroverview.h/cpp
└── core/                 # Core models and services
    ├── industrialcontroller.h/cpp
    ├── controllermanager.h/cpp
    └── udpservice.h/cpp
```

## Building

### Linux (Development)
```bash
cd build
make
./bin/SciFiDataScreen
```

### Windows (Cross-compilation)
```bash
# Using Docker for automated cross-compilation
docker build -t scifi-app .
docker run --rm -v $(pwd):/output scifi-app
```

## Features

- **Multi-controller support**: EPIC4, EPIC5, SNAP_PAC protocols
- **Real-time data visualization**: 4-graph dashboard in 2x2 layout
- **UDP discovery**: Automatic controller detection on network
- **State management**: Robust connection lifecycle handling
- **Command auditing**: Full operation logging with undo/redo
- **Cross-platform**: Linux, Windows via MXE cross-compilation
- **Plugin extensible**: Add new controller types via plugins

## Controller Discovery Protocol

The application broadcasts "Module Scan" on UDP port 3250 and parses responses like:
```
Protocol version = 1.00;FB type = EPIC4;Module version = 1.99;MAC = C0-22-F1-41-03-3A;IP = 192.168.10.243;SN = 255.255.255.0;GW = 192.168.10.1;DHCP = OFF;PSWD = OFF;HN = Andritz;DNS1 = 0.0.0.0;DNS2 = 0.0.0.0;
```

## Industrial Standards Compliance

- **Event acknowledgment** system for alarm management
- **State machine** approach for robust connection handling
- **Command pattern** for operation auditing and rollback
- **Modular architecture** for easy maintenance and testing
- **Thread-safe** real-time data handling

## Contributing

When adding new controller types:
1. Implement `ControllerStrategy` interface
2. Add to `ControllerStrategyFactory`
3. Create specific command classes if needed
4. Update discovery parsing logic
5. Add comprehensive tests

## License

This project demonstrates enterprise-grade architecture patterns for industrial HMI applications.