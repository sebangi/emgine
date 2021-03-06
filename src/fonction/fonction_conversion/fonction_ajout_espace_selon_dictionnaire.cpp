/** \file fonction_ajout_espace_selon_dictionnaire.cpp
 * \brief Fichier d'implémentation de la classe fonction_ajout_espace_selon_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_ajout_espace_selon_dictionnaire.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_ajout_espace_selon_dictionnaire.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_ajout_espace_selon_dictionnaire::fonction_ajout_espace_selon_dictionnaire( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_ajout_espace_selon_dictionnaire);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_DICTIONNAIRE,
                       new base_parametre( this,
                                           base_parametre::tr("Dictionnaire"),
                                           base_parametre::tr("Dictionnaire utilisé."),
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_AUCUN) );
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_ajout_espace_selon_dictionnaire::initialisation_par_defaut()
{
    m_parametres[PARAM_DICTIONNAIRE]->set_dictionnaire_par_defaut( "mes_projets/dico.txt" );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_ajout_espace_selon_dictionnaire::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_ajout_espace_selon_dictionnaire::get_valeur_courte() const
{
    return base_fonction::tr("[Ajout d'espaces selon dictionnaire]");
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ajout_espace_selon_dictionnaire::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    const textes & textes_dico = m_parametres[PARAM_DICTIONNAIRE]->get_textes_out();

    if ( textes_dico.empty() )
        return;

    const dictionnaire * dico = compil.get_dictionnaire( textes_dico[0].to_string() );
    if ( dico == NULL )
        return;

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;
            l.set_separateur_mot( it_l->get_separateur_mot() );
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                QString s_m = it_m->to_string();

                while ( ! s_m.isEmpty() )
                {
                    QString plus_grand_prefixe = dico->plus_grand_prefixe(s_m);

                    int taille = plus_grand_prefixe.size();
                    if ( taille == 0 )
                    {
                        taille = 1;
                        plus_grand_prefixe = s_m.mid(0,1);
                    }

                    mot m;
                    m.set_separateur_caractere( it_m->get_separateur_caractere() );
                    for ( int i = 0; i != plus_grand_prefixe.size(); ++i )
                        m.push_back( base_element( plus_grand_prefixe[i] ) );
                    l.ajouter_mot( m );
                    s_m.remove(0,taille);
                }
            }
            t.ajouter_ligne(l);
        }

        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}
