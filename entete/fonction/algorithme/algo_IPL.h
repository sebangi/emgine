#ifndef ALGO_IPL_H
#define ALGO_IPL_H

/** \file algo_IPL.h
 * \brief Fichier de déclaration de la classe algo_IPL.
 * \author Sébastien Angibaud
 */

#include "entete/element/ligne.h"
#include "entete/fonction/define_parametre.h"

#include <map>

/**
  \class algo_MIPL
  \brief Classe de stockage pour l'utilisation de l'algorithme IPL (Itération Par Ligne)
  \author Sébastien Angibaud
*/
class algo_IPL
{
    public:
        /** \brief Tableau associatif permettant d'associer à un type de paramètre un objet algo_IPL. */
        typedef std::map< type_id_parametre, algo_IPL > type_map_IPL;

    public:
        algo_IPL();
        ~algo_IPL();

    public:
        /** \brief Pointeur sur la ligne courante. */
        const ligne* ligne_courante;

        /** \brief Itérateur sur le début de la ligne courante, i.e. sur le premier mot. */
        ligne::const_iterator it_ligne_debut;

        /** \brief Itérateur sur le mot courant de la ligne courante. */
        ligne::const_iterator it_mot_courant;

        /** \brief Itérateur sur la fin de la ligne courante. */
        ligne::const_iterator it_ligne_fin; // la fin de la ligne

        /** \brief Itérateur sur le début du mot courant, i.e. sur le premier caractère. */
        mot::const_iterator it_mot_debut;

        /** \brief Itérateur sur le caractère du courant du mot courante. */
        mot::const_iterator it_caractere_courant;

        /** \brief Itérateur sur la fin du mot courant. */
        mot::const_iterator it_mot_fin; // la fin du mot
};

#endif // ALGO_IPL_H
