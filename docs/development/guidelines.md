---
applyTo: '**'
---

# Project Context

This project is a real-time industrial HMI touch screen application built with **Qt5 Widgets and C++**.  
It uses Qt Widgets for the user interface, C++ backend for data processing, and UDP/Modbus TCP for real-time data acquisition.

## Touch Screen Optimization Requirements
**CRITICAL**: This HMI is primarily designed for **touch screen interfaces** in industrial environments:
- **Minimum button sizes**: 44x44px (recommended 60x60px) for reliable touch targets
- **Touch-friendly spacing**: Minimum 8px gaps between interactive elements
- **Large, clear fonts**: Minimum 14px for readability from arm's length
- **High contrast colors**: Essential for visibility in various lighting conditions
- **Gesture support**: Swipe navigation, pinch-to-zoom for graphs where applicable
- **Feedback mechanisms**: Visual/haptic feedback for touch interactions
- **Glove-friendly design**: Accommodate work gloves and safety equipment

## Current UI Architecture (Qt Widgets)
The application currently uses **Qt5 Widgets** optimized for touch interaction:
- **ModernMainWindow**: Touch-optimized HMI with large buttons and clear layouts
- **ControllerCardWidget**: Touch-friendly controller cards with gesture support
- **Qt Widgets** components sized and spaced for touch interaction
- **C++ UI classes** with `.h/.cpp` implementation files
- **Working cross-platform** builds (Linux + Windows) with touch support

## Touch Screen Design Principles
- **Finger-first design**: All interactions must work reliably with finger touch
- **Visual hierarchy**: Clear distinction between interactive and informational elements
- **Error prevention**: Confirmation dialogs for critical operations
- **Accessibility**: Support for different hand sizes and dexterity levels
- **Industrial durability**: Design for frequent use and harsh environments
- **Moderate frame usage**: Clean interfaces following Apple design principles

## Frame Usage Guidelines
## Design System Guidelines
**CRITICAL**: Follow **clean, minimal design** principles for professional industrial interfaces:

### **Theme System**
- **Multi-theme support**: Dark, Light, High Contrast, Apple Light, Apple Dark themes available
- **Theme toggle**: Industrial-friendly button in header bar for quick theme switching
- **Clean styling**: All themes maintain borderless design while adapting colors appropriately
- **Accessibility**: High contrast mode for harsh industrial lighting conditions
- **Apple themes**: iOS/iPadOS inspired light and dark modes for modern touch interfaces

### **Color Palette**
- **Dynamic theming**: Colors adapt based on selected theme (Dark/Light/High Contrast/Apple themes)
- **Primary colors**: Theme-appropriate backgrounds and foregrounds
- **Backgrounds**: Theme-specific panel colors with appropriate contrast ratios
- **Text**: Theme-adaptive text colors with proper hierarchy (primary/secondary/accent)
- **Interactive**: Theme-consistent button states and hover effects
- **Industrial status**: Color-coded controller states (Active/Inactive/Fault) across all themes

### **Border Policy** 
- **NO BORDERS**: Remove all decorative borders from frames, panels, and containers across all themes
- **Clean separation**: Use theme-appropriate background color differences and spacing for visual hierarchy
- **Focus only**: Borders only for accessibility focus states when absolutely required
- **Touch feedback**: Theme-appropriate background color changes on hover/press instead of border changes

### **Layout Principles**
- **Generous spacing**: 16px, 24px, 32px margins for clean separation across all themes
- **Card-based design**: Theme-appropriate background colors with border-radius (8px, 12px) but no borders
- **Typography hierarchy**: Font weights and sizes for organization, not visual frames
- **Clean grouping**: Theme-adaptive background differentiation rather than border containers

---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don't introduce non-Qt GUI frameworks.  
- ❌ Don't mix UI with business logic.
- ❌ Don't add decorative borders - use clean, theme-appropriate backgrounds and spacing
- ❌ Don't hardcode colors - use ThemeManager for dynamic theming across multiple modes

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

## Apple Design System Integration
**CRITICAL**: Apply **clean, minimal design** with Apple principles adapted for industrial use:

### **Typography Scale**
- **Large Title**: 28px, font-weight: 700 - Main section headers
- **Title 1**: 22px, font-weight: 700 - Panel titles  
- **Body**: 17px, font-weight: 400 - Content text
- **Footnote**: 15px, font-weight: 400 - Status information
- **Caption**: 13px, font-weight: 400 - Secondary details

### **Clean Visual Hierarchy**
- **No decorative borders**: Use background colors and spacing for organization
- **Subtle backgrounds**: Light grays (#f8f8f8, #fafafa) for panels and cards
- **Consistent radius**: 8px for buttons, 12px for panels - no border lines
- **Touch optimization**: 60x60px minimum touch targets with clean backgrounds

## Workflow
1. **Define core classes and interfaces first** (data models, services).  
2. **Build UI components on top**, wiring them with signals/slots.  
3. **Apply clean minimal design** - black/white/gray colors, no decorative borders
4. **Use background differentiation** instead of frames for visual hierarchy
5. Write **unit tests** for logic-heavy classes (non-UI) using `QTest`.  
6. Keep build portable with **CMake** or **qmake** (depending on project setup).  

## Documentation
- Document all public classes and methods with **Doxygen-style comments**.
- Keep diagrams (if needed) in **Mermaid or PlantUML**, with modern syntax.
- Main spec lives in Markdown — YAML configs can be derived if structured input is needed.

---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don't introduce non-Qt GUI frameworks.  
- ❌ Don't mix UI with business logic.

---

# Current Build Status (October 2025)

## ✅ **Verified Working Builds**

### **Linux Build** ✅ 
- **Location**: `build-linux-x64/bin/ModernSciFiHMI`
- **Size**: 823KB + Qt5 system libraries
- **Build Time**: ~30 seconds
- **Dependencies**: Qt5 system packages
- **Status**: **WORKING** - All architectural patterns operational
- **Last Built**: October 4, 2025 - Professional structure with Apple design integration

### **Windows Build** ✅
- **Location**: `build-windows-x64/bin/ModernSciFiHMI.exe`
- **Size**: 49MB (fully standalone)
- **Build Time**: ~2-5 minutes (after MXE setup)
- **Dependencies**: None (static linking)
- **Status**: **WORKING** - Cross-compilation via MXE
- **Last Built**: October 4, 2025 - Touch-optimized HMI with professional build structure
- **Fixed Issues**: Windows API naming conflicts + libmodbus platform compatibility resolved

### **Architecture Components** ✅
- ✅ **Strategy Pattern**: EPIC4/SNAP_PAC protocol abstraction
- ✅ **Command Pattern**: Industrial operations with undo/redo
- ✅ **State Machine Pattern**: Connection lifecycle management
- ✅ **Observer Pattern**: Real-time event system
- ✅ **Repository Pattern**: Data persistence interfaces
- ✅ **Plugin Architecture**: Extensible controller support
- ✅ **UDP Discovery**: Enhanced structured response parsing
- ✅ **Industrial Standards**: Alarm acknowledgment, audit trails

### **Known Working Features**
- ✅ UDP broadcast on port 3250 ("Module Scan")
- ✅ Structured controller response parsing (EPIC4 format)
- ✅ Multi-controller management with ControllerManager
- ✅ Industrial HMI faceplates with ControllerOverview
- ✅ Cross-platform Qt Resource system (icons working)
- ✅ libmodbus integration for Modbus TCP
- ✅ Real-time data visualization framework
- ✅ Apple Human Interface Guidelines design system integration
- ✅ Professional build structure with organized scripts directory

### **Professional Build Structure** ✅
```
project-root/
├── scripts/                    # Build and automation scripts
│   ├── build-linux.sh         # Linux native build
│   ├── build-windows.sh       # Windows cross-compilation
│   ├── build-all.sh           # Universal build script
│   └── README.md              # Build documentation
├── build-linux-x64/           # Linux x64 build artifacts
│   └── bin/ModernSciFiHMI     # Linux executable (823KB)
├── build-windows-x64/         # Windows x64 build artifacts
│   └── bin/ModernSciFiHMI.exe # Windows executable (49MB)
└── src/                       # Source code with enterprise architecture
```

### **Build Scripts** ✅
- **Linux**: `scripts/build-linux.sh` - Professional native build automation
- **Windows**: `scripts/build-windows.sh` - Professional MXE cross-compilation
- **Universal**: `scripts/build-all.sh` - Build both platforms sequentially
- **Docker**: `docker build -t scifi-hmi .` - Multi-platform automation
- **All scripts tested and working with professional structure**

### **MXE Cross-Compilation Environment** ✅
- **Location**: `/workspaces/qpcetu/mxe-lite/`
- **Status**: Fully built and operational
- **Components**: Qt5, libmodbus, all required dependencies
- **Build Time**: 20-40 minutes initial, cached thereafter
- **Toolchain**: `x86_64-w64-mingw32.static-*` tools available

## 🔧 **Quick Commands Reference**

```bash
# Linux Build (Professional Structure)
cd scripts && ./build-linux.sh

# Windows Build (Professional Structure) 
cd scripts && ./build-windows.sh

# Build All Platforms (Recommended)
cd scripts && ./build-all.sh

# Both Platforms via Docker
docker build -t scifi-hmi . && docker run --rm -v $(pwd)/output:/output scifi-hmi

# Verify Build Output
ls -la build-linux-x64/bin/ModernSciFiHMI
ls -la build-windows-x64/bin/ModernSciFiHMI.exe

# Verify UDP Discovery
netstat -udln | grep 3250

# Run Applications
build-linux-x64/bin/ModernSciFiHMI        # Linux
wine build-windows-x64/bin/ModernSciFiHMI.exe  # Windows (via Wine)
```

# Check Windows executable
file build-windows-x64/bin/ModernSciFiHMI.exe
```

**Last Updated**: October 4, 2025 - Both platforms building successfully with complete enterprise architecture implementation.

---

# Industrial HMI Architecture

## System Overview

```
┌─────────────────────────────────────────────────────────────┐
│                 Qt Widgets Presentation Layer               │
│  ┌─────────────────┐ ┌─────────────────┐ ┌───────────────┐ │
│  │  OverviewPage   │ │  DashboardPage  │ │  GraphsPage   │ │
│  │  (MainWindow)   │ │  (QWidget)      │ │  (QWidget)    │ │
│  └─────────────────┘ └─────────────────┘ └───────────────┘ │
│  ┌─────────────────┐ ┌─────────────────┐                  │
│  │  SettingsPage   │ │ UdpResponsePage │                  │
│  │  (QWidget)      │ │  (QWidget)      │                  │
│  └─────────────────┘ └─────────────────┘                  │
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
├── ui/                # Qt Widgets UI Components
│   ├── mainwindow.h/cpp
│   ├── overviewpage.h/cpp
│   ├── dashboardpage.h/cpp
│   ├── graphspage.h/cpp
│   ├── settingspage.h/cpp
│   └── udpresponsepage.h/cpp
└── core/              # Core models and services
    ├── udpservice.h/cpp
    ├── controllermanager.h/cpp
    └── industrialcontroller.h/cpp
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
   - Advanced UI Features (potentially QML migration)
   - Testing Framework

---

# AI Coding Guidelines (Qt Widgets Focus)

## General
- Always write **modern C++ (C++17)** when possible.
- Prefer **RAII** (Resource Acquisition Is Initialization) for resource management.
- Use **smart pointers (std::unique_ptr, std::shared_ptr)** instead of raw new/delete.
- Keep headers and implementation files **separated** (`.h` and `.cpp`).
- Keep classes **focused and under ~500 lines** — split if needed.

## Qt5 Widgets Touch-Optimized Guidelines
- Use **large touch targets** with minimum 60x60px button sizes for industrial use
- Implement **proper spacing** with 12-20px margins between interactive elements
- Apply **high contrast styling** for visibility in industrial lighting conditions
- Use **clear, large fonts** (14px minimum, 16-18px preferred) for readability
- Design **swipe gestures** for navigation between pages and panels
- Implement **visual feedback** for all touch interactions (pressed states, animations)
- Create **confirmation dialogs** for critical operations to prevent accidental activation
- Support **multi-touch gestures** where appropriate (pinch-zoom on graphs)
- Ensure **glove compatibility** with larger touch targets and simplified interactions
- Design for **landscape orientation** as primary layout for industrial displays

## Future QML Migration Guidelines (Optional)
- When migrating to QML, use **Q_PROPERTY** for data binding between C++ and QML
- Use **Q_INVOKABLE** for methods called from QML
- Register C++ types with **qmlRegisterType** for QML usage
- Use **QQmlApplicationEngine** for QML application loading
- Prefer **QtQuick.Controls** for standard UI components

---

# Build System Documentation

## Build Requirements

### Dependencies
- **Qt5** (5.15+): Core, Widgets, Network, Svg modules
- **CMake** (3.16+): Build system
- **C++17 Compiler**: GCC 7+, Clang 5+, MSVC 2019+
- **libmodbus**: Industrial Modbus TCP communication
- **Git**: Version control and submodule management

### Linux Development Environment
```bash
# Ubuntu/Debian
sudo apt install qtbase5-dev qtdeclarative5-dev libqt5svg5-dev cmake build-essential git

# Fedora/RHEL
sudo dnf install qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtsvg-devel cmake gcc-c++ git

# Arch Linux
sudo pacman -S qt5-base qt5-declarative qt5-svg cmake gcc git
```

## Build Process

### Linux Native Build ✅

**Quick Build:**
```bash
# Use the automated build script
cd scripts && ./build-linux.sh
```

**Manual Build:**
```bash
# Create and enter build directory
mkdir -p build-linux-x64 && cd build-linux-x64

# Configure with CMake
cmake ..

# Build (use all CPU cores)
make -j$(nproc)

# Run the application
./bin/ModernSciFiHMI
```

**Build Output:**
- **Executable**: `build-linux-x64/bin/ModernSciFiHMI`
- **Size**: 823KB (with Qt5 shared libraries)
- **Dependencies**: Qt5 system libraries required

### Windows Cross-Compilation ✅

**Prerequisites:**
```bash
# MXE (M Cross Environment) must be built first
cd mxe-lite
make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets
# This takes 20-40 minutes initially, cached afterward
```

**Build Process:**
```bash
# Use the automated Windows build script
**Build Process:**
```bash
# Use the automated Windows build script
cd scripts && ./build-windows.sh
```

**Manual Windows Build:**
```bash
cd build-windows-x64

# Set MXE environment
export PATH="/workspaces/qpcetu/mxe-lite/usr/bin:$PATH"

# Clean previous build
rm -rf CMakeCache.txt CMakeFiles/

# Configure with MXE toolchain
cmake -DCMAKE_TOOLCHAIN_FILE=/workspaces/qpcetu/mxe-lite/usr/x86_64-w64-mingw32.static/share/cmake/mxe-conf.cmake \
      -DCMAKE_BUILD_TYPE=Release ..

# Build
make -j$(nproc)
```

**Build Output:**
- **Executable**: `build-windows-x64/bin/ModernSciFiHMI.exe`
- **Size**: ~49MB (fully static, standalone)
- **Dependencies**: None (all libraries statically linked)

### Docker Automated Build 🐳

**Build Both Platforms:**
```bash
# Build Linux and Windows versions in Docker
docker build -t scifi-hmi .

# Extract binaries
docker run --rm -v $(pwd)/output:/output scifi-hmi
```

**Output Locations:**
- Linux: `output/build-linux-x64/ModernSciFiHMI`
- Windows: `output/build-windows-x64/ModernSciFiHMI.exe`

## Build Verification

### Test Commands
```bash
# Linux: Check dependencies
ldd build-linux-x64/bin/ModernSciFiHMI

# Windows: Check executable
file build-windows-x64/bin/ModernSciFiHMI.exe

# Both: Verify UDP functionality
netstat -udln | grep 3250  # Check if listening on port 3250
```

### Expected Behavior
1. **Application Startup**: GUI loads with sci-fi interface
2. **UDP Discovery**: Broadcasts "Module Scan" on port 3250
3. **Controller Detection**: Parses structured responses like:
   ```
   Protocol version = 1.00;FB type = EPIC4;Module version = 1.99;MAC = C0-22-F1-41-03-3A;IP = 192.168.10.243;...
   ```
4. **Architecture Components**: All patterns (Strategy, Command, State Machine) operational

## Troubleshooting

### Common Issues

**Linux Build Failures:**
```bash
# Missing Qt5 development packages
sudo apt install qtbase5-dev libqt5svg5-dev

# CMake too old
# Update to CMake 3.16+ or use newer Ubuntu/Debian
```

**Windows Build Issues:**
```bash
# MXE not built
cd mxe-lite && make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets

# Path issues
export PATH="/workspaces/qpcetu/mxe-lite/usr/bin:$PATH"

# Windows API conflicts (ERROR macro)
# Already fixed: IndustrialController::ERROR → IndustrialController::COMM_ERROR
```

**Runtime Issues:**
```bash
# Qt5 libraries not found (Linux)
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/qt5:$LD_LIBRARY_PATH

# UDP port conflicts
sudo netstat -tulpn | grep 3250  # Check what's using the port
```

### Architecture-Specific Notes

**Strategy Pattern Integration:**
- Controller strategies automatically selected based on discovery response
- EPIC4/EPIC5 use Epic4Strategy, SNAP_PAC uses SnapPacStrategy
- New strategies added via ControllerStrategyFactory

**State Machine Lifecycle:**
- Controllers: Disconnected → Connecting → Connected → Running → Fault
- Heartbeat monitoring with automatic fault detection
- Thread-safe state transitions

**Command Pattern Operations:**
- All industrial operations logged for audit trails
- Undo/redo support for critical operations
- Start/Stop/Reset/Configure commands available

---

## Documentation
- Document all public classes and methods with **Doxygen-style comments**.
- Document **QML components** with clear property descriptions.
- Keep diagrams (if needed) in **Mermaid or PlantUML**, with modern syntax.
- Main spec lives in Markdown — YAML configs can be derived if structured input is needed.

---

# Industrial HMI Architecture

## High-Level Goals
- Create a modern **Qt Widgets-based** user interface with professional industrial styling
- Implement real-time data visualization with 4 graphs in 2x2 layout
- Integrate UDP discovery and Modbus TCP client for industrial data acquisition
- Ensure cross-platform compatibility (Linux, Windows)
- Follow enterprise-grade architecture patterns for industrial HMI systems
- Consider **QML migration** for advanced UI features in future phases

## Current Implementation Status
- ✅ **Qt Widgets UI**: MainWindow with 5 functional pages
- ✅ **Enterprise Architecture**: All 6 design patterns implemented
- ✅ **Cross-Platform Builds**: Linux and Windows working
- ✅ **Industrial Protocols**: UDP discovery and controller management
- 🔄 **Future Enhancement**: QML migration for modern touch interfaces

## Architecture Patterns
This project follows proven design patterns for industrial HMI applications:

### 1. **Model-View Pattern (Qt Widgets)**
- **Qt Widgets Views**: UI presentation layer (MainWindow, QWidget pages)
- **C++ Models**: Business logic and data management (ControllerManager, etc.)
- **Signal/Slot Communication**: Real-time updates between components

---

# AI Coding Guidelines

## General
- Always write **modern C++ (C++17)** when possible.
- Prefer **RAII** (Resource Acquisition Is Initialization) for resource management.
- Use **smart pointers (std::unique_ptr, std::shared_ptr)** instead of raw new/delete.
- Keep headers and implementation files **separated** (`.h` and `.cpp`).
- Keep classes **focused and under ~500 lines** — split if needed.

## Qt5 Widgets Specific Guidelines
- Use **Qt Widgets** for current UI implementation (QWidget, QPushButton, QVBoxLayout, etc.)
- Follow **Model-View patterns** with C++ ViewModels and Models
- Use **signals/slots** for component communication
- Implement **real-time updates** with QTimer and proper data binding
- Use **custom painting** (QPainter) for advanced visualizations
- Follow **Qt styling** with stylesheets for modern appearance

## Future QML Migration Guidelines (Optional)
- When migrating to QML, use **Q_PROPERTY** for data binding between C++ and QML
- Use **Q_INVOKABLE** for methods called from QML
- Register C++ types with **qmlRegisterType** for QML usage
- Use **QQmlApplicationEngine** for QML application loading
- Prefer **QtQuick.Controls** for standard UI components

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
3. **Apply Apple design principles** for consistent user experience.
4. Write **unit tests** for logic-heavy classes (non-UI) using `QTest`.  
5. Keep build portable with **CMake** or **qmake** (depending on project setup).  

## Documentation
- Document all public classes and methods with **Doxygen-style comments**.  
- Keep diagrams (if needed) in **Mermaid or PlantUML**, with modern syntax.  
- Main spec lives in Markdown — YAML configs can be derived if structured input is needed.  

---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don't introduce non-Qt GUI frameworks.  
- ❌ Don't mix UI with business logic.

---

# Current Build Status (October 2025)

## ✅ **Verified Working Builds**

### **Linux Build** ✅ 
- **Location**: `build-linux-x64/bin/ModernSciFiHMI`
- **Size**: 823KB + Qt5 system libraries
- **Build Time**: ~30 seconds
- **Dependencies**: Qt5 system packages
- **Status**: **WORKING** - All architectural patterns operational
- **Last Built**: October 4, 2025 - Professional structure with Apple design integration

### **Windows Build** ✅
- **Location**: `build-windows-x64/bin/ModernSciFiHMI.exe`
- **Size**: 49MB (fully standalone)
- **Build Time**: ~2-5 minutes (after MXE setup)
- **Dependencies**: None (static linking)
- **Status**: **WORKING** - Cross-compilation via MXE
- **Last Built**: October 4, 2025 - Touch-optimized HMI with professional build structure
- **Fixed Issues**: Windows API naming conflicts + libmodbus platform compatibility resolved

### **Architecture Components** ✅
- ✅ **Strategy Pattern**: EPIC4/SNAP_PAC protocol abstraction
- ✅ **Command Pattern**: Industrial operations with undo/redo
- ✅ **State Machine Pattern**: Connection lifecycle management
- ✅ **Observer Pattern**: Real-time event system
- ✅ **Repository Pattern**: Data persistence interfaces
- ✅ **Plugin Architecture**: Extensible controller support
- ✅ **UDP Discovery**: Enhanced structured response parsing
- ✅ **Industrial Standards**: Alarm acknowledgment, audit trails

### **Known Working Features**
- ✅ UDP broadcast on port 3250 ("Module Scan")
- ✅ Structured controller response parsing (EPIC4 format)
- ✅ Multi-controller management with ControllerManager
- ✅ Industrial HMI faceplates with ControllerOverview
- ✅ Cross-platform Qt Resource system (icons working)
- ✅ libmodbus integration for Modbus TCP
- ✅ Real-time data visualization framework
- ✅ Apple Human Interface Guidelines design system integration
- ✅ Professional build structure with organized scripts directory

### **Professional Build Structure** ✅
```
project-root/
├── scripts/                    # Build and automation scripts
│   ├── build-linux.sh         # Linux native build
│   ├── build-windows.sh       # Windows cross-compilation
│   ├── build-all.sh           # Universal build script
│   └── README.md              # Build documentation
├── build-linux-x64/           # Linux x64 build artifacts
│   └── bin/ModernSciFiHMI     # Linux executable (823KB)
├── build-windows-x64/         # Windows x64 build artifacts
│   └── bin/ModernSciFiHMI.exe # Windows executable (49MB)
└── src/                       # Source code with enterprise architecture
```

### **Build Scripts** ✅
- **Linux**: `scripts/build-linux.sh` - Professional native build automation
- **Windows**: `scripts/build-windows.sh` - Professional MXE cross-compilation
- **Universal**: `scripts/build-all.sh` - Build both platforms sequentially
- **Docker**: `docker build -t scifi-hmi .` - Multi-platform automation
- **All scripts tested and working with professional structure**

### **MXE Cross-Compilation Environment** ✅
- **Location**: `/workspaces/qpcetu/mxe-lite/`
- **Status**: Fully built and operational
- **Components**: Qt5, libmodbus, all required dependencies
- **Build Time**: 20-40 minutes initial, cached thereafter
- **Toolchain**: `x86_64-w64-mingw32.static-*` tools available

## 🔧 **Quick Commands Reference**

```bash
# Linux Build (Professional Structure)
cd scripts && ./build-linux.sh

# Windows Build (Professional Structure) 
cd scripts && ./build-windows.sh

# Build All Platforms (Recommended)
cd scripts && ./build-all.sh

# Both Platforms via Docker
docker build -t scifi-hmi . && docker run --rm -v $(pwd)/output:/output scifi-hmi

# Verify Build Output
ls -la build-linux-x64/bin/ModernSciFiHMI
ls -la build-windows-x64/bin/ModernSciFiHMI.exe

# Verify UDP Discovery
netstat -udln | grep 3250

# Run Applications
build-linux-x64/bin/ModernSciFiHMI        # Linux
wine build-windows-x64/bin/ModernSciFiHMI.exe  # Windows (via Wine)
```

# Check Windows executable
file build-windows-x64/bin/ModernSciFiHMI.exe
```

**Last Updated**: October 4, 2025 - Both platforms building successfully with complete enterprise architecture implementation.
---

# AI Agent Reminders

- ✅ Always generate `.h` + `.cpp` pairs.  
- ✅ Use **signals/slots** rather than callbacks.  
- ✅ Favor Qt idioms when working with Qt APIs.  
- ❌ Don’t introduce non-Qt GUI frameworks.  
- ❌ Don’t mix UI with business logic.  
