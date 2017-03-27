/**
 * \file fonction_formatage.cpp
 * \brief Fichier d'implémentation de la classe fonction_formatage.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_formatage.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_formatage.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_formatage::fonction_formatage( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_formatage);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_RETRAIT_PONCTUATION,
                       new base_parametre( this,
                                           "Retrait de la ponctuation",
                                           "Indique si la ponctuation est à retirer.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_formatage::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_formatage::get_valeur_courte() const
{
    return "[Formatage]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_formatage::initialisation_par_defaut()
{
    m_parametres[PARAM_RETRAIT_PONCTUATION]->set_booleen_par_defaut(true);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_formatage::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_RETRAIT_PONCTUATION, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>formatage</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_formatage::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
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
                    base_element elem(*it_c);
                    elem.formater( m_map_IPL[PARAM_RETRAIT_PONCTUATION].it_caractere_courant->get_booleen() );
                    if ( ! elem.est_vide() )
                        m.push_back(elem);
                    else if ( ! m.empty() )
                    {
                        l.ajouter_mot(m);
                        m.clear();
                    }
                }
                if ( ! m.empty() )
                    l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
