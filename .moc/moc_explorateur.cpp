/****************************************************************************
** Meta object code from reading C++ file 'explorateur.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../explorateur/explorateur.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'explorateur.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_explorateur_t {
    QByteArrayData data[19];
    char stringdata0[302];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_explorateur_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_explorateur_t qt_meta_stringdata_explorateur = {
    {
QT_MOC_LITERAL(0, 0, 11), // "explorateur"
QT_MOC_LITERAL(1, 12, 20), // "noeud_courant_change"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 11), // "base_noeud*"
QT_MOC_LITERAL(4, 46, 29), // "on_externe_supprimer_fonction"
QT_MOC_LITERAL(5, 76, 14), // "base_fonction*"
QT_MOC_LITERAL(6, 91, 1), // "f"
QT_MOC_LITERAL(7, 93, 37), // "on_externe_activation_fonctio..."
QT_MOC_LITERAL(8, 131, 14), // "on_itemClicked"
QT_MOC_LITERAL(9, 146, 16), // "QTreeWidgetItem*"
QT_MOC_LITERAL(10, 163, 4), // "item"
QT_MOC_LITERAL(11, 168, 6), // "column"
QT_MOC_LITERAL(12, 175, 29), // "on_customContextMenuRequested"
QT_MOC_LITERAL(13, 205, 3), // "pos"
QT_MOC_LITERAL(14, 209, 21), // "on_currentItemChanged"
QT_MOC_LITERAL(15, 231, 20), // "on_set_noeud_courant"
QT_MOC_LITERAL(16, 252, 15), // "on_ajout_source"
QT_MOC_LITERAL(17, 268, 15), // "on_ajout_sortie"
QT_MOC_LITERAL(18, 284, 17) // "on_ajout_fonction"

    },
    "explorateur\0noeud_courant_change\0\0"
    "base_noeud*\0on_externe_supprimer_fonction\0"
    "base_fonction*\0f\0on_externe_activation_fonction_change\0"
    "on_itemClicked\0QTreeWidgetItem*\0item\0"
    "column\0on_customContextMenuRequested\0"
    "pos\0on_currentItemChanged\0"
    "on_set_noeud_courant\0on_ajout_source\0"
    "on_ajout_sortie\0on_ajout_fonction"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_explorateur[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   64,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    1,   67,    2, 0x08 /* Private */,
       7,    1,   70,    2, 0x08 /* Private */,
       8,    2,   73,    2, 0x08 /* Private */,
      12,    1,   78,    2, 0x08 /* Private */,
      14,    1,   81,    2, 0x08 /* Private */,
      15,    0,   84,    2, 0x08 /* Private */,
      16,    0,   85,    2, 0x08 /* Private */,
      17,    0,   86,    2, 0x08 /* Private */,
      18,    0,   87,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 5,    6,
    QMetaType::Void, 0x80000000 | 9, QMetaType::Int,   10,   11,
    QMetaType::Void, QMetaType::QPoint,   13,
    QMetaType::Void, 0x80000000 | 9,   10,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void explorateur::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        explorateur *_t = static_cast<explorateur *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->noeud_courant_change((*reinterpret_cast< base_noeud*(*)>(_a[1]))); break;
        case 1: _t->on_externe_supprimer_fonction((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        case 2: _t->on_externe_activation_fonction_change((*reinterpret_cast< base_fonction*(*)>(_a[1]))); break;
        case 3: _t->on_itemClicked((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1])),(*reinterpret_cast< int(*)>(_a[2]))); break;
        case 4: _t->on_customContextMenuRequested((*reinterpret_cast< const QPoint(*)>(_a[1]))); break;
        case 5: _t->on_currentItemChanged((*reinterpret_cast< QTreeWidgetItem*(*)>(_a[1]))); break;
        case 6: _t->on_set_noeud_courant(); break;
        case 7: _t->on_ajout_source(); break;
        case 8: _t->on_ajout_sortie(); break;
        case 9: _t->on_ajout_fonction(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (explorateur::*_t)(base_noeud * );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&explorateur::noeud_courant_change)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject explorateur::staticMetaObject = {
    { &QTreeWidget::staticMetaObject, qt_meta_stringdata_explorateur.data,
      qt_meta_data_explorateur,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *explorateur::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *explorateur::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_explorateur.stringdata0))
        return static_cast<void*>(const_cast< explorateur*>(this));
    return QTreeWidget::qt_metacast(_clname);
}

int explorateur::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QTreeWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void explorateur::noeud_courant_change(base_noeud * _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
