/** \file fonction_base_sortie.cpp
 * \brief Fichier d'implémentation de la classe fonction_base_sortie.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

#include "entete/explorateur/noeud_fonction.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_base_sortie.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_base_sortie::fonction_base_sortie(fonctions_conteneur * conteneur)
    : base_fonction(conteneur, type_fonction::fonction_sortie)
{
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_base_sortie.
 */
fonction_base_sortie::~fonction_base_sortie()
{

}
