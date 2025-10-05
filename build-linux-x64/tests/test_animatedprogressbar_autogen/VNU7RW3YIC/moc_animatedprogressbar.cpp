/****************************************************************************
** Meta object code from reading C++ file 'animatedprogressbar.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/animatedprogressbar.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'animatedprogressbar.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AnimatedProgressBar_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AnimatedProgressBar_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AnimatedProgressBar_t qt_meta_stringdata_AnimatedProgressBar = {
    {
QT_MOC_LITERAL(0, 0, 19), // "AnimatedProgressBar"
QT_MOC_LITERAL(1, 20, 8), // "setValue"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 5), // "value"
QT_MOC_LITERAL(4, 36, 15) // "animationOffset"

    },
    "AnimatedProgressBar\0setValue\0\0value\0"
    "animationOffset"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AnimatedProgressBar[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       1,   22, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // properties: name, type, flags
       4, QMetaType::QReal, 0x00095103,

       0        // eod
};

void AnimatedProgressBar::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AnimatedProgressBar *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->setValue((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<AnimatedProgressBar *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< qreal*>(_v) = _t->animationOffset(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<AnimatedProgressBar *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setAnimationOffset(*reinterpret_cast< qreal*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject AnimatedProgressBar::staticMetaObject = { {
    QMetaObject::SuperData::link<QProgressBar::staticMetaObject>(),
    qt_meta_stringdata_AnimatedProgressBar.data,
    qt_meta_data_AnimatedProgressBar,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AnimatedProgressBar::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AnimatedProgressBar::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AnimatedProgressBar.stringdata0))
        return static_cast<void*>(this);
    return QProgressBar::qt_metacast(_clname);
}

int AnimatedProgressBar::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QProgressBar::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 1;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 1;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
