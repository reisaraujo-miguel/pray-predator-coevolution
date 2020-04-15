/****************************************************************************
** Meta object code from reading C++ file 'widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../realTimePlotter/widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_Widget_t {
    QByteArrayData data[16];
    char stringdata0[300];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Widget_t qt_meta_stringdata_Widget = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Widget"
QT_MOC_LITERAL(1, 7, 23), // "on_importButton_clicked"
QT_MOC_LITERAL(2, 31, 0), // ""
QT_MOC_LITERAL(3, 32, 19), // "on_herbDisp_clicked"
QT_MOC_LITERAL(4, 52, 7), // "checked"
QT_MOC_LITERAL(5, 60, 19), // "on_herbMean_clicked"
QT_MOC_LITERAL(6, 80, 18), // "on_herbFit_clicked"
QT_MOC_LITERAL(7, 99, 19), // "on_carnDisp_clicked"
QT_MOC_LITERAL(8, 119, 19), // "on_carnMean_clicked"
QT_MOC_LITERAL(9, 139, 18), // "on_carnFit_clicked"
QT_MOC_LITERAL(10, 158, 25), // "on_updateCheckBox_clicked"
QT_MOC_LITERAL(11, 184, 11), // "timeOutSlot"
QT_MOC_LITERAL(12, 196, 32), // "on_interval1SpinBox_valueChanged"
QT_MOC_LITERAL(13, 229, 4), // "arg1"
QT_MOC_LITERAL(14, 234, 32), // "on_interval2SpinBox_valueChanged"
QT_MOC_LITERAL(15, 267, 32) // "on_interval3SpinBox_valueChanged"

    },
    "Widget\0on_importButton_clicked\0\0"
    "on_herbDisp_clicked\0checked\0"
    "on_herbMean_clicked\0on_herbFit_clicked\0"
    "on_carnDisp_clicked\0on_carnMean_clicked\0"
    "on_carnFit_clicked\0on_updateCheckBox_clicked\0"
    "timeOutSlot\0on_interval1SpinBox_valueChanged\0"
    "arg1\0on_interval2SpinBox_valueChanged\0"
    "on_interval3SpinBox_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Widget[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    1,   75,    2, 0x08 /* Private */,
       5,    1,   78,    2, 0x08 /* Private */,
       6,    1,   81,    2, 0x08 /* Private */,
       7,    1,   84,    2, 0x08 /* Private */,
       8,    1,   87,    2, 0x08 /* Private */,
       9,    1,   90,    2, 0x08 /* Private */,
      10,    1,   93,    2, 0x08 /* Private */,
      11,    0,   96,    2, 0x08 /* Private */,
      12,    1,   97,    2, 0x08 /* Private */,
      14,    1,  100,    2, 0x08 /* Private */,
      15,    1,  103,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void, QMetaType::Bool,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,
    QMetaType::Void, QMetaType::Int,   13,

       0        // eod
};

void Widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<Widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_importButton_clicked(); break;
        case 1: _t->on_herbDisp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 2: _t->on_herbMean_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 3: _t->on_herbFit_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 4: _t->on_carnDisp_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_carnMean_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->on_carnFit_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 7: _t->on_updateCheckBox_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->timeOutSlot(); break;
        case 9: _t->on_interval1SpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 10: _t->on_interval2SpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 11: _t->on_interval3SpinBox_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject Widget::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_Widget.data,
    qt_meta_data_Widget,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *Widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Widget::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_Widget.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int Widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
