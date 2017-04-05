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
#include "entete/parametre/parametre_choix.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_ecriture_en_diagonale.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_ecriture_en_diagonale::fonction_ecriture_en_diagonale( fonctions_conteneur * conteneur )
    : base_fonction(conteneur),
      m_choix_elements( QStringList() << liste_choix::appliquer_sur_caracteres
                                      << liste_choix::appliquer_sur_mots,
                        QStringList() << liste_choix::appliquer_sur_caracteres ),
      m_choix_orientation( QStringList() << liste_choix::de_haut_en_bas
                                         << liste_choix::de_bas_en_haut,
                           QStringList() << liste_choix::de_haut_en_bas )
{
    set_id(f_conversion_ecriture_en_diagonale);
    augmenter_max_niveau_visibilite(1);
    set_niveau_visibilite(1);

    ajouter_parametre( PARAM_ELEMENTS,
                       new parametre_choix( this,
                                            "Éléments à écrire",
                                            "Indique s'il faut écrire les mots ou les caractères.",
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_INVISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_elements,
                                            true) );

    ajouter_parametre( PARAM_ORIENTATION,
                       new parametre_choix( this,
                                            "Orientation de l'écriture",
                                            "Indique s'il faut écrire de haut en bas ou de bas en haut.",
                                            base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                            base_parametre::CONFIGURATION_INVISIBLE,
                                            base_parametre::ALGO_IPL,
                                            m_choix_orientation,
                                            true) );

    ajouter_parametre( PARAM_LIGNES,
                       new base_parametre( this,
                                           "Nombre maximal de lignes",
                                           "Le nombre maximal de lignes à écrire (aucune limite si non spécifié ou égale à 0).",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_MOTS,
                       new base_parametre( this,
                                           "Forcer la rectangularité",
                                           "Indique s'il faut forcer la rectangularité. Ce paramètre est pris en compte seulement si le nombre maximal de lignes est spécifié.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
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
    m_parametres[PARAM_ELEMENTS]->set_choix_par_defaut( m_choix_elements.liste_choix_par_defaut() );
    m_parametres[PARAM_ORIENTATION]->set_choix_par_defaut( m_choix_orientation.liste_choix_par_defaut() );
    m_parametres[PARAM_LIGNES]->set_texte_par_defaut("");
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
            ( PARAM_ELEMENTS, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_ELEMENTS.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ecriture_en_diagonale::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_ORIENTATION, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_ORIENTATION.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ecriture_en_diagonale::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_LIGNES, compil, textes_in, textes_out, & base_fonction::callback_param_3 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_LIGNES.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_ecriture_en_diagonale::callback_param_3( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_MOTS, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
     * \brief Exécute la fonction <b>écriture_en_diagonale</b>.
     * \param compil Le compilateur utilisé.
     * \param textes_in Le texte source en entrée.
     * \param textes_out Le texte de sortie généré.
     */
void fonction_ecriture_en_diagonale::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString choix_elements_a_ecrire = m_map_IPL[PARAM_ELEMENTS].it_mot_courant->to_string();
    QString choix_orientation = m_map_IPL[PARAM_ORIENTATION].it_mot_courant->to_string();
    int nb_lignes_maximales = m_map_IPL[PARAM_LIGNES].it_caractere_courant->get_entier();
    bool forcer_rectangularite = m_map_IPL[PARAM_MOTS].it_caractere_courant->get_booleen();

    if ( m_choix_elements.est_valide( choix_elements_a_ecrire ) &&
         m_choix_orientation.est_valide( choix_orientation ) )
    {
        textes t = textes(textes_in);

        for ( textes::iterator it_t = t.begin(); it_t != t.end(); ++it_t )
        {
            if ( choix_elements_a_ecrire == liste_choix::appliquer_sur_mots )
                it_t->ecrire_mots_en_diagonale(choix_orientation, nb_lignes_maximales, forcer_rectangularite);
            else
                it_t->ecrire_caracteres_en_diagonale(choix_orientation, nb_lignes_maximales, forcer_rectangularite);

            textes_out.ajouter_texte(compil.get_configuration(), *it_t);
        }
    }
}
