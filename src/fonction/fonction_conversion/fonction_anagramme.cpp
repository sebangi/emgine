/**
 * \file fonction_anagramme.cpp
 * \brief Fichier d'implémentation de la classe fonction_anagramme.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_anagramme.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_anagramme.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_anagramme::fonction_anagramme( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_anagramme);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DICTIONNAIRE,
                       new base_parametre( this,
                                           "Dictionnaire",
                                           "Dictionnaire utilisé.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_AUCUN) );
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_anagramme::initialisation_par_defaut()
{
    m_parametres[PARAM_DICTIONNAIRE]->set_dictionnaire_par_defaut( "mes_projets/dico.txt" );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_anagramme::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_anagramme::get_valeur_courte() const
{
    return "[Anagramme]";
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_anagramme::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    const textes & textes_dico = m_parametres[PARAM_DICTIONNAIRE]->get_textes_out();

    if ( textes_dico.empty() )
        return;

    const dictionnaire * dico = compil.get_dictionnaire( textes_dico[0].to_string() );
    if ( dico == NULL )
        return;

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        texte t( it_t->get_configuration() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                ligne l;
                QString s_m = it_m->to_string();

                dictionnaire::uint_set mots;
                dico->anagramme( s_m, mots );
                l.ajouter_mot( mot(s_m + " :") );

                for ( dictionnaire::uint_set::const_iterator it = mots.begin(); it != mots.end(); ++it )
                    l.ajouter_mot( mot( (*dico)[*it] ) );

                t.ajouter_ligne(l);
            }
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
