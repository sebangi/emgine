#include "element.h"
#include <sstream>
#include <algorithm>
#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe element.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param c Le caractère représentant l'élément.
*/
element::element(char c)
    : m_caractere(c)
{
    if( m_caractere == '\n' || m_caractere == '\r')
        m_type = retour_ligne;
    else
        m_type = caractere;
}

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nb L'entier représentant l'élément.
*/
element::element(int nb)
    : m_entier(nb), m_type(entier)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param t Le type de l'élément.
*/
element::element(element::type_element t)
    : m_type(t)
{
    if ( m_type == entier )
        m_entier = 0;
    else if ( m_type == entier )
        m_caractere = ' ';
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne le type de l'élément.
*/
element::type_element element::get_type() const
{
    return m_type;
}

/*! --------------------------------------------------------------------------------------
 \brief Convertit l'élément en chaine de carcatères.
*/
std::string element::to_string() const
{
    std::ostringstream convert;

    if ( m_type == entier )
        convert << m_entier << " ";
    else if ( m_type == caractere )
        convert << m_caractere;
    else
        convert << '\n';

    return convert.str();
}

/*! --------------------------------------------------------------------------------------
 \brief Convertit l'élément en caractère.
*/
char element::to_char() const
{
    if ( m_type == entier )
    {
        if ( m_entier > 0 && m_entier <= 26 )
            return 'A' + m_entier - 1;
        else
            return '_';
    }
    else if ( m_type == caractere )
        return m_caractere;
    else
        return '_';
}

/*! --------------------------------------------------------------------------------------
 \brief Convertit l'élément en entier.
*/
int element::to_int() const
{
    if ( m_type == entier )
        return m_entier;
    else if ( m_type == caractere )
    {
        if ( m_caractere >= 'a' && m_caractere <= 'z' )
            return m_caractere - 'a' + 1;
        else if ( m_caractere >= 'A' && m_caractere <= 'Z' )
             return m_caractere - 'A' + 1;
        else
            return 0;
    }
    else
        return 0;
}

/*! --------------------------------------------------------------------------------------
 \brief Test si l'élément est un séparateur (espace, retour à la ligne...).
*/
bool element::est_separateur() const
{
    bool resultat = false;

    if ( m_type == retour_ligne )
        return true;
    else if ( m_type == caractere )
        return ( m_caractere == ' ' ) || ( m_caractere == '\t' );
    else
        return resultat;
}

/*! --------------------------------------------------------------------------------------
 \brief Test si l'élément est un séparateur donné.
*/
bool element::est_separateur(const char separateur) const
{
    bool resultat = false;

    if ( m_type == retour_ligne )
        return true;
    else if ( m_type == caractere )
        return ( m_caractere == separateur );
    else
        return resultat;
}


/*! --------------------------------------------------------------------------------------
 \brief Met l'élément en majuscule.
*/
void element::to_upper()
{
    if ( m_type == caractere )
    {
        std::string str(" ");
        str[0] = m_caractere;
        std::transform(str.begin(), str.end(), str.begin(), ::toupper);
        m_caractere = str[0];
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Met l'élément en minuscule.
*/
void element::to_lower()
{
    if ( m_type == caractere )
    {
        std::string str(" ");
        str[0] = m_caractere;
        std::transform(str.begin(), str.end(), str.begin(), ::tolower);
        m_caractere = str[0];
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Surcharge de l'opérateur de comparaison.
*/
bool element::operator <(const element &e) const
{
    return to_string() < e.to_string();
}

