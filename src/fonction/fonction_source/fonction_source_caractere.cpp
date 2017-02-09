/** \file fonction_source_caractere.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_caractere.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_caractere.h"

#include "entete/compilation/compilateur.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_caractere_widget.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_caractere.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 * \param valeur La valeur initialise de la fonction.
 */
fonction_source_caractere::fonction_source_caractere( fonctions_conteneur * conteneur, QString valeur )
    : fonction_base_source(conteneur), m_valeur(valeur)
{    
    set_id(f_source_caractere);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de al classe fonction_source_caractere.
 */
fonction_source_caractere::~fonction_source_caractere()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_caractere::generer_fonction_widget()
{
    return new fonction_source_caractere_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_caractere::executer( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    mot m;

    for ( int i = 0 ; i != m_valeur.size(); ++i )
    {
        base_element e(m_valeur[i]);
        m.push_back(e);
    }

    ligne l;
    l.ajouter_mot(m);
    texte t;
    t.ajouter_ligne(l);

    textes_out.push_back(t);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_caractere::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_caractere::get_valeur_courte() const
{
    QString resultat;

    resultat += m_valeur;

    return resultat;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction.
 * \return La valeur de la fonction.
 */
QString fonction_source_caractere::get_valeur() const
{
    return m_valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise la valeur de la fonction.
 * \param valeur La nouvelle valeur de la fonction.
 */
void fonction_source_caractere::set_valeur(QString valeur)
{
    m_valeur = valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_caractere::get_string_valeur() const
{
    return m_valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_caractere::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur;
}
