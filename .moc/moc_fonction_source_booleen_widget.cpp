/****************************************************************************
** Meta object code from reading C++ file 'fonction_source_booleen_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fonction_widget/fonction_source_booleen_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fonction_source_booleen_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_fonction_source_booleen_widget_t {
    QByteArrayData data[5];
    char stringdata0[83];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fonction_source_booleen_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fonction_source_booleen_widget_t qt_meta_stringdata_fonction_source_booleen_widget = {
    {
QT_MOC_LITERAL(0, 0, 30), // "fonction_source_booleen_widget"
QT_MOC_LITERAL(1, 31, 19), // "on_oui_stateChanged"
QT_MOC_LITERAL(2, 51, 0), // ""
QT_MOC_LITERAL(3, 52, 10), // "checkState"
QT_MOC_LITERAL(4, 63, 19) // "on_non_stateChanged"

    },
    "fonction_source_booleen_widget\0"
    "on_oui_stateChanged\0\0checkState\0"
    "on_non_stateChanged"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fonction_source_booleen_widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x08 /* Private */,
       4,    1,   27,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void, QMetaType::Int,    3,
    QMetaType::Void, QMetaType::Int,    3,

       0        // eod
};

void fonction_source_booleen_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fonction_source_booleen_widget *_t = static_cast<fonction_source_booleen_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_oui_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->on_non_stateChanged((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    }
}

const QMetaObject fonction_source_booleen_widget::staticMetaObject = {
    { &base_fonction_widget::staticMetaObject, qt_meta_stringdata_fonction_source_booleen_widget.data,
      qt_meta_data_fonction_source_booleen_widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fonction_source_booleen_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fonction_source_booleen_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fonction_source_booleen_widget.stringdata0))
        return static_cast<void*>(const_cast< fonction_source_booleen_widget*>(this));
    return base_fonction_widget::qt_metacast(_clname);
}

int fonction_source_booleen_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = base_fonction_widget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
