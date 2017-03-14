/**
 * \file fonction_fusion.cpp
 * \brief Fichier d'implémentation de la classe fonction_fusion.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_fusion.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_fusion.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_fusion::fonction_fusion( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_fusion);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);


    ajouter_parametre( PARAM_FUSION_CARACTERES,
                       new base_parametre( this,
                                           "Fusionner les caractères",
                                           "Indique s'il faut fusionner les caractères.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_FUSION_MOTS,
                       new base_parametre( this,
                                           "Fusionner les mots",
                                           "Indique s'il faut fusionner les mots.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_FUSION_LIGNES,
                       new base_parametre( this,
                                           "Fusionner les lignes",
                                           "Indique s'il faut fusionner les lignes.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
    ajouter_parametre( PARAM_FUSION_TEXTES,
                       new base_parametre( this,
                                           "Fusionner les textes",
                                           "Indique s'il faut fusionner les textes.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_fusion::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_fusion::get_valeur_courte() const
{
    return "[fusion]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_fusion::initialisation_par_defaut()
{
    m_parametres[PARAM_FUSION_CARACTERES]->set_booleen_par_defaut(false);
    m_parametres[PARAM_FUSION_MOTS]->set_booleen_par_defaut(false);
    m_parametres[PARAM_FUSION_LIGNES]->set_booleen_par_defaut(false);
    m_parametres[PARAM_FUSION_TEXTES]->set_booleen_par_defaut(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_fusion::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_FUSION_CARACTERES, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_FUSION_CARACTERES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_fusion::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_FUSION_MOTS, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_FUSION_MOTS.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_fusion::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_FUSION_LIGNES, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_FUSION_LIGNES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_fusion::callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_FUSION_TEXTES, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>fusion</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_fusion::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool fusion_caracteres =  m_map_IPL[PARAM_FUSION_CARACTERES].it_caractere_courant->get_booleen();
    bool fusion_mots =  m_map_IPL[PARAM_FUSION_MOTS].it_caractere_courant->get_booleen();
    bool fusion_lignes =  m_map_IPL[PARAM_FUSION_LIGNES].it_caractere_courant->get_booleen();
    bool fusion_textes =  m_map_IPL[PARAM_FUSION_TEXTES].it_caractere_courant->get_booleen();

    textes t = textes(textes_in);
    t.fusionner(fusion_caracteres, fusion_mots, fusion_lignes, fusion_textes);

    for ( textes::const_iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        textes_out.ajouter_texte(compil.get_configuration(), *it_t);

    /*
    texte t;
    ligne l;
    mot m;
    base_element elem;

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        if ( ! fusion_textes )
            t = texte(it_t->get_configuration());

        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            if ( ! fusion_lignes )
                l = ligne();

            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m ) {
                if ( ! fusion_mots )
                    m = mot();

                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    if ( ! fusion_caracteres )
                    {
                        elem = base_element(*it_c);
                        // C code 0 à 7
                        m.push_back(elem);
                    }
                    else
                        elem = base_element( elem.to_string() + it_c->to_string() );
                } // FIN MOT

                // C code 8 à 11
                if ( ! fusion_mots && fusion_caracteres )
                {
                    m.push_back(elem);
                    elem = base_element();
                }

                if ( ! fusion_mots )
                    l.ajouter_mot(m);
            } // FIN LIGNE

            // C code 12 à 13
            if ( ! fusion_lignes && fusion_mots && fusion_caracteres )
            {
                m.push_back(elem);
                elem = base_element();
                l.push_back(m);
                m = mot();
            }

            if ( ! fusion_lignes )
                t.ajouter_ligne(l);
        } // FIN TEXTE

        // C code 14
        if ( ! fusion_textes && fusion_lignes && fusion_mots && fusion_caracteres )
        {
            m.push_back(elem);
            elem = base_element();
            l.push_back(m);
            m = mot();
            t.ajouter_ligne(l);
            l = ligne();
        }
        if ( ! fusion_textes )
            textes_out.ajouter_texte(compil.get_configuration(), t);
    } // FIN TEXTES

    // C code 15
    if ( fusion_textes && fusion_lignes && fusion_mots && fusion_caracteres )
    {
        m.push_back(elem);
        l.push_back(m);
        t.ajouter_ligne(l);
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
    */
}
