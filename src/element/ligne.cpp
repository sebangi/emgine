/** \file ligne.cpp
 * \brief Fichier d'implémentation de la classe ligne.
 * \author Sébastien Angibaud
 */

#include "entete/element/ligne.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe ligne.
 */
ligne::ligne()
    : vector<mot>(), m_separateur_mot(" "), m_nb_caracteres(0)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe ligne.
 * \param valeur La chaîne de caractères représentant la ligne.
 * \param separateur_mot Le séparateur des mots.
 */
ligne::ligne(const QString &valeur, const QString & separateur_mot)
    : vector<mot>(), m_separateur_mot(separateur_mot), m_nb_caracteres(0)
{
    if ( ! valeur.isEmpty() )
    {
        mot m(valeur);
        ajouter_mot(m);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un mot à la ligne.
 * \param m Le mot à ajouter.
 */
void ligne::ajouter_mot( const mot & m)
{
    push_back(m);
    m_nb_caracteres += m.nb_caracteres();
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit et retourne la ligne au format QString.
 * \return La ligne en format QString.
 */
QString ligne::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit et retourne la ligne au format QString avec l'ajout de séparateur.
 * \return La ligne en format QString.
 */
QString ligne::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += " " + this->at(i).to_string_lisible();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractères de la ligne.
 * \return Le nombre de caractères de la ligne.
 */
std::vector<mot>::size_type ligne::nb_caracteres() const
{
    return m_nb_caracteres;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de mots de la ligne.
 * \return Le nombre de mots de la ligne.
 */
std::vector<mot>::size_type ligne::nb_mots() const
{
    return size();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'infériorité stricte.
 * \param l La ligne comparée.
 * \return \b True si la ligne courante est inférieur strictement, \b False sinon.
 */
bool ligne::operator<(const ligne & l) const
{
    return to_string() < l.to_string();
}

