/**
 * \file fonction_ecriture_en_diagonale.cpp
 * \brief Fichier d'implémentation de la classe fonction_ecriture_en_diagonale.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_ecriture_en_diagonale.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/base_element.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_ecriture_en_diagonale.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_ecriture_en_diagonale::fonction_ecriture_en_diagonale( fonctions_conteneur * conteneur )
    : base_fonction(conteneur)
{
    set_id(f_conversion_ecriture_en_diagonale);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);

    ajouter_parametre( PARAM_MOTS,
                       new base_parametre( this,
                                           "Écrire les mots en diagonale (au lieu des caractères",
                                           "Indique s'il faut écrire suivant les mots.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_ecriture_en_diagonale::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_ecriture_en_diagonale::get_valeur_courte() const
{
    return "[ecriture_en_diagonale]";
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_ecriture_en_diagonale::initialisation_par_defaut()
{
    m_parametres[PARAM_MOTS]->set_booleen_par_defaut(true);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ecriture_en_diagonale::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_MOTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>ecriture_en_diagonale</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_ecriture_en_diagonale::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    bool ecriture_en_diagonale_mot =  m_map_IPL[PARAM_MOTS].it_caractere_courant->get_booleen();

    textes t = textes(textes_in);

    for ( textes::iterator it_t = t.begin(); it_t != t.end(); ++it_t )
    {
        if ( ecriture_en_diagonale_mot )
        {
            if ( ! it_t->est_rectangulaire_selon_mots() )
                compil.get_vue_logs()->ajouter_log
                        ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                           "La ecriture_en_diagonale d'un texte non rectangulaire déforme le texte.") );

            it_t->transposer_mots();
        }
        else
        {
            if ( ! it_t->est_rectangulaire_selon_caracteres() )
                compil.get_vue_logs()->ajouter_log
                        ( log_compilation( log_compilation::LOG_WARNING, (base_fonction*)this,
                                           "La ecriture_en_diagonale d'un texte non rectangulaire déforme le texte.") );

            it_t->transposer_caracteres();
        }

        textes_out.ajouter_texte(compil.get_configuration(), *it_t);
    }
}
