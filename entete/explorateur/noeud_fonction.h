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
        void update_style(bool actif);

    private:
        void mise_a_jour_icone();
};


#endif // NOEUD_FONCTION_H
