# UI Specification - SciFi Data Screen

## Overview
Modern QML-based interface with sci-fi aesthetics for real-time industrial data visualization.

## Design System

### Color Palette
```qml
// Primary Colors
property color neonCyan: "#00FFFF"
property color neonOrange: "#FF8C00" 
property color neonGreen: "#00FF7F"
property color neonPink: "#FF143C"

// Background/Structure
property color darkNavy: "#080C14"
property color gridBlue: "#285078"
property color panelDark: "#0A0F1A"
```

### Typography
```qml
FontLoader { id: monoFont; source: "fonts/CourierPrime.ttf" }
FontLoader { id: titleFont; source: "fonts/Orbitron.ttf" }

// Text Styles
property int titleSize: 16
property int labelSize: 12
property int valueSize: 14
```

### Visual Effects
- **Glow Effects**: 15px blur radius, 60 opacity
- **Grid Patterns**: Hexagonal overlay, scan lines
- **Animations**: 200ms smooth transitions
- **Corner Brackets**: Futuristic frame elements

## Layout Structure

### Main Window (1920x1080 target)
```qml
ApplicationWindow {
    minimumWidth: 1280
    minimumHeight: 720
    
    // Main layout structure
    RowLayout {
        NavigationPanel { width: 200 }
        StackView { 
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
        StatusPanel { width: 300 }
    }
}
```

### Navigation Panel (200px width)
```
┌─────────────────┐
│ [LOGO]          │
├─────────────────┤
│ ▶ Graphs        │
│   Settings      │
│   Status        │
│   About         │
├─────────────────┤
│ Connection:     │
│ ● CONNECTED     │
└─────────────────┘
```

### Main Content Area (Responsive)
```
┌─────────────────────────────────────┐
│ Page Title                          │
├─────────────────┬─────────────────┤
│                 │                 │
│   Graph 1       │   Graph 2       │
│   (Sine Wave)   │   (Random)      │
│                 │                 │
├─────────────────┼─────────────────┤
│                 │                 │
│   Graph 3       │   Graph 4       │
│   (Step Func)   │   (Pulse)       │
│                 │                 │
└─────────────────┴─────────────────┘
```

## Component Specifications

### GraphWidget QML Component
```qml
// Public Properties
property string title: "Graph"
property int graphType: GraphWidget.SineWave
property color graphColor: "#00FFFF"
property real minValue: 0.0
property real maxValue: 100.0
property int maxDataPoints: 200

// Methods
Q_INVOKABLE void addDataPoint(real value)
Q_INVOKABLE void clearData()
Q_INVOKABLE void exportData()
```

**Visual Elements:**
- **Grid**: 12 vertical × 8 horizontal scan lines
- **Axes**: White 2px lines with value labels
- **Data Line**: Graph color, 1-2px thickness
- **Scan Marker**: Dotted vertical line
- **Value Display**: Top-right corner, yellow text
- **Corner Brackets**: Graph color, 15px size

### Navigation Panel Component
```qml
Rectangle {
    width: 200
    color: "#0A0F1A"
    
    Column {
        Logo { height: 80 }
        Repeater {
            model: navigationModel
            NavigationItem { }
        }
        ConnectionStatus { }
    }
}
```

### StatusPanel Component
```qml
Rectangle {
    width: 300
    color: "#0A0F1A"
    
    Column {
        SystemStats { }
        DataRates { }
        ErrorLog { }
    }
}
```

## Responsive Behavior

### Breakpoints
- **Large**: 1920px+ (4 graphs in 2×2)
- **Medium**: 1280-1919px (4 graphs, smaller)
- **Small**: 800-1279px (2 graphs vertically)
- **Mobile**: <800px (1 graph, stack navigation)

### Layout Adaptation
```qml
GridLayout {
    columns: width > 1280 ? 2 : 1
    rows: width > 1280 ? 2 : 4
    
    Repeater {
        model: 4
        GraphWidget {
            Layout.fillWidth: true
            Layout.fillHeight: true
            Layout.minimumHeight: 300
        }
    }
}
```

## Interactions

### Graph Interactions
- **Click**: Select/focus graph
- **Scroll**: Zoom in/out
- **Drag**: Pan when zoomed
- **Right-click**: Context menu (export, settings)
- **Double-click**: Reset zoom/pan

### Keyboard Shortcuts
- **Ctrl+1-4**: Focus graph 1-4
- **Ctrl+E**: Export current graph
- **Ctrl+R**: Reset all graphs
- **Ctrl+S**: Open settings
- **F11**: Toggle fullscreen

## Animation Specifications

### Transitions
```qml
// Page transitions
StackView {
    pushEnter: Transition {
        PropertyAnimation {
            property: "opacity"
            from: 0; to: 1
            duration: 200
        }
    }
}

// Graph data updates
Behavior on dataValue {
    NumberAnimation { duration: 50 }
}

// Hover effects
MouseArea {
    hoverEnabled: true
    onEntered: glow.opacity = 0.8
    onExited: glow.opacity = 0.4
}
```

### Performance Targets
- **Frame Rate**: 60fps sustained
- **Transition Duration**: 200ms standard
- **Data Update Rate**: 10Hz smooth
- **Memory Usage**: <100MB typical

## Accessibility

### High Contrast Mode
```qml
Settings {
    property bool highContrast: false
}

// Conditional styling
color: settings.highContrast ? "#FFFFFF" : neonCyan
```

### Keyboard Navigation
- Tab order through all interactive elements
- Visual focus indicators
- Escape key to cancel operations

## Implementation Guidelines

### QML Structure
```
qml/
├── main.qml                 # Application entry point
├── components/
│   ├── GraphWidget.qml      # Reusable graph component
│   ├── NavigationPanel.qml  # Left navigation
│   └── StatusPanel.qml      # Right status panel
├── pages/
│   ├── GraphsPage.qml       # Main 2x2 graph view
│   ├── SettingsPage.qml     # Configuration
│   └── AboutPage.qml        # About/help
└── styles/
    ├── Colors.qml           # Color definitions
    ├── Fonts.qml           # Typography
    └── Effects.qml         # Reusable effects
```

### Data Binding Pattern
```qml
// C++ ViewModel exposed to QML
GraphViewModel {
    id: graphModel
    property real currentValue: 0.0
    property var dataPoints: []
}

// QML binds to C++ properties
GraphWidget {
    title: "Sensor Data"
    dataPoints: graphModel.dataPoints
    currentValue: graphModel.currentValue
}
```

## Development Notes

This specification provides:
- **Visual consistency** across components
- **Responsive design** for different screen sizes  
- **Performance targets** for smooth operation
- **Implementation guidance** for QML/C++ integration
- **Accessibility considerations**
- **Clear component interfaces**

For active development tasks, see the GitHub Issues board and follow the coding guidelines in [`.github/instructions/instructions.instructions.md`](.github/instructions/instructions.instructions.md).