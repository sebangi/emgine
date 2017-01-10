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

unsigned int projet::s_nb_projets = 0;

projet::projet()
    : fonctions_conteneur(NULL), m_nouveau(true)
{
    s_nb_projets++;

    m_nom = QString::number( s_nb_projets );
}

projet::~projet()
{
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        delete *it;
    m_fonctions.clear();
}

void projet::sauvegarder( QXmlStreamWriter & stream )
{
    m_nouveau = false;

    stream.writeStartElement("projet");
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("description", m_description);
    stream.writeStartElement("fonctions");

    for ( projet::fonctions_iterateur it = fonctions_begin(); it != fonctions_end(); ++it )
        (*it)->sauvegarder(stream);

    stream.writeEndElement(); // Fonctions
    stream.writeEndElement(); // Projet
}

void projet::charger(QXmlStreamReader & xml)
{    
    std::cout << "->" << "charger_projet" << std::endl;

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
        else if (xml.name() == "fonctions")
            charger_fonctions(xml);
        else
            xml.skipCurrentElement();
    }
    std::cout << "<-" << "charger_projet" << std::endl;
}

QString projet::get_nom() const
{
    return m_nom;
}

void projet::set_nom(const QString &nom)
{
    m_nom = nom;
}

void projet::charger_nom(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "nom");

    m_nom = xml.readElementText();
}

void projet::charger_description(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "description");

    m_description = xml.readElementText();
}

void projet::charger_fonctions(QXmlStreamReader & xml )
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonctions");

    while(xml.readNextStartElement())
    {
        if(xml.name() == "fonction")
            charger_fonction(xml);
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

void projet::charger_fonction(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonction");

    xml.readNextStartElement();

    if(xml.name() == "id")
    {
        QString id = xml.readElementText();
        base_fonction * f = bibliotheque_fonctions::get_fonction( (type_id_fonction)id.toInt() );

        while(xml.readNextStartElement())
        {
            if(xml.name() == "nom")
            {
                QString nom = xml.readElementText();
            }
            else if(xml.name() == "valeur")
            {
                QString valeur = xml.readElementText();
                if ( f->get_type() == base_fonction::fonction_source )
                    ((fonction_base_source*)f)->set_string_valeur(valeur);
            }
            else if(xml.name() == "parametres")
            {
                f->charger(xml);
            }
            else
            {
                std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
                xml.skipCurrentElement();
            }
        }

        m_fonctions.push_back(f);
    }
}

QString projet::get_description() const
{
    return m_description;
}

bool projet::est_nouveau() const
{
    return m_nouveau;
}

QString projet::get_nom_fichier() const
{
    return m_nom_fichier;
}

void projet::set_nom_fichier(const QString &nom_fichier)
{
    m_nom_fichier = nom_fichier;
}

bool projet::est_valide()
{
    bool result = true;

    type_fonctions actifs;
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        if ( (*it)->est_active() )
           actifs.push_back( *it );

    if ( actifs.size() == 0 )
    {
        fenetre_principale::s_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le projet \"" + m_nom + "\" n'a aucune fonction active") );
        result = false;
    }
    else if ( ! actifs.front()->get_type() == base_fonction::fonction_source )
    {
        fenetre_principale::s_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le projet \"" + m_nom + "\" doit commencer par une fonction source active") );
        result = false;
    }

    for ( fonctions_iterateur it = actifs.begin(); it != actifs.end(); ++it )
    {
        bool result_fonction = (*it)->est_fonction_valide();
        result = result && result_fonction;
    }

    return result;
}
