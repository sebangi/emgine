#ifndef NOEUD_FONCTION_H
#define NOEUD_FONCTION_H

#include "entete/explorateur/base_noeud.h"

class base_fonction;

class noeud_fonction : public base_noeud
{
    public:
        noeud_fonction( base_fonction* p );
        ~noeud_fonction();

        base_fonction* get_fonction() const;
        void update_style();
};


#endif // NOEUD_FONCTION_H
