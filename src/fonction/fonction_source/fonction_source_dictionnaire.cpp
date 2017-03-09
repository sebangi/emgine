/** \file fonction_source_dictionnaire.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_dictionnaire.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_dictionnaire.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_dictionnaire_widget.h"

#include <QFile>
#include <QTextStream>

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_dictionnaire.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_source_dictionnaire::fonction_source_dictionnaire(fonctions_conteneur * conteneur)
    : fonction_base_source(conteneur), m_nom_fichier("")
{
    set_id(f_source_dictionnaire);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_dictionnaire.
 */
fonction_source_dictionnaire::~fonction_source_dictionnaire()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_dictionnaire::generer_fonction_widget()
{
    return new fonction_source_dictionnaire_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_dictionnaire::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    ligne l(m_nom_fichier);
    texte t;
    t.ajouter_ligne(l);
    textes_out.push_back(t);

    compil.ajouter_dictionnaire(m_nom_fichier);
}


/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_dictionnaire::est_valide(logs_compilation_widget * vue_logs)
{
    QFile file(m_nom_fichier);

    if (! file.open(QIODevice::ReadOnly))
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "La fonction \"" + get_nom() +
                                   "\" charge un dictionnaire inexistant ou erroné.") );
        return false;
    }

    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_dictionnaire::get_valeur_courte() const
{
    return "Dictionnaire " + m_nom_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nom de fichier source.
 * \return Le nom du fichier source.
 */
QString fonction_source_dictionnaire::get_nom_fichier() const
{
    return m_nom_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le nom du fichier source.
 * \param nom_fichier Le nouveau nom de fichier source.
 */
void fonction_source_dictionnaire::set_nom_fichier(QString nom_fichier)
{
    m_nom_fichier = nom_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_dictionnaire::get_string_valeur() const
{
    return m_nom_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param nom_fichier La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_dictionnaire::set_string_valeur(const QString &nom_fichier)
{
    m_nom_fichier = nom_fichier;
}