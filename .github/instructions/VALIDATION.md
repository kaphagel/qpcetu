# VALIDATION CHECKLIST

**Purpose**: Pre-commit validation for AI agents. Verify every requirement before committing.  
**Last Updated**: October 30, 2025

---

## Checklist Index

1. [Before Creating Any File](#before-creating-any-file)
2. [After Creating .h Header File](#after-creating-h-header-file)
3. [After Creating .cpp Implementation File](#after-creating-cpp-implementation-file)
4. [After Creating UI Component](#after-creating-ui-component)
5. [After Creating ViewModel](#after-creating-viewmodel)
6. [After Creating Service](#after-creating-service)
7. [After Creating Repository](#after-creating-repository)
8. [Before Committing Changes](#before-committing-changes)

---

## Before Creating Any File

**Run this checklist BEFORE writing any code:**

- [ ] **Read DECISIONS.md** to determine component type
- [ ] **Checked RULES.md** for file location (RULE-300 to RULE-310)
- [ ] **Confirmed naming convention** (RULE-010 to RULE-042)
  - [ ] Class name is PascalCase (e.g., `GraphViewModel`)
  - [ ] File name is kebab-case (e.g., `graph-viewmodel.h`)
  - [ ] Matches regex: `^[a-z][a-z0-9-]*\.(h|cpp)$`
- [ ] **Selected appropriate template** from TEMPLATES.md
- [ ] **Verified pattern choice** in DECISIONS.md
- [ ] **Identified dependencies** (interfaces, not concrete classes)

---

## After Creating .h Header File

**Run this checklist after writing header file:**

### File Structure
- [ ] Has `#pragma once` at top (NOT include guards - RULE-002)
- [ ] Includes are in correct order:
  1. Corresponding .cpp include (if exists)
  2. Qt headers
  3. STL headers
  4. Project headers
- [ ] Forward declarations used where possible (reduce dependencies)

### Class Declaration
- [ ] Class name is PascalCase (RULE-010)
- [ ] Interface classes have `I` prefix (RULE-011)
- [ ] Qt classes have `Q_OBJECT` macro (if inherits QObject)
- [ ] Constructor is `explicit` (RULE-211)
- [ ] Destructor is virtual if base class
- [ ] Destructor has `override` keyword if derived (RULE-212)

### Member Variables
- [ ] All members have `m_` prefix (RULE-030)
- [ ] Members are camelCase after prefix (e.g., `m_updateTimer`)
- [ ] Members are in `private:` section (not public)
- [ ] Qt objects with parent use raw pointers
- [ ] Qt objects without parent use smart pointers (RULE-122)

### Methods
- [ ] Method names are camelCase (RULE-020)
- [ ] Qt slots have `on` prefix (RULE-021)
- [ ] Virtual methods have `override` keyword (RULE-403)
- [ ] Const methods are marked `const` (RULE-404)
- [ ] Parameters use const references where appropriate

### Signals (Qt only)
- [ ] Signals are in `signals:` section
- [ ] Signals have NO implementations (RULE-213)
- [ ] Signal names describe events (e.g., `dataUpdated()`)

### Documentation
- [ ] Public API methods have Doxygen comments
- [ ] Comments explain WHY, not WHAT
- [ ] Complex logic has explanatory comments

---

## After Creating .cpp Implementation File

**Run this checklist after writing implementation file:**

### File Structure
- [ ] Includes corresponding .h file FIRST (RULE-004)
- [ ] Includes only necessary headers
- [ ] No business logic in UI classes (RULE-100)

### Constructor
- [ ] Initializer list used for all members
- [ ] Qt objects with parent created correctly
- [ ] Parent-child relationship established for Qt objects
- [ ] Signals connected in constructor or `setupUI()`

### Destructor
- [ ] Manual cleanup only if needed (Qt parent-child handles most)
- [ ] Signals disconnected if manually connected outside class
- [ ] Resources released properly (files, network, etc.)

### Memory Management
- [ ] Uses smart pointers for ownership (RULE-120)
- [ ] Uses `nullptr` not `NULL` or `0` (RULE-402)
- [ ] No raw `new`/`delete` for owned objects (RULE-034)
- [ ] Qt objects with parent use raw pointers (Qt manages)

### Qt Patterns
- [ ] Uses signals/slots not callbacks (RULE-110)
- [ ] Signals connected with new syntax (`&Class::method`)
- [ ] Cross-thread communication uses signals (RULE-502)
- [ ] UI updates only on main thread (RULE-500)

### Error Handling
- [ ] Operations that can fail return `Result<T>` (RULE-600)
- [ ] Errors emit error signals (RULE-601)
- [ ] All errors logged (RULE-602)
- [ ] No exceptions for control flow (RULE-603)

---

## After Creating UI Component

**Additional checks for UI components (QWidget, QDialog, etc.):**

### Touch Screen Compliance
- [ ] **Button sizes >= 60x60px** (RULE-050)
  - [ ] Verified with: `button->setMinimumSize(60, 60);`
  - [ ] NEVER smaller than 60px in any dimension
- [ ] **Touch targets >= 60x60px** (RULE-051)
  - [ ] All interactive elements meet minimum
- [ ] **Spacing 12-20px between elements** (RULE-052)
  - [ ] Layout spacing: `layout->setSpacing(16);`
  - [ ] Margins: `layout->setContentsMargins(16, 16, 16, 16);`

### Typography
- [ ] **Primary text >= 16px** (RULE-060)
- [ ] **Secondary text >= 14px** (RULE-061)
- [ ] Font sizes verified: `font.setPointSize(16);`

### Visual Design
- [ ] **Colors use ThemeManager** (RULE-070)
  - [ ] NO hardcoded hex colors (e.g., `#FF0000`)
  - [ ] Use: `ThemeManager::instance()->primaryColor()`
- [ ] **NO decorative borders** (RULE-071)
  - [ ] Checked stylesheet for `border:` properties
  - [ ] Use backgrounds and spacing instead
- [ ] **Border radius values**: 8px, 12px, or 16px ONLY (RULE-072)
- [ ] **Spacing multiples of 8pt grid** (RULE-073)

### MVVM Pattern
- [ ] View depends on ViewModel (RULE-200)
- [ ] View does NOT contain business logic (RULE-100)
- [ ] ViewModel handles all data operations
- [ ] Signals/slots wire View ↔ ViewModel

### Theme Support
- [ ] Component respects current theme
- [ ] Connected to `ThemeManager::themeChanged` signal
- [ ] `applyTheme()` method updates all colors

---

## After Creating ViewModel

**Additional checks for ViewModel classes:**

### Qt Requirements
- [ ] Inherits from `QObject` (RULE-111)
- [ ] Has `Q_OBJECT` macro
- [ ] Signals declared for View updates
- [ ] Slots declared for View actions

### Business Logic
- [ ] Contains NO UI code (RULE-100)
- [ ] Depends on Service interfaces, not concrete (RULE-113)
- [ ] Handles data transformation
- [ ] Emits signals for View updates

### Dependencies
- [ ] Injected via constructor (dependency injection)
- [ ] Uses interfaces, not concrete classes (RULE-113)
- [ ] Example: `IDataSource*` not `ModbusService*`

### Testing
- [ ] Unit tests created (RULE-700)
- [ ] Tests business logic without UI
- [ ] Mock services used in tests

---

## After Creating Service

**Additional checks for Service classes (external system integration):**

### Threading
- [ ] Long operations run in worker thread (RULE-501)
- [ ] Signals used for cross-thread communication (RULE-502)
- [ ] UI updates via signals to main thread (RULE-500)

### Service Pattern
- [ ] Implements service interface
- [ ] Has `start()` and `stop()` methods
- [ ] Emits `started()`, `stopped()` signals
- [ ] Emits `dataReceived()` signal
- [ ] Emits `errorOccurred()` signal

### Error Handling
- [ ] Network errors handled gracefully
- [ ] Auto-reconnection implemented (if applicable)
- [ ] All errors logged (RULE-602)
- [ ] Error signals emitted (RULE-601)

### Resource Cleanup
- [ ] Connections closed in destructor
- [ ] Worker threads stopped properly
- [ ] Resources released (files, sockets, etc.)

---

## After Creating Repository

**Additional checks for Repository classes (data persistence):**

### Repository Pattern
- [ ] Implements `IRepository<T>` interface (RULE-202)
- [ ] Has `save()`, `findById()`, `findAll()`, `deleteById()`
- [ ] Abstracts storage mechanism
- [ ] Can be swapped with different implementation

### Data Storage
- [ ] Uses appropriate storage mechanism:
  - [ ] Circular buffer for real-time data
  - [ ] SQLite for historical data
  - [ ] QSettings for configuration
  - [ ] In-memory for temporary cache

### Error Handling
- [ ] Database errors handled
- [ ] File I/O errors handled
- [ ] Returns `Result<T>` for operations that can fail (RULE-600)

---

## Before Committing Changes

**Final checklist before committing to version control:**

### Code Quality
- [ ] All compiler warnings resolved
- [ ] No commented-out code
- [ ] No debug print statements (`qDebug()`, `std::cout`)
- [ ] No TODO comments (create tickets instead)

### Testing
- [ ] Unit tests pass (RULE-700)
- [ ] Integration tests pass (RULE-701)
- [ ] Manual testing completed
- [ ] No regressions introduced

### Documentation
- [ ] Public APIs documented (Doxygen comments)
- [ ] ARCHITECTURE.md updated (if architectural change)
- [ ] README.md updated (if feature change)

### Build
- [ ] Linux build succeeds: `./scripts/build-linux.sh`
- [ ] Windows build succeeds: `./scripts/build-windows.sh`
- [ ] No new build warnings

### RULES.md Compliance
- [ ] All MUST rules followed (RULE-xxx)
- [ ] No NEVER rules violated (ANTI-xxx)
- [ ] File locations correct (RULE-300 to RULE-310)
- [ ] Naming conventions correct (RULE-010 to RULE-042)
- [ ] UI constraints met (RULE-050 to RULE-073)
- [ ] Architecture patterns used (RULE-200 to RULE-205)

### Code Review (Self)
- [ ] Read own code as if reviewing someone else's
- [ ] Check for potential bugs
- [ ] Check for edge cases
- [ ] Check for memory leaks
- [ ] Check for thread safety issues

---

## Automated Validation Commands

**Run these commands to verify compliance:**

### Check Naming Conventions
```bash
# Find classes with lowercase names (should be PascalCase)
grep -r "^class [a-z]" src/ && echo "ERROR: Found lowercase class names" || echo "✓ Class names OK"

# Find member variables without m_ prefix
grep -r "    Q.*\* [^m_]" src/ && echo "ERROR: Found members without m_ prefix" || echo "✓ Member names OK"

# Find files not using kebab-case
find src/ -name "*.h" -o -name "*.cpp" | grep -v "^[a-z][a-z0-9-]*\.(h|cpp)$" && echo "ERROR: Found non-kebab-case files" || echo "✓ File names OK"
```

### Check Header Guards
```bash
# Find headers not using #pragma once
find src/ -name "*.h" -exec grep -L "#pragma once" {} \; && echo "ERROR: Found headers without #pragma once" || echo "✓ Pragma once OK"
```

### Check UI Constraints
```bash
# Find buttons smaller than 60px
grep -r "setMinimumSize.*[0-5][0-9]" src/views/ && echo "ERROR: Found buttons < 60px" || echo "✓ Button sizes OK"

# Find hardcoded colors
grep -r "#[0-9A-Fa-f]\{6\}" src/ --include="*.cpp" && echo "WARNING: Found hardcoded colors" || echo "✓ Colors OK"

# Find decorative borders
grep -r "border:.*[1-9]px" src/ --include="*.cpp" && echo "WARNING: Found decorative borders" || echo "✓ No decorative borders"
```

### Check Memory Management
```bash
# Find raw new/delete
grep -r "\bnew [A-Z]" src/ --include="*.cpp" | grep -v "QTimer\|QLabel\|QPushButton" && echo "WARNING: Found raw new" || echo "✓ Memory management OK"
```

---

## Quick Validation Summary

**For AI agents: Run these 3 checks on every file:**

1. **RULES.md Compliance**
   - File location correct? (RULE-300+)
   - Naming conventions correct? (RULE-010+)
   - Pattern used correctly? (RULE-200+)

2. **TEMPLATES.md Usage**
   - Used appropriate template?
   - All required methods present?
   - Follows template structure?

3. **DECISIONS.md Path**
   - Followed decision tree?
   - Made correct choices?
   - Applied correct pattern?

**If all 3 checks pass → Safe to commit**

---

**Last Updated**: October 30, 2025  
**Version**: 1.0 (AI-First Documentation)  
**Purpose**: Pre-commit validation checklist for AI agent code generation
