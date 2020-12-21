/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.5)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.5. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[24];
    char stringdata0[341];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 8), // "send_pcd"
QT_MOC_LITERAL(2, 20, 0), // ""
QT_MOC_LITERAL(3, 21, 8), // "send_imu"
QT_MOC_LITERAL(4, 30, 16), // "display_gps_info"
QT_MOC_LITERAL(5, 47, 8), // "latitude"
QT_MOC_LITERAL(6, 56, 9), // "longitude"
QT_MOC_LITERAL(7, 66, 16), // "display_can_info"
QT_MOC_LITERAL(8, 83, 6), // "handle"
QT_MOC_LITERAL(9, 90, 19), // "handle_acceleration"
QT_MOC_LITERAL(10, 110, 19), // "gps_view_initialize"
QT_MOC_LITERAL(11, 130, 11), // "display_cam"
QT_MOC_LITERAL(12, 142, 5), // "image"
QT_MOC_LITERAL(13, 148, 12), // "speedChanged"
QT_MOC_LITERAL(14, 161, 5), // "value"
QT_MOC_LITERAL(15, 167, 21), // "Initializing_for_Live"
QT_MOC_LITERAL(16, 189, 25), // "Initializing_for_Playback"
QT_MOC_LITERAL(17, 215, 11), // "initial_map"
QT_MOC_LITERAL(18, 227, 13), // "get_log_token"
QT_MOC_LITERAL(19, 241, 21), // "on_pushButton_clicked"
QT_MOC_LITERAL(20, 263, 22), // "on_label_3_itemClicked"
QT_MOC_LITERAL(21, 286, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(22, 303, 4), // "item"
QT_MOC_LITERAL(23, 308, 32) // "on_actionStroing_To_DB_triggered"

    },
    "MainWindow\0send_pcd\0\0send_imu\0"
    "display_gps_info\0latitude\0longitude\0"
    "display_can_info\0handle\0handle_acceleration\0"
    "gps_view_initialize\0display_cam\0image\0"
    "speedChanged\0value\0Initializing_for_Live\0"
    "Initializing_for_Playback\0initial_map\0"
    "get_log_token\0on_pushButton_clicked\0"
    "on_label_3_itemClicked\0QListWidgetItem*\0"
    "item\0on_actionStroing_To_DB_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,
       3,    3,   87,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    2,   94,    2, 0x0a /* Public */,
       7,    2,   99,    2, 0x0a /* Public */,
      10,    0,  104,    2, 0x0a /* Public */,
      11,    1,  105,    2, 0x0a /* Public */,
      13,    1,  108,    2, 0x0a /* Public */,
      15,    0,  111,    2, 0x08 /* Private */,
      16,    0,  112,    2, 0x08 /* Private */,
      17,    0,  113,    2, 0x08 /* Private */,
      18,    0,  114,    2, 0x08 /* Private */,
      19,    0,  115,    2, 0x08 /* Private */,
      20,    1,  116,    2, 0x08 /* Private */,
      23,    0,  119,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Float, QMetaType::Float, QMetaType::Float,    2,    2,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    5,    6,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QImage,   12,
    QMetaType::Void, QMetaType::Int,   14,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 21,   22,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->send_pcd((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->send_imu((*reinterpret_cast< float(*)>(_a[1])),(*reinterpret_cast< float(*)>(_a[2])),(*reinterpret_cast< float(*)>(_a[3]))); break;
        case 2: _t->display_gps_info((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 3: _t->display_can_info((*reinterpret_cast< QString(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2]))); break;
        case 4: _t->gps_view_initialize(); break;
        case 5: _t->display_cam((*reinterpret_cast< QImage(*)>(_a[1]))); break;
        case 6: _t->speedChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 7: _t->Initializing_for_Live(); break;
        case 8: _t->Initializing_for_Playback(); break;
        case 9: _t->initial_map(); break;
        case 10: _t->get_log_token(); break;
        case 11: _t->on_pushButton_clicked(); break;
        case 12: _t->on_label_3_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 13: _t->on_actionStroing_To_DB_triggered(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (MainWindow::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::send_pcd)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (MainWindow::*)(float , float , float );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&MainWindow::send_imu)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject MainWindow::staticMetaObject = { {
    &QMainWindow::staticMetaObject,
    qt_meta_stringdata_MainWindow.data,
    qt_meta_data_MainWindow,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::send_pcd(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void MainWindow::send_imu(float _t1, float _t2, float _t3)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
