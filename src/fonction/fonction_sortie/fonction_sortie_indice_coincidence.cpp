/** \file fonction_sortie_indice_coincidence.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_indice_coincidence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_sortie_indice_coincidence.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_indice_coincidence_widget.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_indice_coincidence.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_sortie_indice_coincidence::fonction_sortie_indice_coincidence(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur)
{
    set_id(f_sortie_indice_coincidence);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_sortie_indice_coincidence.
 */
fonction_sortie_indice_coincidence::~fonction_sortie_indice_coincidence()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_sortie_indice_coincidence::generer_fonction_widget()
{
    return new fonction_sortie_indice_coincidence_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_sortie_indice_coincidence::executer_sortie_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    m_indices_textes.clear();
    textes_in.calculer_indice_coincidence();

    for ( textes::iterator it_texte = textes_in.begin(); it_texte != textes_in.end(); ++it_texte )
    {
        texte t;
        ligne l;
        l.ajouter_mot( mot( QString::number( it_texte->get_indice_coincidence() ) ) );
        t.ajouter_ligne( l );
        m_indices_textes.ajouter_texte( it_texte->get_configuration(), t );
    }
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_sortie_indice_coincidence::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs des indices de coincidences.
 * \return Les indices de coincidence.
 */
textes & fonction_sortie_indice_coincidence::get_indices_textes()
{
    return m_indices_textes;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_sortie_indice_coincidence::get_valeur_courte() const
{
    return m_textes.to_string_lisible();
}
