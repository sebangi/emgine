#include "entete/element/textes.h"
#include <iostream>

textes::textes()
    : vector<texte>()
{

}

textes::textes(const QString &valeur)
{
    texte t(valeur);

    push_back(t);
}

QString textes::to_string() const
{
    QString result;

    for ( int i = 0; i != size(); ++i )
        result += this->at(i).to_string();

    return result;
}

QString textes::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += "\n---------------------------------------\n" + this->at(i).to_string_lisible();

    return result;
}
