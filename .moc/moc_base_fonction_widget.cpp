/****************************************************************************
** Meta object code from reading C++ file 'base_fonction_widget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fonction_widget/base_fonction_widget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_fonction_widget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_base_fonction_widget_t {
    QByteArrayData data[13];
    char stringdata0[222];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_base_fonction_widget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_base_fonction_widget_t qt_meta_stringdata_base_fonction_widget = {
    {
QT_MOC_LITERAL(0, 0, 20), // "base_fonction_widget"
QT_MOC_LITERAL(1, 21, 32), // "signal_bfw_parametre_selectionne"
QT_MOC_LITERAL(2, 54, 0), // ""
QT_MOC_LITERAL(3, 55, 15), // "base_parametre*"
QT_MOC_LITERAL(4, 71, 1), // "p"
QT_MOC_LITERAL(5, 73, 22), // "on_inverser_activation"
QT_MOC_LITERAL(6, 96, 9), // "on_fermer"
QT_MOC_LITERAL(7, 106, 19), // "on_parametre_switch"
QT_MOC_LITERAL(8, 126, 7), // "on_aide"
QT_MOC_LITERAL(9, 134, 37), // "on_externe_activation_fonctio..."
QT_MOC_LITERAL(10, 172, 14), // "base_fonction*"
QT_MOC_LITERAL(11, 187, 1), // "f"
QT_MOC_LITERAL(12, 189, 32) // "on_externe_parametre_selectionne"

    },
    "base_fonction_widget\0"
    "signal_bfw_parametre_selectionne\0\0"
    "base_parametre*\0p\0on_inverser_activation\0"
    "on_fermer\0on_parametre_switch\0on_aide\0"
    "on_externe_activation_fonction_change\0"
    "base_fonction*\0f\0on_externe_parametre_selectionne"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_base_fonction_widget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   49,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,   52,    2, 0x08 /* Private */,
       6,    0,   53,    2, 0x08 /* Private */,
       7,    0,   54,    2, 0x08 /* Private */,
       8,    0,   55,    2, 0x08 /* Private */,
       9,    1,   56,    2, 0x08 /* Private */,
      12,    1,   59,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void base_fonction_widget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        base_fonction_widget *_t = static_cast<base_fonction_widget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_bfw_parametre_selectionne((*reinterpret_cast< base_parametre*(*)>(_a[1]))); break;
        case 1: _t->on_inverser_activation(); break;
        case 2: _t->on_fermer(); break;
        case 3: _t->on_parametre_switch(); break;
        case 4: _t->on_aide(); break;
        case 5: _t->on_externe_activation_fonction_change((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        case 6: _t->on_externe_parametre_selectionne((*reinterpret_cast< base_parametre*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (base_fonction_widget::*_t)(base_parametre * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&base_fonction_widget::signal_bfw_parametre_selectionne)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject base_fonction_widget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_base_fonction_widget.data,
      qt_meta_data_base_fonction_widget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *base_fonction_widget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *base_fonction_widget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_base_fonction_widget.stringdata0))
        return static_cast<void*>(const_cast< base_fonction_widget*>(this));
    if (!strcmp(_clname, "QTableWidgetItem"))
        return static_cast< QTableWidgetItem*>(const_cast< base_fonction_widget*>(this));
    return QWidget::qt_metacast(_clname);
}

int base_fonction_widget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void base_fonction_widget::signal_bfw_parametre_selectionne(base_parametre * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
