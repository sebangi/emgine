/**
 * \file fonction_transposition.cpp
 * \brief Fichier d'implémentation de la classe fonction_transposition.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_transposition.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/parametre/parametre_choix.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_transposition.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_transposition::fonction_transposition( fonctions_conteneur * conteneur )
    : base_fonction(conteneur),
      m_choix_elements( QStringList() << liste_choix::appliquer_sur_caracteres
                                      << liste_choix::appliquer_sur_mots,
                        QStringList() << liste_choix::appliquer_sur_caracteres )
{
    set_id(f_conversion_transposition);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new parametre_choix( this,
                                            base_parametre::tr("Éléments à transposer"),
                                            base_parametre::tr("Indique s'il faut transposer sur les mots ou sur les caractères."),
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_INVISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_elements,
                                            true) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_transposition::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_transposition::get_valeur_courte() const
{
    return base_fonction::tr("[transposition]");
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_transposition::initialisation_par_defaut()
{
    m_parametres[PARAM_ELEMENTS]->set_choix_par_defaut( m_choix_elements.liste_choix_par_defaut() );
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_transposition::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ELEMENTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>transposition</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_transposition::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString choix_elements_a_transposer =  m_map_IPL[PARAM_ELEMENTS].it_mot_courant->to_string();

    if ( m_choix_elements.est_valide( choix_elements_a_transposer ) )
    {
        textes t = textes(textes_in);

        for ( textes::iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        {
            if ( choix_elements_a_transposer == liste_choix::appliquer_sur_mots )
            {
                if ( ! it_t->est_rectangulaire_selon_mots() )
                    compil.get_vue_logs()->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               base_fonction::tr("La transposition d'un texte non rectangulaire déforme le texte.")) );

                it_t->transposer_mots();
            }
            else
            {
                if ( ! it_t->est_rectangulaire_selon_caracteres() )
                    compil.get_vue_logs()->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               base_fonction::tr("La transposition d'un texte non rectangulaire déforme le texte.")) );

                it_t->transposer_caracteres();
            }

            textes_out.ajouter_texte(compil.get_configuration(), *it_t);
        }
    }
}
