/** \file base_element.cpp
 * \brief Fichier d'implémentation de la classe base_element.
 * \author Sébastien Angibaud
 */

#include "entete/element/base_element.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 */
base_element::base_element()
    : m_type(type_element_indefini)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur booléenne de l'élément créé.
 */
base_element::base_element(bool valeur)
    : m_type(type_element_booleen),
      m_booleen(valeur)
{
    m_string = to_string();
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur entière de l'élément créé.
 */
base_element::base_element(int valeur)
    : m_type(type_element_entier),
      m_entier(valeur)
{
    m_string = to_string();
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur de type QChar de l'élément créé.
 */
base_element::base_element(QChar valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{
    m_string = to_string();
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur de type QCharRef de l'élément créé.
 */
base_element::base_element(QCharRef valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{
    m_string = to_string();
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la class base_element.
 * \param valeur La valeur de type QString de l'élément créé..
 */
base_element::base_element(QString valeur)
    : m_type(type_element_string), m_string(valeur)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'attribut type.
 * \return Le type de l'élément.
 */
type_element base_element::get_type() const
{
    return m_type;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur booléenne de l'élément.
 * \return La valeur booléenne de l'élément.
 */
bool base_element::get_booleen() const
{
    if ( m_type == type_element_entier )
        return m_entier != 0;
    else if ( m_type == type_element_string )
        return m_string != "0" && m_string != "non";
    else if ( m_type == type_element_caractere )
        return m_caractere != '0';
    else
        return m_booleen;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur entière de l'élément.
 * \return La valeur entière de l'élément.
 */
int base_element::get_entier() const
{
    if ( m_type == type_element_entier )
        return m_entier;
    else
        return m_string.toInt();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de type QChar de l'élément.
 * \return La valeur de type QChar de l'élément.
 */
QChar base_element::get_caractere() const
{
    return m_caractere;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de type QString de l'élément.
 * \return La valeur de type QString de l'élément.
 */
QString base_element::to_string() const
{
    switch ( m_type )
    {
        case type_element_booleen:
            if ( m_booleen )
                return "oui";
            else
                return "non";

        case type_element_entier:
            return QString::number(m_entier);

        case type_element_caractere:
            return QString(m_caractere);

        case type_element_string:
            return m_string;

        default:
            return "";
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'infériorité.
 * \param e Le base_element avec qui se comparer.
 * \return \b True si le base_element courant est inférieur strictement au base_element donné, \b False sinon.
 */
bool base_element::operator <(const base_element& e) const
{
    return m_string.compare( e.m_string ) < 0;
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'égalité.
 * \param e Le base_element avec qui se comparer.
 * \return \b True si le base_element courant est égal au base_element donné, \b False sinon.
 */
bool base_element::operator==(const base_element &e) const
{
    return m_string.compare( e.m_string ) == 0;
}

