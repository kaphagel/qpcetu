# Development Documentation

## Qt5 Industrial HMI Development Guide

This section contains technical documentation for developers working on the Qt5-based industrial HMI system.

## 📋 Documentation Index

### **[Guidelines](./guidelines.md)**
Comprehensive development guidelines including:
- **Project Context**: Industrial touch screen HMI requirements
- **Architecture Patterns**: Strategy, Command, State Machine, Observer, Repository, Plugin
- **Qt5 Guidelines**: Widgets-specific best practices and touch optimization
- **Design System**: Clean, borderless design with multi-theme support
- **Build System**: CMake configuration and cross-platform compatibility

### **[Build System](./build-system.md)**
Cross-platform build documentation including:
- **Build Requirements**: Dependencies and toolchain setup
- **Linux Native Build**: Professional build automation
- **Windows Cross-Compilation**: MXE toolchain integration
- **Docker Support**: Multi-platform build automation
- **Troubleshooting**: Common build issues and solutions

## 🎯 Development Workflow

### **1. Setup Development Environment**
```bash
# Clone repository
git clone <repository-url>
cd qpcetu

# Setup dependencies (Linux)
sudo apt install qtbase5-dev qtdeclarative5-dev libqt5svg5-dev cmake build-essential

# Verify environment
./scripts/build-linux.sh
```

### **2. Follow Architecture Patterns**
The codebase implements 6 core enterprise patterns:
- **Strategy Pattern**: `src/strategies/` - Controller protocol abstraction
- **Command Pattern**: `src/commands/` - Industrial operations with undo/redo
- **State Machine Pattern**: `src/statemachine/` - Connection lifecycle management
- **Observer Pattern**: `src/events/` - Real-time event propagation
- **Repository Pattern**: `src/data/` - Data persistence interfaces
- **Plugin Architecture**: `src/plugins/` - Extensible controller support

### **3. Implement Clean Design**
Follow the clean, borderless design principles:
- **No decorative borders**: Use theme-appropriate backgrounds and spacing
- **Theme-aware styling**: Use ThemeManager for dynamic color management
- **Touch optimization**: 60x60px minimum button sizes, generous spacing
- **Professional typography**: Clear hierarchy with font weights and sizes

### **4. Test Cross-Platform**
Ensure changes work on both platforms:
```bash
# Test Linux build
./scripts/build-linux.sh

# Test Windows cross-compilation
./scripts/build-windows.sh

# Test both platforms
./scripts/build-all.sh
```

## 🔧 Development Tools

### **Recommended IDE Setup**
- **VS Code**: With C++ and CMake extensions
- **Qt Creator**: For Qt-specific development and UI design
- **Git**: Version control with professional commit messages

### **Code Quality Tools**
- **clang-format**: Code formatting consistency
- **cppcheck**: Static analysis for C++ code
- **QTest**: Unit testing framework for Qt applications
- **Doxygen**: API documentation generation

### **Debugging Tools**
- **gdb**: Linux debugging with Qt integration
- **Qt Creator Debugger**: Visual debugging for Qt applications
- **Valgrind**: Memory leak detection and profiling

## 🏗️ Architecture Overview

```
src/
├── commands/           # Command Pattern implementations
├── statemachine/       # State Machine Pattern
├── strategies/         # Strategy Pattern for protocols  
├── events/            # Observer Pattern + Event System
├── data/              # Repository Pattern
├── plugins/           # Plugin Architecture
├── ui/                # Qt Widgets UI Components
└── core/              # Core models and services
```

## 📝 Coding Standards

### **C++ Guidelines**
- **Modern C++17**: Use latest language features appropriately
- **RAII**: Resource Acquisition Is Initialization for resource management
- **Smart Pointers**: std::unique_ptr, std::shared_ptr instead of raw pointers
- **Qt Idioms**: Signals/slots, proper Qt object lifecycle management

### **File Organization**
- **Header/Implementation Separation**: Always create .h + .cpp pairs
- **Class Size**: Keep classes focused and under 500 lines
- **Naming**: Clear, descriptive names following Qt conventions
- **Documentation**: Doxygen-style comments for all public APIs

### **UI Development**
- **Qt Widgets**: Current implementation using QWidget components
- **Touch Optimization**: Large targets, generous spacing, clear feedback
- **Theme Integration**: Use ThemeManager for all color decisions
- **Accessibility**: Support for different hand sizes and industrial gloves

## 🧪 Testing Strategy

### **Unit Testing**
- **QTest Framework**: For business logic and core components
- **Mock Objects**: For external dependencies and hardware interfaces
- **Test Coverage**: Focus on critical paths and error handling

### **Integration Testing**
- **Cross-Platform Testing**: Verify functionality on Linux and Windows
- **Hardware Testing**: Test with actual industrial controllers when available
- **Performance Testing**: Ensure smooth 60fps operation under load

### **User Acceptance Testing**
- **Touch Interface Testing**: Verify usability with fingers and gloves
- **Industrial Environment Testing**: Test in various lighting conditions
- **Theme Testing**: Verify all themes work appropriately

---

## 📞 Developer Support

For technical questions and development support:
1. Review the [Guidelines](./guidelines.md) for detailed standards
2. Check the [Build System](./build-system.md) for build issues
3. Examine existing code patterns in the `src/` directory
4. Follow the established architecture patterns

**Last Updated**: October 30, 2025
**Focus**: Enterprise-grade Qt5 development with industrial requirements