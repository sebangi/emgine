/**
 * \file fonction_source_ensemble_sources.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_ensemble_sources.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_ensemble_sources.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/base_fonction_widget.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_ensemble_sources.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_source_ensemble_sources::fonction_source_ensemble_sources(fonctions_conteneur * conteneur)
    : fonction_base_source(conteneur)
{
    set_id(f_source_ensemble_sources);

    ajouter_parametre( PARAM_TEXTES,
                       new base_parametre( this,
                                           "Sources",
                                           "Les textes sources.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_AUCUN) );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_ensemble_sources.
 */
fonction_source_ensemble_sources::~fonction_source_ensemble_sources()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_ensemble_sources::generer_fonction_widget()
{
    return new base_fonction_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les paramètres de la fonction.
 */
void fonction_source_ensemble_sources::initialisation_par_defaut()
{
    m_parametres[PARAM_TEXTES]->set_texte_par_defaut("");
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_ensemble_sources::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    textes_out = textes_in;

    // ajout de l'ensemble
    const textes & sources = m_parametres[PARAM_TEXTES]->get_textes_out();
    for ( textes::const_iterator it_t = sources.begin(); it_t != sources.end(); ++it_t )
        textes_out.ajouter_texte(compil.get_configuration(), *it_t);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_ensemble_sources::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_ensemble_sources::get_valeur_courte() const
{
    return "ensemble de textes ";
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_ensemble_sources::get_string_valeur() const
{
    return "";
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param nom_fichier La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_ensemble_sources::set_string_valeur(const QString &nom_fichier)
{
}
