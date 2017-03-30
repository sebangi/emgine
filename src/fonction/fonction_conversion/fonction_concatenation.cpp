/**
 * \file fonction_concatenation.cpp
 * \brief Fichier d'implémentation de la classe fonction_concatenation.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_concatenation.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_concatenation.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_concatenation::fonction_concatenation( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_concatenation);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_TEXTES,
                       new base_parametre( this,
                                           "Le texte à concaténer",
                                           "Le texte à concaténer.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_AUCUN) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_concatenation::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_concatenation::get_valeur_courte() const
{
    return "[concatenation]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_concatenation::initialisation_par_defaut()
{
    m_parametres[PARAM_TEXTES]->set_texte_par_defaut("Texte à concaténer");
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_concatenation::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    const textes& t1 = m_parametres[PARAM_TEXTES]->get_textes_out();

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
        for ( textes::const_iterator it_t1 = t1.begin(); it_t1 != t1.end(); ++it_t1 )
        {
            texte nouveau(*it_t);
            nouveau.ajouter_texte(*it_t1);
            textes_out.ajouter_texte(compil.get_configuration(), nouveau);
        }
}
