/** \file fonction_base_source.cpp
 * \brief Fichier d'implémentation de la classe fonction_base_source.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_base_source.h"

#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/fonctions_conteneur.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_base_source.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_base_source::fonction_base_source(fonctions_conteneur * conteneur)
    : base_fonction(conteneur, type_fonction::fonction_source)
{
    set_est_etendu(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_base_source.
 */
fonction_base_source::~fonction_base_source()
{

}
