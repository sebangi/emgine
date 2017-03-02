#ifndef FONCTION_SORTIE_INDICE_COINCIDENCE_WIDGET_H
#define FONCTION_SORTIE_INDICE_COINCIDENCE_WIDGET_H

/** \file fonction_sortie_indice_coincidence_widget.h
 * \brief Fichier de déclaration de la classe fonction_sortie_indice_coincidence_widget.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_indice_coincidence.h"
#include "entete/fonction_widget/base_fonction_widget.h"

#include <QListWidgetItem>

class liste_texte_widget;

/**
 * \class fonction_sortie_indice_coincidence_widget
 * \brief Classe décrivant un widget affichant une fonction de type sortie_indice_coincidence.
 * \author Sébastien Angibaud
 */
class fonction_sortie_indice_coincidence_widget : public base_fonction_widget
{
        Q_OBJECT

    private:
        /** \brief Le type de la classe parente. */
        typedef base_fonction_widget super;

    public:
        fonction_sortie_indice_coincidence_widget( base_fonction* fonction, QWidget *parent = 0 );

    private slots:
        void on_externe_fbs_textes_modifie();
        void onTexteDoubleClicked(QListWidgetItem* item);

    private:
        void creer_liste_texte();
        void init();

    private:
        /** \brief La référence des indices de coincidences des textes. */
        textes & m_indices_textes;

        /** \brief Un pointeur sur le widget affichant la liste de textes. */
        liste_texte_widget* m_liste_texte;
};

#endif // FONCTION_SORTIE_INDICE_COINCIDENCE_WIDGET_H
