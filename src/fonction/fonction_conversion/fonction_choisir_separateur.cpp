/** \file fonction_choisir_separateur.cpp
 * \brief Fichier d'implémentation de la classe fonction_choisir_separateur.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_choisir_separateur.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_choisir_separateur.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 * \param texte Le texte de la fonction.
 */
fonction_choisir_separateur::fonction_choisir_separateur(fonctions_conteneur * conteneur)
    : base_fonction(conteneur)
{
    set_id(f_conversion_choisir_separateur);
    augmenter_max_niveau_visibilite(2);
    set_niveau_visibilite(2);

    ajouter_parametre( PARAM_CARACTERE_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur d'élément"),
                                           base_parametre::tr("Les séparateurs d'éléments."),
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_MOT_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur de mot"),
                                           base_parametre::tr("Les séparateurs de mot."),
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_LIGNE_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur de ligne"),
                                           base_parametre::tr("Les séparateurs de ligne."),
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_choisir_separateur.
 */
fonction_choisir_separateur::~fonction_choisir_separateur()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialise par défaut la fonction.
 */
void fonction_choisir_separateur::initialisation_par_defaut()
{
    initialisation_par_defaut("", " ","\n");
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les paramètres de la fonction.
 * \param separ_caractere Le séparateur de caractères.
 * \param separ_mot Le séparateur de mots.
 * \param separ_ligne Le séparateur de lignes.
 */
void fonction_choisir_separateur::initialisation_par_defaut(QString separ_caractere, QString separ_mot, QString separ_ligne )
{
    m_parametres[PARAM_CARACTERE_SEPARATEUR]->set_caractere_par_defaut(separ_caractere);
    m_parametres[PARAM_MOT_SEPARATEUR]->set_caractere_par_defaut(separ_mot);
    m_parametres[PARAM_LIGNE_SEPARATEUR]->set_caractere_par_defaut(separ_ligne);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_choisir_separateur::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_LIGNE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_LIGNE_SEPARATEUR.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_choisir_separateur::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_MOT_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_MOT_SEPARATEUR.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_choisir_separateur::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
            ( PARAM_CARACTERE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>fonction_texte</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_choisir_separateur::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString t_caractere = m_map_IPL[PARAM_CARACTERE_SEPARATEUR].it_mot_courant->to_string();
    QString t_mot = m_map_IPL[PARAM_MOT_SEPARATEUR].it_mot_courant->to_string();
    QString t_ligne = m_map_IPL[PARAM_LIGNE_SEPARATEUR].it_mot_courant->to_string();

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t( it_t->get_configuration(), t_ligne );
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;
            l.set_separateur_mot( t_mot );
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
            {
                mot m;
                m.set_separateur_caractere( t_caractere );
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                    m.push_back(*it_c);
                l.ajouter_mot(m);
            }
            t.ajouter_ligne(l);
        }
        textes_out.ajouter_texte(compil.get_configuration(), t);
    }
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_choisir_separateur::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_choisir_separateur::get_valeur_courte() const
{
    return base_fonction::tr("[choix des séparateurs]");
}
