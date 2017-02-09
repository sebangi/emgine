#ifndef ALGO_LIPL_H
#define ALGO_LIPL_H

/** \file algo_LIPL.h
 * \brief Fichier de déclaration de la classe algo_LIPL.
 * \author Sébastien Angibaud
 */

#include "entete/element/ligne.h"
#include "entete/fonction/define_parametre.h"

#include <map>

/**
  \class algo_LIPL
  \brief Classe de stockage pour l'utilisation de l'algorithme LIPL (Ligne Itération Par Ligne)
  \author Sébastien Angibaud
*/
class algo_LIPL
{
    public:
        /** \brief Tableau associatif permettant d'associer à un type de paramètre un objet algo_LIPL. */
        typedef std::map< type_id_parametre, algo_LIPL > type_map_LIPL;

    public:
        algo_LIPL();
        ~algo_LIPL();

    public:
        /** \brief Pointeur sur la ligne courante. */
        const ligne* ligne_courante;

        /** \brief Itérateur sur le début de la ligne courante, i.e. sur le premier mot. */
        ligne::const_iterator it_debut;

        /** \brief Itérateur sur le mot courant de la ligne courante. */
        ligne::const_iterator it_courant;

        /** \brief Itérateur sur la fin de la ligne courante. */
        ligne::const_iterator it_fin; // le fin de la ligne
};

#endif // ALGO_LIPL_H
