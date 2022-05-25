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
    QByteArrayData data[13];
    char stringdata0[268];
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
QT_MOC_LITERAL(12, 241, 26) // "on_actionRestore_triggered"

    },
    "root\0listItemClicked\0\0QModelIndex\0"
    "index\0on_actionInsert_triggered\0"
    "on_actionImport_data_from_file_triggered\0"
    "on_actionClear_triggered\0"
    "on_actionDelete_triggered\0"
    "on_actionEdit_triggered\0"
    "on_actionSearch_Item_triggered\0"
    "on_actionTransfer_triggered\0"
    "on_actionRestore_triggered"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_root[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   59,    2, 0x08 /* Private */,
       5,    0,   62,    2, 0x08 /* Private */,
       6,    0,   63,    2, 0x08 /* Private */,
       7,    0,   64,    2, 0x08 /* Private */,
       8,    0,   65,    2, 0x08 /* Private */,
       9,    0,   66,    2, 0x08 /* Private */,
      10,    0,   67,    2, 0x08 /* Private */,
      11,    0,   68,    2, 0x08 /* Private */,
      12,    0,   69,    2, 0x08 /* Private */,

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
QT_WARNING_POP
QT_END_MOC_NAMESPACE
