/****************************************************************************
** Meta object code from reading C++ file 'mockudpservice.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../../tests/mocks/mockudpservice.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mockudpservice.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MockUdpService_t {
    QByteArrayData data[16];
    char stringdata0[190];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MockUdpService_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MockUdpService_t qt_meta_stringdata_MockUdpService = {
    {
QT_MOC_LITERAL(0, 0, 14), // "MockUdpService"
QT_MOC_LITERAL(1, 15, 16), // "responseReceived"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 4), // "data"
QT_MOC_LITERAL(4, 38, 12), // "QHostAddress"
QT_MOC_LITERAL(5, 51, 6), // "sender"
QT_MOC_LITERAL(6, 58, 13), // "broadcastSent"
QT_MOC_LITERAL(7, 72, 13), // "errorOccurred"
QT_MOC_LITERAL(8, 86, 5), // "error"
QT_MOC_LITERAL(9, 92, 16), // "listeningStarted"
QT_MOC_LITERAL(10, 109, 4), // "port"
QT_MOC_LITERAL(11, 114, 16), // "listeningStopped"
QT_MOC_LITERAL(12, 131, 14), // "startListening"
QT_MOC_LITERAL(13, 146, 13), // "stopListening"
QT_MOC_LITERAL(14, 160, 13), // "sendBroadcast"
QT_MOC_LITERAL(15, 174, 15) // "onResponseTimer"

    },
    "MockUdpService\0responseReceived\0\0data\0"
    "QHostAddress\0sender\0broadcastSent\0"
    "errorOccurred\0error\0listeningStarted\0"
    "port\0listeningStopped\0startListening\0"
    "stopListening\0sendBroadcast\0onResponseTimer"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MockUdpService[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    2,   59,    2, 0x06 /* Public */,
       6,    1,   64,    2, 0x06 /* Public */,
       7,    1,   67,    2, 0x06 /* Public */,
       9,    1,   70,    2, 0x06 /* Public */,
      11,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   74,    2, 0x0a /* Public */,
      13,    0,   75,    2, 0x0a /* Public */,
      14,    1,   76,    2, 0x0a /* Public */,
      15,    0,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QByteArray, 0x80000000 | 4,    3,    5,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void, QMetaType::QString,    8,
    QMetaType::Void, QMetaType::UShort,   10,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    3,
    QMetaType::Void,

       0        // eod
};

void MockUdpService::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MockUdpService *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->responseReceived((*reinterpret_cast< const QByteArray(*)>(_a[1])),(*reinterpret_cast< const QHostAddress(*)>(_a[2]))); break;
        case 1: _t->broadcastSent((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 2: _t->errorOccurred((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->listeningStarted((*reinterpret_cast< quint16(*)>(_a[1]))); break;
        case 4: _t->listeningStopped(); break;
        case 5: _t->startListening(); break;
        case 6: _t->stopListening(); break;
        case 7: _t->sendBroadcast((*reinterpret_cast< const QByteArray(*)>(_a[1]))); break;
        case 8: _t->onResponseTimer(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MockUdpService::*)(const QByteArray & , const QHostAddress & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockUdpService::responseReceived)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MockUdpService::*)(const QByteArray & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockUdpService::broadcastSent)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (MockUdpService::*)(const QString & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockUdpService::errorOccurred)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (MockUdpService::*)(quint16 );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockUdpService::listeningStarted)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (MockUdpService::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MockUdpService::listeningStopped)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MockUdpService::staticMetaObject = { {
    QMetaObject::SuperData::link<QObject::staticMetaObject>(),
    qt_meta_stringdata_MockUdpService.data,
    qt_meta_data_MockUdpService,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MockUdpService::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MockUdpService::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MockUdpService.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int MockUdpService::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void MockUdpService::responseReceived(const QByteArray & _t1, const QHostAddress & _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))), const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t2))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MockUdpService::broadcastSent(const QByteArray & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void MockUdpService::errorOccurred(const QString & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void MockUdpService::listeningStarted(quint16 _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void MockUdpService::listeningStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
