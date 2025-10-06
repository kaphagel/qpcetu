/****************************************************************************
** Meta object code from reading C++ file 'breadcrumbwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/navigation/breadcrumbwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'breadcrumbwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_BreadcrumbWidget_t {
    QByteArrayData data[11];
    char stringdata0[136];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BreadcrumbWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BreadcrumbWidget_t qt_meta_stringdata_BreadcrumbWidget = {
    {
QT_MOC_LITERAL(0, 0, 16), // "BreadcrumbWidget"
QT_MOC_LITERAL(1, 17, 17), // "breadcrumbClicked"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "index"
QT_MOC_LITERAL(4, 42, 11), // "homeClicked"
QT_MOC_LITERAL(5, 54, 11), // "backClicked"
QT_MOC_LITERAL(6, 66, 15), // "navigateToIndex"
QT_MOC_LITERAL(7, 82, 6), // "goHome"
QT_MOC_LITERAL(8, 89, 6), // "goBack"
QT_MOC_LITERAL(9, 96, 19), // "onBreadcrumbClicked"
QT_MOC_LITERAL(10, 116, 19) // "onAnimationFinished"

    },
    "BreadcrumbWidget\0breadcrumbClicked\0\0"
    "index\0homeClicked\0backClicked\0"
    "navigateToIndex\0goHome\0goBack\0"
    "onBreadcrumbClicked\0onAnimationFinished"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BreadcrumbWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    0,   57,    2, 0x06 /* Public */,
       5,    0,   58,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   59,    2, 0x0a /* Public */,
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    0,   64,    2, 0x08 /* Private */,
      10,    0,   65,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void BreadcrumbWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<BreadcrumbWidget *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->breadcrumbClicked((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->homeClicked(); break;
        case 2: _t->backClicked(); break;
        case 3: _t->navigateToIndex((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->goHome(); break;
        case 5: _t->goBack(); break;
        case 6: _t->onBreadcrumbClicked(); break;
        case 7: _t->onAnimationFinished(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (BreadcrumbWidget::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BreadcrumbWidget::breadcrumbClicked)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (BreadcrumbWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BreadcrumbWidget::homeClicked)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (BreadcrumbWidget::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&BreadcrumbWidget::backClicked)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject BreadcrumbWidget::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_BreadcrumbWidget.data,
    qt_meta_data_BreadcrumbWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BreadcrumbWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BreadcrumbWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BreadcrumbWidget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int BreadcrumbWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void BreadcrumbWidget::breadcrumbClicked(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void BreadcrumbWidget::homeClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void BreadcrumbWidget::backClicked()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}
struct qt_meta_stringdata_BreadcrumbButton_t {
    QByteArrayData data[1];
    char stringdata0[17];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_BreadcrumbButton_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_BreadcrumbButton_t qt_meta_stringdata_BreadcrumbButton = {
    {
QT_MOC_LITERAL(0, 0, 16) // "BreadcrumbButton"

    },
    "BreadcrumbButton"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_BreadcrumbButton[] = {

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

void BreadcrumbButton::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject BreadcrumbButton::staticMetaObject = { {
    QMetaObject::SuperData::link<QPushButton::staticMetaObject>(),
    qt_meta_stringdata_BreadcrumbButton.data,
    qt_meta_data_BreadcrumbButton,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *BreadcrumbButton::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *BreadcrumbButton::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_BreadcrumbButton.stringdata0))
        return static_cast<void*>(this);
    return QPushButton::qt_metacast(_clname);
}

int BreadcrumbButton::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QPushButton::qt_metacall(_c, _id, _a);
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
