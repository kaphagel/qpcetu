# SciFi Data Screen

[![Build Status](https://github.com/kaphagel/qpcetu/workflows/CI/badge.svg)](https://github.com/kaphagel/qpcetu/actions)
[![Qt Version](https://img.shields.io/badge/Qt-6.x-green.svg)](https://www.qt.io/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

# SciFi Data Screen - Industrial HMI Application

A modern Qt5-based industrial Human-Machine Interface (HMI) application with sci-fi aesthetics, designed for real-time data visualization and industrial controller management.

## 🏗️ Enterprise Architecture

This application implements proven **design patterns** for industrial HMI systems:

- **Strategy Pattern**: Pluggable controller protocols (EPIC4, EPIC5, SNAP_PAC)
- **State Machine Pattern**: Robust connection lifecycle management
- **Command Pattern**: Industrial operations with undo/redo and audit logging
- **MVVM Pattern**: QML views with C++ ViewModels and Models
- **Observer Pattern**: Real-time event system for alarms and notifications
- **Repository Pattern**: Historical data persistence and configuration management
- **Plugin Architecture**: Extensible controller support

📖 **[Detailed Architecture Documentation](docs/ARCHITECTURE.md)**

## ✨ Features

- **Multi-Controller Support**: EPIC4/EPIC5 (Opto22), SNAP_PAC controllers
- **Real-time Visualization**: 4-graph dashboard with industrial data
- **UDP Discovery**: Automatic controller detection on network
- **Cross-Platform**: Linux, Windows (via MXE cross-compilation)
- **Industrial Standards**: Event acknowledgment, state management, operation auditing
- **Modular Design**: Easy to extend with new controller types
- **Thread-Safe**: Robust real-time data handling

## 🚀 Quick Start

## Features

- 🚀 **Real-time Data Visualization** - 4 synchronized graphs in 2x2 layout
- 🌐 **Modbus TCP Integration** - Live data from industrial devices
- 🎨 **Sci-Fi Interface** - Dark theme with neon accents and glow effects
- ⚡ **High Performance** - Efficient circular buffers and smooth animations
- 🔧 **Cross-Platform** - Linux, Windows, macOS support

## Requirements

- Qt6 with QML support
- CMake 3.20 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
- libmodbus for network communication
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
