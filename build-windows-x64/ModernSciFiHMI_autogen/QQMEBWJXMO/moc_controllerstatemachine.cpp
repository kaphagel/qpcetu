/****************************************************************************
** Meta object code from reading C++ file 'controllerstatemachine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/statemachine/controllerstatemachine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controllerstatemachine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControllerStateMachine_t {
    QByteArrayData data[27];
    char stringdata0[372];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControllerStateMachine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControllerStateMachine_t qt_meta_stringdata_ControllerStateMachine = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ControllerStateMachine"
QT_MOC_LITERAL(1, 23, 12), // "stateChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 15), // "ControllerState"
QT_MOC_LITERAL(4, 53, 8), // "newState"
QT_MOC_LITERAL(5, 62, 21), // "connectionEstablished"
QT_MOC_LITERAL(6, 84, 16), // "operationStarted"
QT_MOC_LITERAL(7, 101, 16), // "operationStopped"
QT_MOC_LITERAL(8, 118, 13), // "faultDetected"
QT_MOC_LITERAL(9, 132, 5), // "error"
QT_MOC_LITERAL(10, 138, 19), // "maintenanceRequired"
QT_MOC_LITERAL(11, 158, 19), // "connectToController"
QT_MOC_LITERAL(12, 178, 14), // "startOperation"
QT_MOC_LITERAL(13, 193, 13), // "stopOperation"
QT_MOC_LITERAL(14, 207, 16), // "enterMaintenance"
QT_MOC_LITERAL(15, 224, 10), // "clearFault"
QT_MOC_LITERAL(16, 235, 23), // "handleCommunicationLoss"
QT_MOC_LITERAL(17, 259, 14), // "onStateEntered"
QT_MOC_LITERAL(18, 274, 13), // "onStateExited"
QT_MOC_LITERAL(19, 288, 14), // "checkHeartbeat"
QT_MOC_LITERAL(20, 303, 12), // "Disconnected"
QT_MOC_LITERAL(21, 316, 10), // "Connecting"
QT_MOC_LITERAL(22, 327, 9), // "Connected"
QT_MOC_LITERAL(23, 337, 7), // "Running"
QT_MOC_LITERAL(24, 345, 5), // "Fault"
QT_MOC_LITERAL(25, 351, 11), // "Maintenance"
QT_MOC_LITERAL(26, 363, 8) // "Stopping"

    },
    "ControllerStateMachine\0stateChanged\0"
    "\0ControllerState\0newState\0"
    "connectionEstablished\0operationStarted\0"
    "operationStopped\0faultDetected\0error\0"
    "maintenanceRequired\0connectToController\0"
    "startOperation\0stopOperation\0"
    "enterMaintenance\0clearFault\0"
    "handleCommunicationLoss\0onStateEntered\0"
    "onStateExited\0checkHeartbeat\0Disconnected\0"
    "Connecting\0Connected\0Running\0Fault\0"
    "Maintenance\0Stopping"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControllerStateMachine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       1,  108, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   89,    2, 0x06 /* Public */,
       5,    0,   92,    2, 0x06 /* Public */,
       6,    0,   93,    2, 0x06 /* Public */,
       7,    0,   94,    2, 0x06 /* Public */,
       8,    1,   95,    2, 0x06 /* Public */,
      10,    0,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    0,   99,    2, 0x0a /* Public */,
      12,    0,  100,    2, 0x0a /* Public */,
      13,    0,  101,    2, 0x0a /* Public */,
      14,    0,  102,    2, 0x0a /* Public */,
      15,    0,  103,    2, 0x0a /* Public */,
      16,    0,  104,    2, 0x0a /* Public */,
      17,    0,  105,    2, 0x08 /* Private */,
      18,    0,  106,    2, 0x08 /* Private */,
      19,    0,  107,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    7,  113,

 // enum data: key, value
      20, uint(ControllerStateMachine::Disconnected),
      21, uint(ControllerStateMachine::Connecting),
      22, uint(ControllerStateMachine::Connected),
      23, uint(ControllerStateMachine::Running),
      24, uint(ControllerStateMachine::Fault),
      25, uint(ControllerStateMachine::Maintenance),
      26, uint(ControllerStateMachine::Stopping),

       0        // eod
};

void ControllerStateMachine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControllerStateMachine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< ControllerState(*)>(_a[1]))); break;
        case 1: _t->connectionEstablished(); break;
        case 2: _t->operationStarted(); break;
        case 3: _t->operationStopped(); break;
        case 4: _t->faultDetected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->maintenanceRequired(); break;
        case 6: _t->connectToController(); break;
        case 7: _t->startOperation(); break;
        case 8: _t->stopOperation(); break;
        case 9: _t->enterMaintenance(); break;
        case 10: _t->clearFault(); break;
        case 11: _t->handleCommunicationLoss(); break;
        case 12: _t->onStateEntered(); break;
        case 13: _t->onStateExited(); break;
        case 14: _t->checkHeartbeat(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControllerStateMachine::*)(ControllerState );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControllerStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::connectionEstablished)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControllerStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::operationStarted)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControllerStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::operationStopped)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ControllerStateMachine::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::faultDetected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ControllerStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStateMachine::maintenanceRequired)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControllerStateMachine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ControllerStateMachine.data,
    qt_meta_data_ControllerStateMachine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControllerStateMachine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControllerStateMachine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControllerStateMachine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ControllerStateMachine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void ControllerStateMachine::stateChanged(ControllerState _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControllerStateMachine::connectionEstablished()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ControllerStateMachine::operationStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ControllerStateMachine::operationStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ControllerStateMachine::faultDetected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ControllerStateMachine::maintenanceRequired()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
