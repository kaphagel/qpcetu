/****************************************************************************
** Meta object code from reading C++ file 'mockcontrollermanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../tests/mocks/mockcontrollermanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mockcontrollermanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MockControllerManager_t {
    QByteArrayData data[15];
    char stringdata0[245];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MockControllerManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MockControllerManager_t qt_meta_stringdata_MockControllerManager = {
    {
QT_MOC_LITERAL(0, 0, 21), // "MockControllerManager"
QT_MOC_LITERAL(1, 22, 20), // "controllerDiscovered"
QT_MOC_LITERAL(2, 43, 0), // ""
QT_MOC_LITERAL(3, 44, 7), // "address"
QT_MOC_LITERAL(4, 52, 4), // "info"
QT_MOC_LITERAL(5, 57, 19), // "controllerConnected"
QT_MOC_LITERAL(6, 77, 22), // "controllerDisconnected"
QT_MOC_LITERAL(7, 100, 15), // "controllerError"
QT_MOC_LITERAL(8, 116, 5), // "error"
QT_MOC_LITERAL(9, 122, 16), // "discoveryStarted"
QT_MOC_LITERAL(10, 139, 17), // "discoveryFinished"
QT_MOC_LITERAL(11, 157, 24), // "onControllerStateChanged"
QT_MOC_LITERAL(12, 182, 38), // "IndustrialController::Connect..."
QT_MOC_LITERAL(13, 221, 5), // "state"
QT_MOC_LITERAL(14, 227, 17) // "onControllerError"

    },
    "MockControllerManager\0controllerDiscovered\0"
    "\0address\0info\0controllerConnected\0"
    "controllerDisconnected\0controllerError\0"
    "error\0discoveryStarted\0discoveryFinished\0"
    "onControllerStateChanged\0"
    "IndustrialController::ConnectionStatus\0"
    "state\0onControllerError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MockControllerManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       6,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   54,    2, 0x06 /* Public */,
       5,    1,   59,    2, 0x06 /* Public */,
       6,    1,   62,    2, 0x06 /* Public */,
       7,    2,   65,    2, 0x06 /* Public */,
       9,    0,   70,    2, 0x06 /* Public */,
      10,    0,   71,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      11,    1,   72,    2, 0x08 /* Private */,
      14,    1,   75,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QVariantMap,    3,    4,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    8,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 12,   13,
    QMetaType::Void, QMetaType::QString,    8,

       0        // eod
};

void MockControllerManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MockControllerManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->controllerDiscovered((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 1: _t->controllerConnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->controllerDisconnected((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->controllerError((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 4: _t->discoveryStarted(); break;
        case 5: _t->discoveryFinished(); break;
        case 6: _t->onControllerStateChanged((*reinterpret_cast< IndustrialController::ConnectionStatus(*)>(_a[1]))); break;
        case 7: _t->onControllerError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MockControllerManager::*)(const QString & , const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::controllerDiscovered)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MockControllerManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::controllerConnected)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MockControllerManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::controllerDisconnected)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MockControllerManager::*)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::controllerError)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MockControllerManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::discoveryStarted)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (MockControllerManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockControllerManager::discoveryFinished)) {
                *result = 5;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MockControllerManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MockControllerManager.data,
    qt_meta_data_MockControllerManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MockControllerManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MockControllerManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MockControllerManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MockControllerManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void MockControllerManager::controllerDiscovered(const QString & _t1, const QVariantMap & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MockControllerManager::controllerConnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MockControllerManager::controllerDisconnected(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MockControllerManager::controllerError(const QString & _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MockControllerManager::discoveryStarted()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}

// SIGNAL 5
void MockControllerManager::discoveryFinished()
{
    QMetaObject::activate(this, &staticMetaObject, 5, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
