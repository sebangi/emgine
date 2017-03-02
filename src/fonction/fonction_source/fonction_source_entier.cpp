/** \file fonction_source_entier.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_entier.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_entier.h"

#include "entete/compilation/compilateur.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_entier.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 * \param valeur La valeur initiale de la fonction.
 */
fonction_source_entier::fonction_source_entier(fonctions_conteneur * conteneur, int valeur)
    : fonction_base_source(conteneur), m_valeur(valeur)
{    
    set_id(f_source_entier);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_entier.
 */
fonction_source_entier::~fonction_source_entier()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_entier::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
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
QString fonction_source_entier::get_valeur_courte() const
{
    return QString::number(m_valeur);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction.
 * \return La valeur de la fonction.
 */
int fonction_source_entier::get_valeur() const
{
    return m_valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise la valeur de la fonction.
 * \param valeur La nouvelle valeur de la fonction.
 */
void fonction_source_entier::set_valeur(int valeur)
{
    m_valeur = valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_entier::get_string_valeur() const
{
    return QString::number(m_valeur);
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_entier::set_string_valeur(const QString &valeur)
{
    m_valeur = valeur.toInt();
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_entier::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}
