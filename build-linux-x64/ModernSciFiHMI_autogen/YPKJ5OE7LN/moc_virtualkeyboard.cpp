/****************************************************************************
** Meta object code from reading C++ file 'virtualkeyboard.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/virtualkeyboard.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'virtualkeyboard.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_VirtualKeyboard_t {
    QByteArrayData data[13];
    char stringdata0[164];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_VirtualKeyboard_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_VirtualKeyboard_t qt_meta_stringdata_VirtualKeyboard = {
    {
QT_MOC_LITERAL(0, 0, 15), // "VirtualKeyboard"
QT_MOC_LITERAL(1, 16, 25), // "keyboardVisibilityChanged"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 7), // "visible"
QT_MOC_LITERAL(4, 51, 14), // "onInputFocusIn"
QT_MOC_LITERAL(5, 66, 8), // "QWidget*"
QT_MOC_LITERAL(6, 75, 6), // "widget"
QT_MOC_LITERAL(7, 82, 15), // "onInputFocusOut"
QT_MOC_LITERAL(8, 98, 12), // "onKeyPressed"
QT_MOC_LITERAL(9, 111, 3), // "key"
QT_MOC_LITERAL(10, 115, 18), // "onBackspacePressed"
QT_MOC_LITERAL(11, 134, 14), // "onEnterPressed"
QT_MOC_LITERAL(12, 149, 14) // "onClearPressed"

    },
    "VirtualKeyboard\0keyboardVisibilityChanged\0"
    "\0visible\0onInputFocusIn\0QWidget*\0"
    "widget\0onInputFocusOut\0onKeyPressed\0"
    "key\0onBackspacePressed\0onEnterPressed\0"
    "onClearPressed"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_VirtualKeyboard[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   52,    2, 0x0a /* Public */,
       7,    0,   55,    2, 0x0a /* Public */,
       8,    1,   56,    2, 0x08 /* Private */,
      10,    0,   59,    2, 0x08 /* Private */,
      11,    0,   60,    2, 0x08 /* Private */,
      12,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void VirtualKeyboard::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<VirtualKeyboard *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->keyboardVisibilityChanged((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 1: _t->onInputFocusIn((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 2: _t->onInputFocusOut(); break;
        case 3: _t->onKeyPressed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 4: _t->onBackspacePressed(); break;
        case 5: _t->onEnterPressed(); break;
        case 6: _t->onClearPressed(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (VirtualKeyboard::*)(bool );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&VirtualKeyboard::keyboardVisibilityChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject VirtualKeyboard::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_VirtualKeyboard.data,
    qt_meta_data_VirtualKeyboard,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *VirtualKeyboard::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *VirtualKeyboard::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_VirtualKeyboard.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int VirtualKeyboard::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void VirtualKeyboard::keyboardVisibilityChanged(bool _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_InputEventFilter_t {
    QByteArrayData data[6];
    char stringdata0[61];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_InputEventFilter_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_InputEventFilter_t qt_meta_stringdata_InputEventFilter = {
    {
QT_MOC_LITERAL(0, 0, 16), // "InputEventFilter"
QT_MOC_LITERAL(1, 17, 12), // "inputFocusIn"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 8), // "QWidget*"
QT_MOC_LITERAL(4, 40, 6), // "widget"
QT_MOC_LITERAL(5, 47, 13) // "inputFocusOut"

    },
    "InputEventFilter\0inputFocusIn\0\0QWidget*\0"
    "widget\0inputFocusOut"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_InputEventFilter[] = {

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
       5,    0,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,

       0        // eod
};

void InputEventFilter::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<InputEventFilter *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->inputFocusIn((*reinterpret_cast< QWidget*(*)>(_a[1]))); break;
        case 1: _t->inputFocusOut(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QWidget* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (InputEventFilter::*)(QWidget * );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InputEventFilter::inputFocusIn)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (InputEventFilter::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&InputEventFilter::inputFocusOut)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject InputEventFilter::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_InputEventFilter.data,
    qt_meta_data_InputEventFilter,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *InputEventFilter::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *InputEventFilter::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_InputEventFilter.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int InputEventFilter::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void InputEventFilter::inputFocusIn(QWidget * _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void InputEventFilter::inputFocusOut()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
