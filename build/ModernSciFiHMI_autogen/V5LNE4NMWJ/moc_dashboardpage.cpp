/****************************************************************************
** Meta object code from reading C++ file 'dashboardpage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/pages/dashboardpage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'dashboardpage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DashboardPage_t {
    QByteArrayData data[22];
    char stringdata0[387];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DashboardPage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DashboardPage_t qt_meta_stringdata_DashboardPage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "DashboardPage"
QT_MOC_LITERAL(1, 14, 19), // "onEnergyCoreUpdated"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 5), // "value"
QT_MOC_LITERAL(4, 41, 21), // "onShieldMatrixUpdated"
QT_MOC_LITERAL(5, 63, 21), // "onEngineThrustUpdated"
QT_MOC_LITERAL(6, 85, 20), // "onWeaponArrayUpdated"
QT_MOC_LITERAL(7, 106, 25), // "onSystemParametersUpdated"
QT_MOC_LITERAL(8, 132, 36), // "DashboardViewModel::SystemPar..."
QT_MOC_LITERAL(9, 169, 6), // "params"
QT_MOC_LITERAL(10, 176, 23), // "onNavigationDataUpdated"
QT_MOC_LITERAL(11, 200, 34), // "DashboardViewModel::Navigatio..."
QT_MOC_LITERAL(12, 235, 4), // "data"
QT_MOC_LITERAL(13, 240, 21), // "onSystemStatusChanged"
QT_MOC_LITERAL(14, 262, 32), // "DashboardViewModel::SystemStatus"
QT_MOC_LITERAL(15, 295, 6), // "status"
QT_MOC_LITERAL(16, 302, 7), // "message"
QT_MOC_LITERAL(17, 310, 13), // "onTimeUpdated"
QT_MOC_LITERAL(18, 324, 9), // "timestamp"
QT_MOC_LITERAL(19, 334, 16), // "onAlertGenerated"
QT_MOC_LITERAL(20, 351, 25), // "onConnectionStatusChanged"
QT_MOC_LITERAL(21, 377, 9) // "connected"

    },
    "DashboardPage\0onEnergyCoreUpdated\0\0"
    "value\0onShieldMatrixUpdated\0"
    "onEngineThrustUpdated\0onWeaponArrayUpdated\0"
    "onSystemParametersUpdated\0"
    "DashboardViewModel::SystemParameters\0"
    "params\0onNavigationDataUpdated\0"
    "DashboardViewModel::NavigationData\0"
    "data\0onSystemStatusChanged\0"
    "DashboardViewModel::SystemStatus\0"
    "status\0message\0onTimeUpdated\0timestamp\0"
    "onAlertGenerated\0onConnectionStatusChanged\0"
    "connected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DashboardPage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x08 /* Private */,
       4,    1,   67,    2, 0x08 /* Private */,
       5,    1,   70,    2, 0x08 /* Private */,
       6,    1,   73,    2, 0x08 /* Private */,
       7,    1,   76,    2, 0x08 /* Private */,
      10,    1,   79,    2, 0x08 /* Private */,
      13,    2,   82,    2, 0x08 /* Private */,
      17,    1,   87,    2, 0x08 /* Private */,
      19,    1,   90,    2, 0x08 /* Private */,
      20,    2,   93,    2, 0x08 /* Private */,

 // slots: parameters
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

       0        // eod
};

void DashboardPage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DashboardPage *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->onEnergyCoreUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->onShieldMatrixUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->onEngineThrustUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->onWeaponArrayUpdated((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->onSystemParametersUpdated((*reinterpret_cast< const DashboardViewModel::SystemParameters(*)>(_a[1]))); break;
        case 5: _t->onNavigationDataUpdated((*reinterpret_cast< const DashboardViewModel::NavigationData(*)>(_a[1]))); break;
        case 6: _t->onSystemStatusChanged((*reinterpret_cast< DashboardViewModel::SystemStatus(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 7: _t->onTimeUpdated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->onAlertGenerated((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 9: _t->onConnectionStatusChanged((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DashboardPage::staticMetaObject = { {
    QMetaObject::SuperData::link<QWidget::staticMetaObject>(),
    qt_meta_stringdata_DashboardPage.data,
    qt_meta_data_DashboardPage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DashboardPage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DashboardPage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DashboardPage.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int DashboardPage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
