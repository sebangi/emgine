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

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_base_sortie::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    m_textes = textes_in;
    textes_out = textes_in;

    executer_sortie_specifique(compil, textes_in, textes_out);

    emit signal_fbs_textes_modifie();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs des textes de sortie de la fonction.
 * \return Les textes de sortie.
 */
textes & fonction_base_sortie::get_textes()
{
    return m_textes;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les textes de la fonction.
 * \param textes Les nouveaux textes de la fonction.
 */
void fonction_base_sortie::set_textes(const textes &textes)
{
    m_textes = textes;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs des textes de sortie de la fonction.
 * \return Les textes de sortie.
 */
textes & fonction_base_sortie::get_textes_a_afficher()
{
    return m_textes_a_afficher;
}
