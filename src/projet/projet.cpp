#include "entete/projet/projet.h"

#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/base_fonction.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/fenetre_principale.h"

#include <iostream>
#include <QDir>

unsigned int projet::s_nb_projets = 0;

projet::projet()
    : fonctions_conteneur(NULL), m_nouveau(true), m_est_modifie(false), m_est_executable(true)
{
    s_nb_projets++;

    m_nom = "Nouveau projet " + QString::number( s_nb_projets );
}

projet::~projet()
{

}

void projet::sauvegarder( QXmlStreamWriter & stream )
{
    m_nouveau = false;

    stream.writeStartElement("projet");
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("description", m_description);
    objet_selectionnable::sauvegarder(stream);
    stream.writeStartElement("fonctions");

    for ( projet::fonctions_iterateur it = fonctions_begin(); it != fonctions_end(); ++it )
        (*it)->sauvegarder(stream);

    stream.writeEndElement(); // Fonctions
    stream.writeEndElement(); // Projet

    m_est_modifie = false;
    emit signal_p_projet_etat_modification_change(this, false);
}

void projet::charger(QXmlStreamReader & xml)
{    
    Q_ASSERT( xml.isStartElement() &&
              xml.name() == "projet" );

    Q_ASSERT( m_nouveau );

    m_nouveau = false;

    while (xml.readNextStartElement())
    {
        if (xml.name() == "nom")
            charger_nom(xml);
        else if (xml.name() == "description")
            charger_description(xml);
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if (xml.name() == "fonctions")
            charger_fonctions(xml);
        else
            xml.skipCurrentElement();
    }

    m_est_modifie = false;
    emit signal_p_projet_etat_modification_change(this, false);
}

QString projet::get_nom() const
{
    return m_nom;
}

QString projet::get_titre() const
{
    return get_nom();
}

void projet::set_nom(const QString &nom)
{
    m_nom = nom;

    emit signal_p_nom_projet_change(this);
}

void projet::charger_nom(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "nom");

    // ne pas retirer cette ligne : il fait lire l'élément pour charger la suite
    QString nom = xml.readElementText();
    // Le nom est ignoré
}

void projet::charger_description(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "description");

    m_description = xml.readElementText();
}

void projet::set_est_modifie(bool est_modifie)
{
    m_est_modifie = est_modifie;

    emit signal_p_projet_etat_modification_change((projet*)this, est_modifie);
}

bool projet::est_enregistrable() const
{
    return ! est_nouveau() && est_modifie();
}

void projet::set_executable( bool executable )
{
    m_est_executable = executable;

    emit signal_p_projet_executable_change((projet*)this);
}

bool projet::est_executable() const
{
    return m_est_executable;
}

void projet::executer()
{
    set_executable( false );
}

bool projet::est_modifie() const
{
    return m_est_modifie;
}

QString projet::get_description() const
{
    return m_description;
}

bool projet::est_nouveau() const
{
    return m_nouveau;
}

bool projet::est_projet() const
{
    return true;
}

QString projet::get_nom_fichier() const
{
    return m_nom_fichier;
}

void projet::set_nom_fichier(const QString &nom_fichier)
{
    m_nom_fichier = nom_fichier;

    QString nom = m_nom_fichier.split("/").last();
    set_nom( nom.split(".").first() );
}

bool projet::est_valide(logs_compilation_widget * vue_logs)
{
    bool result = true;

    type_fonctions actifs;
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        if ( (*it)->est_active() )
            actifs.push_back( *it );

    if ( actifs.size() == 0 )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le projet \"" + m_nom + "\" n'a aucune fonction active") );
        result = false;
    }
    else if ( ! actifs.front()->get_type() == base_fonction::fonction_source )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le projet \"" + m_nom + "\" doit commencer par une fonction source active") );
        result = false;
    }

    for ( fonctions_iterateur it = actifs.begin(); it != actifs.end(); ++it )
    {
        bool result_fonction = (*it)->est_fonction_valide(vue_logs);
        result = result && result_fonction;
    }

    return result;
}
