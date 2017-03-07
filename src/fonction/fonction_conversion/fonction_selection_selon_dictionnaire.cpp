/** \file fonction_selection_selon_dictionnaire.cpp
 * \brief Fichier d'implémentation de la classe fonction_selection_selon_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_selection_selon_dictionnaire.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_selection_selon_dictionnaire.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_selection_selon_dictionnaire::fonction_selection_selon_dictionnaire( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_selection_selon_dictionnaire);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_selection_selon_dictionnaire::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_selection_selon_dictionnaire::get_valeur_courte() const
{
    return "[Selection selon dictionnaire]";
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_selection_selon_dictionnaire::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    // TODO : tout à modifier quand le grep du dico sera fait
    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t ) {
        texte t( it_t->get_configuration() );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l ) {
            ligne l;
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m ) {
                mot m;
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                {
                    base_element elem(*it_c);
                    elem.formater( m_map_PMIPL[PARAM_RETRAIT_PONCTUATION].it_courant->get_booleen() );
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
