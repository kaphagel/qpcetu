# Quantum Tactical Processing Center - ETU
## Industrial HMI Documentation

This directory contains comprehensive documentation for the Qt5-based industrial HMI system with touch-optimized interface and cross-platform support.

## 📚 Documentation Structure

### 🔧 [Development](./development/)
Technical documentation for developers working on the HMI system.
- **[Guidelines](./development/guidelines.md)** - Coding standards, architecture patterns, and best practices
- **[Build System](./development/build-system.md)** - Cross-platform build documentation and troubleshooting

### 🎨 [Design](./design/)
UI/UX design specifications and visual design system documentation.
- **[Project Specifications](./design/project-specifications.md)** - Complete project requirements and architecture
- **[UI Specification](./design/ui-specification.md)** - User interface design specifications
- **[Apple Design System](./design/apple-design-system.md)** - iOS/iPadOS inspired design guidelines

### 🚀 [Deployment](./deployment/)
Build, deployment, and operational documentation.
- **[Build Scripts](./deployment/build-scripts.md)** - Automated build system documentation

### 📖 [API](./api/)
API documentation and developer references.
- *API documentation will be generated here*

## 🏗️ Project Overview

### **Technology Stack**
- **Framework**: Qt5 Widgets with C++17
- **Platforms**: Linux (native) + Windows (cross-compilation via MXE)
- **Communication**: UDP discovery, Modbus TCP, real-time data acquisition
- **Design**: Apple Human Interface Guidelines adapted for industrial use

### **Architecture Patterns**
- **Strategy Pattern**: Protocol-specific controller communication
- **Command Pattern**: Industrial operations with undo/redo support
- **State Machine**: Connection lifecycle management
- **Observer Pattern**: Real-time event propagation
- **Repository Pattern**: Data persistence and historical storage
- **Plugin Architecture**: Extensible controller type support

### **Key Features**
- ✅ **Touch-Optimized Interface**: 60x60px minimum buttons, generous spacing
- ✅ **Multi-Theme Support**: Dark, Light, High Contrast, Apple Light/Dark themes
- ✅ **Industrial Protocols**: UDP controller discovery, Modbus TCP communication
- ✅ **Cross-Platform**: Professional build system for Linux and Windows
- ✅ **Real-Time Data**: Circular buffers, smooth 60fps rendering
- ✅ **Enterprise Architecture**: All 6 core design patterns implemented

## 🚀 Quick Start

### **Development Setup**
```bash
# Clone and setup development environment
git clone <repository-url>
cd qpcetu

# Build for Linux (native)
cd scripts && ./build-linux.sh

# Build for Windows (cross-compilation)
cd scripts && ./build-windows.sh

# Build both platforms
cd scripts && ./build-all.sh
```

### **Build Requirements**
- **Qt5** (5.15+): Core, Widgets, Network, Svg modules
- **CMake** (3.16+): Build system
- **C++17 Compiler**: GCC 7+, Clang 5+, MSVC 2019+
- **libmodbus**: Industrial Modbus TCP communication

## 📊 Build Status

### **Verified Working Builds** ✅
- **Linux**: `build-linux-x64/bin/ModernSciFiHMI` (796KB + Qt5 libraries)
- **Windows**: `build-windows-x64/bin/ModernSciFiHMI.exe` (48MB standalone)

### **Professional Build Structure**
```
project-root/
├── scripts/              # Build automation
├── build-linux-x64/     # Linux build artifacts
├── build-windows-x64/   # Windows build artifacts
├── docs/                 # Comprehensive documentation
├── src/                  # Source code with enterprise architecture
└── deps/                 # Dependencies and external libraries
```

## 🎯 Industrial Applications

This HMI system is designed for:
- **Manufacturing Control**: Real-time monitoring and control of industrial processes
- **SCADA Systems**: Supervisory control and data acquisition
- **Process Automation**: Touch-friendly interfaces for industrial environments
- **Remote Monitoring**: Cross-platform deployment for various industrial computers
- **Data Visualization**: Real-time graphs and industrial dashboard displays

## 📞 Support

For technical support, development questions, or feature requests:
1. Check the relevant documentation section above
2. Review the [Development Guidelines](./development/guidelines.md)
3. Consult the [Build System Documentation](./development/build-system.md)

---

**Last Updated**: October 4, 2025
**Version**: Professional Structure Implementation (Steps 1-3 Complete)