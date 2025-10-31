# Quantum Tactical Processing Center - ETU
## Industrial HMI Documentation

This directory contains comprehensive documentation for the Qt5-based industrial HMI system with touch-optimized interface and cross-platform support.

## 📚 Documentation Structure

### 🏛️ Architecture & Design Principles
**CRITICAL**: Read these foundational documents before making any architectural changes.

- **[ARCHITECTURE.md](./ARCHITECTURE.md)** - 📖 **PRIMARY REFERENCE** for all architectural decisions
  - SOLID Principles with code examples
  - Clean Architecture layered design
  - 8 Primary Design Patterns (MVVM, Strategy, Repository, Observer, Command, State Machine, Factory, Singleton)
  - Technology Stack decisions with rationale
  - Directory structure and organization
  - Coding standards and testing strategy
  - System architecture diagrams

### 🔧 [Development](./development/)
Technical documentation for developers working on the HMI system.
- **[Guidelines](./development/guidelines.md)** - Coding standards, architecture patterns, and best practices
- **[Build System](./development/build-system.md)** - Cross-platform build documentation and troubleshooting

### 🎨 [Design](./design/)
UI/UX design specifications and visual design system documentation.
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
All architectural patterns are comprehensively documented in **[ARCHITECTURE.md](./ARCHITECTURE.md)** with code examples:

- **MVVM Pattern**: View-ViewModel-Model separation with Qt signals/slots
- **Strategy Pattern**: Protocol-specific controller communication (EPIC4, SNAP_PAC)
- **Command Pattern**: Industrial operations with undo/redo support and audit trails
- **State Machine**: Connection lifecycle management (Disconnected → Connected → Running → Fault)
- **Observer Pattern**: Real-time event propagation using Qt signals/slots
- **Repository Pattern**: Data persistence and historical storage abstraction
- **Factory Pattern**: Object creation for controllers, strategies, commands
- **Singleton Pattern**: Global services (ThemeManager, NavigationManager, EventManager)

**See [ARCHITECTURE.md](./ARCHITECTURE.md) for detailed implementation examples and SOLID principles.**

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

This HMI system follows **SOLID principles** and **Clean Architecture** for industrial-grade reliability:

### **Application Domains**
- **Manufacturing Control**: Real-time monitoring and control of industrial processes
- **SCADA Systems**: Supervisory control and data acquisition
- **Process Automation**: Touch-friendly interfaces for industrial environments
- **Remote Monitoring**: Cross-platform deployment for various industrial computers
- **Data Visualization**: Real-time graphs and industrial dashboard displays

### **Design Goals** (from [ARCHITECTURE.md](./ARCHITECTURE.md))
1. **Maintainability**: Easy to understand, modify, and extend over time
2. **Testability**: Components can be tested in isolation
3. **Flexibility**: Support multiple controller types and protocols
4. **Scalability**: Handle multiple controllers and large datasets
5. **Reliability**: Industrial-grade robustness for 24/7 operation
6. **User Experience**: Professional, clean, Apple-inspired touch interfaces

## 📞 Support

For technical support, development questions, or feature requests:
1. **Start with [ARCHITECTURE.md](./ARCHITECTURE.md)** - Comprehensive architectural guide
2. Check the relevant documentation section above
3. Review the [Development Guidelines](./development/guidelines.md)
4. Consult the [Build System Documentation](./development/build-system.md)

### **Documentation Philosophy**
This project maintains **living documentation** that evolves with the codebase:
- **ARCHITECTURE.md**: Authoritative source for all architectural decisions
- **Development docs**: Practical guides for daily development work
- **Design docs**: UI/UX specifications and design system guidelines
- **API docs**: Generated from code comments (Doxygen-style)

---

**Last Updated**: October 30, 2025  
**Version**: SOLID Principles & Clean Architecture Implementation  
**Primary Reference**: [ARCHITECTURE.md](./ARCHITECTURE.md)