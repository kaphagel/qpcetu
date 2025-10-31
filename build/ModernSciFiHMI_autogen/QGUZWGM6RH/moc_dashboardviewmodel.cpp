/****************************************************************************
** Meta object code from reading C++ file 'dashboardviewmodel.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/viewmodels/dashboardviewmodel.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboardviewmodel.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DashboardViewModel_t {
    QByteArrayData data[27];
    char stringdata0[358];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DashboardViewModel_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DashboardViewModel_t qt_meta_stringdata_DashboardViewModel = {
    {
QT_MOC_LITERAL(0, 0, 18), // "DashboardViewModel"
QT_MOC_LITERAL(1, 19, 17), // "energyCoreUpdated"
QT_MOC_LITERAL(2, 37, 0), // ""
QT_MOC_LITERAL(3, 38, 5), // "value"
QT_MOC_LITERAL(4, 44, 19), // "shieldMatrixUpdated"
QT_MOC_LITERAL(5, 64, 19), // "engineThrustUpdated"
QT_MOC_LITERAL(6, 84, 18), // "weaponArrayUpdated"
QT_MOC_LITERAL(7, 103, 23), // "systemParametersUpdated"
QT_MOC_LITERAL(8, 127, 16), // "SystemParameters"
QT_MOC_LITERAL(9, 144, 6), // "params"
QT_MOC_LITERAL(10, 151, 21), // "navigationDataUpdated"
QT_MOC_LITERAL(11, 173, 14), // "NavigationData"
QT_MOC_LITERAL(12, 188, 4), // "data"
QT_MOC_LITERAL(13, 193, 19), // "systemStatusChanged"
QT_MOC_LITERAL(14, 213, 12), // "SystemStatus"
QT_MOC_LITERAL(15, 226, 6), // "status"
QT_MOC_LITERAL(16, 233, 7), // "message"
QT_MOC_LITERAL(17, 241, 11), // "timeUpdated"
QT_MOC_LITERAL(18, 253, 9), // "timestamp"
QT_MOC_LITERAL(19, 263, 14), // "alertGenerated"
QT_MOC_LITERAL(20, 278, 23), // "connectionStatusChanged"
QT_MOC_LITERAL(21, 302, 9), // "connected"
QT_MOC_LITERAL(22, 312, 13), // "onUpdateTimer"
QT_MOC_LITERAL(23, 326, 6), // "Online"
QT_MOC_LITERAL(24, 333, 7), // "Warning"
QT_MOC_LITERAL(25, 341, 8), // "Critical"
QT_MOC_LITERAL(26, 350, 7) // "Offline"

    },
    "DashboardViewModel\0energyCoreUpdated\0"
    "\0value\0shieldMatrixUpdated\0"
    "engineThrustUpdated\0weaponArrayUpdated\0"
    "systemParametersUpdated\0SystemParameters\0"
    "params\0navigationDataUpdated\0"
    "NavigationData\0data\0systemStatusChanged\0"
    "SystemStatus\0status\0message\0timeUpdated\0"
    "timestamp\0alertGenerated\0"
    "connectionStatusChanged\0connected\0"
    "onUpdateTimer\0Online\0Warning\0Critical\0"
    "Offline"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DashboardViewModel[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       1,  104, // enums/sets
       0,    0, // constructors
       0,       // flags
      10,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   69,    2, 0x06 /* Public */,
       4,    1,   72,    2, 0x06 /* Public */,
       5,    1,   75,    2, 0x06 /* Public */,
       6,    1,   78,    2, 0x06 /* Public */,
       7,    1,   81,    2, 0x06 /* Public */,
      10,    1,   84,    2, 0x06 /* Public */,
      13,    2,   87,    2, 0x06 /* Public */,
      17,    1,   92,    2, 0x06 /* Public */,
      19,    1,   95,    2, 0x06 /* Public */,
      20,    2,   98,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      22,    0,  103,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, 0x80000000 | 8,    9,
    QMetaType::Void, 0x80000000 | 11,   12,
    QMetaType::Void, 0x80000000 | 14, QMetaType::QString,   15,   16,
    QMetaType::Void, QMetaType::QString,   18,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString,   21,   16,

 // slots: parameters
    QMetaType::Void,

 // enums: name, alias, flags, count, data
      14,   14, 0x2,    4,  109,

 // enum data: key, value
      23, uint(DashboardViewModel::SystemStatus::Online),
      24, uint(DashboardViewModel::SystemStatus::Warning),
      25, uint(DashboardViewModel::SystemStatus::Critical),
      26, uint(DashboardViewModel::SystemStatus::Offline),

       0        // eod
};

void DashboardViewModel::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DashboardViewModel *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->energyCoreUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->shieldMatrixUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->engineThrustUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->weaponArrayUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->systemParametersUpdated((*reinterpret_cast< const SystemParameters(*)>(_a[1]))); break;
        case 5: _t->navigationDataUpdated((*reinterpret_cast< const NavigationData(*)>(_a[1]))); break;
        case 6: _t->systemStatusChanged((*reinterpret_cast< SystemStatus(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->timeUpdated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->alertGenerated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->connectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 10: _t->onUpdateTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DashboardViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::energyCoreUpdated)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::shieldMatrixUpdated)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::engineThrustUpdated)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::weaponArrayUpdated)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(const SystemParameters & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::systemParametersUpdated)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(const NavigationData & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::navigationDataUpdated)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(SystemStatus , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::systemStatusChanged)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::timeUpdated)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::alertGenerated)) {
                *result = 8;
                return;
            }
        }
        {
            using _t = void (DashboardViewModel::*)(bool , const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DashboardViewModel::connectionStatusChanged)) {
                *result = 9;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DashboardViewModel::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_DashboardViewModel.data,
    qt_meta_data_DashboardViewModel,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DashboardViewModel::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardViewModel::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardViewModel.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int DashboardViewModel::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 11;
    }
    return _id;
}

// SIGNAL 0
void DashboardViewModel::energyCoreUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DashboardViewModel::shieldMatrixUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void DashboardViewModel::engineThrustUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void DashboardViewModel::weaponArrayUpdated(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void DashboardViewModel::systemParametersUpdated(const SystemParameters & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void DashboardViewModel::navigationDataUpdated(const NavigationData & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void DashboardViewModel::systemStatusChanged(SystemStatus _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void DashboardViewModel::timeUpdated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void DashboardViewModel::alertGenerated(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void DashboardViewModel::connectionStatusChanged(bool _t1, const QString & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
