/**
 * \file fonction_transposition.cpp
 * \brief Fichier d'implémentation de la classe fonction_transposition.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_transposition.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_transposition.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_transposition::fonction_transposition( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_transposition);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);

    ajouter_parametre( PARAM_TRANSPOSITION_MOTS,
                       new base_parametre( this,
                                           "transposer suivant les mots",
                                           "Indique s'il faut transposer suivant les mots.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_transposition::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_transposition::get_valeur_courte() const
{
    return "[transposition]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_transposition::initialisation_par_defaut()
{
    m_parametres[PARAM_TRANSPOSITION_MOTS]->set_booleen_par_defaut(true);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_transposition::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_TRANSPOSITION_MOTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>transposition</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_transposition::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool transposition_mot =  m_map_IPL[PARAM_TRANSPOSITION_MOTS].it_caractere_courant->get_booleen();

    textes t = textes(textes_in);
    if ( transposition_mot )
        t.transposer_mots();
    else
        t.transposer_caracteres();

    for ( textes::const_iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        textes_out.ajouter_texte(compil.get_configuration(), *it_t);
}
