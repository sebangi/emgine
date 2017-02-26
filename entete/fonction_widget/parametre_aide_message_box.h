#ifndef PARAMETRE_AIDE_MESSAGE_BOX_H
#define PARAMETRE_AIDE_MESSAGE_BOX_H

/** \file parametre_aide_message_box.h
 * \brief Fichier d de la classe parametre_aide_message_box.
 * \author Sébastien Angibaud
 */

#include <QDialog>

class base_parametre;

/**
 * \class parametre_aide_message_box
 * \brief Classe décrivant une fenêtre affichant l'éaide d'un paramètre.
 * \author Sébastien Angibaud
 */
class parametre_aide_message_box : public QDialog
{
    public:
        parametre_aide_message_box(QWidget *parent, const base_parametre* parametre);

    private:
        void init();

    private:
        /** \brief Un poiteur sur le paramètre dont il faut afficher l'aide. */
        const base_parametre* m_parametre;
};

#endif // PARAMETRE_AIDE_MESSAGE_BOX_H
