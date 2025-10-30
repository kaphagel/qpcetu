[![Build Status](https://github.com/kaphagel/qpcetu/workflows/CI/badge.svg)](https://github.com/kaphagel/qpcetu/actions)
[![Qt Version](https://img.shields.io/badge/Qt-5.15-green.svg)](https://www.qt.io/)
[![License](https://img.shields.io/badge/License-MIT-blue.svg)](LICENSE)

# SciFi Data Screen - Touch-Optimized Industrial HMI

A modern Qt5-based industrial Human-Machine Interface (HMI) application with sci-fi aesthetics, designed for real-time data visualization and industrial controller management. **Optimized for touch screen interfaces** in industrial environments.

## 📱 Touch Screen Optimization

This HMI is specifically designed for **touch screen operation** with:

- **Large Touch Targets**: Minimum 60x60px buttons for reliable finger interaction
- **Industrial Glove Support**: Oversized controls for safety equipment compatibility  
- **High Contrast Design**: Clear visibility in various industrial lighting conditions
- **Touch Feedback**: Visual pressed states and animation feedback for all interactions
- **Finger-First Design**: All controls optimized for direct finger operation
- **Large Fonts**: Minimum 14px fonts for arm's-length readability
- **Generous Spacing**: 12-20px margins prevent accidental activation

## 🍎 Apple Design System Integration

This HMI implements **Apple Human Interface Guidelines** for professional consistency:

- **Typography Scale**: Complete Apple font hierarchy (Large Title → Caption 2)
- **Semantic Colors**: Apple system colors with light/dark theme support  
- **Motion Design**: Apple-compliant animations and transitions
- **Accessibility**: VoiceOver support and accessibility best practices
- **Touch Guidelines**: Apple touch interaction standards adapted for industrial use

## 🏗️ Enterprise Architecture

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
docker build -t modern-industrial-hmi . 
docker run -it --rm -p 3250:3250/udp -p 502:502/tcp modern-industrial-hmi
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

## 💻 Installation

### Ubuntu/Debian
```bash
sudo apt update
sudo apt install qtbase5-dev qttools5-dev libqt5svg5-dev cmake build-essential libmodbus-dev
```

### Fedora/CentOS
```bash
sudo dnf install qt5-qtbase-devel qt5-qttools-devel qt5-qtsvg-devel cmake gcc-c++ libmodbus-devel
```

### Arch Linux
```bash
sudo pacman -S qt5-base qt5-tools qt5-svg cmake gcc libmodbus
```

## 🔧 Building the Application

Use the professional build scripts for best results:

```bash
# Recommended: Use build scripts
cd scripts && ./build-all.sh

# Or build individually:
cd scripts && ./build-linux.sh      # Linux native
cd scripts && ./build-windows.sh    # Windows cross-compilation
```

### Manual Build (if needed):

1. **Create build directory:**
   ```bash
   mkdir -p build-linux-x64
   cd build-linux-x64
   ```

2. **Configure with CMake:**
   ```bash
   cmake ..
   ```

3. **Build the application:**
   ```bash
   make -j$(nproc)
   ```

4. **Run the application:**
   ```bash
   ./bin/ModernSciFiHMI
   ```

## 📁 Project Structure

```
qpcetu/
├── CMakeLists.txt              # Build configuration
├── README.md                   # This file
├── Dockerfile                  # Docker build configuration
├── .github/
│   └── instructions/           # Build documentation and architecture
├── scripts/                    # Professional build scripts
│   ├── build-linux.sh         # Linux native build
│   ├── build-windows.sh       # Windows cross-compilation
│   └── build-all.sh           # Build both platforms
├── src/                       # Source code
│   ├── commands/              # Command Pattern implementations
│   ├── data/                  # Repository Pattern + data structures
│   ├── events/                # Observer Pattern + event system
│   ├── navigation/            # Navigation management
│   ├── pages/                 # UI pages (Overview, Dashboard, Graphs, etc.)
│   ├── plugins/               # Plugin Architecture
│   ├── services/              # Business services (UDP, XML, Modbus)
│   ├── statemachine/          # State Machine Pattern
│   ├── strategies/            # Strategy Pattern for protocols
│   └── ui/                    # Qt Widgets UI components
├── tests/                     # Unit tests
│   ├── unit/                  # Unit tests
│   ├── integration/           # Integration tests
│   └── mocks/                 # Mock objects
├── resources/                 # Qt resource files
│   └── icons/                 # Application icons
├── build-linux-x64/           # Linux build artifacts
└── build-windows-x64/         # Windows build artifacts
```

## 🖥️ Touch Screen Interface

### Modern Touch-Optimized HMI (`ModernSciFiHMI`)
- **60x60px minimum** touch targets for reliable interaction
- **Large fonts** (14-18px) for readability from arm's length
- **High contrast** sci-fi industrial styling with blue accents (#00E5FF)
- **Touch feedback** with pressed states and visual animations
- **Controller cards** with real-time metrics and status indicators
- **Glove-friendly** design for industrial safety equipment

### Interface Components
- **Header Bar**: Connection status, user info, real-time clock, theme toggle
- **Status Strip**: Live system monitoring (Discovery, Modbus, Events, Data)
- **Controller Grid**: Card-based layout with drag-friendly spacing
- **Navigation Menu**: Hamburger menu with 6 pages (Overview, Dashboard, Graphs, Settings, Network, Industrial)
- **Status Bar**: System metrics (CPU, Memory, Network, Updates)

### Pages
- **Overview**: Controller discovery and management cards
- **Dashboard**: Real-time data visualization
- **Graphs**: Historical data trends with Modbus TCP integration
- **Settings**: Application configuration and theme selection
- **Network**: UDP discovery responses and network diagnostics
- **Industrial**: Controller-specific operations and XML data forms

### Touch Gestures
- **Tap**: Primary selection and activation
- **Long Press**: Context menus and detailed views (future)
- **Swipe**: Navigation between pages (future enhancement)

## 🎨 Customization

The application uses Qt's stylesheet system and the ThemeManager for professional theming:

### Available Themes
- **Dark Theme**: Default industrial dark theme
- **Light Theme**: Clean light theme for bright environments
- **High Contrast**: Enhanced visibility for harsh lighting
- **Apple Light**: iOS/macOS inspired light mode
- **Apple Dark**: iOS/macOS inspired dark mode

### Color Scheme (Dark Theme)
- **Primary Accent**: `#00E5FF` (Cyan blue)
- **Background**: `#0F1419` (Deep blue-black)
- **Panel Background**: `#1A1F2E` (Dark blue-gray)
- **Border**: `#2A3F5F` (Medium blue)
- **Success**: `#00FF88` (Bright green)
- **Warning**: `#FFB84D` (Orange)
- **Critical**: `#FF4D6A` (Red)

### Customizing Themes
Modify `src/ui/thememanager.cpp` to add or customize themes. The ThemeManager provides:
- Dynamic theme switching
- Borderless design principles
- Consistent color application
- Theme-adaptive components

## 🔍 Troubleshooting

### Qt5 Not Found
If CMake cannot find Qt5, set the Qt5 path:
```bash
export CMAKE_PREFIX_PATH=/usr/lib/x86_64-linux-gnu/cmake/Qt5
cmake ..
```

### Missing Dependencies
Install all required Qt5 development packages:
```bash
# Ubuntu/Debian
sudo apt install qtbase5-dev qttools5-dev libqt5svg5-dev libqt5test5 libmodbus-dev

# Fedora
sudo dnf install qt5-qtbase-devel qt5-qttools-devel qt5-qtsvg-devel libmodbus-devel
```

### Compilation Errors
- Ensure you're using **C++17** compatible compiler
- Verify you're using **Qt5.15+** (not Qt6)
- Check that all source files are in the correct directories

### VS Code Qt for Python Extension Issues
This is a **C++ Qt5 project**, not Python. If you see Python rcc errors:
1. The Qt for Python extension is disabled in `.vscode/settings.json`
2. Reload VS Code window: `Ctrl+Shift+P` → "Developer: Reload Window"
3. Or disable the extension: `seanwu.vscode-qt-for-python`

### Build Errors
```bash
# Clean build
rm -rf build-linux-x64 build-windows-x64
cd scripts && ./build-all.sh
```

## 🐳 Docke
Build and run both platforms in a container:

```bash
# Build the container
docker build -t modern-industrial-hmi .

# Run with port forwarding  
docker run -it --rm -p 3250:3250/udp -p 502:502/tcp modern-industrial-hmi
```

**Note:** MXE cross-compilation takes 20-40 minutes on first build.

## 📝 License

This project is provided as a learning example for Qt development and industrial HMI interface design.

## 🤝 Contributing

Contributions are welcome! Please feel free to submit pull requests or open issues for bugs and feature requests.

## 📚 Documentation

- **Architecture**: See `.github/instructions/instructions.instructions.md` for complete architecture documentation
- **Build System**: See `scripts/README.md` for build script documentation
- **Docker**: See `DOCKERFILE_VERIFICATION.md` for Docker build details

---

**Built with Qt5 Widgets • C++17 • Cross-Platform • Touch-Optimized • Industrial-Grade**

