#ifndef FONCTION_SOURCE_ENTIER_WIDGET_H
#define FONCTION_SOURCE_ENTIER_WIDGET_H

/** \file fonction_source_entier_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_entier_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QSpinBox>

/**
 * \class fonction_source_entier_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_entier.
 * \author Sébastien Angibaud
 */
class fonction_source_entier_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_entier_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();
        void informer_verrouillage_change();

    private slots :
        void on_entier_changed(int valeur);

    private:
        /** \brief Un pointeur sur le SpinBox contenant l'entier. */
        QSpinBox * m_spin_box;
};


#endif // FONCTION_SOURCE_ENTIER_WIDGET_H
