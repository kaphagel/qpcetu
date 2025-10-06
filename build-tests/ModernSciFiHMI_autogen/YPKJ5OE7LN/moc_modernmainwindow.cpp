/****************************************************************************
** Meta object code from reading C++ file 'modernmainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/modernmainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modernmainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModernMainWindow_t {
    QByteArrayData data[15];
    char stringdata0[203];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModernMainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModernMainWindow_t qt_meta_stringdata_ModernMainWindow = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ModernMainWindow"
QT_MOC_LITERAL(1, 17, 14), // "navigateToPage"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 5), // "index"
QT_MOC_LITERAL(4, 39, 22), // "onControllerDiscovered"
QT_MOC_LITERAL(5, 62, 2), // "ip"
QT_MOC_LITERAL(6, 65, 4), // "data"
QT_MOC_LITERAL(7, 70, 24), // "onControllerCountChanged"
QT_MOC_LITERAL(8, 95, 5), // "count"
QT_MOC_LITERAL(9, 101, 18), // "updateSystemStatus"
QT_MOC_LITERAL(10, 120, 14), // "updateDateTime"
QT_MOC_LITERAL(11, 135, 21), // "showControllerDetails"
QT_MOC_LITERAL(12, 157, 18), // "refreshControllers"
QT_MOC_LITERAL(13, 176, 11), // "toggleTheme"
QT_MOC_LITERAL(14, 188, 14) // "onThemeChanged"

    },
    "ModernMainWindow\0navigateToPage\0\0index\0"
    "onControllerDiscovered\0ip\0data\0"
    "onControllerCountChanged\0count\0"
    "updateSystemStatus\0updateDateTime\0"
    "showControllerDetails\0refreshControllers\0"
    "toggleTheme\0onThemeChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModernMainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x0a /* Public */,
       4,    2,   62,    2, 0x0a /* Public */,
       7,    1,   67,    2, 0x0a /* Public */,
       9,    0,   70,    2, 0x08 /* Private */,
      10,    0,   71,    2, 0x08 /* Private */,
      11,    1,   72,    2, 0x08 /* Private */,
      12,    0,   75,    2, 0x08 /* Private */,
      13,    0,   76,    2, 0x08 /* Private */,
      14,    0,   77,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QByteArray,    5,    6,
    QMetaType::Void, QMetaType::Int,    8,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ModernMainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ModernMainWindow *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->navigateToPage((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onControllerDiscovered((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QByteArray(*)>(_a[2]))); break;
        case 2: _t->onControllerCountChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->updateSystemStatus(); break;
        case 4: _t->updateDateTime(); break;
        case 5: _t->showControllerDetails((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->refreshControllers(); break;
        case 7: _t->toggleTheme(); break;
        case 8: _t->onThemeChanged(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ModernMainWindow::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_ModernMainWindow.data,
    qt_meta_data_ModernMainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ModernMainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModernMainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ModernMainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int ModernMainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
