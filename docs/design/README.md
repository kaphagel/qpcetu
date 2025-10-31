# Design Documentation

## Industrial HMI Design System

This section contains UI/UX design specifications and visual design system documentation for the touch-optimized industrial HMI.

## 📋 Documentation Index

### **[UI Specification](./ui-specification.md)**
Detailed user interface design specifications including:
- **Interface Layout**: Multi-page navigation and component organization
- **Touch Optimization**: Button sizes, spacing, and gesture support
- **Industrial Requirements**: Visibility, durability, and accessibility standards
- **Component Specifications**: Detailed UI element definitions

### **[Apple Design System](./apple-design-system.md)**
iOS/iPadOS inspired design guidelines adapted for industrial use including:
- **Typography Scale**: Large Title, Title 1, Body, Footnote, Caption hierarchy
- **Color System**: Dynamic theming with Dark, Light, High Contrast, Apple themes
- **Layout Principles**: Clean, borderless design with background differentiation
- **Touch Standards**: 60x60px minimum targets with generous spacing

> **Note**: For comprehensive project architecture and specifications, see [../ARCHITECTURE.md](../ARCHITECTURE.md) - the authoritative architectural reference.

## 🎨 Design System Overview

### **Multi-Theme Architecture**
The HMI supports 5 professional themes optimized for different industrial environments:

#### **Dark Theme** 🌙
- **Use Case**: Low-light industrial environments, night shifts
- **Colors**: Deep blues (#0F1419), cyan accents (#00E5FF)
- **Readability**: High contrast white text on dark backgrounds

#### **Light Theme** ☀️
- **Use Case**: Bright industrial environments, daylight operation
- **Colors**: Clean whites (#FAFAFA), blue accents (#1976D2)
- **Readability**: Dark text on light backgrounds for bright conditions

#### **High Contrast Theme** ⚡
- **Use Case**: Accessibility and harsh lighting conditions
- **Colors**: Pure black/white with bright accent colors
- **Readability**: Maximum contrast for visibility challenges

#### **Apple Light Theme** 🍎
- **Use Case**: Modern touch interfaces, iOS/iPadOS familiarity
- **Colors**: iOS system colors (#F2F2F7, #007AFF)
- **Design**: Clean, minimal aesthetic inspired by iOS Human Interface Guidelines

#### **Apple Dark Theme** 🌃
- **Use Case**: Modern dark mode with iOS/iPadOS consistency
- **Colors**: iOS dark system colors (#000000, #0A84FF)
- **Design**: Professional dark mode following Apple's design standards

### **Touch Optimization Standards**

#### **Minimum Touch Targets**
- **Primary Buttons**: 60x60px minimum (recommended 80x60px)
- **Secondary Controls**: 44x44px minimum
- **Critical Actions**: 80x60px for safety-critical operations
- **Text Input**: 60px minimum height for reliable touch input

#### **Spacing Requirements**
- **Between Interactive Elements**: 12px minimum, 16px recommended
- **Section Spacing**: 24px between major UI sections
- **Content Margins**: 20-32px from screen edges
- **Card Padding**: 16-24px internal padding for content cards

#### **Industrial Environment Adaptations**
- **Glove Compatibility**: Larger touch targets for safety gloves
- **Vibration Resistance**: Generous spacing to prevent accidental activation
- **Lighting Adaptability**: High contrast themes for various lighting conditions
- **Durability Focus**: Reduced precision requirements for harsh environments

### **Clean, Borderless Design Philosophy**

#### **No Decorative Borders Policy**
- **Visual Separation**: Use background color differences instead of borders
- **Focus States**: Borders only for accessibility focus when absolutely required
- **Touch Feedback**: Background color changes on hover/press, not border changes
- **Clean Aesthetics**: Minimal design reducing visual clutter

#### **Background Differentiation**
- **Primary Content**: Main theme background color
- **Secondary Panels**: Subtle background color variation for grouping
- **Interactive Elements**: Clear background changes for button states
- **Status Indicators**: Theme-appropriate color coding for system states

### **Typography Hierarchy**

#### **Apple-Inspired Typography Scale**
- **Large Title**: 28px, font-weight: 700 - Main section headers
- **Title 1**: 22px, font-weight: 700 - Panel titles
- **Body**: 17px, font-weight: 400 - Primary content text
- **Footnote**: 15px, font-weight: 400 - Status and secondary information
- **Caption**: 13px, font-weight: 400 - Detailed secondary text

#### **Industrial Readability Standards**
- **Minimum Size**: 14px for any readable text in industrial environments
- **Recommended Size**: 16-18px for primary content text
- **High Contrast**: Appropriate color contrast ratios for all themes
- **Distance Viewing**: Optimized for arm's length reading distance

## 🏗️ Component Design Standards

### **Controller Cards**
- **Size**: 300x200px minimum for touch interaction
- **Information Hierarchy**: Status → Name → Key Metrics → Actions
- **Status Indicators**: Color-coded backgrounds with icon support
- **Action Buttons**: Clearly labeled with generous touch targets

### **Navigation Interface**
- **Tab Navigation**: Large, clearly labeled tabs with touch optimization
- **Breadcrumbs**: Clear navigation path indication
- **Back Navigation**: Prominent back buttons where appropriate
- **Search Interface**: Touch-friendly search with large input areas

### **Data Visualization**
- **Real-Time Graphs**: Clean, minimal design with clear data lines
- **Status Dashboards**: Grid-based layout with consistent card sizing
- **Alert Indicators**: Prominent, color-coded alerts with clear messaging
- **Progress Indicators**: Large, easy-to-read progress bars and percentages

### **Form Design**
- **Input Fields**: Large, clearly labeled input areas
- **Button Groups**: Logical grouping with consistent spacing
- **Validation Feedback**: Clear, immediate feedback for user inputs
- **Submit Actions**: Prominent, clearly labeled primary actions

## 🎯 Industrial Design Considerations

### **Environmental Factors**
- **Temperature Variations**: UI elements sized for thermal expansion considerations
- **Humidity Resistance**: Clear, readable text in high humidity conditions
- **Dust Resistance**: Simplified interfaces reducing cleaning complexity
- **Chemical Resistance**: Durable design elements for industrial chemical exposure

### **User Factors**
- **PPE Compatibility**: Design accommodating safety equipment and gloves
- **Fatigue Resistance**: Clear, easy-to-read interfaces reducing eye strain
- **Stress Conditions**: Simplified interactions for high-stress industrial situations
- **Training Efficiency**: Intuitive design reducing training requirements

### **Safety Integration**
- **Emergency Actions**: Prominent, easily accessible emergency controls
- **Status Clarity**: Clear indication of system states and alerts
- **Error Prevention**: Design preventing accidental activation of critical functions
- **Audit Trail**: Visual indication of user actions for compliance

---

## 📞 Design Support

For design questions and UI/UX guidance:
1. Review the specific design documentation above
2. Check the [Apple Design System](./apple-design-system.md) for detailed styling
3. Examine the [UI Specification](./ui-specification.md) for component details
4. Follow established design patterns in the existing interface

**Last Updated**: October 30, 2025
**Focus**: Touch-optimized industrial HMI with multi-theme support