#ifndef FONCTION_SORTIE_TEXTE_WIDGET_H
#define FONCTION_SORTIE_TEXTE_WIDGET_H

/** \file fonction_sortie_texte_widget.h
 * \brief Fichier de déclaration de la classe fonction_sortie_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"
#include "entete/fonction_widget/base_fonction_widget.h"

#include <QListWidgetItem>

class liste_texte_widget;

/**
 * \class fonction_sortie_texte_widget
 * \brief Classe décrivant un widget affichant une fonction de type sortie_texte.
 * \author Sébastien Angibaud
 */
class fonction_sortie_texte_widget : public base_fonction_widget
{
        Q_OBJECT

    private:
        /** \brief Le type de la classe parente. */
        typedef base_fonction_widget super;

    public:
        fonction_sortie_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private slots:
        void on_externe_fst_textes_modifie();
        void onTexteDoubleClicked(QListWidgetItem* item);
        void showContextMenu(const QPoint& pos);
        void creer_projet();
        void sauvegarder_texte();

    private:
        void creer_liste_texte();
        void init();

    private:
        /** \brief La référence de la liste de textes à afficher. */
        textes & m_textes;

        /** \brief Un pointeur sur le widget affichant la liste de textes. */
        liste_texte_widget* m_liste_texte;
};

#endif // FONCTION_SORTIE_TEXTE_WIDGET_H
