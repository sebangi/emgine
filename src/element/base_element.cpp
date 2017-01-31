#include "entete/element/base_element.h"


base_element::base_element()
    : m_type(type_element_indefini)
{

}

base_element::base_element(bool valeur)
    : m_type(type_element_booleen),
      m_booleen(valeur)
{

}

base_element::base_element(int valeur)
    : m_type(type_element_entier),
      m_entier(valeur)
{

}

base_element::base_element(QChar valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{

}

base_element::base_element(QCharRef valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{

}

base_element::base_element(QString valeur)
    : m_type(type_element_string), m_string(valeur)
{

}

type_element base_element::get_type() const
{
    return m_type;
}

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

int base_element::get_entier() const
{
    if ( m_type == type_element_entier )
        return m_entier;
    else
        return m_string.toInt();
}

QChar base_element::get_caractere() const
{
    return m_caractere;
}

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

bool base_element::operator <(const base_element& e) const
{
    return m_string < e.m_string;
}

