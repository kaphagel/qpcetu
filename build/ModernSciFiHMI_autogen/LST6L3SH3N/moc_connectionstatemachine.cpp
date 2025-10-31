/****************************************************************************
** Meta object code from reading C++ file 'connectionstatemachine.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/statemachines/connectionstatemachine.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'connectionstatemachine.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConnectionStateMachine_t {
    QByteArrayData data[35];
    char stringdata0[459];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConnectionStateMachine_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConnectionStateMachine_t qt_meta_stringdata_ConnectionStateMachine = {
    {
QT_MOC_LITERAL(0, 0, 22), // "ConnectionStateMachine"
QT_MOC_LITERAL(1, 23, 12), // "stateChanged"
QT_MOC_LITERAL(2, 36, 0), // ""
QT_MOC_LITERAL(3, 37, 29), // "ConnectionStateMachine::State"
QT_MOC_LITERAL(4, 67, 8), // "oldState"
QT_MOC_LITERAL(5, 76, 8), // "newState"
QT_MOC_LITERAL(6, 85, 17), // "connectingStarted"
QT_MOC_LITERAL(7, 103, 7), // "address"
QT_MOC_LITERAL(8, 111, 4), // "port"
QT_MOC_LITERAL(9, 116, 9), // "connected"
QT_MOC_LITERAL(10, 126, 7), // "running"
QT_MOC_LITERAL(11, 134, 13), // "faultOccurred"
QT_MOC_LITERAL(12, 148, 6), // "reason"
QT_MOC_LITERAL(13, 155, 12), // "reconnecting"
QT_MOC_LITERAL(14, 168, 13), // "attemptNumber"
QT_MOC_LITERAL(15, 182, 12), // "disconnected"
QT_MOC_LITERAL(16, 195, 18), // "reconnectionFailed"
QT_MOC_LITERAL(17, 214, 13), // "connectToHost"
QT_MOC_LITERAL(18, 228, 10), // "disconnect"
QT_MOC_LITERAL(19, 239, 19), // "onConnectionSuccess"
QT_MOC_LITERAL(20, 259, 19), // "onConnectionFailure"
QT_MOC_LITERAL(21, 279, 14), // "onDataReceived"
QT_MOC_LITERAL(22, 294, 14), // "onNetworkError"
QT_MOC_LITERAL(23, 309, 5), // "error"
QT_MOC_LITERAL(24, 315, 17), // "resetAndReconnect"
QT_MOC_LITERAL(25, 333, 16), // "onConnectTimeout"
QT_MOC_LITERAL(26, 350, 17), // "onActivityTimeout"
QT_MOC_LITERAL(27, 368, 23), // "onReconnectDelayTimeout"
QT_MOC_LITERAL(28, 392, 5), // "State"
QT_MOC_LITERAL(29, 398, 12), // "Disconnected"
QT_MOC_LITERAL(30, 411, 10), // "Connecting"
QT_MOC_LITERAL(31, 422, 9), // "Connected"
QT_MOC_LITERAL(32, 432, 7), // "Running"
QT_MOC_LITERAL(33, 440, 5), // "Fault"
QT_MOC_LITERAL(34, 446, 12) // "Reconnecting"

    },
    "ConnectionStateMachine\0stateChanged\0"
    "\0ConnectionStateMachine::State\0oldState\0"
    "newState\0connectingStarted\0address\0"
    "port\0connected\0running\0faultOccurred\0"
    "reason\0reconnecting\0attemptNumber\0"
    "disconnected\0reconnectionFailed\0"
    "connectToHost\0disconnect\0onConnectionSuccess\0"
    "onConnectionFailure\0onDataReceived\0"
    "onNetworkError\0error\0resetAndReconnect\0"
    "onConnectTimeout\0onActivityTimeout\0"
    "onReconnectDelayTimeout\0State\0"
    "Disconnected\0Connecting\0Connected\0"
    "Running\0Fault\0Reconnecting"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConnectionStateMachine[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      18,   14, // methods
       0,    0, // properties
       1,  142, // enums/sets
       0,    0, // constructors
       0,       // flags
       8,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,  104,    2, 0x06 /* Public */,
       6,    2,  109,    2, 0x06 /* Public */,
       9,    0,  114,    2, 0x06 /* Public */,
      10,    0,  115,    2, 0x06 /* Public */,
      11,    1,  116,    2, 0x06 /* Public */,
      13,    1,  119,    2, 0x06 /* Public */,
      15,    0,  122,    2, 0x06 /* Public */,
      16,    0,  123,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      17,    2,  124,    2, 0x0a /* Public */,
      18,    0,  129,    2, 0x0a /* Public */,
      19,    0,  130,    2, 0x0a /* Public */,
      20,    1,  131,    2, 0x0a /* Public */,
      21,    0,  134,    2, 0x0a /* Public */,
      22,    1,  135,    2, 0x0a /* Public */,
      24,    0,  138,    2, 0x0a /* Public */,
      25,    0,  139,    2, 0x08 /* Private */,
      26,    0,  140,    2, 0x08 /* Private */,
      27,    0,  141,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::Int,    7,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   23,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      28,   28, 0x2,    6,  147,

 // enum data: key, value
      29, uint(ConnectionStateMachine::State::Disconnected),
      30, uint(ConnectionStateMachine::State::Connecting),
      31, uint(ConnectionStateMachine::State::Connected),
      32, uint(ConnectionStateMachine::State::Running),
      33, uint(ConnectionStateMachine::State::Fault),
      34, uint(ConnectionStateMachine::State::Reconnecting),

       0        // eod
};

void ConnectionStateMachine::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ConnectionStateMachine *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< ConnectionStateMachine::State(*)>(_a[1])),(*reinterpret_cast< ConnectionStateMachine::State(*)>(_a[2]))); break;
        case 1: _t->connectingStarted((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 2: _t->connected(); break;
        case 3: _t->running(); break;
        case 4: _t->faultOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->reconnecting((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 6: _t->disconnected(); break;
        case 7: _t->reconnectionFailed(); break;
        case 8: _t->connectToHost((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 9: _t->disconnect(); break;
        case 10: _t->onConnectionSuccess(); break;
        case 11: _t->onConnectionFailure((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 12: _t->onDataReceived(); break;
        case 13: _t->onNetworkError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 14: _t->resetAndReconnect(); break;
        case 15: _t->onConnectTimeout(); break;
        case 16: _t->onActivityTimeout(); break;
        case 17: _t->onReconnectDelayTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ConnectionStateMachine::*)(ConnectionStateMachine::State , ConnectionStateMachine::State );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)(const QString & , int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::connectingStarted)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::connected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::running)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::faultOccurred)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::reconnecting)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::disconnected)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (ConnectionStateMachine::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ConnectionStateMachine::reconnectionFailed)) {
                *result = 7;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ConnectionStateMachine::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ConnectionStateMachine.data,
    qt_meta_data_ConnectionStateMachine,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ConnectionStateMachine::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConnectionStateMachine::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ConnectionStateMachine.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ConnectionStateMachine::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 18)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 18;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 18)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 18;
    }
    return _id;
}

// SIGNAL 0
void ConnectionStateMachine::stateChanged(ConnectionStateMachine::State _t1, ConnectionStateMachine::State _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ConnectionStateMachine::connectingStarted(const QString & _t1, int _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ConnectionStateMachine::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ConnectionStateMachine::running()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ConnectionStateMachine::faultOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ConnectionStateMachine::reconnecting(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ConnectionStateMachine::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 6, nullptr);
}

// SIGNAL 7
void ConnectionStateMachine::reconnectionFailed()
{
    QMetaObject::activate(this, &staticMetaObject, 7, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
