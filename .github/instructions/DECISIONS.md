# DECISION TREES

**Purpose**: Deterministic decision-making for AI agents. Follow flowcharts exactly.  
**Last Updated**: October 30, 2025

---

## Decision Tree Index

1. [Creating New Component](#decision-creating-new-component)
2. [Choosing Design Pattern](#decision-choosing-design-pattern)
3. [Selecting File Location](#decision-selecting-file-location)
4. [Error Handling Strategy](#decision-error-handling-strategy)
5. [Threading Strategy](#decision-threading-strategy)
6. [Data Storage Strategy](#decision-data-storage-strategy)

---

## Decision: Creating New Component

```
START: Need to create new component
  ↓
┌─────────────────────────────────────────┐
│ Is it a UI component (visual)?         │
└─────────────────┬───────────────────────┘
                  │
        ┌─────────┴─────────┐
        YES                 NO
        │                   │
        ↓                   ↓
┌───────────────────┐  ┌────────────────────────┐
│ Is it a full page?│  │ Is it business logic?  │
└────┬──────────┬───┘  └──────┬─────────────────┘
     │          │              │
    YES        NO         ┌────┴────┐
     │          │        YES        NO
     ↓          ↓         │          │
  CREATE      CREATE      ↓          ↓
  in:         in:    ┌─────────────────────┐  ┌───────────────────┐
  src/views/  src/   │Is it page-specific? │  │Is it data storage?│
  pages/      views/ └──┬──────────────┬───┘  └───┬───────────────┘
              widgets/  │              │          │
                       YES            NO      ┌───┴───┐
  Pattern:              │              │     YES      NO
  MVVM                  ↓              ↓      │        │
  (View +          CREATE in:     CREATE in:  ↓        ↓
  ViewModel)       src/viewmodels/ src/      CREATE  ┌──────────────────┐
                                   services/  in:    │Is it data model? │
  File name:                                  src/   └───┬──────────────┘
  [name]page.h                    Pattern:    repos/     │
  [name]page.cpp                  Service              ┌─┴──┐
                                  Layer               YES   NO
  Template:                                            │     │
  TEMPLATES.md                    File name:           ↓     ↓
  "Qt Widget Page"                [name]service.h   CREATE  Review
                                  [name]service.cpp  in:    ARCHITECTURE.md
  Widget size:                                       src/   or ask human
  >= 60x60px                      Template:          models/
  (RULE-050)                      TEMPLATES.md
                                  "Service"          Pattern:
                                                     Domain Model
                                                     (pure C++)

                                                     File name:
                                                     [name].h
                                                     [name].cpp

                                                     Template:
                                                     TEMPLATES.md
                                                     "Domain Model"
```

### Quick Reference Table

| What are you creating? | File Location | Pattern | Template |
|------------------------|---------------|---------|----------|
| Full-page UI | `src/views/pages/` | MVVM | Qt Widget Page |
| Reusable widget | `src/views/widgets/` | Component | Qt Widget Component |
| Page business logic | `src/viewmodels/` | MVVM | ViewModel |
| External system integration | `src/services/` | Service | Service |
| Data persistence | `src/repositories/` | Repository | Repository |
| Data structure | `src/models/` | Domain Model | Domain Model |
| Communication protocol | `src/strategies/` | Strategy | Strategy |
| Industrial operation | `src/commands/` | Command | Command |
| Abstraction/contract | `src/interfaces/` | Interface | Interface |

---

## Decision: Choosing Design Pattern

```
START: Need to choose design pattern
  ↓
┌──────────────────────────────────────────────────┐
│ What problem are you solving?                   │
└───────────────────┬──────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        │                       │
        ↓                       ↓
┌─────────────────┐      ┌──────────────────────┐
│Need to add new  │      │Need to separate UI   │
│controller type? │      │from business logic?  │
└────┬────────────┘      └──────┬───────────────┘
     │                          │
    YES                        YES
     │                          │
     ↓                          ↓
  USE STRATEGY PATTERN       USE MVVM PATTERN
  - Create in:               - View: src/views/
    src/strategies/          - ViewModel: src/viewmodels/
  - Implements:              - Model: src/models/
    ICommunicationStrategy   
  - Example:                 - View depends on ViewModel
    ModbusTcpStrategy        - ViewModel depends on Services
    UdpStrategy              - Model is pure C++
  - File:                    
    [controller]strategy.h   - Template:
    [controller]strategy.cpp   TEMPLATES.md
                               "Qt Widget Page"
  - Template:                  "ViewModel"
    TEMPLATES.md               "Domain Model"
    "Strategy"
  
  (RULE-201)                 (RULE-200)

        ↓                          ↓
┌─────────────────┐      ┌──────────────────────┐
│Need undo/redo   │      │Need to persist data? │
│for operations?  │      └──────┬───────────────┘
└────┬────────────┘             │
     │                          YES
    YES                          │
     │                           ↓
     ↓                     USE REPOSITORY PATTERN
  USE COMMAND PATTERN      - Create in:
  - Create in:               src/repositories/
    src/commands/          - Implements:
  - Implements:              IRepository<T>
    ICommand               - Examples:
  - Provides:                SqliteRepository
    - execute()              CircularBufferRepository
    - undo()               - File:
    - description()          [data]repository.h
    - timestamp()            [data]repository.cpp
  - File:                  
    [operation]command.h   - Template:
    [operation]command.cpp   TEMPLATES.md
                             "Repository"
  - Template:              
    TEMPLATES.md           (RULE-202)
    "Command"
  
  (RULE-203)

        ↓                          ↓
┌─────────────────────────┐ ┌─────────────────────────┐
│Need to manage           │ │Need to propagate events │
│connection lifecycle?    │ │in real-time?            │
└────┬────────────────────┘ └──────┬──────────────────┘
     │                             │
    YES                           YES
     │                             │
     ↓                             ↓
  USE STATE MACHINE PATTERN   USE OBSERVER PATTERN
  - Create in:                - Use Qt signals/slots
    src/statemachines/        - Sender emits signals
  - States:                   - Receiver connects slots
    Disconnected              - Thread-safe
    Connecting                - Automatic disconnect
    Connected                 - Example:
    Running                     Service → ViewModel → View
    Fault                     
    Reconnecting              - Pattern:
  - File:                       connect(sender, &Sender::signal,
    [entity]statemachine.h            receiver, &Receiver::slot);
    [entity]statemachine.cpp  
                              (RULE-205)
  - Use Qt State Machine
    Framework
  
  (RULE-204)
```

### Pattern Selection Checklist

**Before implementing, answer these questions:**

- [ ] Does it involve UI? → **MVVM Pattern** (RULE-200)
- [ ] Does it involve different protocols? → **Strategy Pattern** (RULE-201)
- [ ] Does it need undo/redo? → **Command Pattern** (RULE-203)
- [ ] Does it manage connections? → **State Machine Pattern** (RULE-204)
- [ ] Does it propagate events? → **Observer Pattern (signals/slots)** (RULE-205)
- [ ] Does it persist data? → **Repository Pattern** (RULE-202)
- [ ] Does it create objects? → **Factory Pattern**
- [ ] Is it a global service? → **Singleton Pattern** (use sparingly)

---

## Decision: Selecting File Location

```
START: Need to determine file location
  ↓
┌──────────────────────────────────────────────────┐
│ What type of file are you creating?             │
└───────────────────┬──────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        │                       │
        ↓                       ↓
  ┌─────────┐            ┌──────────────┐
  │Source   │            │Documentation │
  │Code     │            │              │
  └────┬────┘            └──────┬───────┘
       │                        │
       ↓                        ↓
┌──────────────┐         ┌──────────────┐
│What layer?   │         │What type?    │
└──┬───────────┘         └──┬───────────┘
   │                        │
   ├─ Domain Model    →  src/models/           (RULE-300)
   ├─ ViewModel       →  src/viewmodels/       (RULE-301)
   ├─ View (UI)       →  src/views/            (RULE-302)
   │   ├─ Page        →  src/views/pages/
   │   ├─ Widget      →  src/views/widgets/
   │   └─ Dialog      →  src/views/dialogs/
   ├─ Service         →  src/services/         (RULE-303)
   ├─ Repository      →  src/repositories/     (RULE-304)
   ├─ Interface       →  src/interfaces/       (RULE-305)
   ├─ Strategy        →  src/strategies/       (RULE-306)
   ├─ Command         →  src/commands/         (RULE-307)
   ├─ State Machine   →  src/statemachines/    (RULE-308)
   ├─ Factory         →  src/factories/        (RULE-309)
   └─ Utility         →  src/utils/            (RULE-310)
                              │
                              ├─ Architecture    →  docs/ARCHITECTURE.md      (RULE-320)
                              ├─ Development     →  docs/development/         (RULE-321)
                              ├─ Design          →  docs/design/              (RULE-322)
                              ├─ API             →  docs/api/                 (RULE-323)
                              ├─ Deployment      →  docs/deployment/          (RULE-324)
                              └─ AI Instructions →  .github/instructions/     (RULE-325)
```

### File Location Quick Reference

| Component Type | Location | Rule |
|----------------|----------|------|
| Domain Model | `src/models/` | RULE-300 |
| ViewModel | `src/viewmodels/` | RULE-301 |
| View (UI) | `src/views/` | RULE-302 |
| Service | `src/services/` | RULE-303 |
| Repository | `src/repositories/` | RULE-304 |
| Interface | `src/interfaces/` | RULE-305 |
| Strategy | `src/strategies/` | RULE-306 |
| Command | `src/commands/` | RULE-307 |
| State Machine | `src/statemachines/` | RULE-308 |
| Factory | `src/factories/` | RULE-309 |
| Utility | `src/utils/` | RULE-310 |

---

## Decision: Error Handling Strategy

```
START: Operation can fail
  ↓
┌──────────────────────────────────────────────────┐
│ What type of error can occur?                   │
└───────────────────┬──────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        │                       │
        ↓                       ↓
┌─────────────────┐      ┌──────────────────────┐
│Synchronous      │      │Asynchronous          │
│operation        │      │operation             │
│(returns result) │      │(emits signal)        │
└────┬────────────┘      └──────┬───────────────┘
     │                          │
    YES                        YES
     │                          │
     ↓                          ↓
  USE Result<T>              EMIT ERROR SIGNAL
  - Return type:             - Signal:
    Result<T>                  void errorOccurred(QString msg)
  - Success:                 - Example:
    return Result<T>::       if (error) {
      success(value);           emit errorOccurred("Failed to...");
  - Failure:                   return;
    return Result<T>::       }
      failure("error msg");  
  - Caller checks:           - Caller connects:
    if (result.isSuccess())    connect(service, &Service::errorOccurred,
      auto val = result.value();     this, &Widget::onError);
    else                     
      auto err = result.error();
  
  - Example:                 - Log error:
    Result<int> readValue();   LogManager::error(msg);
  
  (RULE-600)                 (RULE-601)

        ↓                          ↓
┌─────────────────────────────────────────────────┐
│ ALWAYS log errors with structured logging      │
│ LogManager::error(msg, {{"tag", tag}})         │
│ (RULE-602)                                      │
└─────────────────────────────────────────────────┘

        ↓
┌─────────────────────────────────────────────────┐
│ NEVER use exceptions for control flow          │
│ (RULE-603)                                      │
└─────────────────────────────────────────────────┘
```

---

## Decision: Threading Strategy

```
START: Need to perform work
  ↓
┌──────────────────────────────────────────────────┐
│ Does it involve UI updates?                     │
└───────────────────┬──────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        YES                     NO
        │                       │
        ↓                       ↓
  ┌────────────────┐      ┌───────────────────┐
  │ MAIN THREAD    │      │Is it long-running │
  │ ONLY           │      │or blocking?       │
  │                │      └────┬──────────────┘
  │ - QWidget      │           │
  │   updates      │      ┌────┴────┐
  │ - QPainter     │     YES       NO
  │   drawing      │      │         │
  │ - Layout       │      ↓         ↓
  │   changes      │  USE        MAIN
  │                │  WORKER     THREAD
  │ (RULE-500)     │  THREAD     OK
  └────────────────┘      │
                          ↓
                    ┌─────────────────────┐
                    │ What type of work?  │
                    └──────┬──────────────┘
                           │
                  ┌────────┴────────┐
                  │                 │
                  ↓                 ↓
            ┌──────────┐      ┌────────────┐
            │Network   │      │Heavy       │
            │I/O       │      │computation │
            └────┬─────┘      └────┬───────┘
                 │                 │
                 ↓                 ↓
          USE QThread         USE QtConcurrent
          - Create QThread    - For parallel tasks
          - Move worker       - Auto thread pool
            to thread         - Example:
          - Connect signals     QtConcurrent::run(fn)
          - Start thread      
          - Worker emits      (RULE-501)
            signals to UI
          
          Example:
          QThread* thread = new QThread;
          Worker* worker = new Worker;
          worker->moveToThread(thread);
          connect(thread, &QThread::started,
                  worker, &Worker::doWork);
          connect(worker, &Worker::resultReady,
                  this, &UI::onResult);
          thread->start();
          
          (RULE-501)

        ↓
┌─────────────────────────────────────────────────┐
│ Use signals/slots for cross-thread communication│
│ (thread-safe, automatic)                        │
│ (RULE-502)                                      │
└─────────────────────────────────────────────────┘
```

### Threading Quick Rules

- **UI updates** → Main thread ONLY (RULE-500)
- **Background work** → QThread (RULE-501)
- **Cross-thread** → Signals/slots (RULE-502)
- **Modbus/UDP** → Separate thread (RULE-503)
- **NEVER** → std::thread with Qt objects (RULE-501)

---

## Decision: Data Storage Strategy

```
START: Need to store data
  ↓
┌──────────────────────────────────────────────────┐
│ How long should data persist?                   │
└───────────────────┬──────────────────────────────┘
                    │
        ┌───────────┴───────────┐
        │                       │
        ↓                       ↓
┌─────────────────┐      ┌──────────────────────┐
│Only during      │      │Persist across        │
│application run  │      │application restarts  │
└────┬────────────┘      └──────┬───────────────┘
     │                          │
    YES                        YES
     │                          │
     ↓                          ↓
  ┌────────────────┐      ┌───────────────────┐
  │Is it real-time │      │What type of data? │
  │data?           │      └────┬──────────────┘
  └────┬───────────┘           │
       │                  ┌────┴────┐
  ┌────┴────┐            │         │
 YES       NO            ↓         ↓
  │         │      ┌──────────┐ ┌─────────┐
  ↓         ↓      │Config/   │ │Time-    │
USE         USE    │Settings  │ │series   │
CIRCULAR    IN-    └────┬─────┘ └────┬────┘
BUFFER      MEMORY      │            │
            DATA        ↓            ↓
- Fixed     STRUCTURE   USE          USE
  size                  QSettings    SQLite
- Fast      - QVector   - JSON       - Database
  access    - QList     - Platform   - Indexed
- Auto      - QMap        native     - Query
  overwrite - Example:  - Example:     support
- Example:    QList<    QSettings    - Example:
  Circular    Data      settings;      QSql
  DataBuffer  Point>    settings.      Database
  <DataPoint> data;     setValue();  
                        settings.
- Template:             value();     - Template:
  TEMPLATES.md                         TEMPLATES.md
  "Repository"        (RULE-202)       "Repository"
  (Circular                          
  Buffer impl)
  
(RULE-202)
```

### Data Storage Quick Reference

| Data Type | Duration | Storage | Pattern |
|-----------|----------|---------|---------|
| Real-time metrics | Runtime only | Circular Buffer | Repository |
| Configuration | Persistent | QSettings (JSON) | Repository |
| Historical data | Persistent | SQLite | Repository |
| Temporary cache | Runtime only | In-memory (QMap) | Repository |
| Application state | Session | In-memory | State Machine |

---

## Usage Instructions for AI Agents

### How to Use Decision Trees

1. **Start at the top** of the appropriate decision tree
2. **Follow arrows** based on YES/NO answers
3. **Apply the outcome** (pattern, location, template)
4. **Verify with RULES.md** (check rule numbers cited)
5. **Use TEMPLATES.md** (copy appropriate template)
6. **Run VALIDATION.md** (complete checklist)

### Decision Tree Priority

1. **Creating New Component** (most common - start here)
2. **Choosing Design Pattern** (architectural decisions)
3. **Selecting File Location** (before creating any file)
4. **Error Handling** (for any operation that can fail)
5. **Threading** (for any background work)
6. **Data Storage** (for any data persistence)

---

**Last Updated**: October 30, 2025  
**Version**: 1.0 (AI-First Documentation)  
**Purpose**: Deterministic decision-making for AI agent code generation
