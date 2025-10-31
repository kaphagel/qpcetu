# ABSOLUTE RULES (NEVER VIOLATE)

**Purpose**: Machine-readable constraints for AI agents. Every rule is MANDATORY.  
**Last Updated**: October 30, 2025

---

## File Organization Rules

- **RULE-001**: Every C++ class MUST have `.h` + `.cpp` pair (NO exceptions except templates)
- **RULE-002**: Header files MUST use `#pragma once` (NOT include guards)
- **RULE-003**: Implementation MUST be in `.cpp` (NEVER in `.h` except templates)
- **RULE-004**: Include corresponding `.h` file FIRST in `.cpp` files
- **RULE-005**: One class per file pair (exception: small helper structs in same file)

---

## Naming Convention Rules (Regex Patterns)

### Classes & Types
- **RULE-010**: Class names: `^[A-Z][a-zA-Z0-9]+$` (PascalCase, e.g., `GraphViewModel`)
- **RULE-011**: Interface names: `^I[A-Z][a-zA-Z0-9]+$` (I prefix, e.g., `IDataSource`)

### Methods & Functions
- **RULE-020**: Method names: `^[a-z][a-zA-Z0-9]+$` (camelCase, e.g., `updateData`)
- **RULE-021**: Qt slots: `^on[A-Z][a-zA-Z0-9]+$` (on prefix, e.g., `onDataReceived`)

### Variables
- **RULE-030**: Member variables: `^m_[a-z][a-zA-Z0-9]+$` (m_ prefix MANDATORY, e.g., `m_timer`)
- **RULE-031**: Local variables: `^[a-z][a-zA-Z0-9]+$` (camelCase, e.g., `dataPoint`)
- **RULE-032**: Constants: `^[A-Z][A-Z0-9_]+$` (UPPER_SNAKE_CASE, e.g., `MAX_BUFFER_SIZE`)

### Files
- **RULE-040**: C++ files: `^[a-z][a-z0-9-]*\.(h|cpp)$` (kebab-case, e.g., `graph-widget.h`)
- **RULE-041**: Exception: `ARCHITECTURE.md` and `README.md` use uppercase (intentional prominence)
- **RULE-042**: All other markdown: `^[a-z][a-z0-9-]*\.md$` (kebab-case, e.g., `build-system.md`)

---

## UI/UX Rules (Touch Screen Optimization)

### Sizing Constraints
- **RULE-050**: Button size MUST be >= 60px × 60px (NEVER < 60px in any dimension)
- **RULE-051**: Touch targets MUST be >= 60px × 60px (industrial safety requirement)
- **RULE-052**: Interactive elements spacing MUST be 12-20px (NEVER < 12px)

### Typography Constraints
- **RULE-060**: Primary text font size MUST be >= 16px (NEVER < 16px)
- **RULE-061**: Secondary text font size MUST be >= 14px (NEVER < 14px)
- **RULE-062**: Minimum readable font size: 12px (for non-critical info only)

### Visual Design Constraints
- **RULE-070**: Colors MUST use `ThemeManager::instance()` (NEVER hardcode hex values)
- **RULE-071**: NO decorative borders EVER (use backgrounds and spacing only)
- **RULE-072**: Border radius values: 8px (small), 12px (medium), 16px (large) ONLY
- **RULE-073**: Spacing multiples: 8px, 12px, 16px, 20px, 24px, 32px (8pt grid system)

---

## Architecture Rules (SOLID Principles)

### Separation of Concerns
- **RULE-100**: UI classes (QWidget) MUST NOT contain business logic
- **RULE-101**: Business logic MUST be in ViewModels (inherit QObject)
- **RULE-102**: Domain models MUST be pure C++ (NO Qt dependencies)
- **RULE-103**: Services handle external systems ONLY (Modbus, UDP, database)

### Dependency Rules
- **RULE-110**: Use signals/slots for communication (NEVER use callbacks)
- **RULE-111**: Every ViewModel MUST inherit from QObject (for signals/slots)
- **RULE-112**: UI classes depend on ViewModels (NEVER on Services directly)
- **RULE-113**: ViewModels depend on Service interfaces (NEVER concrete implementations)

### Memory Management
- **RULE-120**: Use smart pointers for ownership (NEVER raw `new`/`delete`)
- **RULE-121**: Qt objects with parent: raw pointers OK (Qt manages lifetime)
- **RULE-122**: Qt objects without parent: use `QSharedPointer` or `QScopedPointer`
- **RULE-123**: Non-Qt objects: use `std::unique_ptr` or `std::shared_ptr`

---

## Design Pattern Rules (Mandatory Patterns)

### Pattern Selection
- **RULE-200**: New UI component → MUST use **MVVM pattern** (View + ViewModel)
- **RULE-201**: New communication protocol → MUST use **Strategy pattern**
- **RULE-202**: Data persistence → MUST use **Repository pattern**
- **RULE-203**: Industrial operations (write/config) → MUST use **Command pattern**
- **RULE-204**: Connection lifecycle → MUST use **State Machine pattern**
- **RULE-205**: Event propagation → MUST use **Observer pattern** (Qt signals/slots)

### Qt-Specific Patterns
- **RULE-210**: Every QObject-derived class MUST have `Q_OBJECT` macro
- **RULE-211**: Constructors taking `QWidget*` parent MUST use `explicit` keyword
- **RULE-212**: Virtual destructors MUST use `override` keyword
- **RULE-213**: Signal declarations MUST NOT have implementations

---

## File Location Rules (Absolute Paths)

### Source Code Organization
- **RULE-300**: Domain models → `src/models/` (ALWAYS, pure C++)
- **RULE-301**: ViewModels → `src/viewmodels/` (ALWAYS, Qt-based business logic)
- **RULE-302**: Views (UI) → `src/views/` (ALWAYS, Qt Widgets)
  - Pages → `src/views/pages/`
  - Widgets → `src/views/widgets/`
  - Dialogs → `src/views/dialogs/`
- **RULE-303**: Services → `src/services/` (ALWAYS, external system integration)
- **RULE-304**: Repositories → `src/repositories/` (ALWAYS, data persistence)
- **RULE-305**: Interfaces → `src/interfaces/` (ALWAYS, abstract classes)
- **RULE-306**: Strategies → `src/strategies/` (ALWAYS, Strategy pattern implementations)
- **RULE-307**: Commands → `src/commands/` (ALWAYS, Command pattern implementations)
- **RULE-308**: State Machines → `src/statemachines/` (ALWAYS, State pattern implementations)
- **RULE-309**: Factories → `src/factories/` (ALWAYS, Factory pattern implementations)
- **RULE-310**: Utilities → `src/utils/` (ALWAYS, helper classes)

### Documentation Organization
- **RULE-320**: Architecture docs → `docs/ARCHITECTURE.md` (PRIMARY REFERENCE)
- **RULE-321**: Development guides → `docs/development/`
- **RULE-322**: Design specs → `docs/design/`
- **RULE-323**: API docs → `docs/api/`
- **RULE-324**: Deployment docs → `docs/deployment/`
- **RULE-325**: AI agent instructions → `.github/instructions/` (THIS DIRECTORY)

---

## Code Quality Rules

### C++ Standards
- **RULE-400**: Use C++17 standard (NEVER older, NEVER newer without approval)
- **RULE-401**: Use `auto` for complex types (e.g., iterators, lambdas)
- **RULE-402**: Use `nullptr` (NEVER use `NULL` or `0`)
- **RULE-403**: Use `override` keyword for virtual methods (MANDATORY)
- **RULE-404**: Use `const` correctness (methods, parameters, return types)

### Qt Standards
- **RULE-410**: Use Qt types for Qt APIs (`QString`, `QDateTime`, `QList`)
- **RULE-411**: Use STL types for non-Qt code (`std::string`, `std::vector`)
- **RULE-412**: Connect signals/slots in constructor or `setupUI()` method
- **RULE-413**: Disconnect signals in destructor if manual connection used

---

## Threading Rules

### Thread Safety
- **RULE-500**: UI updates MUST be on main thread ONLY (NEVER from worker threads)
- **RULE-501**: Use `QThread` for background work (NEVER `std::thread` with Qt objects)
- **RULE-502**: Use signals/slots for cross-thread communication (thread-safe)
- **RULE-503**: Modbus/UDP operations MUST run in separate thread (background)

---

## Error Handling Rules

### Error Propagation
- **RULE-600**: Use `Result<T>` type for operations that can fail
- **RULE-601**: Emit error signals for runtime failures (e.g., `errorOccurred(QString)`)
- **RULE-602**: Log all errors with structured logging (JSON format)
- **RULE-603**: NEVER use exceptions for control flow (C++ exceptions discouraged)

---

## Testing Rules

### Test Coverage
- **RULE-700**: Every ViewModel MUST have unit tests (70% of test suite)
- **RULE-701**: Every Service MUST have integration tests (20% of test suite)
- **RULE-702**: UI components need E2E tests (10% of test suite)
- **RULE-703**: Use Qt Test framework (NEVER third-party test frameworks)

---

## Build Rules

### Build System
- **RULE-800**: Use CMake 3.16+ (NEVER older versions)
- **RULE-801**: Qt5 5.15+ required (NEVER Qt4, Qt6 not yet supported)
- **RULE-802**: C++17 compiler required (GCC 7+, Clang 5+, MSVC 2019+)
- **RULE-803**: Build scripts in `scripts/` directory (ALWAYS)

---

## Anti-Patterns (FORBIDDEN)

### NEVER Do These
- **ANTI-001**: NEVER mix UI with business logic in same class
- **ANTI-002**: NEVER use callbacks (use signals/slots)
- **ANTI-003**: NEVER hardcode colors (use ThemeManager)
- **ANTI-004**: NEVER create buttons < 60px × 60px
- **ANTI-005**: NEVER add decorative borders (use backgrounds)
- **ANTI-006**: NEVER use raw pointers for ownership (use smart pointers)
- **ANTI-007**: NEVER introduce non-Qt GUI frameworks
- **ANTI-008**: NEVER use `std::thread` with Qt objects (use QThread)
- **ANTI-009**: NEVER update UI from worker threads (use signals)
- **ANTI-010**: NEVER skip reading ARCHITECTURE.md for major changes

---

## Validation Commands

### Pre-Commit Validation
```bash
# Check naming conventions
grep -r "class [a-z]" src/  # Should find NOTHING (PascalCase required)

# Check pragma once
find src/ -name "*.h" -exec grep -L "#pragma once" {} \;  # Should be EMPTY

# Check member prefix
grep -r "    Q.*\* [^m_]" src/  # Should find NOTHING (m_ prefix required)

# Check button sizes in UI files
grep -r "setMinimumSize.*[0-5][0-9]" src/views/  # Should find NOTHING (>= 60px)
```

---

## Rule Severity Levels

- **MUST**: Violation breaks the build or causes runtime errors
- **NEVER**: Violation introduces bugs or maintainability issues
- **ALWAYS**: Violation causes inconsistency across codebase

**All rules are MANDATORY. No exceptions without explicit approval.**

---

**Last Updated**: October 30, 2025  
**Version**: 1.0 (AI-First Documentation)  
**Purpose**: Machine-readable constraints for AI agent code generation
