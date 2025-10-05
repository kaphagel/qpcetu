/****************************************************************************
** Meta object code from reading C++ file 'controllercardwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/controllercardwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'controllercardwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ControllerCardWidget_t {
    QByteArrayData data[10];
    char stringdata0[157];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ControllerCardWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ControllerCardWidget_t qt_meta_stringdata_ControllerCardWidget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "ControllerCardWidget"
QT_MOC_LITERAL(1, 21, 11), // "cardClicked"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 9), // "ipAddress"
QT_MOC_LITERAL(4, 44, 18), // "configureRequested"
QT_MOC_LITERAL(5, 63, 20), // "diagnosticsRequested"
QT_MOC_LITERAL(6, 84, 18), // "onConfigureClicked"
QT_MOC_LITERAL(7, 103, 20), // "onDiagnosticsClicked"
QT_MOC_LITERAL(8, 124, 20), // "updatePulseAnimation"
QT_MOC_LITERAL(9, 145, 11) // "statusColor"

    },
    "ControllerCardWidget\0cardClicked\0\0"
    "ipAddress\0configureRequested\0"
    "diagnosticsRequested\0onConfigureClicked\0"
    "onDiagnosticsClicked\0updatePulseAnimation\0"
    "statusColor"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ControllerCardWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       1,   56, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   44,    2, 0x06 /* Public */,
       4,    1,   47,    2, 0x06 /* Public */,
       5,    1,   50,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // properties: name, type, flags
       9, QMetaType::QColor, 0x00095103,

       0        // eod
};

void ControllerCardWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ControllerCardWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->cardClicked((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->configureRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 2: _t->diagnosticsRequested((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->onConfigureClicked(); break;
        case 4: _t->onDiagnosticsClicked(); break;
        case 5: _t->updatePulseAnimation(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ControllerCardWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerCardWidget::cardClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ControllerCardWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerCardWidget::configureRequested)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ControllerCardWidget::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ControllerCardWidget::diagnosticsRequested)) {
                *result = 2;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        auto *_t = static_cast<ControllerCardWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QColor*>(_v) = _t->statusColor(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        auto *_t = static_cast<ControllerCardWidget *>(_o);
        (void)_t;
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setStatusColor(*reinterpret_cast< QColor*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

QT_INIT_METAOBJECT const QMetaObject ControllerCardWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_ControllerCardWidget.data,
    qt_meta_data_ControllerCardWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ControllerCardWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ControllerCardWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ControllerCardWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int ControllerCardWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void ControllerCardWidget::cardClicked(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ControllerCardWidget::configureRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ControllerCardWidget::diagnosticsRequested(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
