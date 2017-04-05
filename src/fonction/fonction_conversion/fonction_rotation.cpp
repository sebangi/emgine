/**
 * \file fonction_rotation.cpp
 * \brief Fichier d'implémentation de la classe fonction_rotation.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_rotation.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/parametre/parametre_choix.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_rotation.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_rotation::fonction_rotation( fonctions_conteneur * conteneur )
    : base_fonction(conteneur),
      m_choix_rotation( QStringList() << liste_choix::rotation_0
                                      << liste_choix::rotation_90
                                      << liste_choix::rotation_180
                                      << liste_choix::rotation_270 ,
                        QStringList() << liste_choix::rotation_90 ),
      m_choix_elements( QStringList() << liste_choix::appliquer_sur_caracteres
                                           << liste_choix::appliquer_sur_mots,
                             QStringList() << liste_choix::appliquer_sur_caracteres )
{
    set_id(f_conversion_rotation);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new parametre_choix( this,
                                            "Éléments à tourner",
                                            "Indique s'il faut appliquer la rotation sur les mots ou sur les caractères.",
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_INVISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_elements,
                                            true) );

    ajouter_parametre( PARAM_ROTATION,
                       new parametre_choix( this,
                                            "La rotation à réaliser",
                                            "Indique quelle rotation réaliser.",
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_VISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_rotation,
                                            true ) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_rotation::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_rotation::get_valeur_courte() const
{
    return "[rotation]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_rotation::initialisation_par_defaut()
{
    m_parametres[PARAM_ELEMENTS]->set_choix_par_defaut( m_choix_elements.liste_choix_par_defaut() );
    m_parametres[PARAM_ROTATION]->set_choix_par_defaut( m_choix_rotation.liste_choix_par_defaut() );
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_rotation::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ELEMENTS, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_ELEMENTS.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_rotation::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ROTATION, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>rotation</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_rotation::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString choix_elements_a_tourner = m_map_IPL[PARAM_ELEMENTS].it_mot_courant->to_string();
    QString choix_rotation( m_map_IPL[PARAM_ROTATION].it_mot_courant->to_string() );

    if ( m_choix_rotation.est_valide( choix_rotation ) && m_choix_elements.est_valide( choix_elements_a_tourner ) )
    {
        textes t = textes(textes_in);

        for ( textes::iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        {
            if ( choix_elements_a_tourner == liste_choix::appliquer_sur_mots )
            {
                if ( ! it_t->est_rectangulaire_selon_mots() )
                    compil.get_vue_logs()->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               "La rotation d'un texte non rectangulaire déforme le texte.") );

                it_t->tourner_mots(choix_rotation);
            }
            else
            {
                if ( ! it_t->est_rectangulaire_selon_caracteres() )
                    compil.get_vue_logs()->ajouter_log
                            ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                               "La rotation d'un texte non rectangulaire déforme le texte.") );

                it_t->tourner_caracteres(choix_rotation);
            }

            textes_out.ajouter_texte(compil.get_configuration(), *it_t);
        }
    }
}
