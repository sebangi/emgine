/****************************************************************************
** Meta object code from reading C++ file 'vue_fonctions.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../vue_fonction/vue_fonctions.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'vue_fonctions.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_vue_fonctions_t {
    QByteArrayData data[9];
    char stringdata0[145];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_vue_fonctions_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_vue_fonctions_t qt_meta_stringdata_vue_fonctions = {
    {
QT_MOC_LITERAL(0, 0, 13), // "vue_fonctions"
QT_MOC_LITERAL(1, 14, 31), // "signal_vf_parametre_selectionne"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 15), // "base_parametre*"
QT_MOC_LITERAL(4, 63, 1), // "p"
QT_MOC_LITERAL(5, 65, 29), // "on_externe_supprimer_fonction"
QT_MOC_LITERAL(6, 95, 14), // "base_fonction*"
QT_MOC_LITERAL(7, 110, 1), // "f"
QT_MOC_LITERAL(8, 112, 32) // "on_externe_parametre_selectionne"

    },
    "vue_fonctions\0signal_vf_parametre_selectionne\0"
    "\0base_parametre*\0p\0on_externe_supprimer_fonction\0"
    "base_fonction*\0f\0on_externe_parametre_selectionne"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_vue_fonctions[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   29,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    1,   32,    2, 0x08 /* Private */,
       8,    1,   35,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void vue_fonctions::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        vue_fonctions *_t = static_cast<vue_fonctions *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_vf_parametre_selectionne((*reinterpret_cast< base_parametre*(*)>(_a[1]))); break;
        case 1: _t->on_externe_supprimer_fonction((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        case 2: _t->on_externe_parametre_selectionne((*reinterpret_cast< base_parametre*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (vue_fonctions::*_t)(base_parametre * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&vue_fonctions::signal_vf_parametre_selectionne)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject vue_fonctions::staticMetaObject = {
    { &QTableWidget::staticMetaObject, qt_meta_stringdata_vue_fonctions.data,
      qt_meta_data_vue_fonctions,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *vue_fonctions::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *vue_fonctions::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_vue_fonctions.stringdata0))
        return static_cast<void*>(const_cast< vue_fonctions*>(this));
    return QTableWidget::qt_metacast(_clname);
}

int vue_fonctions::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTableWidget::qt_metacall(_c, _id, _a);
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
void vue_fonctions::signal_vf_parametre_selectionne(base_parametre * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
