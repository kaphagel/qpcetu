# Project Specifications - SciFi Data Screen

> **Note**: This document serves as a high-level technical reference. For active development tasks, see [GitHub Issues](https://github.com/kaphagel/qpcetu/issues) and the [Project Board](https://github.com/kaphagel/qpcetu/projects).

## Project Overview

### What We're Building
A modern Qt-based desktop application for real-time data visualization with a sci-fi aesthetic, featuring multiple graph displays and network data acquisition capabilities.

## Core Requirements

### 1. Technology Stack
- **Framework**: Qt6 with QML/Quick for modern UI
- **Language**: C++ backend with QML frontend
- **Build System**: CMake
- **Platform**: Cross-platform (Linux primary, Windows/macOS secondary)
- **Data Protocol**: Modbus TCP for real-time data acquisition

### 2. User Interface Requirements

#### Layout Structure
- **Main Window**: Resizable, minimum 1024x768
- **Navigation**: Side panel or tab-based navigation
- **Graph Area**: 2x2 grid layout with 4 equally-sized graphs
- **Status Bar**: Connection status, data rates, timestamps

#### Visual Design
- **Theme**: Sci-fi/futuristic dark theme
- **Colors**: Neon accents (cyan, orange, green, red/pink)
- **Fonts**: Monospace fonts (Courier New style)
- **Effects**: Subtle glow effects, animated elements
- **Grid**: Hexagonal overlay patterns on graphs

### 3. Data Visualization Requirements

#### Graph Types
1. **EEG Waveform** (Primary)
   - Real-time streaming data from Modbus TCP
   - Oscilloscope-style sweep display
   - Range: 0-120 (scaled from Modbus /10)
   - Update rate: 1 second intervals

2. **Additional Graphs** (3 more)
   - Shield Harmonics (RandomData)
   - System Status (StepFunction) 
   - Network Traffic (PulseWave)
   - Each with configurable ranges and update rates

#### Graph Features
- **Real-time Updates**: Smooth data streaming
- **Circular Buffer**: Efficient memory usage
- **Zoom/Pan**: User interaction capabilities
- **Export**: Data export to CSV/JSON
- **Alerts**: Threshold-based visual alerts

### 4. Network Data Acquisition

#### Modbus TCP Client
- **Server**: 192.168.10.243:502
- **Register**: Input register 25
- **Polling**: 1-second intervals
- **Error Handling**: Robust reconnection logic
- **Data Processing**: Scale factor (divide by 10)

#### Connection Management
- **Auto-reconnect**: On connection failures
- **Retry Logic**: Exponential backoff
- **Status Monitoring**: Connection health display
- **Timeout Handling**: Configurable timeouts

## Technical Specifications

### 1. Architecture

#### Component Structure
```
Application Layer (QML)
├── Main Window
├── Navigation Panel
├── Graph Views (4x)
└── Status Components

Business Logic Layer (C++)
├── Data Manager
├── Modbus Client
├── Graph Controller
└── Configuration Manager

Data Layer
├── Circular Buffers
├── Data Models
└── Export Handlers
```

#### Design Patterns
- **Model-View-ViewModel (MVVM)**: For QML data binding
- **Observer Pattern**: For real-time updates
- **Factory Pattern**: For graph type creation
- **Singleton Pattern**: For configuration management

### 2. Performance Requirements

#### Real-time Performance
- **Update Rate**: 1Hz minimum, 10Hz target
- **Latency**: <100ms from data acquisition to display
- **Memory Usage**: <100MB typical, <500MB maximum
- **CPU Usage**: <10% on modern systems

#### Scalability
- **Data Points**: Support 10,000+ points per graph
- **Concurrent Connections**: Multiple Modbus sources
- **History**: 24-hour data retention minimum

### 3. Data Management

#### Data Flow
1. **Acquisition**: Modbus TCP polling
2. **Processing**: Scaling, validation, filtering
3. **Storage**: Circular buffer in memory
4. **Display**: Real-time graph updates
5. **Export**: File output on demand

#### Data Validation
- **Range Checking**: Min/max value validation
- **Error Detection**: Invalid/missing data handling
- **Quality Indicators**: Data confidence levels

## User Experience Requirements

### 1. Usability

#### Navigation
- **Intuitive**: Clear visual hierarchy
- **Responsive**: Immediate feedback
- **Accessible**: Keyboard navigation support
- **Consistent**: Uniform interaction patterns

#### Graph Interaction
- **Zoom**: Mouse wheel or gesture
- **Pan**: Click and drag
- **Selection**: Time range selection
- **Context Menu**: Right-click options

### 2. Visual Feedback

#### Status Indicators
- **Connection Status**: Green/red indicators
- **Data Flow**: Animated data flow indicators
- **Alerts**: Color-coded warning levels
- **Performance**: FPS/update rate display

#### Animations
- **Smooth Transitions**: 60fps target
- **Glow Effects**: Subtle enhancement
- **Data Flow**: Animated scan lines
- **State Changes**: Smooth transitions

## Quality Requirements

### 1. Reliability

#### Error Handling
- **Network Failures**: Graceful degradation
- **Data Corruption**: Recovery mechanisms
- **Memory Leaks**: Proper resource management
- **Crash Recovery**: Automatic restart capabilities

#### Testing
- **Unit Tests**: Core functionality coverage
- **Integration Tests**: End-to-end scenarios
- **Performance Tests**: Load and stress testing
- **UI Tests**: Automated interface testing

### 2. Maintainability

#### Code Quality
- **Documentation**: Comprehensive inline docs
- **Code Style**: Consistent formatting
- **Modularity**: Loosely coupled components
- **Version Control**: Git with clear commit messages

#### Configuration
- **Settings File**: JSON/XML configuration
- **Runtime Config**: Dynamic parameter changes
- **User Preferences**: Persistent UI settings
- **Debug Mode**: Verbose logging options

## Development Phases

### Phase 1: Foundation (Week 1-2)
- [ ] Qt6 + QML project setup
- [ ] Basic window structure
- [ ] Navigation framework
- [ ] Build system configuration

### Phase 2: Core Graphics (Week 3-4)
- [ ] Graph widget implementation
- [ ] Real-time data binding
- [ ] Visual styling and themes
- [ ] Basic interaction support

### Phase 3: Data Integration (Week 5-6)
- [ ] Modbus TCP client
- [ ] Data acquisition pipeline
- [ ] Error handling and reconnection
- [ ] Performance optimization

### Phase 4: Polish & Testing (Week 7-8)
- [ ] User experience refinement
- [ ] Comprehensive testing
- [ ] Documentation completion
- [ ] Deployment preparation

## Success Criteria

### Functional Requirements
- ✅ **Real-time Data**: Successful Modbus data acquisition
- ✅ **Graph Display**: 4 working graphs in 2x2 layout
- ✅ **Visual Quality**: Sci-fi themed interface
- ✅ **Performance**: Smooth 1Hz updates minimum
- ✅ **Reliability**: 24-hour continuous operation

### Non-Functional Requirements
- ✅ **Usability**: Intuitive operation within 5 minutes
- ✅ **Performance**: <100ms response time
- ✅ **Reliability**: <1% data loss under normal conditions
- ✅ **Maintainability**: Modular, documented codebase
- ✅ **Portability**: Runs on Linux/Windows/macOS

## Questions for Clarification

### Business Requirements
1. **Primary Use Case**: What is the main purpose of this application?
2. **Users**: Who will be using this system (operators, engineers, researchers)?
3. **Environment**: Will this run in industrial, lab, or office environments?
4. **Compliance**: Any regulatory or safety requirements?

### Technical Requirements
1. **Data Sources**: Are there other data sources besides Modbus TCP?
2. **Integration**: Does this need to integrate with existing systems?
3. **Deployment**: How will the application be distributed/installed?
4. **Licensing**: Any specific licensing requirements for Qt or other libraries?

### Operational Requirements
1. **Support**: What level of user support is expected?
2. **Updates**: How will updates be delivered and installed?
3. **Monitoring**: Any remote monitoring or diagnostics needed?
4. **Backup**: Data backup and recovery requirements?

---

**Next Steps**: Please review this specification and provide feedback on:
1. Missing requirements or features
2. Priority adjustments
3. Technical constraints or preferences
4. Timeline expectations
5. Any additional clarifications needed

This document will serve as our development roadmap and can be updated as requirements evolve.