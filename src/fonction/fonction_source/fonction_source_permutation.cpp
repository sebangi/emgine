/** \file fonction_source_permutation.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_permutation.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_permutation.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/base_fonction_widget.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_permutation.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_source_permutation::fonction_source_permutation(fonctions_conteneur * conteneur)
    : fonction_base_source(conteneur)
{
    set_id(f_source_generateur_permutation);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new base_parametre( this,
                                           "Éléments",
                                           "Les éléments utilisés pour générer les permutations.\nÉviter de dépasser 9 éléments car trop long.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_permutation.
 */
fonction_source_permutation::~fonction_source_permutation()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_source_permutation::initialisation_par_defaut()
{
    initialisation_par_defaut("1 2 3");
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation les paramètres de la fonction.
 * \param elements Les éléments au format QString.
 */
void fonction_source_permutation::initialisation_par_defaut(QString elements)
{
    m_parametres[PARAM_ELEMENTS]->set_texte_par_defaut(elements);
}

base_fonction_widget *fonction_source_permutation::generer_fonction_widget()
{
    return new base_fonction_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_permutation::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
        ( PARAM_ELEMENTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>décalage de césar</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_permutation::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    texte t("", "\n" );

    ligne l(* m_map_IPL[PARAM_ELEMENTS].ligne_courante);
    std::sort(l.begin(), l.end());

    do
    {
        t.ajouter_ligne(l);
    } while ( std::next_permutation( l.begin(), l.end() ) );

    textes_out.ajouter_texte(compil.get_configuration(), t);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_permutation::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_permutation::get_valeur_courte() const
{
    return "généré lors de l'exécution";
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_permutation::get_string_valeur() const
{
    return "";
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_permutation::set_string_valeur(const QString &valeur)
{
    // rien à faire
}
