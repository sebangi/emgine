/** \file mot.cpp
 * \brief Fichier d'implémentation de la classe mot.
 * \author Sébastien Angibaud
 */

#include "entete/element/mot.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe mot.
 */
mot::mot()
    : vector<base_element>(), m_separateur_caractere("")
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe mot.
 * \param valeur La chaîne de caractères représentant la ligne.
 * \param separateur_caractere Le séparateur de caractères.
 */
mot::mot(const QString &valeur, const QString & separateur_caractere)
    : vector<base_element>(), m_separateur_caractere(separateur_caractere)
{
    if ( ! valeur.isEmpty())
    {
        base_element e(valeur);
        push_back(e);
    }
}


/** --------------------------------------------------------------------------------------
 * \brief Constructeur par copie de la classe mot.
 * \param m Le mot à copier.
 */
mot::mot(const mot &m)
    : vector<base_element>(m), m_separateur_caractere(m.m_separateur_caractere)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le séparateur de caractères.
 * \param separateur_caractere Le séparateur de caractères.
 */void mot::set_separateur_caractere(const QString &separateur_caractere)
{
    m_separateur_caractere = separateur_caractere;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le mot au format QString.
 * \return Le mot au format QString.
 */
QString mot::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le mot au format QString avec ajout des séparateurs de mots.
 * \return Le mot au format QString.
 */
QString mot::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string();

    for ( int i = 1; i < size(); ++i )
        result += m_separateur_caractere + this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractère du mot.
 * \return Le nombre de caractères du mot.
 */
std::vector<base_element>::size_type mot::nb_caracteres() const
{
    return size();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractère alphabet du mot.
 * \return Le nombre de caractères alphabet du mot.
 */
std::vector<base_element>::size_type mot::nb_caracteres_alphabet() const
{
    std::vector<base_element>::size_type nb = 0;

    for ( int i = 0; i < size(); ++i )
        if ( this->at(i).est_lettre_alphabet() )
            nb++;

    return nb;
}

/** --------------------------------------------------------------------------------------
 * \brief Fusion des caractères.
 */
void mot::fusionner()
{
    base_element elem(to_string());
    clear();
    push_back(elem);
}


/** --------------------------------------------------------------------------------------
 * \brief Accesseur du séparateur de caractères.
 * \return Le séparateur de caractere.
 */
QString mot::get_separateur_caractere() const
{
    return m_separateur_caractere;
}
