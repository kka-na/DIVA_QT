/****************************************************************************
** Meta object code from reading C++ file 'lidarthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../lidarthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lidarthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lidarThread_t {
    QByteArrayData data[6];
    char stringdata0[77];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lidarThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lidarThread_t qt_meta_stringdata_lidarThread = {
    {
QT_MOC_LITERAL(0, 0, 11), // "lidarThread"
QT_MOC_LITERAL(1, 12, 10), // "send_lidar"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 35), // "pcl::PointCloud<pcl::PointXYZ..."
QT_MOC_LITERAL(4, 60, 11), // "connectedOK"
QT_MOC_LITERAL(5, 72, 4) // "stop"

    },
    "lidarThread\0send_lidar\0\0"
    "pcl::PointCloud<pcl::PointXYZ>::Ptr\0"
    "connectedOK\0stop"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lidarThread[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,
       4,    0,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   33,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void lidarThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<lidarThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_lidar((*reinterpret_cast< pcl::PointCloud<pcl::PointXYZ>::Ptr(*)>(_a[1]))); break;
        case 1: _t->connectedOK(); break;
        case 2: _t->stop(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (lidarThread::*)(pcl::PointCloud<pcl::PointXYZ>::Ptr );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lidarThread::send_lidar)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (lidarThread::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&lidarThread::connectedOK)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lidarThread::staticMetaObject = { {
    &QThread::staticMetaObject,
    qt_meta_stringdata_lidarThread.data,
    qt_meta_data_lidarThread,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lidarThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lidarThread::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lidarThread.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int lidarThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void lidarThread::send_lidar(pcl::PointCloud<pcl::PointXYZ>::Ptr _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void lidarThread::connectedOK()
{
    QMetaObject::activate(this, &staticMetaObject, 1, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE