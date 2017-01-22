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
    : base_fonction(conteneur, "Chiffrement par Code César")
{    
    set_id(f_conversion_cesar);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DECALAGE,
                       new base_parametre( this, "Décalage", "Le décalage à réaliser (sur un mot). Itération sur les lignes", true) );
    ajouter_parametre( PARAM_SOUSTRACTIF,
                       new base_parametre( this, "Soustractif", "Indique si le décalage est soustractif (sur un mot).  Itération sur les lignes", false) );
    ajouter_parametre( PARAM_ALPHABET,
                       new base_parametre( this, "Alphabet", "Alphabet utilisé (sur un mot). Itération sur les lignes", false) );
}

void fonction_cesar::initialisation_par_defaut()
{
    m_parametres[PARAM_DECALAGE]->set_texte_par_defaut("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", ",", " ", "\n" );
    m_parametres[PARAM_SOUSTRACTIF]->set_booleen_par_defaut(false);
    m_parametres[PARAM_ALPHABET]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ\nabcdefghijklmnopqrstuvwxyz");
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_cesar::get_aide() const
{
    return QString("Outil pour décoder/encoder avec César.\nLe code César (ou chiffre de César) est un chiffrement par décalage parmi les plus simples et les plus connu, il utilise la substitution d'une lettre par une autre plus loin dans l'alphabet.");
}

/*! --------------------------------------------------------------------------------------
 \brief Indique si la fonction est valide.
*/
bool fonction_cesar::est_valide(logs_compilation_widget * vue_logs) const
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
    m_alphabet.clear();

    for ( mot::const_iterator it_c = m_map_IPMPL_debut[PARAM_ALPHABET];
          it_c != m_map_IPMPL_fin[PARAM_ALPHABET]; ++it_c )
    {
        m_alphabet.push_back(*it_c);
        m_position_alphabet[*it_c] = m_alphabet.size()-1;
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_cesar::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_IPMPL_iteration_premier_mot_par_ligne
            ( PARAM_ALPHABET, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre PARAM_ALPHABET.
*/
void fonction_cesar::callback_param_1( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    construire_alphabet();

    algo_IPMPL_iteration_premier_mot_par_ligne
            ( PARAM_SOUSTRACTIF, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre PARAM_SOUSTRACTIF.
*/
void fonction_cesar::callback_param_2( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    algo_IPMPL_iteration_premier_mot_par_ligne
            ( PARAM_DECALAGE, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre PARAM_DECALAGE.
*/
void fonction_cesar::callback_param_3( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t;
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                mot m;
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    std::map<base_element, int>::const_iterator it_pos = m_position_alphabet.find(*it_c);
                    if ( it_pos == m_position_alphabet.end() )
                        m.push_back(*it_c);
                    else
                    {
                        int pos;

                        if (  m_map_IPMPL_courant[PARAM_SOUSTRACTIF]->get_booleen() )
                        {
                            pos = it_pos->second - m_map_IPMPL_courant[PARAM_DECALAGE]->get_entier();
                            if ( pos < 0 )
                                pos += m_alphabet.size();
                        }
                        else
                            pos = (it_pos->second + m_map_IPMPL_courant[PARAM_DECALAGE]->get_entier()) % m_alphabet.size();

                        IPMPL_suivant(PARAM_SOUSTRACTIF);
                        IPMPL_suivant(PARAM_DECALAGE);

                        m.push_back( m_alphabet[pos] );
                    }
                }
                l.push_back(m);
            }
            t.push_back(l);
        }
        textes_out.push_back(t);
    }
}
