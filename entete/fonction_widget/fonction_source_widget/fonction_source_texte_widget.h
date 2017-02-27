#ifndef FONCTION_SOURCE_TEXTE_WIDGET_H
#define FONCTION_SOURCE_TEXTE_WIDGET_H

/**
 * \file fonction_source_texte_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget_avec_text_edit.h"

class text_edit;

/**
 * \class fonction_source_texte_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_texte.
 * \author Sébastien Angibaud
 */
class fonction_source_texte_widget : public base_fonction_widget_avec_text_edit
{
        Q_OBJECT

    public:
        fonction_source_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private :
        void on_nouveau_texte();
        QString chercher_valeur() const;
};

#endif // FONCTION_SOURCE_TEXTE_WIDGET_H
