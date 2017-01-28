#ifndef BASE_NOEUD_H
#define BASE_NOEUD_H

#include <QTreeWidgetItem>
#include <QObject>
#include "entete/compilation/compilateur.h"

class fonctions_conteneur;
class objet_selectionnable;

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
        base_noeud( objet_selectionnable * obj, type_noeud type );
        ~base_noeud();

        objet_selectionnable *get_objet() const;
        void update_style(bool actif);

        bool get_save_expanded() const;
        void save_expanded();
        virtual void mise_a_jour_icone();

    protected:
        objet_selectionnable * m_objet;
        bool m_save_expanded;
};

#endif // BASE_NOEUD_H
