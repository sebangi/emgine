#include "entete/element/texte.h"
#include "entete/projet/base_fonction.h"
#include <iostream>

texte::texte()
    : vector<ligne>()
{

}

texte::texte( const configuration& config )
    : vector<ligne>(), m_configuration(config)
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

QString texte::get_string_configuration() const
{
    QString result = "Configuration :";

    for ( configuration::const_iterator it = m_configuration.begin(); it != m_configuration.end(); ++it )
        result += "\n" + it->first.first->get_nom() +
                "[" + it->first.first->get_parametre(it->first.second)->get_nom() + "] => " + it->second;

    return result;
}

void texte::ajouter_configuration(const configuration &config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
        m_configuration[ it->first ] = it->second;
}

const configuration& texte::get_configuration() const
{
    return m_configuration;
}
