/** \file fonction_cesar.cpp
 * \brief Fichier d'implémentation de la classe fonction_cesar.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_cesar.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_cesar.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_cesar::fonction_cesar( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{    
    set_id(f_conversion_cesar);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DECALAGE,
                       new base_parametre( this,
                                           "Décalage",
                                           "Le décalage à réaliser.\nPossibilité d'alternance si le mot est une séquence.\n Le premier mot pour la première ligne. Le deuxième mot pour la seconde ligne, etc..",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_ADDITIF,
                       new base_parametre( this,
                                           "Additif",
                                           "Indique si le décalage est additif (Oui ou 1 pour Additif et Non ou 0 pour soustractif).\nPossibilité d'alternance si le mot est une séquence.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_ALPHABET,
                       new base_parametre( this,
                                           "Alphabet",
                                           "Alphabets utilisé (chaque mot de la ligne est un alphabet).",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_TRAITER_PAR_LIGNE,
                       new base_parametre( this,
                                           "Traiter par ligne",
                                           "Indique si le césar se réaliser par ligne, par opposition à tout le texte.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_cesar::initialisation_par_defaut()
{
    m_parametres[PARAM_DECALAGE]->set_texte_par_defaut("0\n1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25", ",", " ", "\n" );
    m_parametres[PARAM_ADDITIF]->set_booleen_par_defaut(true);
    m_parametres[PARAM_ALPHABET]->set_texte_par_defaut("ABCDEFGHIJKLMNOPQRSTUVWXYZ abcdefghijklmnopqrstuvwxyz");
    m_parametres[PARAM_TRAITER_PAR_LIGNE]->set_booleen_par_defaut(false);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_cesar::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_cesar::get_valeur_courte() const
{
    return "[césar]";
}

/** --------------------------------------------------------------------------------------
 * \brief Construit l'alphabet.
 */
void fonction_cesar::construire_alphabet()
{
    m_position_alphabet.clear();
    m_alphabets.clear();

    int nb_alphabets = 0;

    for ( ligne::const_iterator it_m = m_map_IPL[PARAM_ALPHABET].it_ligne_debut;
          it_m != m_map_IPL[PARAM_ALPHABET].it_ligne_fin; ++it_m )
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

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_cesar::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_TRAITER_PAR_LIGNE, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_TRAITER_PAR_LIGNE.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_cesar::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ALPHABET, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_ALPHABET.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_cesar::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    construire_alphabet();

    algo_IPL_iteration_par_ligne
            ( PARAM_ADDITIF, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_ADDITIF.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_cesar::callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_DECALAGE, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>décalage de césar</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_cesar::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            ligne l;
            l.set_separateur_mot( it_l->get_separateur_mot() );
            if ( m_map_IPL[PARAM_TRAITER_PAR_LIGNE].it_caractere_courant->get_booleen() )
            {
                IPL_init(PARAM_ADDITIF);
                IPL_init(PARAM_DECALAGE);
            }

            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m ) {
                mot m;
                m.set_separateur_caractere( it_m->get_separateur_caractere() );
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c ) {
                    std::map<base_element, std::pair<int,int>>::const_iterator it_pos = m_position_alphabet.find(*it_c);
                    if ( it_pos == m_position_alphabet.end() )
                        m.push_back(*it_c);
                    else
                    {
                        int pos;
                        int num_alphabet = it_pos->second.first;

                        if (  m_map_IPL[PARAM_ADDITIF].it_caractere_courant->get_booleen() )
                            pos = (it_pos->second.second + m_map_IPL[PARAM_DECALAGE].it_caractere_courant->get_entier()) %
                                    m_alphabets[num_alphabet].size();
                        else
                        {
                            pos = it_pos->second.second - m_map_IPL[PARAM_DECALAGE].it_caractere_courant->get_entier();
                            if ( pos < 0 )
                                pos += m_alphabets[num_alphabet].size();
                        }

                        IPL_caractere_suivant_dans_mot(PARAM_ADDITIF);
                        IPL_caractere_suivant_dans_mot(PARAM_DECALAGE);

                        m.push_back( m_alphabets[num_alphabet][pos] );
                    }
                }
                l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);

            IPL_mot_suivant(PARAM_DECALAGE);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
