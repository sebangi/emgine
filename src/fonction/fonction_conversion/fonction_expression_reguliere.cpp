/**
 * \file fonction_expression_reguliere.cpp
 * \brief Fichier d'implémentation de la classe fonction_expression_reguliere.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_expression_reguliere.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_expression_reguliere.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_expression_reguliere::fonction_expression_reguliere( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_expression_reguliere);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DICTIONNAIRE,
                       new base_parametre( this,
                                           "Dictionnaire",
                                           "Dictionnaire utilisé.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_AUCUN) );

    ajouter_parametre( PARAM_LIGNES,
                       new base_parametre( this,
                                           "Générer un texte par mot",
                                           "Indique si chaque mot en entrée génère un texte avec toutes les possibilités.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_expression_reguliere::initialisation_par_defaut()
{
    m_parametres[PARAM_DICTIONNAIRE]->set_dictionnaire_par_defaut( "mes_projets/dico.txt" );
    m_parametres[PARAM_LIGNES]->set_booleen_par_defaut( false );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_expression_reguliere::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_expression_reguliere::get_valeur_courte() const
{
    return "[expression_reguliere]";
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_expression_reguliere::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_LIGNES, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>expression_reguliere</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
*/
void fonction_expression_reguliere::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool un_mot_par_ligne = m_map_IPL[PARAM_LIGNES].it_caractere_courant->get_booleen();
    const textes & textes_dico = m_parametres[PARAM_DICTIONNAIRE]->get_textes_out();

    if ( textes_dico.empty() )
        return;

    const dictionnaire * dico = compil.get_dictionnaire( textes_dico[0].to_string() );
    if ( dico == NULL )
        return;

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;
            l.set_separateur_mot( it_l->get_separateur_mot() );
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                QString s_m = it_m->to_string();

                dictionnaire::qstring_set mots;
                dico->recherche_expression_reguliere( s_m, mots );

                if ( ! mots.empty())
                {
                    dictionnaire::qstring_set::const_iterator it = mots.begin();

                    if ( un_mot_par_ligne )
                    {
                        for ( ; it != mots.end(); ++it )
                        {
                            l.ajouter_mot( mot( *it, it_m->get_separateur_caractere() ) );
                            if ( ! l.empty() )
                            {
                                t.ajouter_ligne(l);
                                l = ligne();
                            }
                        }
                        if ( ! t.empty() )
                        {
                            t.scinder(true,false,false);
                            textes_out.ajouter_texte(compil.get_configuration(), t);
                            t = texte( it_t->get_configuration(), it_t->get_separateur_ligne() );
                        }
                    }
                    else
                    {
                        if ( mots.size() > 1 )
                            l.ajouter_mot( mot("(", it_m->get_separateur_caractere() ) );

                        l.ajouter_mot( mot( *it, it_m->get_separateur_caractere() ) );

                        for ( ++it; it != mots.end(); ++it )
                        {
                            l.ajouter_mot( mot( "|", it_m->get_separateur_caractere() ) );
                            l.ajouter_mot( mot( *it, it_m->get_separateur_caractere() ) );
                        }

                        if ( mots.size() > 1 )
                            l.ajouter_mot( mot(")", it_m->get_separateur_caractere() ) );
                    }
                }
            }
            if ( ! l.empty() && ! un_mot_par_ligne )
                t.ajouter_ligne(l);
        }
        if ( ! t.empty() )
        {
            t.scinder(true,false,false);
            textes_out.ajouter_texte(compil.get_configuration(), t);
        }
    }
}
