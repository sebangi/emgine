#ifndef NOEUD_FONCTIONS_CONTENEUR_H
#define NOEUD_FONCTIONS_CONTENEUR_H

/** \file noeud_fonctions_conteneur.h
 * \brief Fichier de déclaration de la classe noeud_fonctions_conteneur.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/base_noeud.h"

class base_fonction;
class fonctions_conteneur;

/**
 * \class noeud_fonctions_conteneur
 * \brief Classe décrivant un noeud associé à un fonctions_conteneur.
 * \author Sébastien Angibaud
 */
class noeud_fonctions_conteneur : public base_noeud
{
     public:
        noeud_fonctions_conteneur( fonctions_conteneur * conteneur, type_noeud type );
        ~noeud_fonctions_conteneur();
};

#endif // NOEUD_FONCTIONS_CONTENEUR_H
