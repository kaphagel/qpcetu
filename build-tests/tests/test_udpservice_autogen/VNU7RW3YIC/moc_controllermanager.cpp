/****************************************************************************
** Meta object code from reading C++ file 'controllermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/controllermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controllermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControllerManager_t {
    QByteArrayData data[28];
    char stringdata0[462];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControllerManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControllerManager_t qt_meta_stringdata_ControllerManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "ControllerManager"
QT_MOC_LITERAL(1, 18, 22), // "controllerCountChanged"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 13), // "statusChanged"
QT_MOC_LITERAL(4, 56, 15), // "controllerAdded"
QT_MOC_LITERAL(5, 72, 21), // "IndustrialController*"
QT_MOC_LITERAL(6, 94, 10), // "controller"
QT_MOC_LITERAL(7, 105, 17), // "controllerRemoved"
QT_MOC_LITERAL(8, 123, 17), // "controllerUpdated"
QT_MOC_LITERAL(9, 141, 23), // "onControllerDataUpdated"
QT_MOC_LITERAL(10, 165, 22), // "performPeriodicCleanup"
QT_MOC_LITERAL(11, 188, 21), // "addOrUpdateController"
QT_MOC_LITERAL(12, 210, 8), // "response"
QT_MOC_LITERAL(13, 219, 12), // "QHostAddress"
QT_MOC_LITERAL(14, 232, 6), // "sender"
QT_MOC_LITERAL(15, 239, 13), // "getController"
QT_MOC_LITERAL(16, 253, 9), // "ipAddress"
QT_MOC_LITERAL(17, 263, 18), // "getControllerByMac"
QT_MOC_LITERAL(18, 282, 10), // "macAddress"
QT_MOC_LITERAL(19, 293, 20), // "getControllersByType"
QT_MOC_LITERAL(20, 314, 28), // "QList<IndustrialController*>"
QT_MOC_LITERAL(21, 343, 36), // "IndustrialController::Control..."
QT_MOC_LITERAL(22, 380, 4), // "type"
QT_MOC_LITERAL(23, 385, 14), // "getCountByType"
QT_MOC_LITERAL(24, 400, 24), // "removeOfflineControllers"
QT_MOC_LITERAL(25, 425, 8), // "clearAll"
QT_MOC_LITERAL(26, 434, 15), // "controllerCount"
QT_MOC_LITERAL(27, 450, 11) // "onlineCount"

    },
    "ControllerManager\0controllerCountChanged\0"
    "\0statusChanged\0controllerAdded\0"
    "IndustrialController*\0controller\0"
    "controllerRemoved\0controllerUpdated\0"
    "onControllerDataUpdated\0performPeriodicCleanup\0"
    "addOrUpdateController\0response\0"
    "QHostAddress\0sender\0getController\0"
    "ipAddress\0getControllerByMac\0macAddress\0"
    "getControllersByType\0QList<IndustrialController*>\0"
    "IndustrialController::ControllerType\0"
    "type\0getCountByType\0removeOfflineControllers\0"
    "clearAll\0controllerCount\0onlineCount"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControllerManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       2,  116, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x06 /* Public */,
       3,    0,   85,    2, 0x06 /* Public */,
       4,    1,   86,    2, 0x06 /* Public */,
       7,    1,   89,    2, 0x06 /* Public */,
       8,    1,   92,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       9,    0,   95,    2, 0x0a /* Public */,
      10,    0,   96,    2, 0x0a /* Public */,

 // methods: name, argc, parameters, tag, flags
      11,    2,   97,    2, 0x02 /* Public */,
      15,    1,  102,    2, 0x02 /* Public */,
      17,    1,  105,    2, 0x02 /* Public */,
      19,    1,  108,    2, 0x02 /* Public */,
      23,    1,  111,    2, 0x02 /* Public */,
      24,    0,  114,    2, 0x02 /* Public */,
      25,    0,  115,    2, 0x02 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

 // methods: parameters
    0x80000000 | 5, QMetaType::QString, 0x80000000 | 13,   12,   14,
    0x80000000 | 5, QMetaType::QString,   16,
    0x80000000 | 5, QMetaType::QString,   18,
    0x80000000 | 20, 0x80000000 | 21,   22,
    QMetaType::Int, 0x80000000 | 21,   22,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
      26, QMetaType::Int, 0x00495001,
      27, QMetaType::Int, 0x00495001,

 // properties: notify_signal_id
       0,
       1,

       0        // eod
};

void ControllerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControllerManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->controllerCountChanged(); break;
        case 1: _t->statusChanged(); break;
        case 2: _t->controllerAdded((*reinterpret_cast< IndustrialController*(*)>(_a[1]))); break;
        case 3: _t->controllerRemoved((*reinterpret_cast< IndustrialController*(*)>(_a[1]))); break;
        case 4: _t->controllerUpdated((*reinterpret_cast< IndustrialController*(*)>(_a[1]))); break;
        case 5: _t->onControllerDataUpdated(); break;
        case 6: _t->performPeriodicCleanup(); break;
        case 7: { IndustrialController* _r = _t->addOrUpdateController((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< IndustrialController**>(_a[0]) = std::move(_r); }  break;
        case 8: { IndustrialController* _r = _t->getController((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< IndustrialController**>(_a[0]) = std::move(_r); }  break;
        case 9: { IndustrialController* _r = _t->getControllerByMac((*reinterpret_cast< const QString(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< IndustrialController**>(_a[0]) = std::move(_r); }  break;
        case 10: { QList<IndustrialController*> _r = _t->getControllersByType((*reinterpret_cast< IndustrialController::ControllerType(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< QList<IndustrialController*>*>(_a[0]) = std::move(_r); }  break;
        case 11: { int _r = _t->getCountByType((*reinterpret_cast< IndustrialController::ControllerType(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = std::move(_r); }  break;
        case 12: _t->removeOfflineControllers(); break;
        case 13: _t->clearAll(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 2:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IndustrialController* >(); break;
            }
            break;
        case 3:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IndustrialController* >(); break;
            }
            break;
        case 4:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< IndustrialController* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControllerManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerManager::controllerCountChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControllerManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerManager::statusChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControllerManager::*)(IndustrialController * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerManager::controllerAdded)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ControllerManager::*)(IndustrialController * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerManager::controllerRemoved)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ControllerManager::*)(IndustrialController * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerManager::controllerUpdated)) {
                *result = 4;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ControllerManager *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< int*>(_v) = _t->controllerCount(); break;
        case 1: *reinterpret_cast< int*>(_v) = _t->onlineCount(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ControllerManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QAbstractListModel::staticMetaObject>(),
    qt_meta_stringdata_ControllerManager.data,
    qt_meta_data_ControllerManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControllerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControllerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControllerManager.stringdata0))
        return static_cast<void*>(this);
    return QAbstractListModel::qt_metacast(_clname);
}

int ControllerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QAbstractListModel::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 2;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 2;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void ControllerManager::controllerCountChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ControllerManager::statusChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void ControllerManager::controllerAdded(IndustrialController * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ControllerManager::controllerRemoved(IndustrialController * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ControllerManager::controllerUpdated(IndustrialController * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
