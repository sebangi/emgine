#include "entete/element/ligne.h"

ligne::ligne()
    : vector<mot>(), m_separateur_mot(" ")
{

}

ligne::ligne(const QString &valeur, const QString & separateur_mot)
    : vector<mot>(), m_separateur_mot(separateur_mot)
{
    if ( ! valeur.isEmpty() )
    {
        mot m(valeur);
        push_back(m);
    }
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
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += m_separateur_mot + this->at(i).to_string_lisible();

    return result;
}

