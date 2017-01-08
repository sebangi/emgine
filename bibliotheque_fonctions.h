#ifndef BIBLIOTHEQUE_FONCTION_H
#define BIBLIOTHEQUE_FONCTION_H

#include "fonction/base_fonction.h"

class bibliotheque_fonctions
{
    public:
        static QString nom_to_string(type_id_fonction id);
        static base_fonction *get_fonction(type_id_fonction id);
};

#endif // BIBLIOTHEQUE_FONCTION_H
