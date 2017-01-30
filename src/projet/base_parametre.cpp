#include "entete/projet/base_parametre.h"

#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/fenetre_principale.h"

#include <iostream>

base_parametre::base_parametre( objet_selectionnable * parent, QString nom, QString aide,
                                bool peut_etre_vide, bool dans_configuration, type_algorithme algorithme)
    : fonctions_conteneur(parent), m_fonction_parent((base_fonction*)parent), m_nom(nom), m_aide(aide),
      m_peut_etre_vide(peut_etre_vide), m_textes_out(), m_dans_configuration(dans_configuration), m_algorithme(algorithme)
{

}

base_parametre::~base_parametre()
{
    clear_fonctions();
}

void base_parametre::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("parametre");
    stream.writeTextElement("id", QString::number(m_id));
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("dans_configuration", QString::number(m_dans_configuration) );
    objet_selectionnable::sauvegarder(stream);
    fonctions_conteneur::sauvegarder(stream);
    stream.writeEndElement(); // Paramètre
}

QString base_parametre::get_nom() const
{
    return m_nom;
}

QString base_parametre::get_titre() const
{
    return get_fonction_parent()->get_nom() + " : paramètre " + get_nom();
}

QString base_parametre::get_valeur_courte() const
{
    int nb_fonctions_actives = get_nb_fonctions_actives();

    if ( nb_fonctions_actives == 0 )
        return "aucun";
    else if ( nb_fonctions_actives == 1 )
        return premiere_fonction_active()->get_valeur_courte();
    else
        return "complexe";
}

QString base_parametre::get_aide() const
{
    return m_aide;
}

QString base_parametre::get_aide_algorithme() const
{
    if ( m_algorithme == ALGO_AUCUN )
        return "aucun algorithme. Tout le texte est considéré d'un coup. Aucune itération.";
    else if ( m_algorithme == ALGO_PMIPL )
        return "Seul le premier mot de chaque ligne est considéré. Itération sur les lignes.";
    else if ( m_algorithme == ALGO_LIPL )
        return "Chaque ligne est considérée d'un coup. Itération sur les lignes";
    else
        return "inconnu";
}

type_element base_parametre::get_type() const
{
    return m_type;
}

base_fonction *base_parametre::get_fonction_parent() const
{
    return m_fonction_parent;
}

bool base_parametre::is_requis() const
{
    return m_peut_etre_vide;
}

void base_parametre::set_booleen_par_defaut(bool valeur)
{
    base_fonction * f = new fonction_source_booleen(this,valeur);
    ajouter_fonction(f, NULL);
}

void base_parametre::set_texte_par_defaut
(QString texte, QString separ_caractere, QString separ_mot, QString separ_ligne)
{
    base_fonction * f = new fonction_source_texte(this,texte);
    ((fonction_source_texte *)f)->initialisation_par_defaut( separ_caractere, separ_mot, separ_ligne );
    ajouter_fonction(f, NULL);
}

void base_parametre::set_caractere_par_defaut(QString s)
{
    base_fonction * f = new fonction_source_caractere(this,s);
    ajouter_fonction(f, NULL);
}

const textes & base_parametre::get_textes_out() const
{
    return m_textes_out;
}

void base_parametre::set_textes_out(const textes &textes_out)
{
    m_textes_out = textes_out;
}

void base_parametre::set_id(const type_id_parametre &value)
{
    m_id = value;
}

bool base_parametre::est_valide(logs_compilation_widget * vue_logs)
{
    bool result = true;

    type_fonctions actifs;
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        if ( (*it)->est_active() )
            actifs.push_back(*it);

    if ( actifs.size() == 0 )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le parametre \"" + m_nom +
                                   "\" de la fonction \"" + m_fonction_parent->get_nom() +
                                   "\" n'a aucune fonction active") );
        result = false;
    }
    else if ( ! actifs.front()->get_type() == base_fonction::fonction_source )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le parametre \"" + m_nom +
                                   "\" de la fonction \"" + m_fonction_parent->get_nom() +
                                   "\" doit commencer par une fonction source active") );
        result = false;
    }

    for ( fonctions_iterateur it = actifs.begin(); it != actifs.end(); ++it )
        result = result && (*it)->est_fonction_valide(vue_logs);

    return result;
}

void base_parametre::charger(QXmlStreamReader & xml)
{
    while( xml.readNextStartElement() )
    {
        if(xml.name() == "nom")
        {
            QString nom = xml.readElementText();
            // on n'en fait rien; c'est seulement pour la lisibilité du fichier
        }
        else if(xml.name() == "dans_configuration")
        {
            QString dans_configuration = xml.readElementText();
            set_dans_configuration( dans_configuration.toInt() );

        }
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if(xml.name() == "fonctions")
        {
            charger_fonctions(xml, NULL);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

bool base_parametre::est_dans_configuration() const
{
    return m_dans_configuration;
}

void base_parametre::inverser_dans_configuration()
{
    m_dans_configuration = ! m_dans_configuration;
    modifier();
}

void base_parametre::set_dans_configuration(bool dans_configuration)
{
    m_dans_configuration = dans_configuration;
}

bool base_parametre::peut_etre_vide() const
{
    return m_peut_etre_vide;
}
