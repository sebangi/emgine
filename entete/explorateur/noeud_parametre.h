#ifndef NOEUD_PARAMETRE_H
#define NOEUD_PARAMETRE_H

/** \file noeud_parametre.h
 * \brief Fichier de déclaration de la classe noeud_parametre.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/base_noeud.h"

class base_parametre;

/**
 * \class noeud_parametre
 * \brief Classe décrivant un noeud associé à un paramètre.
 * \author Sébastien Angibaud
 */
class noeud_parametre : public base_noeud
{
    public:
        noeud_parametre( base_parametre* p );
        ~noeud_parametre();

        base_parametre* get_parametre() const;
        void mise_a_jour_icone();
        void maj_langues();
};

#endif // NOEUD_PARAMETRE_H
