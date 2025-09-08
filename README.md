# Quantum Tactical Processing Center - ETU

A futuristic Qt application that simulates a sci-fi data screen interface with dark blue theme, animated elements, and real-time data updates.

## Features

- **Sci-Fi Interface**: Dark blue theme with glowing effects reminiscent of science fiction movies
- **Real-time Data**: Animated progress bars and data widgets that update continuously  
- **Interactive Controls**: Buttons for system engagement, alerts, and deep scans
- **System Monitoring**: Energy, shields, engines, weapons, and navigation displays
- **Animated Elements**: Smooth transitions, flowing progress bars, and pulsing glow effects
- **System Log**: Real-time event logging with sci-fi style messages

## Requirements

- Qt6 (Core and Widgets modules)
- CMake 3.16 or higher
- C++17 compatible compiler (GCC, Clang, or MSVC)
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
