#ifndef BIBLIOTHEQUE_FONCTION_H
#define BIBLIOTHEQUE_FONCTION_H

#include "entete/fonction/define_fonction.h"

#include <map>
#include <set>
#include <QString>

class base_fonction;

class bibliotheque_fonctions
{        
    public:
        static base_fonction *get_fonction(type_id_fonction id);

        static QString get_aide(type_id_fonction id);
        static QString get_nom(type_id_fonction id);
        static bool contient_mot_cle(type_id_fonction id, const QString & cle );

    private:
        static std::map<type_id_fonction, QString> s_fonctions_aide;
        static std::map<type_id_fonction, QString> s_fonctions_nom;
        static std::map<type_id_fonction, std::set<QString> > s_categories;
};

#endif // BIBLIOTHEQUE_FONCTION_H
