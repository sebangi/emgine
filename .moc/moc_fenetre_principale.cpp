/****************************************************************************
** Meta object code from reading C++ file 'fenetre_principale.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.7.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../fenetre_principale.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fenetre_principale.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.7.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_fenetre_principale_t {
    QByteArrayData data[20];
    char stringdata0[427];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_fenetre_principale_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_fenetre_principale_t qt_meta_stringdata_fenetre_principale = {
    {
QT_MOC_LITERAL(0, 0, 18), // "fenetre_principale"
QT_MOC_LITERAL(1, 19, 32), // "on_ajouter_fonction_source_click"
QT_MOC_LITERAL(2, 52, 0), // ""
QT_MOC_LITERAL(3, 53, 36), // "on_ajouter_fonction_conversio..."
QT_MOC_LITERAL(4, 90, 32), // "on_ajouter_fonction_sortie_click"
QT_MOC_LITERAL(5, 123, 23), // "on_nouveau_projet_click"
QT_MOC_LITERAL(6, 147, 32), // "on_sauvegarder_projet_sous_click"
QT_MOC_LITERAL(7, 180, 27), // "on_sauvegarder_projet_click"
QT_MOC_LITERAL(8, 208, 22), // "on_ouvrir_projet_click"
QT_MOC_LITERAL(9, 231, 17), // "on_compiler_click"
QT_MOC_LITERAL(10, 249, 32), // "on_vue_fonction_selectionChanged"
QT_MOC_LITERAL(11, 282, 14), // "QItemSelection"
QT_MOC_LITERAL(12, 297, 10), // "last_index"
QT_MOC_LITERAL(13, 308, 9), // "new_index"
QT_MOC_LITERAL(14, 318, 31), // "on_externe_noeud_courant_change"
QT_MOC_LITERAL(15, 350, 11), // "base_noeud*"
QT_MOC_LITERAL(16, 362, 13), // "noeud_courant"
QT_MOC_LITERAL(17, 376, 32), // "on_externe_parametre_selectionne"
QT_MOC_LITERAL(18, 409, 15), // "base_parametre*"
QT_MOC_LITERAL(19, 425, 1) // "p"

    },
    "fenetre_principale\0on_ajouter_fonction_source_click\0"
    "\0on_ajouter_fonction_conversion_click\0"
    "on_ajouter_fonction_sortie_click\0"
    "on_nouveau_projet_click\0"
    "on_sauvegarder_projet_sous_click\0"
    "on_sauvegarder_projet_click\0"
    "on_ouvrir_projet_click\0on_compiler_click\0"
    "on_vue_fonction_selectionChanged\0"
    "QItemSelection\0last_index\0new_index\0"
    "on_externe_noeud_courant_change\0"
    "base_noeud*\0noeud_courant\0"
    "on_externe_parametre_selectionne\0"
    "base_parametre*\0p"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_fenetre_principale[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      11,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   69,    2, 0x08 /* Private */,
       3,    0,   70,    2, 0x08 /* Private */,
       4,    0,   71,    2, 0x08 /* Private */,
       5,    0,   72,    2, 0x08 /* Private */,
       6,    0,   73,    2, 0x08 /* Private */,
       7,    0,   74,    2, 0x08 /* Private */,
       8,    0,   75,    2, 0x08 /* Private */,
       9,    0,   76,    2, 0x08 /* Private */,
      10,    2,   77,    2, 0x08 /* Private */,
      14,    1,   82,    2, 0x08 /* Private */,
      17,    1,   85,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 11, 0x80000000 | 11,   12,   13,
    QMetaType::Void, 0x80000000 | 15,   16,
    QMetaType::Void, 0x80000000 | 18,   19,

       0        // eod
};

void fenetre_principale::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        fenetre_principale *_t = static_cast<fenetre_principale *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_ajouter_fonction_source_click(); break;
        case 1: _t->on_ajouter_fonction_conversion_click(); break;
        case 2: _t->on_ajouter_fonction_sortie_click(); break;
        case 3: _t->on_nouveau_projet_click(); break;
        case 4: _t->on_sauvegarder_projet_sous_click(); break;
        case 5: _t->on_sauvegarder_projet_click(); break;
        case 6: _t->on_ouvrir_projet_click(); break;
        case 7: _t->on_compiler_click(); break;
        case 8: _t->on_vue_fonction_selectionChanged((*reinterpret_cast< const QItemSelection(*)>(_a[1])),(*reinterpret_cast< const QItemSelection(*)>(_a[2]))); break;
        case 9: _t->on_externe_noeud_courant_change((*reinterpret_cast< base_noeud*(*)>(_a[1]))); break;
        case 10: _t->on_externe_parametre_selectionne((*reinterpret_cast< base_parametre*(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 8:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 1:
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QItemSelection >(); break;
            }
            break;
        }
    }
}

const QMetaObject fenetre_principale::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_fenetre_principale.data,
      qt_meta_data_fenetre_principale,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *fenetre_principale::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *fenetre_principale::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_fenetre_principale.stringdata0))
        return static_cast<void*>(const_cast< fenetre_principale*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int fenetre_principale::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 11)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 11;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
