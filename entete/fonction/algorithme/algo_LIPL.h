#ifndef ALGO_LIPL_H
#define ALGO_LIPL_H

#include <map>

#include "entete/define.h"
#include "entete/element/ligne.h"

/**
 \brief Classe de stockage pour l'utilisation de l'algorithme LIPL.
        Ligne Itération par ligne
 \author Sébastien Angibaud
*/
class algo_LIPL
{
    public:
        typedef std::map< type_id_parametre, algo_LIPL > type_map_LIPL;

    public:
        algo_LIPL();
        ~algo_LIPL();

    public:
        const ligne* ligne_courante;
        ligne::const_iterator it_debut; // le début de la ligne
        ligne::const_iterator it_courant; // le mot courant dans la ligne
        ligne::const_iterator it_fin; // le fin de la ligne
};

#endif // ALGO_LIPL_H
