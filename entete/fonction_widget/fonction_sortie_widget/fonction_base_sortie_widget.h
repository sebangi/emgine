#ifndef FONCTION_BASE_SORTIE_WIDGET_H
#define FONCTION_BASE_SORTIE_WIDGET_H

/** \file fonction_base_sortie_widget.h
 * \brief Fichier de déclaration de la classe fonction_base_sortie_widget.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"
#include "entete/fonction_widget/base_fonction_widget.h"

#include <QListWidgetItem>

class liste_texte_widget;

/**
 * \class fonction_base_sortie_widget
 * \brief Classe décrivant un widget de base affichant une fonction de type sortie.
 * \author Sébastien Angibaud
 */
class fonction_base_sortie_widget : public base_fonction_widget
{
        Q_OBJECT

    private:
        /** \brief Le type de la classe parente. */
        typedef base_fonction_widget super;

    public:
        fonction_base_sortie_widget( base_fonction* fonction, QWidget *parent = 0 );

    private slots:
        void on_externe_fbs_textes_modifie();
        void onTexteDoubleClicked(QListWidgetItem* item);

    private:
        void creer_liste_texte();

    protected:
        virtual void init();

    protected:
        /** \brief La référence des fréquences des textes. */
        textes & m_textes_a_afficher;

        /** \brief Un pointeur sur le widget affichant la liste de textes. */
        liste_texte_widget* m_liste_texte;
};

#endif // FONCTION_BASE_SORTIE_WIDGET_H
