#ifndef BASE_NOEUD_H
#define BASE_NOEUD_H

/** \file base_noeud.h
 * \brief Fichier de déclaration de la classe base_noeud.
 * \author Sébastien Angibaud
 */

#include <QTreeWidgetItem>

class objet_selectionnable;

/**
 * \class base_noeud
 * \brief Classe décrivant un noeud quelconque de l'explorateur.
 * \author Sébastien Angibaud
 */
class base_noeud : public QTreeWidgetItem
{
    public:
        /** \enum type_noeud
         *  \author Sébastien Angibaud
         *  \brief Enumération représentant les différents types de noeud de l'explorateur.
         */
        enum type_noeud{
            /** \brief Type de noeud pour les projets. */
            TYPE_NOEUD_PROJET = QTreeWidgetItem::UserType,

            /** \brief Type de noeud pour les paramètres. */
            TYPE_NOEUD_PARAMETRE,

            /** \brief Type de noeud pour les fonctions. */
            TYPE_NOEUD_FONCTION
        };

    public:
        base_noeud( objet_selectionnable * obj, type_noeud type );
        ~base_noeud();

        objet_selectionnable *get_objet() const;
        void mettre_a_jour_style(bool actif);
        bool get_save_expanded() const;
        void save_expanded();
        virtual void mise_a_jour_icone();
        virtual void maj_langues();

    protected:
        /** \brief L'objet sélectionnable associé au noeud. */
        objet_selectionnable * m_objet;

        /** \brief Sauvegarde de l'état d'expansion du noeud avant compactage automatique. */
        bool m_save_expanded;
};

#endif // BASE_NOEUD_H
