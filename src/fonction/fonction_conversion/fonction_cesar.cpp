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

    ajouter_parametre( PARAM_DECALAGE,  new base_parametre( this, "Décalage", "Le décalage à réaliser sur une ligne. Un seul mot par ligne", true,
                                                            type_element_caractere | type_element_entier) );
    ajouter_parametre( PARAM_SOUSTRACTIF, new base_parametre( this, "Soustractif", "Indique si le décalage est soustractif. Un seul mot par ligne", false,
                                                              type_element_booleen) );
    ajouter_parametre( PARAM_ALPHABET, new base_parametre( this, "Alphabet", "Alphabet utilisé sur une ligne. Un seul mot par ligne", false,
                                                           type_element_booleen) );
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_cesar::executer( compilateur &compil, const texte & texte_in, texte & texte_out )
{    
    construire_alphabet();

    executer_selon_soustractif(compil, texte_in, texte_out);
}

void fonction_cesar::initialisation_par_defaut()
{
    m_parametres[PARAM_DECALAGE]->set_texte_par_defaut("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", ",", " ", "\n" );
    m_parametres[PARAM_SOUSTRACTIF]->set_booleen_par_defaut(false);
    m_parametres[PARAM_ALPHABET]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ");
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
bool fonction_cesar::est_valide() const
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

    const texte& t_alphabet = get_texte_parametre(PARAM_ALPHABET);

    if ( t_alphabet.empty() )
    {
        fenetre_principale::s_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                   "Le paramètre alphabet est vide.") );
    }
    else
    {
        texte::const_iterator it_l = t_alphabet.begin();
        for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
            {
                m_alphabet.push_back(*it_c);
                m_position_alphabet[*it_c] = m_alphabet.size()-1;
            }
    }
}

void fonction_cesar::decalage_suivant()
{
    m_it_decalage++;
    if ( m_it_decalage == m_it_decalage_fin )
        m_it_decalage = m_it_decalage_debut;
}

void fonction_cesar::soustractif_suivant()
{
    m_it_soustractif++;
    if ( m_it_soustractif == m_it_soustractif_fin )
        m_it_soustractif = m_it_soustractif_debut;
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre soustractif.
*/
void fonction_cesar::executer_selon_soustractif( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    const texte& t_soustractif = get_texte_parametre(PARAM_SOUSTRACTIF);

    if ( t_soustractif.empty() )
    {
        fenetre_principale::s_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                   "Le paramètre soustractif est vide.") );
    }
    else
    {
        for ( texte::const_iterator it_l = t_soustractif.begin(); it_l != t_soustractif.end(); ++it_l)
        {
            if ( it_l->empty() )
            {
                fenetre_principale::s_vue_logs->ajouter_log
                        ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                           "Le paramètre soustractif est vide sur une ligne.") );
            }
            else
            {
                ligne::const_iterator it_m = it_l->begin();

                if ( it_m->empty() )
                {
                    fenetre_principale::s_vue_logs->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               "Le paramètre soustractif est vide sur une ligne.") );
                }
                else
                {
                    m_it_soustractif_debut = it_m->begin();
                    m_it_soustractif = it_m->begin();
                    m_it_soustractif_fin = it_m->end();

                    executer_selon_decalage(compil, texte_in, texte_out);
                }
            }
        }
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction selon le parametre decalage.
*/
void fonction_cesar::executer_selon_decalage( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    const texte& t_decalage = get_texte_parametre(PARAM_DECALAGE);

    if ( t_decalage.empty() )
    {
        fenetre_principale::s_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                   "Le paramètre decalage est vide.") );
    }
    else
    {
        for ( texte::const_iterator it_l = t_decalage.begin(); it_l != t_decalage.end(); ++it_l )
        {
            if ( it_l->empty() )
            {
                fenetre_principale::s_vue_logs->ajouter_log
                        ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                           "Le paramètre decalage est vide sur une ligne.") );
            }
            else
            {
                ligne::const_iterator it_m = it_l->begin();

                if ( it_m->empty() )
                {
                    fenetre_principale::s_vue_logs->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               "Le paramètre decalage est vide sur une ligne.") );
                }
                else
                {
                    m_it_decalage_debut = it_m->begin();
                    m_it_decalage = it_m->begin();
                    m_it_decalage_fin = it_m->end();

                    executer_cesar(compil, texte_in, texte_out);
                }
            }
        }
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Exécution de la fonction.
*/
void fonction_cesar::executer_cesar( compilateur &compil, const texte & texte_in, texte & texte_out )
{
    for ( texte::const_iterator it_l = texte_in.begin(); it_l != texte_in.end(); ++it_l )
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

                    if ( m_it_soustractif->get_booleen() )
                    {
                        pos = it_pos->second - m_it_decalage->get_entier();
                        if ( pos < 0 )
                            pos += m_alphabet.size();
                    }
                    else
                        pos = (it_pos->second + m_it_decalage->get_entier()) % m_alphabet.size();
                    soustractif_suivant();
                    decalage_suivant();

                    m.push_back( m_alphabet[pos] );
                }
            }
            l.push_back(m);
        }
        texte_out.push_back(l);
    }
}
