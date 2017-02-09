#ifndef FONCTION_BASE_SORTIE_H
#define FONCTION_BASE_SORTIE_H

/** \file fonction_base_sortie.h
 * \brief Fichier de déclaration de la classe fonction_base_sortie.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"

class textes;

/**
 * \class fonction_base_sortie
 * \brief Classe commune à toutes les fonctions de type sortie.
 * \author Sébastien Angibaud
 */
class fonction_base_sortie : public base_fonction
{
    public:
        fonction_base_sortie(fonctions_conteneur * conteneur);
        ~fonction_base_sortie();
};

#endif // FONCTION_BASE_SORTIE_H
