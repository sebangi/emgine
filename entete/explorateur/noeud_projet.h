#ifndef NOEUD_PROJET_H
#define NOEUD_PROJET_H

#include "entete/explorateur/noeud_fonctions_conteneur.h"

class projet;

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
