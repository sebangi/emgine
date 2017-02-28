#ifndef BIBLIOTHEQUE_FONCTION_H
#define BIBLIOTHEQUE_FONCTION_H

/** \file bibliotheque_fonctions.h
 * \brief Fichier de déclaration de la classe bibliotheque_fonctions.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/define_fonction.h"

#include <QString>

#include <map>
#include <set>

class base_fonction;

/**
 * \class bibliotheque_fonctions
 * \brief Classe répertoriant l'ensemble des fonctions disponibles.
 * \author Sébastien Angibaud
 */
class bibliotheque_fonctions
{        
    public:
        static base_fonction *get_fonction(type_id_fonction id);

        static QString get_aide(type_id_fonction id);
        static QString get_nom(type_id_fonction id);
        static bool contient_mot_cle(type_id_fonction id, const QString & cle );

    private:
        /** \brief Les textes d'aide pour chaque fonction. */
        static std::map<type_id_fonction, QString> s_fonctions_aide;

        /** \brief Les noms de chaque fonction. */
        static std::map<type_id_fonction, QString> s_fonctions_nom;

        /** \brief Les catégories de chaque fonction. */
        static std::map<type_id_fonction, std::set<QString> > s_categories;
};

#endif // BIBLIOTHEQUE_FONCTION_H
