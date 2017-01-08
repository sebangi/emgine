#include "element/ligne.h"

ligne::ligne()
    : vector<mot>()
{

}

ligne::ligne(const QString &valeur)
{
    mot m(valeur);

    push_back(m);
}

QString ligne::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

QString ligne::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string();

    for ( int i = 1; i < size(); ++i )
        result += " " + this->at(i).to_string();

    return result;
}

