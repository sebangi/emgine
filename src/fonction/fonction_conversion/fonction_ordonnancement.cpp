/**
 * \file fonction_ordonnancement.cpp
 * \brief Fichier d'implémentation de la classe fonction_ordonnancement.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_ordonnancement.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/parametre/parametre_choix.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_ordonnancement.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_ordonnancement::fonction_ordonnancement( fonctions_conteneur * conteneur )
    : base_fonction(conteneur),
      m_choix_elements( QStringList() << liste_choix::appliquer_sur_caracteres
                                      << liste_choix::appliquer_sur_mots,
                        QStringList() << liste_choix::appliquer_sur_caracteres )
{
    set_id(f_conversion_ordonnancement);
    augmenter_max_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new parametre_choix( this,
                                            "Éléments à ordonner",
                                            "Indique s'il faut appliquer l'ordonnancement sur les mots ou sur les caractères.",
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_INVISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_elements,
                                            true) );

    ajouter_parametre( PARAM_ORDRE,
                       new base_parametre( this,
                                           "Ordre",
                                           "L'ordre à considérer.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_TRAITER_PAR_LIGNE,
                       new base_parametre( this,
                                           "Traiter par ligne",
                                           "Indique si le ré-ordonnancement se réalise par ligne, par opposition à tout le texte.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_VISIBLE,
                                           base_parametre::ALGO_IPL) );

}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_ordonnancement::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_ordonnancement::get_valeur_courte() const
{
    return "[ordonnancement]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_ordonnancement::initialisation_par_defaut()
{
    m_parametres[PARAM_ELEMENTS]->set_choix_par_defaut( m_choix_elements.liste_choix_par_defaut() );
    m_parametres[PARAM_TRAITER_PAR_LIGNE]->set_booleen_par_defaut(false);
    m_parametres[PARAM_ORDRE]->set_texte_par_defaut("1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20", ",", " ", "\n" );
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ordonnancement::executer( compilateur &compil, textes & textes_in, textes & textes_out )
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
void fonction_ordonnancement::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_TRAITER_PAR_LIGNE, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_TRAITER_PAR_LIGNE.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ordonnancement::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ORDRE, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>ordonnancement</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_ordonnancement::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    mot mot_par_defaut("?");
    QString choix_elements_a_ordonner = m_map_IPL[PARAM_ELEMENTS].it_mot_courant->to_string();

    if ( m_choix_elements.est_valide( choix_elements_a_ordonner ) )
    {
        textes t = textes(textes_in);

        if ( choix_elements_a_ordonner == liste_choix::appliquer_sur_caracteres )
            t.scinder(false,true,false,false);

        if ( ! m_map_IPL[PARAM_TRAITER_PAR_LIGNE].it_caractere_courant->get_booleen() )
             t.fusionner(false,false,true,false);

        for ( textes::const_iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        {
            texte t( it_t->get_configuration(), it_t->get_separateur_ligne() );
            for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
            {
                ligne l;
                l.set_separateur_mot( it_l->get_separateur_mot() );
                if ( m_map_IPL[PARAM_TRAITER_PAR_LIGNE].it_caractere_courant->get_booleen() )
                    IPL_init(PARAM_ORDRE);

                for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
                {
                    int pos = m_map_IPL[PARAM_ORDRE].it_caractere_courant->get_entier() - 1;
                    IPL_caractere_suivant_dans_ligne(PARAM_ORDRE);
                    l.ajouter_mot( it_l->mot_a_la_position(pos, mot_par_defaut) );
                }
                t.ajouter_ligne(l);

                IPL_mot_suivant(PARAM_DECALAGE);
            }
            if ( choix_elements_a_ordonner == liste_choix::appliquer_sur_caracteres )
                t.fusionner(false,true,false);
            textes_out.ajouter_texte(compil.get_configuration(), t);
        }
    }
}

