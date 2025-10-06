/****************************************************************************
** Meta object code from reading C++ file 'mockindustrialcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../tests/mocks/mockindustrialcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mockindustrialcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MockIndustrialController_t {
    QByteArrayData data[15];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MockIndustrialController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MockIndustrialController_t qt_meta_stringdata_MockIndustrialController = {
    {
QT_MOC_LITERAL(0, 0, 24), // "MockIndustrialController"
QT_MOC_LITERAL(1, 25, 12), // "stateChanged"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 38), // "IndustrialController::Connect..."
QT_MOC_LITERAL(4, 78, 8), // "newState"
QT_MOC_LITERAL(5, 87, 12), // "dataReceived"
QT_MOC_LITERAL(6, 100, 4), // "data"
QT_MOC_LITERAL(7, 105, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 119, 5), // "error"
QT_MOC_LITERAL(9, 125, 9), // "connected"
QT_MOC_LITERAL(10, 135, 12), // "disconnected"
QT_MOC_LITERAL(11, 148, 17), // "heartbeatReceived"
QT_MOC_LITERAL(12, 166, 17), // "onConnectionTimer"
QT_MOC_LITERAL(13, 184, 17), // "onDataUpdateTimer"
QT_MOC_LITERAL(14, 202, 16) // "onHeartbeatTimer"

    },
    "MockIndustrialController\0stateChanged\0"
    "\0IndustrialController::ConnectionStatus\0"
    "newState\0dataReceived\0data\0errorOccurred\0"
    "error\0connected\0disconnected\0"
    "heartbeatReceived\0onConnectionTimer\0"
    "onDataUpdateTimer\0onHeartbeatTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MockIndustrialController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x06 /* Public */,
       5,    1,   62,    2, 0x06 /* Public */,
       7,    1,   65,    2, 0x06 /* Public */,
       9,    0,   68,    2, 0x06 /* Public */,
      10,    0,   69,    2, 0x06 /* Public */,
      11,    0,   70,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   71,    2, 0x08 /* Private */,
      13,    0,   72,    2, 0x08 /* Private */,
      14,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QVariantMap,    6,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void MockIndustrialController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MockIndustrialController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->stateChanged((*reinterpret_cast< IndustrialController::ConnectionStatus(*)>(_a[1]))); break;
        case 1: _t->dataReceived((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->connected(); break;
        case 4: _t->disconnected(); break;
        case 5: _t->heartbeatReceived(); break;
        case 6: _t->onConnectionTimer(); break;
        case 7: _t->onDataUpdateTimer(); break;
        case 8: _t->onHeartbeatTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MockIndustrialController::*)(IndustrialController::ConnectionStatus );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::stateChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MockIndustrialController::*)(const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::dataReceived)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MockIndustrialController::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::errorOccurred)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MockIndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::connected)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MockIndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::disconnected)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MockIndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockIndustrialController::heartbeatReceived)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MockIndustrialController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MockIndustrialController.data,
    qt_meta_data_MockIndustrialController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MockIndustrialController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MockIndustrialController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MockIndustrialController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MockIndustrialController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MockIndustrialController::stateChanged(IndustrialController::ConnectionStatus _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MockIndustrialController::dataReceived(const QVariantMap & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MockIndustrialController::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MockIndustrialController::connected()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void MockIndustrialController::disconnected()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MockIndustrialController::heartbeatReceived()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
