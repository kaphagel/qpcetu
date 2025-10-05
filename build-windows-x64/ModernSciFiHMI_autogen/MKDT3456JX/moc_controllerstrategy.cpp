/****************************************************************************
** Meta object code from reading C++ file 'controllerstrategy.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/strategies/controllerstrategy.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controllerstrategy.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControllerStrategy_t {
    QByteArrayData data[6];
    char stringdata0[58];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControllerStrategy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControllerStrategy_t qt_meta_stringdata_ControllerStrategy = {
    {
QT_MOC_LITERAL(0, 0, 18), // "ControllerStrategy"
QT_MOC_LITERAL(1, 19, 12), // "dataReceived"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "data"
QT_MOC_LITERAL(4, 38, 13), // "errorOccurred"
QT_MOC_LITERAL(5, 52, 5) // "error"

    },
    "ControllerStrategy\0dataReceived\0\0data\0"
    "errorOccurred\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControllerStrategy[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       4,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QVariantMap,    3,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void ControllerStrategy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControllerStrategy *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->dataReceived((*reinterpret_cast< const QVariantMap(*)>(_a[1]))); break;
        case 1: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControllerStrategy::*)(const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStrategy::dataReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControllerStrategy::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerStrategy::errorOccurred)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ControllerStrategy::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ControllerStrategy.data,
    qt_meta_data_ControllerStrategy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControllerStrategy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControllerStrategy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControllerStrategy.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ControllerStrategy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void ControllerStrategy::dataReceived(const QVariantMap & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControllerStrategy::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
struct qt_meta_stringdata_Epic4Strategy_t {
    QByteArrayData data[1];
    char stringdata0[14];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Epic4Strategy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Epic4Strategy_t qt_meta_stringdata_Epic4Strategy = {
    {
QT_MOC_LITERAL(0, 0, 13) // "Epic4Strategy"

    },
    "Epic4Strategy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Epic4Strategy[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void Epic4Strategy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject Epic4Strategy::staticMetaObject = { {
    QMetaObject::SuperData::link<ControllerStrategy::staticMetaObject>(),
    qt_meta_stringdata_Epic4Strategy.data,
    qt_meta_data_Epic4Strategy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Epic4Strategy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Epic4Strategy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Epic4Strategy.stringdata0))
        return static_cast<void*>(this);
    return ControllerStrategy::qt_metacast(_clname);
}

int Epic4Strategy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ControllerStrategy::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_SnapPacStrategy_t {
    QByteArrayData data[1];
    char stringdata0[16];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SnapPacStrategy_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SnapPacStrategy_t qt_meta_stringdata_SnapPacStrategy = {
    {
QT_MOC_LITERAL(0, 0, 15) // "SnapPacStrategy"

    },
    "SnapPacStrategy"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SnapPacStrategy[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       0,    0, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

       0        // eod
};

void SnapPacStrategy::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject SnapPacStrategy::staticMetaObject = { {
    QMetaObject::SuperData::link<ControllerStrategy::staticMetaObject>(),
    qt_meta_stringdata_SnapPacStrategy.data,
    qt_meta_data_SnapPacStrategy,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SnapPacStrategy::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SnapPacStrategy::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SnapPacStrategy.stringdata0))
        return static_cast<void*>(this);
    return ControllerStrategy::qt_metacast(_clname);
}

int SnapPacStrategy::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = ControllerStrategy::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
