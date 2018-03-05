/**
 * \file fonction_substitution.cpp
 * \brief Fichier d'implémentation de la classe fonction_substitution.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_substitution.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_substitution.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/fonction_substitution::fonction_substitution( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_substitution);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_CARACTERES_ENTREE,
                       new base_parametre( this,
                                           "Entrée du dictionnaire",
                                           "Les caractères en entrée du dictionnaire.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_CARACTERES_SORTIE,
                       new base_parametre( this,
                                           "Sortie du dictionnaire",
                                           "Les caractères de sortie du dictionnaire.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_CARACTERES,
                       new base_parametre( this,
                                           "Garder les inconnus",
                                           "Les caractères inconnus sont-ils gardés ou bien remplacé par *.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_NUMERO_CHOIX,
                       new base_parametre( this,
                                           "Numéro du choix",
                                           "Les numéro de choix à utiliser dans le cas d'un alphabet polyalphabétique.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_substitution::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_substitution::get_valeur_courte() const
{
    return "[substitution]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_substitution::initialisation_par_defaut()
{
    m_parametres[PARAM_CARACTERES_ENTREE]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
    m_parametres[PARAM_CARACTERES_SORTIE]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ");    
    m_parametres[PARAM_NUMERO_CHOIX]->set_texte_par_defaut("");
    m_parametres[PARAM_CARACTERES]->set_booleen_par_defaut(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_substitution::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERES_ENTREE, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_CARACTERES_ENTREE.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_substitution::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERES_SORTIE, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_CARACTERES_SORTIE.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_substitution::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_NUMERO_CHOIX, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_CARACTERES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_substitution::callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERES, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>substitution</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_substitution::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    construire_map_substitution();
    bool garder_inconnu =  m_map_IPL[PARAM_CARACTERES].it_caractere_courant->get_booleen();

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            ligne l;
            l.set_separateur_mot( it_l->get_separateur_mot() );
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m ) {
                mot m;
                m.set_separateur_caractere( it_m->get_separateur_caractere() );
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    type_map_substitution::iterator it = m_substitution.find( *it_c );

                    if ( it == m_substitution.end() )
                    {
                        if ( garder_inconnu )
                            m.push_back( *it_c );
                        else
                            m.push_back( base_element::element_inconnu() );
                    }
                    else if ( it->second.empty() )
                    {
                        if ( garder_inconnu )
                            m.push_back( *it_c );
                        else
                            m.push_back( base_element::element_inconnu() );
                    }
                    else if ( IPL_test_vide(PARAM_NUMERO_CHOIX) )
                    {
                        if ( it->second.size() == 1 )
                            m.push_back( it->second[0] );
                        else
                        {
                            QString s("(" + it->second[0].to_string() );
                            for( unsigned int i = 1; i < it->second.size();  ++i )
                                s += "|" + it->second[i].to_string();
                            s += ")";
                            m.push_back( base_element(s) );
                        }
                    }
                    else
                    {
                        int pos = m_map_IPL[PARAM_NUMERO_CHOIX].it_caractere_courant->get_entier();
                        if ( pos <= 0 || pos > it->second.size() )
                        {
                            if ( garder_inconnu )
                                m.push_back( *it_c );
                            else
                                    m.push_back( base_element::element_inconnu() );
                        }
                        else
                            m.push_back( it->second[pos-1] );
                    }

                    if ( ! IPL_test_vide(PARAM_NUMERO_CHOIX) )
                        IPL_caractere_suivant_dans_ligne(PARAM_NUMERO_CHOIX);
                }
                l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Construit la map de substitution.
 */
void fonction_substitution::construire_map_substitution()
{
    m_substitution.clear();
    std::vector< base_element > tab_entree;

    for ( ligne::const_iterator it_m = m_map_IPL[PARAM_CARACTERES_ENTREE].it_ligne_debut;
          it_m != m_map_IPL[PARAM_CARACTERES_ENTREE].it_ligne_fin; ++it_m )
        for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
        {
            tab_entree.push_back( *it_c );
            m_substitution[*it_c] = type_vector_element();
        }

    if ( ! tab_entree.empty() )
    {
        unsigned int i = 0;
        for ( ligne::const_iterator it_m = m_map_IPL[PARAM_CARACTERES_SORTIE].it_ligne_debut;
              it_m != m_map_IPL[PARAM_CARACTERES_SORTIE].it_ligne_fin; ++it_m )
            for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
            {
                m_substitution[ tab_entree[i] ].push_back( *it_c );
                ++i;
                if ( i >= tab_entree.size() )
                    i = 0;
            }
    }
}
