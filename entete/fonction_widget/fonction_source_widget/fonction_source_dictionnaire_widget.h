#ifndef FONCTION_SOURCE_DICTIONNAIRE_WIDGET_H
#define FONCTION_SOURCE_DICTIONNAIRE_WIDGET_H


/** \file fonction_source_dictionnaire_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_dictionnaire_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QLabel>
#include <QPushButton>

/**
 * \class fonction_source_dictionnaire_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_dictionnaire_widget.
 * \author Sébastien Angibaud
 */
class fonction_source_dictionnaire_widget : public base_fonction_widget
{
        Q_OBJECT

    private:
        /** \brief Type de la classe parent. */
        typedef base_fonction_widget super;

    public:
        fonction_source_dictionnaire_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void informer_verrouillage_change();
        void init();
        void choisir_nom_fichier();
        void update_boutons();

    private slots :
        void on_choisir_click();

    private:
        /** \brief Un pointeur sur le label affichant le nom du fichier. */
        QLabel * m_nom_fichier_label;

        /** \brief Un pointeur sur le bouton de choix. */
        QPushButton * m_choix_bouton;
};

#endif // FONCTION_SOURCE_DICTIONNAIRE_WIDGET_H
