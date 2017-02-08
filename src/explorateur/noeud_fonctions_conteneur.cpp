/** \file noeud_fonctions_conteneur.cpp
 * \brief Fichier d'implémentation de la class noeud_fonctions_conteneur.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/noeud_fonctions_conteneur.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/fonctions_conteneur.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe noeud_fonctions_conteneur.
 * \param conteneur Un pointeur sur le fonctions_conteneur associé au noeud.
 * \param type Le type du noeud.
 */
noeud_fonctions_conteneur::noeud_fonctions_conteneur( fonctions_conteneur * conteneur, type_noeud type )
    : base_noeud( (objet_selectionnable*)conteneur, type )
{

}

/** --------------------------------------------------------------------------------------
 * \brief Le destructeur de la classe noeud_fonctions_conteneur.
 */
noeud_fonctions_conteneur::~noeud_fonctions_conteneur()
{
}
