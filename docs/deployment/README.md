# Deployment Documentation

## Industrial HMI Build and Deployment Guide

This section contains build, deployment, and operational documentation for the Qt5-based industrial HMI system.

## 📋 Documentation Index

### **[Build Scripts](./build-scripts.md)**
Comprehensive build automation documentation including:
- **Professional Build Structure**: Organized scripts and output directories
- **Cross-Platform Support**: Linux native and Windows cross-compilation
- **Automated Workflows**: Single-command builds for both platforms
- **Docker Integration**: Containerized build environment

## 🚀 Quick Deployment Guide

### **Prerequisites**
Ensure the following dependencies are installed:

#### **Linux Development Environment**
```bash
# Ubuntu/Debian
sudo apt install qtbase5-dev qtdeclarative5-dev libqt5svg5-dev cmake build-essential git

# Fedora/RHEL  
sudo dnf install qt5-qtbase-devel qt5-qtdeclarative-devel qt5-qtsvg-devel cmake gcc-c++ git

# Arch Linux
sudo pacman -S qt5-base qt5-declarative qt5-svg cmake gcc git
```

#### **Windows Cross-Compilation (MXE)**
```bash
# MXE toolchain setup (one-time, 20-40 minutes)
cd mxe-lite
make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets
```

### **Build Commands**

#### **Linux Native Build**
```bash
# Professional automated build
cd scripts && ./build-linux.sh

# Manual build process
mkdir -p build-linux-x64 && cd build-linux-x64
cmake ..
make -j$(nproc)
```

#### **Windows Cross-Compilation**
```bash
# Professional automated build
cd scripts && ./build-windows.sh

# Manual build process
cd build-windows-x64
export PATH="/workspaces/qpcetu/mxe-lite/usr/bin:$PATH"
cmake -DCMAKE_TOOLCHAIN_FILE=/workspaces/qpcetu/mxe-lite/usr/x86_64-w64-mingw32.static/share/cmake/mxe-conf.cmake ..
make -j$(nproc)
```

#### **Universal Build (Both Platforms)**
```bash
# Build both Linux and Windows in sequence
cd scripts && ./build-all.sh
```

#### **Docker Multi-Platform Build**
```bash
# Containerized build for both platforms
docker build -t scifi-hmi .
docker run --rm -v $(pwd)/output:/output scifi-hmi
```

## 📦 Build Outputs

### **Linux Native Build**
- **Location**: `build-linux-x64/bin/ModernSciFiHMI`
- **Size**: ~800KB executable + Qt5 system libraries
- **Dependencies**: Qt5 shared libraries (installed via package manager)
- **Distribution**: Requires Qt5 runtime on target systems

### **Windows Cross-Compilation**
- **Location**: `build-windows-x64/bin/ModernSciFiHMI.exe`
- **Size**: ~48MB standalone executable
- **Dependencies**: None (fully static linking)
- **Distribution**: Single executable file, no runtime dependencies

### **Professional Directory Structure**
```
project-root/
├── scripts/                    # Build automation scripts
│   ├── build-linux.sh         # Linux native build
│   ├── build-windows.sh       # Windows cross-compilation  
│   ├── build-all.sh           # Universal build script
│   └── README.md              # Build system documentation
├── build-linux-x64/           # Linux build artifacts
│   ├── bin/ModernSciFiHMI     # Linux executable
│   └── CMakeFiles/            # Build system files
├── build-windows-x64/         # Windows build artifacts
│   ├── bin/ModernSciFiHMI.exe # Windows executable
│   └── CMakeFiles/            # Build system files
└── docs/                      # Comprehensive documentation
```

## 🎯 Target Deployment Environments

### **Industrial Computer Systems**
- **Linux Distributions**: Ubuntu 20.04+, RHEL 8+, Industrial Linux variants
- **Windows Systems**: Windows 10/11, Windows IoT Enterprise
- **ARM Platforms**: Raspberry Pi 4+ (with Qt5 ARM support)
- **x86_64 Systems**: Standard industrial PC hardware

### **Touch Screen Hardware**
- **Screen Sizes**: 10" to 24" industrial touch displays
- **Resolution**: 1024x768 minimum, 1920x1080 recommended
- **Touch Technology**: Capacitive or resistive touch panels
- **Environmental Rating**: IP65+ for industrial environments

### **Network Requirements**
- **UDP Port 3250**: Controller discovery broadcasts
- **Modbus TCP**: Standard Modbus TCP/IP communication
- **Local Network**: Ethernet connectivity for controller communication
- **Internet**: Optional for remote monitoring features

## 🔧 Installation Procedures

### **Linux Installation**
```bash
# Install Qt5 runtime dependencies
sudo apt install qtbase5-dev libqt5svg5

# Deploy executable
cp build-linux-x64/bin/ModernSciFiHMI /usr/local/bin/
chmod +x /usr/local/bin/ModernSciFiHMI

# Create desktop entry (optional)
cat > ~/.local/share/applications/scifi-hmi.desktop << EOF
[Desktop Entry]
Name=SciFi HMI
Exec=/usr/local/bin/ModernSciFiHMI
Icon=application-x-executable
Type=Application
Categories=Industrial;Development;
EOF
```

### **Windows Installation**
```batch
# Simple file copy deployment
copy build-windows-x64\bin\ModernSciFiHMI.exe C:\Industrial\SciFiHMI\

# Create shortcut (optional)
# Right-click desktop → New → Shortcut → Browse to ModernSciFiHMI.exe
```

### **Docker Deployment**
```bash
# Build container with application
docker build -t scifi-hmi .

# Run containerized HMI (with X11 forwarding)
docker run -it --rm \
  -e DISPLAY=$DISPLAY \
  -v /tmp/.X11-unix:/tmp/.X11-unix \
  scifi-hmi
```

## 🚦 Operational Verification

### **Startup Verification**
1. **Application Launch**: HMI interface loads successfully
2. **Theme Functionality**: Theme toggle button cycles through all themes
3. **UDP Discovery**: Application broadcasts "Module Scan" on port 3250
4. **Network Listening**: UDP service listens for controller responses

### **Controller Discovery Testing**
```bash
# Verify UDP functionality
netstat -udln | grep 3250  # Check port 3250 listening

# Test controller response (manual simulation)
echo "Protocol version = 1.00;FB type = EPIC4;Module version = 1.99;MAC = C0-22-F1-41-03-3A;IP = 192.168.10.243;" | nc -u localhost 3250
```

### **Performance Verification**
- **Startup Time**: < 5 seconds on industrial hardware
- **Memory Usage**: < 100MB typical operation
- **CPU Usage**: < 5% during normal operation
- **Touch Response**: < 50ms touch-to-feedback latency

## 🛠️ Troubleshooting

### **Common Build Issues**

#### **Linux Build Failures**
```bash
# Missing Qt5 development packages
sudo apt install qtbase5-dev libqt5svg5-dev

# CMake version too old
# Update to CMake 3.16+ or use newer Ubuntu/Debian version

# Permission issues
chmod +x scripts/build-linux.sh
```

#### **Windows Build Issues**
```bash
# MXE not built
cd mxe-lite && make MXE_TARGETS='x86_64-w64-mingw32.static' qtbase qtsvg qtwidgets

# PATH environment issues
export PATH="/workspaces/qpcetu/mxe-lite/usr/bin:$PATH"

# Windows API conflicts (already resolved)
# IndustrialController::ERROR → IndustrialController::COMM_ERROR
```

### **Runtime Issues**

#### **Linux Runtime Problems**
```bash
# Qt5 libraries not found
export LD_LIBRARY_PATH=/usr/lib/x86_64-linux-gnu/qt5:$LD_LIBRARY_PATH

# UDP port conflicts
sudo netstat -tulpn | grep 3250  # Check what's using port 3250
sudo fuser -k 3250/udp          # Kill conflicting process
```

#### **Windows Runtime Problems**
```batch
# Missing Visual C++ Redistributables (not needed for static build)
# Network firewall blocking UDP port 3250
# Check Windows Firewall settings for port 3250
```

## 📊 Build Performance Metrics

### **Build Times** ⏱️
- **Linux Native**: ~30-60 seconds (incremental builds: ~10 seconds)
- **Windows Cross-Compilation**: ~2-5 minutes (incremental builds: ~30 seconds)
- **MXE Initial Setup**: 20-40 minutes (one-time only)
- **Docker Full Build**: ~15-25 minutes (cached layers: ~5 minutes)

### **Output Sizes** 📦
- **Linux Executable**: ~800KB + Qt5 system libraries (~50MB total)
- **Windows Executable**: ~48MB standalone (no dependencies)
- **Docker Image**: ~200MB (including base OS and Qt5)

---

## 📞 Deployment Support

For deployment questions and operational support:
1. Review the [Build Scripts](./build-scripts.md) documentation
2. Check the troubleshooting section above for common issues
3. Verify network requirements and firewall settings
4. Test on target hardware before production deployment

**Last Updated**: October 30, 2025
**Status**: Professional cross-platform build system fully operational