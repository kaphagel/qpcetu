/****************************************************************************
** Meta object code from reading C++ file 'thememanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
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
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThemeManager_t {
    QByteArrayData data[35];
    char stringdata0[411];
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
QT_MOC_LITERAL(5, 42, 4), // "Dark"
QT_MOC_LITERAL(6, 47, 5), // "Light"
QT_MOC_LITERAL(7, 53, 12), // "HighContrast"
QT_MOC_LITERAL(8, 66, 10), // "AppleLight"
QT_MOC_LITERAL(9, 77, 9), // "AppleDark"
QT_MOC_LITERAL(10, 87, 9), // "ColorRole"
QT_MOC_LITERAL(11, 97, 14), // "MainBackground"
QT_MOC_LITERAL(12, 112, 19), // "SecondaryBackground"
QT_MOC_LITERAL(13, 132, 16), // "HeaderBackground"
QT_MOC_LITERAL(14, 149, 14), // "CardBackground"
QT_MOC_LITERAL(15, 164, 21), // "StatusStripBackground"
QT_MOC_LITERAL(16, 186, 11), // "PrimaryText"
QT_MOC_LITERAL(17, 198, 13), // "SecondaryText"
QT_MOC_LITERAL(18, 212, 10), // "AccentText"
QT_MOC_LITERAL(19, 223, 10), // "StatusText"
QT_MOC_LITERAL(20, 234, 7), // "Primary"
QT_MOC_LITERAL(21, 242, 7), // "Success"
QT_MOC_LITERAL(22, 250, 7), // "Warning"
QT_MOC_LITERAL(23, 258, 5), // "Error"
QT_MOC_LITERAL(24, 264, 16), // "ButtonBackground"
QT_MOC_LITERAL(25, 281, 11), // "ButtonHover"
QT_MOC_LITERAL(26, 293, 13), // "ButtonPressed"
QT_MOC_LITERAL(27, 307, 11), // "BorderColor"
QT_MOC_LITERAL(28, 319, 10), // "FocusColor"
QT_MOC_LITERAL(29, 330, 16), // "ControllerActive"
QT_MOC_LITERAL(30, 347, 18), // "ControllerInactive"
QT_MOC_LITERAL(31, 366, 15), // "ControllerFault"
QT_MOC_LITERAL(32, 382, 8), // "DataGood"
QT_MOC_LITERAL(33, 391, 9), // "DataStale"
QT_MOC_LITERAL(34, 401, 9) // "DataError"

    },
    "ThemeManager\0themeChanged\0\0Theme\0"
    "newTheme\0Dark\0Light\0HighContrast\0"
    "AppleLight\0AppleDark\0ColorRole\0"
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
       3,    3, 0x0,    5,   32,
      10,   10, 0x0,   24,   42,

 // enum data: key, value
       5, uint(ThemeManager::Dark),
       6, uint(ThemeManager::Light),
       7, uint(ThemeManager::HighContrast),
       8, uint(ThemeManager::AppleLight),
       9, uint(ThemeManager::AppleDark),
      11, uint(ThemeManager::MainBackground),
      12, uint(ThemeManager::SecondaryBackground),
      13, uint(ThemeManager::HeaderBackground),
      14, uint(ThemeManager::CardBackground),
      15, uint(ThemeManager::StatusStripBackground),
      16, uint(ThemeManager::PrimaryText),
      17, uint(ThemeManager::SecondaryText),
      18, uint(ThemeManager::AccentText),
      19, uint(ThemeManager::StatusText),
      20, uint(ThemeManager::Primary),
      21, uint(ThemeManager::Success),
      22, uint(ThemeManager::Warning),
      23, uint(ThemeManager::Error),
      24, uint(ThemeManager::ButtonBackground),
      25, uint(ThemeManager::ButtonHover),
      26, uint(ThemeManager::ButtonPressed),
      27, uint(ThemeManager::BorderColor),
      28, uint(ThemeManager::FocusColor),
      29, uint(ThemeManager::ControllerActive),
      30, uint(ThemeManager::ControllerInactive),
      31, uint(ThemeManager::ControllerFault),
      32, uint(ThemeManager::DataGood),
      33, uint(ThemeManager::DataStale),
      34, uint(ThemeManager::DataError),

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
