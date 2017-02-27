#ifndef FONCTION_SOURCE_BOOLEEN_WIDGET_H
#define FONCTION_SOURCE_BOOLEEN_WIDGET_H

/** \file fonction_source_booleen_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_booleen_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QCheckBox>

/**
 * \class fonction_source_booleen_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_booleen.
 * \author Sébastien Angibaud
 */
class fonction_source_booleen_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_booleen_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();
        void informer_verrouillage_change();

    private slots :
        void on_oui_stateChanged(int checkState);
        void on_non_stateChanged(int checkState);

    private:
        /** \brief Un pointeur sur le bouton à cocher OUI. */
        QCheckBox * m_check_oui;

        /** \brief Un pointeur sur le bouton à cocher NON. */
        QCheckBox * m_check_non;
};

#endif // FONCTION_SOURCE_BOOLEEN_WIDGET_H
