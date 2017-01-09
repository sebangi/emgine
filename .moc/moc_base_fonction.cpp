/****************************************************************************
** Meta object code from reading C++ file 'base_fonction.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fonction/base_fonction.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'base_fonction.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_base_fonction_t {
    QByteArrayData data[6];
    char stringdata0[94];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_base_fonction_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_base_fonction_t qt_meta_stringdata_base_fonction = {
    {
QT_MOC_LITERAL(0, 0, 13), // "base_fonction"
QT_MOC_LITERAL(1, 14, 27), // "signal_destruction_fonction"
QT_MOC_LITERAL(2, 42, 0), // ""
QT_MOC_LITERAL(3, 43, 14), // "base_fonction*"
QT_MOC_LITERAL(4, 58, 1), // "f"
QT_MOC_LITERAL(5, 60, 33) // "signal_activation_fonction_ch..."

    },
    "base_fonction\0signal_destruction_fonction\0"
    "\0base_fonction*\0f\0signal_activation_fonction_change"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_base_fonction[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 3,    4,

       0        // eod
};

void base_fonction::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        base_fonction *_t = static_cast<base_fonction *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signal_destruction_fonction((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        case 1: _t->signal_activation_fonction_change((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< base_fonction* >(); break;
            }
            break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< base_fonction* >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (base_fonction::*_t)(base_fonction * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&base_fonction::signal_destruction_fonction)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (base_fonction::*_t)(base_fonction * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&base_fonction::signal_activation_fonction_change)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject base_fonction::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_base_fonction.data,
      qt_meta_data_base_fonction,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *base_fonction::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *base_fonction::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_base_fonction.stringdata0))
        return static_cast<void*>(const_cast< base_fonction*>(this));
    return QObject::qt_metacast(_clname);
}

int base_fonction::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void base_fonction::signal_destruction_fonction(base_fonction * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void base_fonction::signal_activation_fonction_change(base_fonction * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
