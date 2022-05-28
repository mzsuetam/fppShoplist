/****************************************************************************
** Meta object code from reading C++ file 'root.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../root.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'root.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_root_t {
    QByteArrayData data[17];
    char stringdata0[383];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_root_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_root_t qt_meta_stringdata_root = {
    {
QT_MOC_LITERAL(0, 0, 4), // "root"
QT_MOC_LITERAL(1, 5, 15), // "listItemClicked"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 11), // "QModelIndex"
QT_MOC_LITERAL(4, 34, 5), // "index"
QT_MOC_LITERAL(5, 40, 25), // "on_actionInsert_triggered"
QT_MOC_LITERAL(6, 66, 40), // "on_actionImport_data_from_fil..."
QT_MOC_LITERAL(7, 107, 24), // "on_actionClear_triggered"
QT_MOC_LITERAL(8, 132, 25), // "on_actionDelete_triggered"
QT_MOC_LITERAL(9, 158, 23), // "on_actionEdit_triggered"
QT_MOC_LITERAL(10, 182, 30), // "on_actionSearch_Item_triggered"
QT_MOC_LITERAL(11, 213, 27), // "on_actionTransfer_triggered"
QT_MOC_LITERAL(12, 241, 26), // "on_actionRestore_triggered"
QT_MOC_LITERAL(13, 268, 25), // "on_actionBackup_triggered"
QT_MOC_LITERAL(14, 294, 24), // "on_actionAbout_triggered"
QT_MOC_LITERAL(15, 319, 28), // "on_actionShortcuts_triggered"
QT_MOC_LITERAL(16, 348, 34) // "on_actionSearch_for_Host_trig..."

    },
    "root\0listItemClicked\0\0QModelIndex\0"
    "index\0on_actionInsert_triggered\0"
    "on_actionImport_data_from_file_triggered\0"
    "on_actionClear_triggered\0"
    "on_actionDelete_triggered\0"
    "on_actionEdit_triggered\0"
    "on_actionSearch_Item_triggered\0"
    "on_actionTransfer_triggered\0"
    "on_actionRestore_triggered\0"
    "on_actionBackup_triggered\0"
    "on_actionAbout_triggered\0"
    "on_actionShortcuts_triggered\0"
    "on_actionSearch_for_Host_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_root[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      13,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   79,    2, 0x08 /* Private */,
       5,    0,   82,    2, 0x08 /* Private */,
       6,    0,   83,    2, 0x08 /* Private */,
       7,    0,   84,    2, 0x08 /* Private */,
       8,    0,   85,    2, 0x08 /* Private */,
       9,    0,   86,    2, 0x08 /* Private */,
      10,    0,   87,    2, 0x08 /* Private */,
      11,    0,   88,    2, 0x08 /* Private */,
      12,    0,   89,    2, 0x08 /* Private */,
      13,    0,   90,    2, 0x08 /* Private */,
      14,    0,   91,    2, 0x08 /* Private */,
      15,    0,   92,    2, 0x08 /* Private */,
      16,    0,   93,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void root::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<root *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->listItemClicked((*reinterpret_cast< const QModelIndex(*)>(_a[1]))); break;
        case 1: _t->on_actionInsert_triggered(); break;
        case 2: _t->on_actionImport_data_from_file_triggered(); break;
        case 3: _t->on_actionClear_triggered(); break;
        case 4: _t->on_actionDelete_triggered(); break;
        case 5: _t->on_actionEdit_triggered(); break;
        case 6: _t->on_actionSearch_Item_triggered(); break;
        case 7: _t->on_actionTransfer_triggered(); break;
        case 8: _t->on_actionRestore_triggered(); break;
        case 9: _t->on_actionBackup_triggered(); break;
        case 10: _t->on_actionAbout_triggered(); break;
        case 11: _t->on_actionShortcuts_triggered(); break;
        case 12: _t->on_actionSearch_for_Host_triggered(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject root::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_root.data,
    qt_meta_data_root,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *root::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *root::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_root.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int root::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 13)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 13;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 13)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 13;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
