/**
 * \file fonction_inversion.cpp
 * \brief Fichier d'implémentation de la classe fonction_inversion.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_inversion.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_inversion.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_inversion::fonction_inversion( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_inversion);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);

    ajouter_parametre( PARAM_CARACTERES,
                       new base_parametre( this,
                                           "inverser les éléments",
                                           "Indique s'il faut inverser les éléments.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_MOTS,
                       new base_parametre( this,
                                           "inverser l'ordre des caractères",
                                           "Indique s'il faut inverser l'ordre des caractères.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_LIGNES,
                       new base_parametre( this,
                                           "inverser l'ordre des mots",
                                           "Indique s'il faut inverser l'ordre des mots.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_TEXTES,
                       new base_parametre( this,
                                           "inverser l'ordre des lignes",
                                           "Indique s'il faut inverser l'ordre des lignes.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_inversion::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_inversion::get_valeur_courte() const
{
    return "[inversion]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_inversion::initialisation_par_defaut()
{
    m_parametres[PARAM_CARACTERES]->set_booleen_par_defaut(true);
    m_parametres[PARAM_MOTS]->set_booleen_par_defaut(true);
    m_parametres[PARAM_LIGNES]->set_booleen_par_defaut(true);
    m_parametres[PARAM_TEXTES]->set_booleen_par_defaut(true);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_inversion::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERES, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_CARACTERES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_inversion::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_MOTS, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_MOTS.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_inversion::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_LIGNES, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_LIGNES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_inversion::callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_TEXTES, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}
/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>inversion</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_inversion::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool inversion_caracteres =  m_map_IPL[PARAM_CARACTERES].it_caractere_courant->get_booleen();
    bool inversion_mots =  m_map_IPL[PARAM_MOTS].it_caractere_courant->get_booleen();
    bool inversion_lignes =  m_map_IPL[PARAM_LIGNES].it_caractere_courant->get_booleen();
    bool inversion_textes =  m_map_IPL[PARAM_TEXTES].it_caractere_courant->get_booleen();

    textes t = textes(textes_in);

    for ( textes::iterator it_t = t.begin(); it_t != t.end(); ++it_t )
    {
        it_t->inverser(inversion_caracteres, inversion_mots, inversion_lignes, inversion_textes);

        textes_out.ajouter_texte(compil.get_configuration(), *it_t);
    }
}


