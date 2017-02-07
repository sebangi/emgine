#ifndef NOEUD_PROJET_H
#define NOEUD_PROJET_H

/** \file noeud_projet
 * \brief Fichier de déclaration de la classe noeud_projet.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/noeud_fonctions_conteneur.h"

class compilateur;
class projet;

/**
 * \class noeud_projet
 * \brief Classe décrivant un noeud associé à un projet.
 * \author Sébastien Angibaud
 */
class noeud_projet : public noeud_fonctions_conteneur
{
     public:
        noeud_projet( projet* p );
        ~noeud_projet();

        projet* get_projet() const;
        QString get_nom() const;
        void executer( compilateur & compil );
        void charger();
        void mise_a_jour_icone();
};

#endif // NOEUD_PROJET_H
