/****************************************************************************
** Meta object code from reading C++ file 'canthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../canthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'canthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_canThread_t {
    QByteArrayData data[12];
    char stringdata0[101];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_canThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_canThread_t qt_meta_stringdata_canThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "canThread"
QT_MOC_LITERAL(1, 10, 10), // "send_speed"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "send_handle"
QT_MOC_LITERAL(4, 34, 9), // "send_gear"
QT_MOC_LITERAL(5, 44, 9), // "send_turn"
QT_MOC_LITERAL(6, 54, 8), // "send_end"
QT_MOC_LITERAL(7, 63, 7), // "get_dir"
QT_MOC_LITERAL(8, 71, 5), // "event"
QT_MOC_LITERAL(9, 77, 4), // "stop"
QT_MOC_LITERAL(10, 82, 11), // "hexToBinary"
QT_MOC_LITERAL(11, 94, 6) // "string"

    },
    "canThread\0send_speed\0\0send_handle\0"
    "send_gear\0send_turn\0send_end\0get_dir\0"
    "event\0stop\0hexToBinary\0string"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_canThread[] = {

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
       1,    1,   59,    2, 0x06 /* Public */,
       3,    2,   62,    2, 0x06 /* Public */,
       4,    1,   67,    2, 0x06 /* Public */,
       5,    1,   70,    2, 0x06 /* Public */,
       6,    0,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    1,   74,    2, 0x0a /* Public */,
       8,    0,   77,    2, 0x0a /* Public */,
       9,    0,   78,    2, 0x0a /* Public */,
      10,    2,   79,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    2,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    0x80000000 | 11, 0x80000000 | 11, QMetaType::Int,    2,    2,

       0        // eod
};

void canThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<canThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_speed((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->send_handle((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 2: _t->send_gear((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->send_turn((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->send_end(); break;
        case 5: _t->get_dir((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->event(); break;
        case 7: _t->stop(); break;
        case 8: { string _r = _t->hexToBinary((*reinterpret_cast< string(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2])));
            if (_a[0]) *reinterpret_cast< string*>(_a[0]) = std::move(_r); }  break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (canThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&canThread::send_speed)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (canThread::*)(QString , QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&canThread::send_handle)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (canThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&canThread::send_gear)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (canThread::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&canThread::send_turn)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (canThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&canThread::send_end)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject canThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_canThread.data,
    qt_meta_data_canThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *canThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *canThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_canThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int canThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void canThread::send_speed(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void canThread::send_handle(QString _t1, QString _t2)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void canThread::send_gear(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void canThread::send_turn(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void canThread::send_end()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
