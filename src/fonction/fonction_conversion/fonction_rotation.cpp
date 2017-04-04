/**
 * \file fonction_rotation.cpp
 * \brief Fichier d'implémentation de la classe fonction_rotation.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_rotation.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/parametre/parametre_choix.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_rotation.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_rotation::fonction_rotation( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_rotation);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_ROTATION_MOTS,
                       new base_parametre( this,
                                           "Réaliser la rotation suivant les mots",
                                           "Indique s'il faut réaliser la rotation suivant les mots.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_ROTATION,
                       new parametre_choix( this,
                                           "Les rotations à réaliser",
                                           "Indique quelles rotations réaliser.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL,
                                           rotation::liste_rotations_valides(),
                                           true ) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_rotation::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_rotation::get_valeur_courte() const
{
    return "[rotation]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_rotation::initialisation_par_defaut()
{
    m_parametres[PARAM_ROTATION_MOTS]->set_booleen_par_defaut(true);
    m_parametres[PARAM_ROTATION]->set_choix_par_defaut( rotation::liste_rotations_par_defaut() );
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_rotation::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ROTATION_MOTS, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_CARACTERES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_rotation::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ROTATION, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>rotation</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_rotation::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool rotation_mot =  m_map_IPL[PARAM_ROTATION_MOTS].it_caractere_courant->get_booleen();

    textes t = textes(textes_in);

   /* if ( rotation_mot )
        t.tourner_mots();
    else
        t.tourner_caracteres();
*/
    for ( textes::const_iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        textes_out.ajouter_texte(compil.get_configuration(), *it_t);
}
