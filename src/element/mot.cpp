#include "entete/element/mot.h"

mot::mot()
    : vector<base_element>(), m_separateur_caractere("")
{

}

mot::mot(const QString &valeur, const QString & separateur_caractere)
    : vector<base_element>(), m_separateur_caractere(separateur_caractere)
{
    if ( ! valeur.isEmpty())
    {
        base_element e(valeur);
        push_back(e);
    }
}

QString mot::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}


QString mot::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string();

    for ( int i = 1; i < size(); ++i )
        result += m_separateur_caractere + this->at(i).to_string();

    return result;
}

