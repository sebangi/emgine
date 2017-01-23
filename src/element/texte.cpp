#include "entete/element/texte.h"
#include "entete/projet/base_fonction.h"
#include <iostream>

texte::texte()
    : vector<ligne>(), m_separateur_ligne("\n"), m_configuration_visible(false)
{

}

texte::texte( const configuration& config, const QString & separateur_ligne )
    : vector<ligne>(), m_configuration(config), m_separateur_ligne(separateur_ligne), m_configuration_visible(false)
{
    ajouter_string_configuration( config );
}

texte::texte(const QString &valeur, const QString & separateur_ligne)
    : vector<ligne>(), m_separateur_ligne(separateur_ligne), m_configuration_visible(false)
{
    if ( ! valeur.isEmpty() )
    {
        ligne l(valeur);
        push_back(l);
    }
}

texte::~texte()
{

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
        result += m_separateur_ligne + this->at(i).to_string_lisible();

    return result;
}

QString texte::get_string_configuration() const
{
    QString result = "Configuration :";

    if( m_string_configuration.isEmpty() )
        result += "\n\taucune" ;
    else
        result += m_string_configuration;

    return result;
}

void texte::ajouter_string_configuration(const configuration& config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
        m_string_configuration +=
                "\n\t" + it->first.first->get_nom() +
                "[" + it->first.first->get_parametre(it->first.second)->get_nom() + "] => " + it->second;

}

void texte::ajouter_configuration(const configuration &config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
    {
        m_configuration[ it->first ] = it->second;
        ajouter_string_configuration(config);
    }
}

const configuration& texte::get_configuration() const
{
    return m_configuration;
}

bool texte::get_configuration_visible() const
{
    return m_configuration_visible;
}

void texte::inverser_configuration_visibilite()
{
    m_configuration_visible = ! m_configuration_visible;
}
