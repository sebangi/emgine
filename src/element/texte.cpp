#include "element/texte.h"
#include <iostream>

texte::texte()
    : vector<ligne>()
{

}

texte::texte(const QString &valeur)
{
    ligne l(valeur);

    push_back(l);
}

QString texte::to_string() const
{
    QString result;

    for ( int i = 0; i != size(); ++i )
        result += this->at(i).to_string();

    return result;
}

QString texte::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += "\n" + this->at(i).to_string_lisible();

    return result;
}
