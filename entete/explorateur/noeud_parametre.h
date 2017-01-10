#ifndef NOEUD_PARAMETRE_H
#define NOEUD_PARAMETRE_H

#include "entete/explorateur/base_noeud.h"

class base_parametre;

class noeud_parametre : public base_noeud
{
    public:
        noeud_parametre( base_parametre* p );
        ~noeud_parametre();

        base_parametre* get_parametre() const;
        QString get_nom() const;
        fonctions_conteneur *get_fonctions_conteneur();
};

#endif // NOEUD_PARAMETRE_H
