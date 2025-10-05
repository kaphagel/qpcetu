/****************************************************************************
** Meta object code from reading C++ file 'dragdroppage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../src/pages/dragdroppage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dragdroppage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DraggableRectangle_t {
    QByteArrayData data[1];
    char stringdata0[19];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DraggableRectangle_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DraggableRectangle_t qt_meta_stringdata_DraggableRectangle = {
    {
QT_MOC_LITERAL(0, 0, 18) // "DraggableRectangle"

    },
    "DraggableRectangle"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DraggableRectangle[] = {

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

void DraggableRectangle::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject DraggableRectangle::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DraggableRectangle.data,
    qt_meta_data_DraggableRectangle,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DraggableRectangle::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DraggableRectangle::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DraggableRectangle.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DraggableRectangle::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DropZone_t {
    QByteArrayData data[1];
    char stringdata0[9];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DropZone_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DropZone_t qt_meta_stringdata_DropZone = {
    {
QT_MOC_LITERAL(0, 0, 8) // "DropZone"

    },
    "DropZone"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DropZone[] = {

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

void DropZone::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    (void)_o;
    (void)_id;
    (void)_c;
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject DropZone::staticMetaObject = { {
    QMetaObject::SuperData::link<QFrame::staticMetaObject>(),
    qt_meta_stringdata_DropZone.data,
    qt_meta_data_DropZone,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DropZone::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DropZone::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DropZone.stringdata0))
        return static_cast<void*>(this);
    return QFrame::qt_metacast(_clname);
}

int DropZone::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QFrame::qt_metacall(_c, _id, _a);
    return _id;
}
struct qt_meta_stringdata_DragDropPage_t {
    QByteArrayData data[5];
    char stringdata0[62];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DragDropPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DragDropPage_t qt_meta_stringdata_DragDropPage = {
    {
QT_MOC_LITERAL(0, 0, 12), // "DragDropPage"
QT_MOC_LITERAL(1, 13, 13), // "backRequested"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 18), // "createNewRectangle"
QT_MOC_LITERAL(4, 47, 14) // "clearDropZones"

    },
    "DragDropPage\0backRequested\0\0"
    "createNewRectangle\0clearDropZones"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DragDropPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   30,    2, 0x08 /* Private */,
       4,    0,   31,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void DragDropPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DragDropPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->backRequested(); break;
        case 1: _t->createNewRectangle(); break;
        case 2: _t->clearDropZones(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DragDropPage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DragDropPage::backRequested)) {
                *result = 0;
                return;
            }
        }
    }
    (void)_a;
}

QT_INIT_METAOBJECT const QMetaObject DragDropPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DragDropPage.data,
    qt_meta_data_DragDropPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DragDropPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DragDropPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DragDropPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DragDropPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void DragDropPage::backRequested()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
