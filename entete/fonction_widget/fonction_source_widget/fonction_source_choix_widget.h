#ifndef FONCTION_SOURCE_CHOIX_WIDGET_H
#define FONCTION_SOURCE_CHOIX_WIDGET_H

/** \file fonction_source_choix_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_choix_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QListWidget>

/**
 * \class fonction_source_choix_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_choix .
 * \author Sébastien Angibaud
 */
class fonction_source_choix_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_choix_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();
        void construire_liste();
        void informer_verrouillage_change();

    private slots :
        void on_itemChanged(QListWidgetItem * item);

    private:
        /** \brief Un pointeur sur la liste des choix. */
        QListWidget * m_liste;

        /** \brief Booléen indiquant que les signaux sont bloqués; ceci afin d'éviter un plantage dû à des appels récursifs en boucle. */
        bool m_verrou_boucle_signaux;
};

#endif // FONCTION_SOURCE_CHOIX_WIDGET_H
