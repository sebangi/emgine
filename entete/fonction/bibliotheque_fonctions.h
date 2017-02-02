#ifndef BIBLIOTHEQUE_FONCTION_H
#define BIBLIOTHEQUE_FONCTION_H

#include "entete/fonction/define_fonction.h"

#include <map>
#include <QString>

class base_fonction;

class bibliotheque_fonctions
{        
    public:
        static QString nom_to_string(type_id_fonction id);
        static base_fonction *get_fonction(type_id_fonction id);

        static QString get_aide(type_id_fonction id);
        static QString get_nom(type_id_fonction id);

    private:
        static std::map<type_id_fonction, QString> s_fonctions_aide;
        static std::map<type_id_fonction, QString> s_fonctions_nom;
};

#endif // BIBLIOTHEQUE_FONCTION_H
