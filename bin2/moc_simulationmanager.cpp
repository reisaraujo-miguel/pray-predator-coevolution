/****************************************************************************
** Meta object code from reading C++ file 'simulationmanager.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.12.6)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../simulator/simulationmanager.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'simulationmanager.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.12.6. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SimulationManager_t {
    QByteArrayData data[14];
    char stringdata0[232];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SimulationManager_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SimulationManager_t qt_meta_stringdata_SimulationManager = {
    {
QT_MOC_LITERAL(0, 0, 17), // "SimulationManager"
QT_MOC_LITERAL(1, 18, 23), // "on_importButton_clicked"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 26), // "on_chooseHerb_valueChanged"
QT_MOC_LITERAL(4, 70, 1), // "i"
QT_MOC_LITERAL(5, 72, 26), // "on_chooseCarn_valueChanged"
QT_MOC_LITERAL(6, 99, 25), // "on_chooseGen_valueChanged"
QT_MOC_LITERAL(7, 125, 4), // "arg1"
QT_MOC_LITERAL(8, 130, 19), // "on_progress_clicked"
QT_MOC_LITERAL(9, 150, 7), // "checked"
QT_MOC_LITERAL(10, 158, 15), // "on_loop_clicked"
QT_MOC_LITERAL(11, 174, 11), // "timeOutSlot"
QT_MOC_LITERAL(12, 186, 19), // "on_simulate_clicked"
QT_MOC_LITERAL(13, 206, 25) // "on_frameRate_valueChanged"

    },
    "SimulationManager\0on_importButton_clicked\0"
    "\0on_chooseHerb_valueChanged\0i\0"
    "on_chooseCarn_valueChanged\0"
    "on_chooseGen_valueChanged\0arg1\0"
    "on_progress_clicked\0checked\0on_loop_clicked\0"
    "timeOutSlot\0on_simulate_clicked\0"
    "on_frameRate_valueChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SimulationManager[] = {

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
       1,    0,   59,    2, 0x08 /* Private */,
       3,    1,   60,    2, 0x08 /* Private */,
       5,    1,   63,    2, 0x08 /* Private */,
       6,    1,   66,    2, 0x08 /* Private */,
       8,    1,   69,    2, 0x08 /* Private */,
      10,    1,   72,    2, 0x08 /* Private */,
      11,    0,   75,    2, 0x08 /* Private */,
      12,    1,   76,    2, 0x08 /* Private */,
      13,    1,   79,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    4,
    QMetaType::Void, QMetaType::Int,    7,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool,    9,
    QMetaType::Void, QMetaType::Int,    7,

       0        // eod
};

void SimulationManager::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<SimulationManager *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_importButton_clicked(); break;
        case 1: _t->on_chooseHerb_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->on_chooseCarn_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->on_chooseGen_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 4: _t->on_progress_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 5: _t->on_loop_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 6: _t->timeOutSlot(); break;
        case 7: _t->on_simulate_clicked((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 8: _t->on_frameRate_valueChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject SimulationManager::staticMetaObject = { {
    &QWidget::staticMetaObject,
    qt_meta_stringdata_SimulationManager.data,
    qt_meta_data_SimulationManager,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *SimulationManager::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SimulationManager::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_SimulationManager.stringdata0))
        return static_cast<void*>(this);
    return QWidget::qt_metacast(_clname);
}

int SimulationManager::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
