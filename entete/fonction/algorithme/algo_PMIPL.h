#ifndef ALGO_PMIPL_H
#define ALGO_PMIPL_H

/** \file algo_PMIPL.h
 * \brief Fichier de déclaration de la classe algo_PMIPL.
 * \author Sébastien Angibaud
 */

#include "entete/element/mot.h"
#include "entete/fonction/define_parametre.h"

#include <map>

/**
  \class algo_PMIPL
  \brief Classe de stockage pour l'utilisation de l'algorithme PMIPL ( Premier Mot Itération par ligne ).
  \author Sébastien Angibaud
*/
class algo_PMIPL
{
    public:
        /** \brief Tableau associatif permettant d'associer à un type de paramètre un objet algo_PMIPL. */
        typedef std::map< type_id_parametre, algo_PMIPL > type_map_PMIPL;

    public:
        algo_PMIPL();
        ~algo_PMIPL();

    public:
        /** \brief Pointeur sur le mot courant. */
        const mot* mot_courant;

        /** \brief Itérateur sur le début du mot courant, i.e. sur le premier élément du mot. */
        mot::const_iterator it_debut;

        /** \brief Itérateur sur l'élement courant du mot courant. */
        mot::const_iterator it_courant;

        /** \brief Itérateur sur le fin du mot courant. */
        mot::const_iterator it_fin;
};


#endif // ALGO_PMIPL_H
