/****************************************************************************
** Meta object code from reading C++ file 'industrialcontroller.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/industrialcontroller.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'industrialcontroller.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_IndustrialController_t {
    QByteArrayData data[30];
    char stringdata0[335];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_IndustrialController_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_IndustrialController_t qt_meta_stringdata_IndustrialController = {
    {
QT_MOC_LITERAL(0, 0, 20), // "IndustrialController"
QT_MOC_LITERAL(1, 21, 17), // "controllerChanged"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 13), // "statusChanged"
QT_MOC_LITERAL(4, 54, 11), // "dataUpdated"
QT_MOC_LITERAL(5, 66, 14), // "updateLastSeen"
QT_MOC_LITERAL(6, 81, 9), // "setStatus"
QT_MOC_LITERAL(7, 91, 16), // "ConnectionStatus"
QT_MOC_LITERAL(8, 108, 6), // "status"
QT_MOC_LITERAL(9, 115, 12), // "checkTimeout"
QT_MOC_LITERAL(10, 128, 14), // "controllerType"
QT_MOC_LITERAL(11, 143, 9), // "ipAddress"
QT_MOC_LITERAL(12, 153, 10), // "macAddress"
QT_MOC_LITERAL(13, 164, 8), // "hostname"
QT_MOC_LITERAL(14, 173, 15), // "firmwareVersion"
QT_MOC_LITERAL(15, 189, 8), // "isOnline"
QT_MOC_LITERAL(16, 198, 14), // "signalStrength"
QT_MOC_LITERAL(17, 213, 14), // "ControllerType"
QT_MOC_LITERAL(18, 228, 7), // "UNKNOWN"
QT_MOC_LITERAL(19, 236, 5), // "EPIC4"
QT_MOC_LITERAL(20, 242, 5), // "EPIC5"
QT_MOC_LITERAL(21, 248, 8), // "SNAP_PAC"
QT_MOC_LITERAL(22, 257, 9), // "CLICK_PLC"
QT_MOC_LITERAL(23, 267, 7), // "MODICON"
QT_MOC_LITERAL(24, 275, 13), // "COMPACT_LOGIX"
QT_MOC_LITERAL(25, 289, 7), // "OFFLINE"
QT_MOC_LITERAL(26, 297, 11), // "DISCOVERING"
QT_MOC_LITERAL(27, 309, 6), // "ONLINE"
QT_MOC_LITERAL(28, 316, 10), // "COMM_ERROR"
QT_MOC_LITERAL(29, 327, 7) // "TIMEOUT"

    },
    "IndustrialController\0controllerChanged\0"
    "\0statusChanged\0dataUpdated\0updateLastSeen\0"
    "setStatus\0ConnectionStatus\0status\0"
    "checkTimeout\0controllerType\0ipAddress\0"
    "macAddress\0hostname\0firmwareVersion\0"
    "isOnline\0signalStrength\0ControllerType\0"
    "UNKNOWN\0EPIC4\0EPIC5\0SNAP_PAC\0CLICK_PLC\0"
    "MODICON\0COMPACT_LOGIX\0OFFLINE\0DISCOVERING\0"
    "ONLINE\0COMM_ERROR\0TIMEOUT"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_IndustrialController[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       7,   52, // properties
       2,   80, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   44,    2, 0x06 /* Public */,
       3,    0,   45,    2, 0x06 /* Public */,
       4,    0,   46,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   47,    2, 0x0a /* Public */,
       6,    1,   48,    2, 0x0a /* Public */,
       9,    0,   51,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 7,    8,
    QMetaType::Void,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00495001,
      11, QMetaType::QString, 0x00495001,
      12, QMetaType::QString, 0x00495001,
      13, QMetaType::QString, 0x00495001,
      14, QMetaType::QString, 0x00495001,
      15, QMetaType::Bool, 0x00495001,
      16, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       0,
       0,
       0,
       0,
       1,
       1,

 // enums: name, alias, flags, count, data
      17,   17, 0x0,    7,   90,
       7,    7, 0x0,    5,  104,

 // enum data: key, value
      18, uint(IndustrialController::UNKNOWN),
      19, uint(IndustrialController::EPIC4),
      20, uint(IndustrialController::EPIC5),
      21, uint(IndustrialController::SNAP_PAC),
      22, uint(IndustrialController::CLICK_PLC),
      23, uint(IndustrialController::MODICON),
      24, uint(IndustrialController::COMPACT_LOGIX),
      25, uint(IndustrialController::OFFLINE),
      26, uint(IndustrialController::DISCOVERING),
      27, uint(IndustrialController::ONLINE),
      28, uint(IndustrialController::COMM_ERROR),
      29, uint(IndustrialController::TIMEOUT),

       0        // eod
};

void IndustrialController::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<IndustrialController *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->controllerChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->dataUpdated(); break;
        case 3: _t->updateLastSeen(); break;
        case 4: _t->setStatus((*reinterpret_cast< ConnectionStatus(*)>(_a[1]))); break;
        case 5: _t->checkTimeout(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (IndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IndustrialController::controllerChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (IndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IndustrialController::statusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (IndustrialController::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&IndustrialController::dataUpdated)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<IndustrialController *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->controllerType(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->ipAddress(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->macAddress(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->hostname(); break;
        case 4: *reinterpret_cast< QString*>(_v) = _t->firmwareVersion(); break;
        case 5: *reinterpret_cast< bool*>(_v) = _t->isOnline(); break;
        case 6: *reinterpret_cast< int*>(_v) = _t->signalStrength(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject IndustrialController::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_IndustrialController.data,
    qt_meta_data_IndustrialController,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *IndustrialController::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *IndustrialController::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_IndustrialController.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int IndustrialController::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 7;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 7;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void IndustrialController::controllerChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void IndustrialController::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void IndustrialController::dataUpdated()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
