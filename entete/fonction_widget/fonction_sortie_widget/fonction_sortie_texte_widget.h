#ifndef FONCTION_SORTIE_TEXTE_WIDGET_H
#define FONCTION_SORTIE_TEXTE_WIDGET_H

/** \file fonction_sortie_texte_widget.h
 * \brief Fichier de déclaration de la classe fonction_sortie_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.h"

#include <QListWidgetItem>

class liste_texte_widget;

/**
 * \class fonction_sortie_texte_widget
 * \brief Classe décrivant un widget affichant une fonction de type sortie_texte.
 * \author Sébastien Angibaud
 */
class fonction_sortie_texte_widget : public fonction_base_sortie_widget
{
        Q_OBJECT

    private:
        /** \brief Le type de la classe parente. */
        typedef fonction_base_sortie_widget super;

    public:
        fonction_sortie_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private slots:
        void showContextMenu(const QPoint& pos);
        void creer_projet();
        void sauvegarder_texte();

    private:
        void init();
};

#endif // FONCTION_SORTIE_TEXTE_WIDGET_H
