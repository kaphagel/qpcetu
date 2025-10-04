# API Documentation

## Industrial HMI Core APIs

This section will contain comprehensive API documentation for the Qt5-based industrial HMI system.

### 🏗️ Core Architecture APIs

#### **Controller Management**
- `ControllerManager` - Multi-controller lifecycle management
- `IndustrialController` - Base controller abstraction
- `ControllerCardWidget` - UI representation of controllers

#### **Strategy Pattern APIs**
- `ControllerStrategy` - Base strategy interface
- `Epic4Strategy` - EPIC4 controller protocol implementation
- `SnapPacStrategy` - SNAP_PAC controller protocol implementation

#### **State Machine APIs**
- `ControllerStateMachine` - Connection lifecycle state management
- State transitions: Disconnected → Connecting → Connected → Running → Fault

#### **Command Pattern APIs**
- `Command` - Base command interface with undo/redo support
- `ControllerOperationCommand` - Industrial operation commands
- Audit trail and operation logging

#### **Event System APIs**
- `IndustrialEventManager` - Observer pattern implementation
- Real-time event propagation and alarm management

#### **Data Management APIs**
- `DataRepository` - Repository pattern for data persistence
- `CircularDataBuffer` - Real-time data circular buffer implementation
- Historical data storage and retrieval

### 🌐 Communication APIs

#### **UDP Discovery**
- `UdpService` - Controller discovery via UDP broadcast
- Port 3250 "Module Scan" protocol implementation
- Structured response parsing for EPIC4/SNAP_PAC controllers

#### **Modbus TCP**
- `libmodbus` integration for industrial Modbus communication
- Real-time data acquisition and control
- Robust error handling and auto-reconnection

### 🎨 User Interface APIs

#### **Theme Management**
- `ThemeManager` - Singleton theme management system
- Multi-theme support: Dark, Light, High Contrast, Apple Light/Dark
- Dynamic color management with `ColorRole` enumeration

#### **Modern UI Components**
- `ModernMainWindow` - Main HMI interface with touch optimization
- `ControllerCardWidget` - Industrial controller representation
- `ThemeSettingsWidget` - Theme configuration interface

#### **Apple Design Integration**
- `AppleStyle` - iOS/iPadOS inspired styling for industrial use
- Touch-optimized components with 60x60px minimum targets
- Clean, borderless design with background differentiation

### 📊 Data Visualization APIs

#### **Real-Time Graphs**
- Custom QPainter-based graph rendering
- Smooth 60fps performance with efficient drawing
- Large dataset handling without memory leaks

#### **Progress Indicators**
- `AnimatedProgressBar` - Industrial-grade progress visualization
- Real-time status indicators with theme-aware styling

### 🔌 Plugin Architecture APIs

#### **Plugin Management**
- `ControllerPluginInterface` - Plugin interface for extensibility
- `ControllerPluginManager` - Plugin lifecycle management
- Support for future controller types and protocols

## 📝 API Documentation Generation

API documentation is automatically generated using:
- **Doxygen**: C++ class and method documentation
- **Qt Documentation**: Integration with Qt5 documentation system
- **Markdown**: Human-readable API guides and examples

### **Documentation Standards**
All public APIs follow these documentation standards:
- Comprehensive class and method descriptions
- Parameter and return value documentation
- Usage examples and code samples
- Thread safety and performance considerations
- Industrial environment requirements

---

*Note: Detailed API documentation will be generated automatically from source code comments using Doxygen. This serves as an overview of the available APIs and their organization.*

**Last Updated**: October 4, 2025
**Architecture**: Enterprise-grade with 6 core design patterns