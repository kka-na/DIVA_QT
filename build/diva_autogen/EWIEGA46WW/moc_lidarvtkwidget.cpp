/****************************************************************************
** Meta object code from reading C++ file 'lidarvtkwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../lidarvtkwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'lidarvtkwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_lidarVTKWidget_t {
    QByteArrayData data[7];
    char stringdata0[92];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_lidarVTKWidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_lidarVTKWidget_t qt_meta_stringdata_lidarVTKWidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "lidarVTKWidget"
QT_MOC_LITERAL(1, 15, 13), // "display_lidar"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 35), // "pcl::PointCloud<pcl::PointXYZ..."
QT_MOC_LITERAL(4, 66, 11), // "display_pcd"
QT_MOC_LITERAL(5, 78, 8), // "fileName"
QT_MOC_LITERAL(6, 87, 4) // "init"

    },
    "lidarVTKWidget\0display_lidar\0\0"
    "pcl::PointCloud<pcl::PointXYZ>::Ptr\0"
    "display_pcd\0fileName\0init"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_lidarVTKWidget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x0a /* Public */,
       4,    1,   32,    2, 0x0a /* Public */,
       6,    0,   35,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::QString,    5,
    QMetaType::Void,

       0        // eod
};

void lidarVTKWidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<lidarVTKWidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->display_lidar((*reinterpret_cast< pcl::PointCloud<pcl::PointXYZ>::Ptr(*)>(_a[1]))); break;
        case 1: _t->display_pcd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->init(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject lidarVTKWidget::staticMetaObject = { {
    &QVTKWidget::staticMetaObject,
    qt_meta_stringdata_lidarVTKWidget.data,
    qt_meta_data_lidarVTKWidget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *lidarVTKWidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *lidarVTKWidget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_lidarVTKWidget.stringdata0))
        return static_cast<void*>(this);
    return QVTKWidget::qt_metacast(_clname);
}

int lidarVTKWidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QVTKWidget::qt_metacall(_c, _id, _a);
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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
