/****************************************************************************
** Meta object code from reading C++ file 'thememanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/ui/thememanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'thememanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThemeManager_t {
    QByteArrayData data[32];
    char stringdata0[377];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThemeManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThemeManager_t qt_meta_stringdata_ThemeManager = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ThemeManager"
QT_MOC_LITERAL(1, 13, 12), // "themeChanged"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 5), // "Theme"
QT_MOC_LITERAL(4, 33, 8), // "newTheme"
QT_MOC_LITERAL(5, 42, 5), // "Light"
QT_MOC_LITERAL(6, 48, 4), // "Dark"
QT_MOC_LITERAL(7, 53, 9), // "ColorRole"
QT_MOC_LITERAL(8, 63, 14), // "MainBackground"
QT_MOC_LITERAL(9, 78, 19), // "SecondaryBackground"
QT_MOC_LITERAL(10, 98, 16), // "HeaderBackground"
QT_MOC_LITERAL(11, 115, 14), // "CardBackground"
QT_MOC_LITERAL(12, 130, 21), // "StatusStripBackground"
QT_MOC_LITERAL(13, 152, 11), // "PrimaryText"
QT_MOC_LITERAL(14, 164, 13), // "SecondaryText"
QT_MOC_LITERAL(15, 178, 10), // "AccentText"
QT_MOC_LITERAL(16, 189, 10), // "StatusText"
QT_MOC_LITERAL(17, 200, 7), // "Primary"
QT_MOC_LITERAL(18, 208, 7), // "Success"
QT_MOC_LITERAL(19, 216, 7), // "Warning"
QT_MOC_LITERAL(20, 224, 5), // "Error"
QT_MOC_LITERAL(21, 230, 16), // "ButtonBackground"
QT_MOC_LITERAL(22, 247, 11), // "ButtonHover"
QT_MOC_LITERAL(23, 259, 13), // "ButtonPressed"
QT_MOC_LITERAL(24, 273, 11), // "BorderColor"
QT_MOC_LITERAL(25, 285, 10), // "FocusColor"
QT_MOC_LITERAL(26, 296, 16), // "ControllerActive"
QT_MOC_LITERAL(27, 313, 18), // "ControllerInactive"
QT_MOC_LITERAL(28, 332, 15), // "ControllerFault"
QT_MOC_LITERAL(29, 348, 8), // "DataGood"
QT_MOC_LITERAL(30, 357, 9), // "DataStale"
QT_MOC_LITERAL(31, 367, 9) // "DataError"

    },
    "ThemeManager\0themeChanged\0\0Theme\0"
    "newTheme\0Light\0Dark\0ColorRole\0"
    "MainBackground\0SecondaryBackground\0"
    "HeaderBackground\0CardBackground\0"
    "StatusStripBackground\0PrimaryText\0"
    "SecondaryText\0AccentText\0StatusText\0"
    "Primary\0Success\0Warning\0Error\0"
    "ButtonBackground\0ButtonHover\0ButtonPressed\0"
    "BorderColor\0FocusColor\0ControllerActive\0"
    "ControllerInactive\0ControllerFault\0"
    "DataGood\0DataStale\0DataError"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThemeManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       2,   22, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   19,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // enums: name, alias, flags, count, data
       3,    3, 0x0,    2,   32,
       7,    7, 0x0,   24,   36,

 // enum data: key, value
       5, uint(ThemeManager::Light),
       6, uint(ThemeManager::Dark),
       8, uint(ThemeManager::MainBackground),
       9, uint(ThemeManager::SecondaryBackground),
      10, uint(ThemeManager::HeaderBackground),
      11, uint(ThemeManager::CardBackground),
      12, uint(ThemeManager::StatusStripBackground),
      13, uint(ThemeManager::PrimaryText),
      14, uint(ThemeManager::SecondaryText),
      15, uint(ThemeManager::AccentText),
      16, uint(ThemeManager::StatusText),
      17, uint(ThemeManager::Primary),
      18, uint(ThemeManager::Success),
      19, uint(ThemeManager::Warning),
      20, uint(ThemeManager::Error),
      21, uint(ThemeManager::ButtonBackground),
      22, uint(ThemeManager::ButtonHover),
      23, uint(ThemeManager::ButtonPressed),
      24, uint(ThemeManager::BorderColor),
      25, uint(ThemeManager::FocusColor),
      26, uint(ThemeManager::ControllerActive),
      27, uint(ThemeManager::ControllerInactive),
      28, uint(ThemeManager::ControllerFault),
      29, uint(ThemeManager::DataGood),
      30, uint(ThemeManager::DataStale),
      31, uint(ThemeManager::DataError),

       0        // eod
};

void ThemeManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThemeManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->themeChanged((*reinterpret_cast< Theme(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThemeManager::*)(Theme );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThemeManager::themeChanged)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThemeManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_ThemeManager.data,
    qt_meta_data_ThemeManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThemeManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThemeManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThemeManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ThemeManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
    return _id;
}

// SIGNAL 0
void ThemeManager::themeChanged(Theme _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
