#ifndef BASE_NOEUD_H
#define BASE_NOEUD_H

#include <QTreeWidgetItem>
#include <QObject>
#include "compilation/compilateur.h"

class fonctions_conteneur;

class base_noeud : public QTreeWidgetItem
{
    public:
        /*!
        \brief Type décrivant les différents types de noeud.
        */
        enum type_noeud{
            type_projet = QTreeWidgetItem::UserType,
            type_parametre,
            type_fonction
        };

    public:
        base_noeud( type_noeud type );
        ~base_noeud();

        virtual fonctions_conteneur *get_fonctions_conteneur();

        virtual QString get_nom() const = 0;
};

#endif // BASE_NOEUD_H
