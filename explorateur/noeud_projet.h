#ifndef NOEUD_PROJET_H
#define NOEUD_PROJET_H

#include "explorateur/base_noeud.h"

class projet;

class noeud_projet : public base_noeud
{
     public:
        noeud_projet( projet* p );
        ~noeud_projet();

        projet* get_projet() const;
        QString get_nom() const;
        void executer( compilateur & compil );
        void charger();
        fonctions_conteneur *get_fonctions_conteneur();

    private:
        projet* m_projet;
};

#endif // NOEUD_PROJET_H
