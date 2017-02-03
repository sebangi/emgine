#include "entete/element/texte.h"
#include "entete/projet/base_fonction.h"
#include <iostream>

texte::texte()
    : vector<ligne>(), m_separateur_ligne("\n"), m_configuration_visible(false), m_max_taille_configuration(16), m_nb_caracteres(0), m_nb_mots(0)
{

}

texte::texte( const configuration& config, const QString & separateur_ligne )
    : vector<ligne>(), m_configuration(config), m_separateur_ligne(separateur_ligne),
      m_configuration_visible(false), m_max_taille_configuration(16), m_nb_caracteres(0), m_nb_mots(0)
{
    ajouter_string_configuration( config );
}

texte::texte(const QString &valeur, const QString & separateur_ligne)
    : vector<ligne>(), m_separateur_ligne(separateur_ligne), m_configuration_visible(false), m_max_taille_configuration(16),
      m_nb_caracteres(0), m_nb_mots(0)
{
    if ( ! valeur.isEmpty() )
    {
        ligne l(valeur);
        ajouter_ligne(l);
    }
}

texte::~texte()
{

}

void texte::ajouter_ligne( const ligne & l)
{
    push_back(l);
    m_nb_caracteres += l.nb_caracteres();
    m_nb_mots += l.nb_mots();

    if ( l.to_string_lisible().size() > m_max_taille_configuration )
        m_max_taille_configuration = l.to_string_lisible().size();
}

QString texte::to_string() const
{
    QString result;

    for ( int i = 0; i < size(); ++i )
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
    QString result = "Configuration : \n";

    if( m_string_configuration.isEmpty() )
        result += "\taucune\n" ;
    else
        result += m_string_configuration;

    return result;
}

QString texte::get_string_information_taille() const
{
    return QString( "Nombre de lignes : " + QString::number( nb_lignes() ) + "\n" +
                    "Nombre de mots : " + QString::number( nb_mots() ) + "\n" +
                    "Nombre de caracteres : " + QString::number( nb_caracteres() ) + "\n" );
}

QString texte::get_string_separation() const
{
    QString result;
    for ( int i = 0; i < m_max_taille_configuration; ++i )
        result += "-";
    result += "\n";

    return result;
}

void texte::ajouter_string_configuration(const configuration& config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
    {
        QString s = "\t* " + it->first.first->get_nom() +
                "[" + it->first.first->get_parametre(it->first.second)->get_nom() + "] => " + it->second;

        m_string_configuration += s + "\n";

        // on ajuste le max : le 9 vient de la tabulation
        if ( s.size() + 9 > m_max_taille_configuration )
            m_max_taille_configuration = s.size() + 9;
    }
}

void texte::ajouter_configuration(const configuration &config)
{
    for ( configuration::const_iterator it = config.begin(); it != config.end(); ++it )
        m_configuration[ it->first ] = it->second;

    ajouter_string_configuration(config);
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

int texte::get_nb_lignes_avec_information() const
{
    int result = size();

    if ( m_configuration_visible )
    {
        if ( m_configuration.empty() )
            result += 9; // "Texte" + ligne vide + "configuration" + "aucune" + ligne vide + 4 lignes de taille + transition
        else
            result += 8 + m_configuration.size() ; // "texte" + ligne vide + "configuration" + nb param + 4 lignes de taille + transition
    }

    return result;
}

std::vector<ligne>::size_type texte::nb_caracteres() const
{
    return m_nb_caracteres;
}

std::vector<ligne>::size_type texte::nb_mots() const
{
    return m_nb_mots;
}

std::vector<ligne>::size_type texte::nb_lignes() const
{
    return size();
}
