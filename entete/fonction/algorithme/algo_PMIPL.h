#ifndef ALGO_PMIPL_H
#define ALGO_PMIPL_H

#include <map>

#include "entete/define.h"
#include "entete/element/mot.h"

/**
 \brief Classe de stockage pour l'utilisation de l'algorithme PMIPL.
        Premier Mot Itération par ligne
 \author Sébastien Angibaud
*/
class algo_PMIPL
{
    public:
        typedef std::map< type_id_parametre, algo_PMIPL > type_map_PMIPL;

    public:
        algo_PMIPL();
        ~algo_PMIPL();

    public:
        const mot* mot_courant;
        mot::const_iterator it_debut; // le début du mot
        mot::const_iterator it_courant; // l'élement courant dans le mot
        mot::const_iterator it_fin; // le fin du mot
};


#endif // ALGO_PMIPL_H
