/****************************************************************************
** Meta object code from reading C++ file 'navigationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.17)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../src/navigation/navigationmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'navigationmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.17. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_NavigationManager_t {
    QByteArrayData data[45];
    char stringdata0[536];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationManager_t qt_meta_stringdata_NavigationManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "NavigationManager"
QT_MOC_LITERAL(1, 18, 11), // "pageChanged"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 6), // "PageId"
QT_MOC_LITERAL(4, 38, 8), // "fromPage"
QT_MOC_LITERAL(5, 47, 6), // "toPage"
QT_MOC_LITERAL(6, 54, 22), // "navigationStateChanged"
QT_MOC_LITERAL(7, 77, 18), // "breadcrumbsChanged"
QT_MOC_LITERAL(8, 96, 11), // "breadcrumbs"
QT_MOC_LITERAL(9, 108, 15), // "pageAboutToShow"
QT_MOC_LITERAL(10, 124, 6), // "pageId"
QT_MOC_LITERAL(11, 131, 10), // "parameters"
QT_MOC_LITERAL(12, 142, 9), // "pageShown"
QT_MOC_LITERAL(13, 152, 15), // "pageAboutToHide"
QT_MOC_LITERAL(14, 168, 10), // "pageHidden"
QT_MOC_LITERAL(15, 179, 15), // "navigationError"
QT_MOC_LITERAL(16, 195, 5), // "error"
QT_MOC_LITERAL(17, 201, 20), // "confirmationRequired"
QT_MOC_LITERAL(18, 222, 7), // "message"
QT_MOC_LITERAL(19, 230, 25), // "std::function<void(bool)>"
QT_MOC_LITERAL(20, 256, 8), // "callback"
QT_MOC_LITERAL(21, 265, 17), // "handlePageRequest"
QT_MOC_LITERAL(22, 283, 17), // "handleBackRequest"
QT_MOC_LITERAL(23, 301, 17), // "handleHomeRequest"
QT_MOC_LITERAL(24, 319, 20), // "onTransitionFinished"
QT_MOC_LITERAL(25, 340, 20), // "onConfirmationResult"
QT_MOC_LITERAL(26, 361, 9), // "confirmed"
QT_MOC_LITERAL(27, 371, 8), // "Overview"
QT_MOC_LITERAL(28, 380, 9), // "Dashboard"
QT_MOC_LITERAL(29, 390, 6), // "Graphs"
QT_MOC_LITERAL(30, 397, 8), // "Settings"
QT_MOC_LITERAL(31, 406, 11), // "UdpResponse"
QT_MOC_LITERAL(32, 418, 17), // "ControllerDetails"
QT_MOC_LITERAL(33, 436, 11), // "Diagnostics"
QT_MOC_LITERAL(34, 448, 6), // "Alarms"
QT_MOC_LITERAL(35, 455, 7), // "Reports"
QT_MOC_LITERAL(36, 463, 14), // "TransitionType"
QT_MOC_LITERAL(37, 478, 4), // "None"
QT_MOC_LITERAL(38, 483, 9), // "SlideLeft"
QT_MOC_LITERAL(39, 493, 10), // "SlideRight"
QT_MOC_LITERAL(40, 504, 7), // "SlideUp"
QT_MOC_LITERAL(41, 512, 9), // "SlideDown"
QT_MOC_LITERAL(42, 522, 4), // "Fade"
QT_MOC_LITERAL(43, 527, 4), // "Push"
QT_MOC_LITERAL(44, 532, 3) // "Pop"

    },
    "NavigationManager\0pageChanged\0\0PageId\0"
    "fromPage\0toPage\0navigationStateChanged\0"
    "breadcrumbsChanged\0breadcrumbs\0"
    "pageAboutToShow\0pageId\0parameters\0"
    "pageShown\0pageAboutToHide\0pageHidden\0"
    "navigationError\0error\0confirmationRequired\0"
    "message\0std::function<void(bool)>\0"
    "callback\0handlePageRequest\0handleBackRequest\0"
    "handleHomeRequest\0onTransitionFinished\0"
    "onConfirmationResult\0confirmed\0Overview\0"
    "Dashboard\0Graphs\0Settings\0UdpResponse\0"
    "ControllerDetails\0Diagnostics\0Alarms\0"
    "Reports\0TransitionType\0None\0SlideLeft\0"
    "SlideRight\0SlideUp\0SlideDown\0Fade\0"
    "Push\0Pop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationManager[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      15,   14, // methods
       0,    0, // properties
       2,  134, // enums/sets
       0,    0, // constructors
       0,       // flags
       9,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   89,    2, 0x06 /* Public */,
       6,    0,   94,    2, 0x06 /* Public */,
       7,    1,   95,    2, 0x06 /* Public */,
       9,    2,   98,    2, 0x06 /* Public */,
      12,    1,  103,    2, 0x06 /* Public */,
      13,    1,  106,    2, 0x06 /* Public */,
      14,    1,  109,    2, 0x06 /* Public */,
      15,    1,  112,    2, 0x06 /* Public */,
      17,    2,  115,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      21,    2,  120,    2, 0x0a /* Public */,
      21,    1,  125,    2, 0x2a /* Public | MethodCloned */,
      22,    0,  128,    2, 0x0a /* Public */,
      23,    0,  129,    2, 0x0a /* Public */,
      24,    0,  130,    2, 0x08 /* Private */,
      25,    1,  131,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3,    4,    5,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,    8,
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,   10,   11,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void, QMetaType::QString,   16,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 19,   18,   20,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3, QMetaType::QVariantMap,   10,   11,
    QMetaType::Void, 0x80000000 | 3,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,   26,

 // enums: name, alias, flags, count, data
       3,    3, 0x2,    9,  144,
      36,   36, 0x2,    8,  162,

 // enum data: key, value
      27, uint(NavigationManager::PageId::Overview),
      28, uint(NavigationManager::PageId::Dashboard),
      29, uint(NavigationManager::PageId::Graphs),
      30, uint(NavigationManager::PageId::Settings),
      31, uint(NavigationManager::PageId::UdpResponse),
      32, uint(NavigationManager::PageId::ControllerDetails),
      33, uint(NavigationManager::PageId::Diagnostics),
      34, uint(NavigationManager::PageId::Alarms),
      35, uint(NavigationManager::PageId::Reports),
      37, uint(NavigationManager::TransitionType::None),
      38, uint(NavigationManager::TransitionType::SlideLeft),
      39, uint(NavigationManager::TransitionType::SlideRight),
      40, uint(NavigationManager::TransitionType::SlideUp),
      41, uint(NavigationManager::TransitionType::SlideDown),
      42, uint(NavigationManager::TransitionType::Fade),
      43, uint(NavigationManager::TransitionType::Push),
      44, uint(NavigationManager::TransitionType::Pop),

       0        // eod
};

void NavigationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NavigationManager *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->pageChanged((*reinterpret_cast< PageId(*)>(_a[1])),(*reinterpret_cast< PageId(*)>(_a[2]))); break;
        case 1: _t->navigationStateChanged(); break;
        case 2: _t->breadcrumbsChanged((*reinterpret_cast< const QStringList(*)>(_a[1]))); break;
        case 3: _t->pageAboutToShow((*reinterpret_cast< PageId(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 4: _t->pageShown((*reinterpret_cast< PageId(*)>(_a[1]))); break;
        case 5: _t->pageAboutToHide((*reinterpret_cast< PageId(*)>(_a[1]))); break;
        case 6: _t->pageHidden((*reinterpret_cast< PageId(*)>(_a[1]))); break;
        case 7: _t->navigationError((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 8: _t->confirmationRequired((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< std::function<void(bool)>(*)>(_a[2]))); break;
        case 9: _t->handlePageRequest((*reinterpret_cast< PageId(*)>(_a[1])),(*reinterpret_cast< const QVariantMap(*)>(_a[2]))); break;
        case 10: _t->handlePageRequest((*reinterpret_cast< PageId(*)>(_a[1]))); break;
        case 11: _t->handleBackRequest(); break;
        case 12: _t->handleHomeRequest(); break;
        case 13: _t->onTransitionFinished(); break;
        case 14: _t->onConfirmationResult((*reinterpret_cast< bool(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavigationManager::*)(PageId , PageId );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::pageChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::navigationStateChanged)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(const QStringList & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::breadcrumbsChanged)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(PageId , const QVariantMap & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::pageAboutToShow)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(PageId );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::pageShown)) {
                *result = 4;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(PageId );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::pageAboutToHide)) {
                *result = 5;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(PageId );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::pageHidden)) {
                *result = 6;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::navigationError)) {
                *result = 7;
                return;
            }
        }
        {
            using _t = void (NavigationManager::*)(const QString & , std::function<void(bool)> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationManager::confirmationRequired)) {
                *result = 8;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NavigationManager::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NavigationManager.data,
    qt_meta_data_NavigationManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NavigationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationManager.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NavigationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 15)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 15;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 15)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 15;
    }
    return _id;
}

// SIGNAL 0
void NavigationManager::pageChanged(PageId _t1, PageId _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void NavigationManager::navigationStateChanged()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NavigationManager::breadcrumbsChanged(const QStringList & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void NavigationManager::pageAboutToShow(PageId _t1, const QVariantMap & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void NavigationManager::pageShown(PageId _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void NavigationManager::pageAboutToHide(PageId _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void NavigationManager::pageHidden(PageId _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void NavigationManager::navigationError(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void NavigationManager::confirmationRequired(const QString & _t1, std::function<void(bool)> _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}
struct qt_meta_stringdata_NavigationCommand_t {
    QByteArrayData data[6];
    char stringdata0[48];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_NavigationCommand_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_NavigationCommand_t qt_meta_stringdata_NavigationCommand = {
    {
QT_MOC_LITERAL(0, 0, 17), // "NavigationCommand"
QT_MOC_LITERAL(1, 18, 8), // "executed"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 6), // "undone"
QT_MOC_LITERAL(4, 35, 6), // "failed"
QT_MOC_LITERAL(5, 42, 5) // "error"

    },
    "NavigationCommand\0executed\0\0undone\0"
    "failed\0error"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_NavigationCommand[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       3,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,
       4,    1,   31,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    5,

       0        // eod
};

void NavigationCommand::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<NavigationCommand *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->executed(); break;
        case 1: _t->undone(); break;
        case 2: _t->failed((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (NavigationCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationCommand::executed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (NavigationCommand::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationCommand::undone)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (NavigationCommand::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&NavigationCommand::failed)) {
                *result = 2;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject NavigationCommand::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_NavigationCommand.data,
    qt_meta_data_NavigationCommand,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *NavigationCommand::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *NavigationCommand::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_NavigationCommand.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int NavigationCommand::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void NavigationCommand::executed()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void NavigationCommand::undone()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}

// SIGNAL 2
void NavigationCommand::failed(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
