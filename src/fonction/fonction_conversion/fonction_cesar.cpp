#include "entete/fonction/fonction_conversion/fonction_cesar.h"

#include "entete/explorateur/noeud_fonction.h"
#include "entete/element/type_element.h"
#include "entete/element/base_element.h"
#include "entete/compilation/compilateur.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/element/texte.h"
#include "entete/parametre/parametre_choix.h"

#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_cesar.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_cesar::fonction_cesar( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{    
    set_id(f_conversion_cesar);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DECALAGE,
                       new base_parametre( this,
                                           "Décalage",
                                           "Le décalage à réaliser.\nPossibilité d'alternance si le mot est une séquence.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_PMIPL) );

    ajouter_parametre( PARAM_ADDITIF,
                       new base_parametre( this,
                                           "Additif",
                                           "Indique si le décalage est additif (Oui ou 1 pour Additif et Non ou 0 pour soustractif).\nPossibilité d'alternance si le mot est une séquence.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_PMIPL) );
    ajouter_parametre( PARAM_ALPHABET,
                       new base_parametre( this,
                                           "Alphabet",
                                           "Alphabets utilisé (chaque mot de la ligne est un alphabet).",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_LIPL) );
}

void fonction_cesar::initialisation_par_defaut()
{
    m_parametres[PARAM_DECALAGE]->set_texte_par_defaut("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", ",", " ", "\n" );
    m_parametres[PARAM_ADDITIF]->set_booleen_par_defaut(true);
    m_parametres[PARAM_ALPHABET]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz");
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_cesar::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

QString fonction_cesar::get_valeur_courte() const
{
    return "[césar]";
}

void fonction_cesar::construire_alphabet()
{
    m_position_alphabet.clear();
    m_alphabets.clear();

    int nb_alphabets = 0;

    for ( ligne::const_iterator it_m = m_map_LIPL[PARAM_ALPHABET].it_debut;
          it_m != m_map_LIPL[PARAM_ALPHABET].it_fin; ++it_m )
    {
        std::vector<base_element> alphabet;

        for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
        {
            alphabet.push_back(*it_c);
            m_position_alphabet[*it_c] = std::pair<int,int>(nb_alphabets, alphabet.size()-1);
        }

        m_alphabets.push_back( alphabet );
        ++nb_alphabets;
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_cesar::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_LIPL_iteration_premier_mot_par_ligne
            ( PARAM_ALPHABET, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre PARAM_ALPHABET.
*/
void fonction_cesar::callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    construire_alphabet();

    algo_PMIPL_iteration_premier_mot_par_ligne
            ( PARAM_ADDITIF, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre PARAM_SOUSTRACTIF.
*/
void fonction_cesar::callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_PMIPL_iteration_premier_mot_par_ligne
            ( PARAM_DECALAGE, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction spécifique : fonction_cesar.
*/
void fonction_cesar::execution_specifique( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t( it_t->get_configuration() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                mot m;
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    std::map<base_element, std::pair<int,int>>::const_iterator it_pos = m_position_alphabet.find(*it_c);
                    if ( it_pos == m_position_alphabet.end() )
                        m.push_back(*it_c);
                    else
                    {
                        int pos;
                        int num_alphabet = it_pos->second.first;

                        if (  m_map_PMIPL[PARAM_ADDITIF].it_courant->get_booleen() )
                            pos = (it_pos->second.second + m_map_PMIPL[PARAM_DECALAGE].it_courant->get_entier()) %
                                    m_alphabets[num_alphabet].size();
                        else
                        {
                            pos = it_pos->second.second - m_map_PMIPL[PARAM_DECALAGE].it_courant->get_entier();
                            if ( pos < 0 )
                                pos += m_alphabets[num_alphabet].size();
                        }

                        PMIPL_suivant(PARAM_ADDITIF);
                        PMIPL_suivant(PARAM_DECALAGE);

                        m.push_back( m_alphabets[num_alphabet][pos] );
                    }
                }
                l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
