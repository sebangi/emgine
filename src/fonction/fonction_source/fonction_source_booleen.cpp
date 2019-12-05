/** \file fonction_source_booleen.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_booleen.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_booleen.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/mot.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_booleen_widget.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_booleen.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 * \param valeur La valeur initiale de la fonction.
 */
fonction_source_booleen::fonction_source_booleen(fonctions_conteneur * conteneur,  bool valeur )
    : fonction_base_source(conteneur), m_valeur(valeur)
{
    set_id(f_source_booleen);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_booleen.
 */
fonction_source_booleen::~fonction_source_booleen()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_booleen::generer_fonction_widget()
{
    return new fonction_source_booleen_widget(this);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_booleen::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_booleen::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    textes_out = textes_in;

    base_element e(m_valeur);
    mot m;
    m.push_back(e);
    ligne l;
    l.ajouter_mot(m);
    texte t;
    t.ajouter_ligne(l);

    textes_out.push_back(t);
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_booleen::get_valeur_courte() const
{
    if ( m_valeur )
        return base_fonction::tr("oui");
    else
        return base_fonction::tr("non");
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction.
 * \return La valeur de la fonction.
 */
bool fonction_source_booleen::get_valeur() const
{
    return m_valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise la valeur de la fonction.
 * \param valeur La nouvelle valeur de la fonction.
 */
void fonction_source_booleen::set_valeur(bool valeur)
{
    m_valeur = valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_booleen::get_string_valeur() const
{
    return QString::number(m_valeur);
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_booleen::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur != "0";
}
