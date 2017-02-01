#include "entete/element/ligne.h"

ligne::ligne()
    : vector<mot>(), m_separateur_mot(" "), m_nb_caracteres(0)
{

}

ligne::ligne(const QString &valeur, const QString & separateur_mot)
    : vector<mot>(), m_separateur_mot(separateur_mot), m_nb_caracteres(0)
{
    if ( ! valeur.isEmpty() )
    {
        mot m(valeur);
        ajouter_mot(m);
    }
}

void ligne::ajouter_mot( const mot & m)
{
    push_back(m);
    m_nb_caracteres += m.nb_caracteres();
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

std::vector<mot>::size_type ligne::nb_caracteres() const
{
    return m_nb_caracteres;
}

std::vector<mot>::size_type ligne::nb_mots() const
{
    return size();
}

bool ligne::operator<(const ligne & l) const
{
    return to_string() < l.to_string();
}

