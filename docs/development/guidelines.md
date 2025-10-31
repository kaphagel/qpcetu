# Development Guidelines

> **⚠️ CRITICAL**: This document provides practical day-to-day development guidelines. For comprehensive architectural decisions, SOLID principles, and design patterns, see **[../ARCHITECTURE.md](../ARCHITECTURE.md)** - the authoritative architectural reference.

## Quick Reference

This project is a real-time industrial HMI touch screen application built with **Qt5 Widgets and C++**.  
It uses Qt Widgets for the user interface, C++ backend for data processing, and UDP/Modbus TCP for real-time data acquisition.

### **Primary Documentation**
- **[../ARCHITECTURE.md](../ARCHITECTURE.md)** - SOLID principles, design patterns, technology stack decisions
- **[../README.md](../README.md)** - Documentation index and project overview
- **[build-system.md](./build-system.md)** - Build instructions and cross-platform compilation
- **This file** - Practical day-to-day development guidelines

---

## Touch Screen Optimization Requirements

**CRITICAL**: This HMI is primarily designed for **touch screen interfaces** in industrial environments:
- **Minimum button sizes**: 60x60px for reliable touch targets (Apple minimum: 44x44px)
- **Touch-friendly spacing**: 12-20px margins between interactive elements
- **Large, clear fonts**: 16-18px for readability from arm's length
- **High contrast colors**: Essential for visibility in various lighting conditions
- **Gesture support**: Swipe navigation, pinch-to-zoom for graphs where applicable
- **Feedback mechanisms**: Visual/haptic feedback for touch interactions
- **Glove-friendly design**: Accommodate work gloves and safety equipment
- **Landscape orientation**: Primary layout for industrial displays

---

## Design System Guidelines

**CRITICAL**: Follow **clean, minimal design** principles for professional industrial interfaces.

### **Theme System**
- **Multi-theme support**: Dark, Light, High Contrast, Apple Light, Apple Dark themes
- **Theme toggle**: Industrial-friendly button in header bar for quick theme switching
- **Clean styling**: All themes maintain borderless design while adapting colors appropriately
- **Accessibility**: High contrast mode for harsh industrial lighting conditions
- **Dark mode**: Industry-standard dark gray `#1C1C1E` (NOT pure black - reduces eye strain)

### **Color Palette**
- **Dynamic theming**: Colors adapt based on selected theme
- **Never hardcode colors**: Use `ThemeManager` for all color decisions
- **Industrial status colors**: Color-coded controller states (Active/Inactive/Fault) across all themes
- **iOS colors**: Light mode `#007AFF` blue, Dark mode `#0A84FF` blue, subtle grays for hover

### **Border Policy**
- **NO DECORATIVE BORDERS**: Remove all decorative borders from frames, panels, and containers
- **Clean separation**: Use theme-appropriate background color differences and spacing for visual hierarchy
- **Focus only**: Borders only for accessibility focus states when absolutely required
- **Touch feedback**: iOS-style subtle gray overlays on hover/press (NOT blue colors)
  - Light mode hover: `#E5E5EA` (systemGray5 - visible on white)
  - Light mode pressed: `#D1D1D6` (systemGray4 - darker)
  - Dark mode hover: `#2C2C2E` (subtle dark gray)
  - Dark mode pressed: `#3A3A3C` (slightly lighter gray)

### **Typography Scale**
- **Large Title**: 28px, font-weight: 700 - Main section headers
- **Title 1**: 22px, font-weight: 700 - Panel titles  
- **Body**: 17px, font-weight: 400 - Content text
- **Footnote**: 15px, font-weight: 400 - Status information
- **Caption**: 13px, font-weight: 400 - Secondary details

### **Layout Principles**
- **Generous spacing**: 16px, 24px, 32px margins for clean separation
- **Card-based design**: Theme-appropriate background colors with border-radius (8px, 12px) but no borders
- **Typography hierarchy**: Font weights and sizes for organization, not visual frames
- **Clean header**: Minimal navigation-only header (hamburger, back, home, theme toggle)
- **Content focus**: Remove non-essential status indicators for cleaner interface

---

## Architecture Guidelines

> **📚 For comprehensive architectural documentation, see [../ARCHITECTURE.md](../ARCHITECTURE.md)**

The application follows these core patterns (detailed in ARCHITECTURE.md):
- **MVVM Pattern**: View-ViewModel-Model separation
- **Strategy Pattern**: Controller-specific protocols (EPIC4, SNAP_PAC)
- **Command Pattern**: Industrial operations with undo/redo
- **State Machine Pattern**: Connection lifecycle management
- **Observer Pattern**: Real-time event propagation (Qt signals/slots)
- **Repository Pattern**: Data persistence and historical storage
- **Factory Pattern**: Object creation
- **Singleton Pattern**: Global services (use sparingly)

### Quick Guidelines
- Always separate business logic from UI code
- Use interfaces (abstract classes) for dependency injection
- Ensure thread safety in all real-time components
- Implement proper error handling with industrial-grade robustness
- Follow SOLID principles (see ARCHITECTURE.md for detailed examples)

---

## Qt5 Development Guidelines

### **File Organization**
```cpp
// Always generate .h + .cpp pairs
// Header (.h): Declaration only
// Implementation (.cpp): Implementation only

// Class names: PascalCase
class GraphViewModel { };

// Method names: camelCase
void updateData();
void processAlarm();

// Member variables: m_ prefix + camelCase
private:
    IDataSource* m_dataSource;
    QTimer* m_updateTimer;

// Constants: UPPER_SNAKE_CASE
const int MAX_BUFFER_SIZE = 1000;

// Always use:
// - #pragma once (not include guards)
// - auto for complex types
// - nullptr (not NULL)
// - override keyword
```

### **Qt-Specific Guidelines**
```cpp
class ModernMainWindow : public QMainWindow {
    Q_OBJECT  // Required for signals/slots

public:
    explicit ModernMainWindow(QWidget* parent = nullptr);
    
signals:
    void dataUpdated(const QString& tag, double value);
    
public slots:
    void onDataReceived();
    
private:
    QTimer* m_timer;
};

// Always use:
// - signals/slots (not callbacks)
// - QSharedPointer/QScopedPointer for Qt objects
// - QString, QDateTime (not std::string, time_t)
```

### **C++ Best Practices**
- Write **modern C++ (C++17)**
- Prefer **RAII** (Resource Acquisition Is Initialization)
- Use **smart pointers** (std::unique_ptr, std::shared_ptr) instead of raw new/delete
- Keep classes **focused and under ~500 lines** — split if needed
- Favor **Qt idioms** when working with Qt APIs
- **Don't introduce non-Qt GUI frameworks**
- **Don't mix UI with business logic**

---

## Real-Time Data Guidelines

### **Data Storage**
- Use **circular buffers** for efficient data storage (see `CircularDataBuffer` class)
- Implement **QTimer** for periodic data updates
- Handle **large datasets** without memory leaks

### **Rendering**
- Use **QPainter** for custom visualizations
- Ensure **smooth 60fps** rendering with efficient drawing
- Update only changed regions when possible

### **Threading**
- Keep UI updates on **main thread only**
- Use **QThread** or **QtConcurrent** for background processing
- Use **signals/slots** for thread-safe communication

---

## Modbus TCP Guidelines

### **Communication**
- Use **libmodbus** (deps/external/libmodbus/) for Modbus TCP communication
- Implement **robust error handling** and auto-reconnection
- Use **separate thread** for network operations if needed
- Apply **data scaling and validation** before display

### **Example Pattern**
```cpp
// Service layer (background thread)
class ModbusService {
    modbus_t* m_context;
    void readRegisters(); // Emits signal on success
signals:
    void dataReceived(int address, uint16_t value);
};

// ViewModel (main thread)
class GraphViewModel : public QObject {
    void onModbusData(int address, uint16_t value) {
        // Process and emit UI update signal
    }
};
```

---

## Development Workflow

### **1. Define Core Classes First**
- Start with domain models (pure C++, no Qt dependencies)
- Define interfaces for services (Strategy, Repository patterns)
- Implement business logic in ViewModels

### **2. Build UI Components**
- Create Qt Widget-based views
- Wire with signals/slots to ViewModels
- Apply theme-appropriate styling (use ThemeManager)
- Ensure touch-optimized sizing (60x60px minimum buttons)

### **3. Testing**
- Write unit tests for ViewModels and services (Qt Test framework)
- Test business logic without UI dependencies
- Integration tests for service interactions
- See [../ARCHITECTURE.md](../ARCHITECTURE.md) for testing strategy (70/20/10 pyramid)

### **4. Documentation**
- Document all public classes and methods with **Doxygen-style comments**
- Update relevant documentation when making architectural changes
- Keep diagrams in **Mermaid or PlantUML** syntax
- Main specs live in Markdown

---

## Build Quick Reference

```bash
# Linux Build
cd scripts && ./build-linux.sh

# Windows Build (cross-compilation)
cd scripts && ./build-windows.sh

# Build All Platforms
cd scripts && ./build-all.sh

# Run Application
build-linux-x64/bin/ModernSciFiHMI        # Linux
wine build-windows-x64/bin/ModernSciFiHMI.exe  # Windows (via Wine)
```

For detailed build instructions, see [build-system.md](./build-system.md).

---

## AI Agent Reminders

### **Always Do**
- ✅ Generate `.h` + `.cpp` pairs (separate declaration and implementation)
- ✅ Use **signals/slots** rather than callbacks
- ✅ Favor **Qt idioms** when working with Qt APIs
- ✅ Use **ThemeManager** for all colors (no hardcoding)
- ✅ Follow **SOLID principles** (see ARCHITECTURE.md)
- ✅ Separate **business logic from UI** code
- ✅ Use **interfaces** for dependency injection
- ✅ Ensure **thread safety** in real-time components

### **Never Do**
- ❌ Don't introduce non-Qt GUI frameworks
- ❌ Don't mix UI with business logic
- ❌ Don't add decorative borders (use backgrounds and spacing)
- ❌ Don't hardcode colors (use ThemeManager)
- ❌ Don't create buttons smaller than 60x60px
- ❌ Don't use raw pointers for owned objects (use smart pointers)

---

## References

- **[ARCHITECTURE.md](../ARCHITECTURE.md)** - Comprehensive architectural guide (SOLID, patterns, technology stack)
- **[build-system.md](./build-system.md)** - Build instructions and cross-platform compilation
- **[README.md](../README.md)** - Documentation index
- **[Qt5 Documentation](https://doc.qt.io/qt-5/)** - Official Qt5 reference

---

**Last Updated**: October 30, 2025  
**Version**: Streamlined Guidelines (references ARCHITECTURE.md as primary source)
