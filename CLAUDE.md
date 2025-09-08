# Qt Application Debugging Guide - SciFi Data Screen

## Project Overview
This document captures the debugging process and solutions for the **Quantum Tactical Processing Center - ETU** Qt5 application that was experiencing segmentation faults during deployment. The application now features real-time data widgets, animated progress bars, and live graphing capabilities with fake data simulation.

## Features Added

### Real-Time Graphs
- **GraphWidget Class**: Custom widget that displays scrolling real-time graphs
- **Multiple Graph Types**:
  - `SineWave`: Smooth sinusoidal patterns for energy flux monitoring
  - `RandomData`: Random walk simulation for shield harmonics
  - `StepFunction`: Step-based data for system status monitoring  
  - `PulseWave`: Square wave patterns for network traffic visualization
- **Visual Effects**: Anti-aliased rendering, gradient colors, glow effects, and grid overlays
- **Performance**: Optimized data point management with configurable history limits

### Graph Integration
- **Six Live Graphs**: Energy Flux, Shield Harmonics, System Status, Network Traffic, Thruster Output, Sensor Array
- **Auto-updating**: Graphs update every 100ms with new fake data
- **Color-coded**: Each graph type has distinct neon colors (cyan, orange, green/teal, red/pink)
- **Responsive Layout**: Graphs automatically adjust to window resizing
- **Full Row Coverage**: Complete 4-column layout with graphs in rows 2-3

## Issues Fixed

### Graph Display Problems
- **Issue**: Graphs showed as solid rectangles instead of actual line graphs
- **Root Cause**: 
  1. All graphs initialized with identical data points (50.0)
  2. Data generation had insufficient variation (RandomData: ±5, StepFunction: 3% change rate)
  3. Values clustered around the same range making lines nearly horizontal
- **Solution**:
  1. **Diverse initialization**: Each graph type starts with different random values
  2. **Enhanced data generation**: 
     - RandomData: Increased variation to ±30 (was ±5)
     - StepFunction: Increased change probability to 8% (was 3%)
     - PulseWave: Clearer high/low transitions
     - SineWave: Added random starting offset
  3. **Improved coordinate calculation**: Added bounds checking and division-by-zero protection

### Layout Conflicts  
- **Issue**: Graphs weren't visible due to widget overlap
- **Root Cause**: System Panel and Control Panel occupied the same grid positions as graphs
- **Solution**: Moved all graphs to row 3 to create dedicated graph area

### Graph Widget Positioning (CRITICAL FIX)
- **Issue**: Graphs were completely invisible despite functional paintEvent calls
- **Root Cause**: QGridLayout was positioning GraphWidgets at Y=869 (near bottom edge of window), making them appear off-screen
- **Debug Process**: 
  1. Added extensive debug output to paintEvent showing successful execution
  2. Tested with bright red backgrounds and yellow borders - still invisible
  3. Added widget geometry debugging revealing Y position at 869 vs visible position at Y=85
- **Solution**: Repositioned graphs in layout grid:
  - **Row 2**: Energy Flux (2,2), Shield Harmonics (2,3) - alongside system panels
  - **Row 3**: System Status (3,0), Network Traffic (3,1) - dedicated graph area
- **Result**: Graphs now properly visible with full functionality and sci-fi styling
- **Final Enhancement**: Enhanced with dramatic sci-fi visuals:
  - **Neon Colors**: Bright cyan (energy), orange (shields), green/teal (system), red/pink (network)
  - **Multi-layer Glow Effects**: 8-layer glow with dramatic falloff for cinematic appearance
  - **Futuristic Grid**: Hexagonal overlay patterns with corner brackets and scan lines
  - **Animated Elements**: Moving scan lines and glowing data points
  - **Gradient Fills**: Subtle translucent fills under curves for depth
  - **Enhanced Typography**: Monospace fonts with bright neon colors matching graph themes

## Current Layout
```
Row 0: [Status Panel spanning columns 0-3]
Row 1: [Energy Widget] [Shield Widget] [Empty] [Empty]
Row 2: [Engine Widget] [Weapon Widget] [Energy Graph] [Shield Graph]
Row 3: [System Graph] [Network Graph] [Thruster Graph] [Sensor Graph]
```

### Graph Specifications
- **Energy Flux** (Row 2, Col 2): Bright cyan SineWave, range 0-120
- **Shield Harmonics** (Row 2, Col 3): Bright orange RandomData, range 20-100  
- **System Status** (Row 3, Col 0): Bright green/teal StepFunction, range 0-100
- **Network Traffic** (Row 3, Col 1): Bright red/pink PulseWave, range 0-100
- **Thruster Output** (Row 3, Col 2): Bright cyan SineWave, range 0-150
- **Sensor Array** (Row 3, Col 3): Bright orange RandomData, range 10-90

## Root Causes Identified

### 1. **Qt Version Mismatch**
- **Problem**: CMakeLists.txt was configured for Qt6, but target machine had Qt5
- **Solution**: Updated CMakeLists.txt to use Qt5 components
```cmake
# Changed from Qt6 to Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets)
target_link_libraries(SciFiDataScreen Qt5::Core Qt5::Widgets)
```

### 2. **Missing Animation Destructors**
- **Problem**: `AnimatedProgressBar` and `DataWidget` classes had running animations that weren't properly cleaned up
- **Solution**: Added proper destructors to stop and delete animations

**AnimatedProgressBar Fix:**
```cpp
// Added destructor in animatedprogressbar.h
~AnimatedProgressBar();

// Implementation in animatedprogressbar.cpp
AnimatedProgressBar::~AnimatedProgressBar()
{
    if (m_flowAnimation) {
        m_flowAnimation->stop();
        delete m_flowAnimation;
        m_flowAnimation = nullptr;
    }
    
    if (m_valueAnimation) {
        m_valueAnimation->stop();
        delete m_valueAnimation;
        m_valueAnimation = nullptr;
    }
}
```

**DataWidget Fix:**
```cpp
// Added destructor in datawidget.h
~DataWidget();

// Implementation in datawidget.cpp
DataWidget::~DataWidget()
{
    if (m_glowAnimation) {
        m_glowAnimation->stop();
        delete m_glowAnimation;
        m_glowAnimation = nullptr;
    }
    
    if (m_valueAnimation) {
        m_valueAnimation->stop();
        delete m_valueAnimation;
        m_valueAnimation = nullptr;
    }
}
```

### 3. **Uninitialized Member Variables**
- **Problem**: MainWindow member variables weren't initialized to nullptr, causing undefined behavior
- **Solution**: Added comprehensive initialization list

```cpp
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , m_centralWidget(nullptr)
    , m_mainLayout(nullptr)
    , m_statusLabel(nullptr)
    , m_timeLabel(nullptr)
    , m_connectionStatus(nullptr)
    , m_energyWidget(nullptr)
    , m_shieldWidget(nullptr)
    , m_engineWidget(nullptr)
    , m_weaponWidget(nullptr)
    , m_powerBar(nullptr)
    , m_coolantBar(nullptr)
    , m_fuelBar(nullptr)
    , m_logDisplay(nullptr)
    , m_coordinates(nullptr)
    , m_velocity(nullptr)
    , m_altitude(nullptr)
    , m_engageBtn(nullptr)
    , m_alertBtn(nullptr)
    , m_scanBtn(nullptr)
    , m_updateTimer(nullptr)
    , m_statusTimer(nullptr)
    , m_alertTimer(nullptr)
    , m_alertLevel(0)
    , m_systemOnline(true)
```

### 4. **Invalid QPropertyAnimation Property**
- **Problem**: DataWidget was creating QPropertyAnimation with empty property name `""`
- **Solution**: Removed problematic animation and used direct value updates

```cpp
// Removed problematic animation code:
// m_valueAnimation = new QPropertyAnimation(this, "", this);

// Replaced with simple direct update:
void DataWidget::setValue(int value)
{
    m_targetValue = qBound(0, value, 100);
    m_currentValue = m_targetValue;
    updateDisplay();
}
```

### 5. **Missing Null Pointer Checks**
- **Problem**: Update functions were accessing potentially null widget pointers
- **Solution**: Added comprehensive null checks

```cpp
void MainWindow::updateData()
{
    QRandomGenerator *rng = QRandomGenerator::global();
    
    // Added null checks for all widgets
    if (m_energyWidget) m_energyWidget->setValue(85 + rng->bounded(15));
    if (m_shieldWidget) m_shieldWidget->setValue(70 + rng->bounded(30));
    // ... etc for all widgets
}
```

## Debugging Tools and Techniques Used

### 1. **GDB Debugging**
```bash
# Compile with debug symbols
cmake -DCMAKE_BUILD_TYPE=Debug ..
make

# Run with GDB
gdb ./bin/SciFiDataScreen
(gdb) run
(gdb) bt  # backtrace when crashed
```

### 2. **Dependency Analysis**
```bash
# Check Qt library dependencies
ldd build/bin/SciFiDataScreen | grep -i qt
```

### 3. **Strategic Debug Output**
Added temporary debug statements to pinpoint crash location:
```cpp
#include <QDebug>
qDebug() << "Checkpoint reached: " << __FUNCTION__ << __LINE__;
```

### 4. **Process Monitoring**
```bash
# Check if application is running
ps aux | grep SciFiDataScreen

# Kill hanging processes
pkill SciFiDataScreen
```

## Key Error Messages Encountered

1. **"file called with unknown argument 'OPTIONAL'"**
   - CMake file() command doesn't support OPTIONAL keyword
   - Fixed by using conditional file copying

2. **"Trying to construct an instance of an invalid type, type id: 177"**
   - Qt meta-object system error from invalid QPropertyAnimation
   - Fixed by removing invalid property animations

3. **Segmentation fault in QAbstractAnimation::stop()**
   - Animation objects not properly managed
   - Fixed with proper destructors

## Build Process

### Development Environment
```bash
# Build script handles dependencies and compilation
./build.sh
```

### Manual Build
```bash
mkdir build && cd build
cmake ..
make -j$(nproc)
```

### Dependencies (Ubuntu/Debian)
```bash
sudo apt update
sudo apt install qt5-base-dev libqt5widgets5 cmake build-essential
```

## Deployment Notes

### Target Machine Requirements
- Qt5 runtime libraries installed
- Linux-compatible binary (same architecture)
- X11 display environment for GUI

### Verification Commands
```bash
# Check Qt5 availability
pkg-config --modversion Qt5Core Qt5Widgets

# Test application
timeout 30 ./bin/SciFiDataScreen && echo "SUCCESS"
```

## Lessons Learned

1. **Always initialize pointer members to nullptr**
2. **Proper RAII for Qt animations - stop and delete in destructors**
3. **Use null checks before accessing widget pointers**
4. **Match Qt versions between development and target environments**
5. **Remove or properly implement animation property names**
6. **Test timer callbacks thoroughly as they run after window creation**

## Code Quality Improvements Made

1. **Memory Safety**: Added destructors and null checks
2. **Initialization**: Proper member variable initialization
3. **Error Handling**: Defensive programming practices
4. **Animation Management**: Proper lifecycle management
5. **Qt Best Practices**: Correct use of Qt's meta-object system

## Files Modified

- `CMakeLists.txt` - Qt6 → Qt5 migration, added GraphWidget files
- `src/animatedprogressbar.h` - Added destructor declaration
- `src/animatedprogressbar.cpp` - Implemented destructor
- `src/datawidget.h` - Added destructor declaration  
- `src/datawidget.cpp` - Implemented destructor, fixed setValue()
- `src/mainwindow.cpp` - Added member initialization, null checks, graph integration
- `src/mainwindow.h` - Added GraphWidget declarations and member variables
- `src/graphwidget.h` - **NEW**: Real-time graph widget header
- `src/graphwidget.cpp` - **NEW**: Real-time graph widget implementation
- `build.sh` - Updated to check Qt5 dependencies

## New Graph Widget API

### GraphWidget Constructor
```cpp
GraphWidget(const QString &title, GraphType type, QWidget *parent = nullptr)
```

### Graph Types
```cpp
enum GraphType {
    SineWave,      // Smooth sinusoidal patterns
    RandomData,    // Random walk simulation  
    StepFunction,  // Step-based data changes
    PulseWave      // Square wave patterns
};
```

### Key Methods
```cpp
void addDataPoint(qreal value);           // Add new data point
void setColor(const QColor &color);       // Set graph line color
void setRange(qreal min, qreal max);      // Set Y-axis range
```

### Integration Example
```cpp
// Create graph with sine wave pattern
m_energyGraph = new GraphWidget("ENERGY FLUX", GraphWidget::SineWave);
m_energyGraph->setRange(0, 120);
layout->addWidget(m_energyGraph, row, col);
```

## Final Result
✅ Application now runs stably on target machine without segmentation faults
✅ All animations and timers work correctly
✅ Memory leaks eliminated through proper destructors
✅ Robust error handling with null pointer checks


Visual Theme

Dark Mode Base: Dark background (black or deep navy) with high-contrast text and visuals.

Neon/Glowing Accents: Use bright cyan, teal, orange, and red for highlights, borders, and alerts.

Minimal Gradients: Mostly flat colors with occasional glowing effects.

📊 Layout & Structure

Grid Layout: Multiple panels arranged in a grid-like structure, each dedicated to a specific dataset.

Large Header Panels: Top row features large, detailed visualizations (3D models, trajectory paths, or key system diagrams).

Smaller Data Panels: Bottom rows show gauges, graphs, tables, and real-time stats.

Symmetry: Balanced arrangement for readability and focus.

📈 Data Visualization Style

Futuristic Charts: Line graphs, circular gauges, and bar indicators with glowing outlines.

3D Models / Schematics: Technical wireframe or shaded models in the center of panels.

Telemetry Panels: Numbers with units, system statuses, progress indicators.

Radar & Trajectories: Semi-circular arc plots for direction and navigation.

🔤 Typography

Sans-serif fonts: Clean, futuristic, and readable (e.g., Orbitron, Roboto Mono, or Eurostile).

High Contrast Text: White or light-gray text against dark background, with color-coded alerts (red = error, green = nominal).

✨ Overall Mood

High-tech / Aerospace UI (inspired by NASA, SpaceX, or sci-fi).

Functional but cinematic: Data-heavy but designed for clarity and drama.

Real-time feel: Everything looks like it updates live.

---
*This debugging session demonstrates the importance of proper C++ memory management and Qt-specific best practices in GUI application development.*
