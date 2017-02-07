#ifndef NOEUD_FONCTION_H
#define NOEUD_FONCTION_H

/** \file noeud_fonction.h
 * \brief Fichier de déclaration de la classe noeud_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/base_noeud.h"

class base_fonction;

/**
 * \class noeud_fonction
 * \brief Classe décrivant un noeud associé à une fonction.
 * \author Sébastien Angibaud
 */
class noeud_fonction : public base_noeud
{
    public:
        noeud_fonction( base_fonction* p );
        ~noeud_fonction();

        base_fonction* get_fonction() const;
        void mettre_a_jour_style(bool actif);
        void mise_a_jour_icone();
};

#endif // NOEUD_FONCTION_H
