# SciFi Da## 🍎 Apple Design System Integration

This HMI implements **Apple Human Interface Guidelines** for professional consistency:

- **Typography Scale**: Complete Apple font hierarchy (Large Title → Caption 2)
- **Semantic Colors**: Apple system colors with light/dark theme support  
- **Motion Design**: Apple-compliant animations and transitions
- **Accessibility**: VoiceOver support and accessibility best practices
- **Touch Guidelines**: Apple touch interaction standards adapted for industrial use

## 📱 Touch Screen Optimization

This HMI is specifically designed for **touch screen operation** with:

- **Large Touch Targets**: Minimum 60x60px buttons for reliable finger interaction
- **Industrial Glove Support**: Oversized controls for safety equipment compatibility  
- **High Contrast Design**: Clear visibility in various industrial lighting conditions
- **Touch Feedback**: Visual pressed states and animation feedback for all interactions
- **Finger-First Design**: All controls optimized for direct finger operation
- **Large Fonts**: Minimum 14px fonts for arm's-length readability
- **Generous Spacing**: 12-20px margins prevent accidental activation[![Build Status](https://github.com/kaphagel/qpcetu/workflows/CI/badge.svg)](https://github.com/kaphagel/qpcetu/actions)
[![Qt Version](https://img.shields.io/badge/Qt-6.x-green.svg)](https://www.qt.io/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

# SciFi Data Screen - Touch-Optimized Industrial HMI

A modern Qt5-based industrial Human-Machine Interface (HMI) application with sci-fi aesthetics, designed for real-time data visualization and industrial controller management. **Optimized for touch screen interfaces** in industrial environments.

## � Touch Screen Optimization

This HMI is specifically designed for **touch screen operation** with:

- **Large Touch Targets**: Minimum 60x60px buttons for reliable finger interaction
- **Industrial Glove Support**: Oversized controls for safety equipment compatibility  
- **High Contrast Design**: Clear visibility in various industrial lighting conditions
- **Touch Feedback**: Visual pressed states and animation feedback for all interactions
- **Finger-First Design**: All controls optimized for direct finger operation
- **Large Fonts**: Minimum 14px fonts for arm's-length readability
- **Generous Spacing**: 12-20px margins prevent accidental activation

## �🏗️ Enterprise Architecture

This application implements proven **design patterns** for industrial HMI systems:

- **Strategy Pattern**: Pluggable controller protocols (EPIC4, EPIC5, SNAP_PAC)
- **State Machine Pattern**: Robust connection lifecycle management
- **Command Pattern**: Industrial operations with undo/redo and audit logging
- **Observer Pattern**: Real-time event system for alarms and notifications
- **Repository Pattern**: Historical data persistence and configuration management
- **Plugin Architecture**: Extensible controller support

📖 **[Detailed Architecture Documentation](docs/ARCHITECTURE.md)**

## ✨ Features

- **Apple Design System**: Full implementation of Apple HIG for professional UX
- **Touch-Optimized Interface**: Large, clearly spaced controls for industrial touch screens
- **Professional Build Structure**: Organized scripts and build artifacts
- **Multi-Controller Support**: EPIC4/EPIC5 (Opto22), SNAP_PAC controllers
- **Real-time Visualization**: 4-graph dashboard with industrial data
- **UDP Discovery**: Automatic controller detection on network
- **Cross-Platform**: Linux (native) + Windows (MXE cross-compilation)
- **Industrial Standards**: Event acknowledgment, state management, operation auditing
- **Modular Design**: Easy to extend with new controller types
- **Thread-Safe**: Robust real-time data handling

## 🚀 Quick Start

### Professional Build System
```bash
# Linux Build (Professional Structure)
cd scripts && ./build-linux.sh

# Windows Build (Professional Structure) 
cd scripts && ./build-windows.sh

# Build All Platforms (Recommended)
cd scripts && ./build-all.sh
```

### Build Output
- **Linux**: `build-linux-x64/bin/ModernSciFiHMI` (823KB + Qt5 libraries)
- **Windows**: `build-windows-x64/bin/ModernSciFiHMI.exe` (49MB standalone)

### Docker (Both Platforms)
```bash
docker build -t scifi-hmi . && docker run --rm -v $(pwd)/output:/output scifi-hmi
```

🔧 **[Complete Build Instructions & Status](.github/instructions/instructions.instructions.md)**

## 🖥️ Touch Screen Interface

### Modern Touch-Optimized HMI (`ModernSciFiHMI`)
- **60x60px minimum** touch targets for reliable interaction
- **Large fonts** (14-18px) for readability from arm's length
- **High contrast** sci-fi industrial styling with blue accents (#00E5FF)
- **Touch feedback** with pressed states and visual animations
- **Controller cards** with real-time metrics and status indicators
- **Glove-friendly** design for industrial safety equipment

### Interface Components
- **Header Bar**: Connection status, user info, real-time clock
- **Status Strip**: Live system monitoring (Discovery, Modbus, Events, Data)
- **Controller Grid**: Card-based layout with drag-friendly spacing
- **Quick Actions Panel**: Large buttons for common operations
- **Status Bar**: System metrics (CPU, Memory, Network, Updates)

### Touch Gestures
- **Tap**: Primary selection and activation
- **Long Press**: Context menus and detailed views
- **Swipe**: Navigation between pages (future enhancement)

## 📋 Requirements

- **Qt5.15+**: Core, Widgets, Network, Svg modules
- **CMake 3.16+**: Build system
- **C++17 Compiler**: GCC 7+, Clang 5+, MSVC 2019+
- **libmodbus**: Industrial Modbus TCP communication
- **Touch Screen**: For optimal user experience (mouse/keyboard also supported)
- Linux, Windows, or macOS

## Installation

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install qt5-default qt5-qmake libqt5svg5-dev cmake build-essential
```
```

### Windows Build
```bash
cd build-windows && ./build.sh
```

### Docker (Both Platforms)
```bash
docker build -t scifi-hmi . && docker run --rm -v $(pwd)/output:/output scifi-hmi
```

� **[Complete Build Instructions & Status](.github/instructions/instructions.instructions.md)**

## 📋 Requirements

- **Qt5.15+**: Core, Widgets, Network, Svg modules
- **CMake 3.16+**: Build system
- **C++17 Compiler**: GCC 7+, Clang 5+, MSVC 2019+
- **libmodbus**: Industrial Modbus TCP communication
- Linux, Windows, or macOS

## Installation

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install qt6-base-dev qt6-tools-dev cmake build-essential
```

### Fedora/CentOS
```bash
sudo dnf install qt6-qtbase-devel cmake gcc-c++
```

### Arch Linux
```bash
sudo pacman -S qt6-base cmake gcc
```

## Building the Application

1. **Clone or navigate to the project directory:**
   ```bash
   cd /home/ecs/src/qtpcetu
   ```

2. **Create build directory:**
   ```bash
   mkdir build
   cd build
   ```

3. **Configure with CMake:**
   ```bash
   cmake ..
   ```

4. **Build the application:**
   ```bash
   make -j$(nproc)
   ```

5. **Run the application:**
   ```bash
   ./bin/SciFiDataScreen
   ```

## Quick Build Script

For convenience, you can use the provided build script:

```bash
chmod +x build.sh
./build.sh
```

## Project Structure

```
qtpcetu/
├── CMakeLists.txt          # Build configuration
├── README.md              # This file
├── build.sh               # Quick build script
├── src/
│   ├── main.cpp           # Application entry point
│   ├── mainwindow.h       # Main window header
│   ├── mainwindow.cpp     # Main window implementation
│   ├── datawidget.h       # Custom data display widget header
│   ├── datawidget.cpp     # Custom data display widget implementation
│   ├── animatedprogressbar.h    # Animated progress bar header
│   └── animatedprogressbar.cpp  # Animated progress bar implementation
└── build/                 # Build output directory (created during build)
```

## Interface Elements

### Status Panel
- System status indicator (ONLINE/WARNING)
- Real-time clock display  
- Quantum link connection status

### Data Panels
- **Energy Core**: Power output in MW
- **Shield Matrix**: Shield strength percentage
- **Engine Thrust**: Thrust output in KN
- **Weapon Array**: Weapon system readiness

### System Parameters
- **Power Distribution**: Animated progress bar
- **Coolant System**: System temperature management
- **Fuel Reserves**: Remaining fuel percentage
- **Navigation**: Coordinates, velocity, and altitude

### Control Panel
- **Engage Systems**: Activate all systems
- **Alert Status**: Trigger system alerts
- **Deep Scan**: Initiate scanning protocols
- **System Log**: Real-time event display

## Customization

The application uses Qt's stylesheet system for theming. You can modify the appearance by editing the stylesheet in `mainwindow.cpp`. Key color scheme:

- **Primary Blue**: `#00aaff`
- **Background**: `#0a0a1a` 
- **Panel Background**: `#001133`
- **Border**: `#0066cc`
- **Success Green**: `#00ff88`
- **Warning Orange**: `#ffaa00`
- **Critical Red**: `#ff4444`

## Troubleshooting

### Qt6 Not Found
If CMake cannot find Qt6, you may need to set the Qt6 path:
```bash
export CMAKE_PREFIX_PATH=/path/to/qt6
cmake ..
```

### Missing Dependencies
Make sure you have all Qt6 development packages installed:
```bash
# Ubuntu/Debian
sudo apt install qt6-base-dev qt6-tools-dev

# Fedora
sudo dnf install qt6-qtbase-devel
```

### Compilation Errors
Ensure you're using a C++17 compatible compiler and Qt6 (not Qt5).

## License

This project is provided as a learning example for Qt development and sci-fi interface design.
