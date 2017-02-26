#ifndef BOUTON_CHOIX_FONCTION_H
#define BOUTON_CHOIX_FONCTION_H

/** \file bouton_choix_fonction.h
 * \brief Fichier d de la classe bouton_choix_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/define.h"
#include "entete/projet/base_fonction.h"

#include <QPushButton>

/**
 * \class bouton_choix_fonction
 * \brief Classe décrivant un bouton de choix de fonction.
 * \author Sébastien Angibaud
 */
class bouton_choix_fonction : public QPushButton
{
    public:
        bouton_choix_fonction(type_id_fonction id, QWidget *parent = 0);

        base_fonction* get_fonction();
        type_id_fonction get_id_fonction() const;
        void mettre_a_jour_visibilite( const QString & cle );

    private:
        /** \brief L'identifiant de la fonction associée au bouton. */
        type_id_fonction m_id_fonction;
};

#endif // BOUTON_CHOIX_FONCTION_H
