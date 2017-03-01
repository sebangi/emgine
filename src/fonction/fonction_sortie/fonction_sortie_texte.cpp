/** \file fonction_sortie_texte.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_texte.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_texte.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_sortie_texte::fonction_sortie_texte(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur)
{
    set_id(f_sortie_texte);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_sortie_texte.
 */
fonction_sortie_texte::~fonction_sortie_texte()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_sortie_texte::generer_fonction_widget()
{
    return new fonction_sortie_texte_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_sortie_texte::executer_sortie_specifique( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    // rien à faire
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_sortie_texte::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_sortie_texte::get_valeur_courte() const
{
    return m_textes.to_string_lisible();
}

