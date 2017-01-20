#include "entete/projet/base_fonction.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/projet/base_parametre.h"
#include <iostream>

/** --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction.
 \author Sébastien Angibaud
*/

/** --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
base_fonction::base_fonction(fonctions_conteneur * parent, const QString & nom, type_fonction type)
    : objet_selectionnable(parent), m_nom(nom), m_type(type), m_id(fonction_indefini),
      m_conteneur(parent), m_niveau_visibilite(1), m_max_niveau_visibilite(1),
      m_niveau_visibilite_avant_desactivation(1)
{
}

base_fonction::~base_fonction()
{
    for ( parametres_iterateur it = m_parametres.begin(); it != m_parametres.end(); ++it )
        delete it->second;
    m_parametres.clear();

    if ( s_objet_courant == this )
        deselectionner();

    emit signal_destruction_fonction(this);
}

void base_fonction::initialisation_par_defaut()
{

}

QString base_fonction::get_info_bulle() const
{
    QString resultat = get_aide();

    if ( ! m_parametres.empty() )
    {
        resultat += "\n\nParamètre";
        if ( m_parametres.size() > 1 )
            resultat += "s";
        resultat += " :";

        parametres_const_iterateur it;
        for ( it = m_parametres.begin(); it != m_parametres.end(); ++it )
            resultat += "\n\t" + it->second->get_nom() + " :\n\t\t" + it->second->get_aide() + "\n";
    }

    return resultat;
}

void base_fonction::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("fonction");
    stream.writeTextElement("id", QString::number(m_id));
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("niveau_visibilite", QString::number(m_niveau_visibilite));
    stream.writeTextElement("active", QString::number(m_est_active));
    objet_selectionnable::sauvegarder(stream);

    if ( m_type == fonction_source )
        stream.writeTextElement( "valeur", ((fonction_base_source*)(this))->get_string_valeur() );

    stream.writeStartElement("parametres");
    parametres_const_iterateur it;
    for ( it = m_parametres.begin(); it != m_parametres.end(); ++it )
        it->second->sauvegarder(stream);

    stream.writeEndElement(); // parametres
    stream.writeEndElement(); // fonction
}

base_fonction_widget *base_fonction::generer_fonction_widget()
{
    return new base_fonction_widget(this);
}

/** --------------------------------------------------------------------------------------
 \brief Retourne le nom de la fonction.
*/
QString base_fonction::get_nom() const
{
    return m_nom;
}

/** --------------------------------------------------------------------------------------
 \brief Retourne le type de la fonction.
*/
base_fonction::type_fonction base_fonction::get_type() const
{
    return m_type;
}

void base_fonction::ajouter_parametre(type_id_parametre id, base_parametre *p)
{
    m_parametres[id] = p;
    p->set_id( id );
}

const texte &base_fonction::get_texte_parametre(type_id_parametre type) const
{
    parametres_const_iterateur it = m_parametres.find(type);

    if ( it != m_parametres.end() )
    {
        const texte& t = it->second->get_texte_out();
        return t;
    }
    else
    {
        std::cout << "base_fonction::get_texte_parametre : impossible de trouver le parametre " << type << std::endl;
        return texte();
    }
}

void base_fonction::augmenter_max_niveau_visibilite(int val)
{
    m_max_niveau_visibilite += val;
    m_niveau_visibilite += val;
    m_niveau_visibilite_avant_desactivation += val;
}

type_id_fonction base_fonction::get_id() const
{
    return m_id;
}

void base_fonction::set_conteneur(fonctions_conteneur *conteneur)
{
    m_objet_parent = conteneur;
    m_conteneur = conteneur;
}

fonctions_conteneur *base_fonction::get_conteneur() const
{
    return m_conteneur;
}

void base_fonction::set_id(const type_id_fonction &id)
{
    m_id = id;
}

void base_fonction::change_niveau_visibilite()
{
    int niveau = m_niveau_visibilite - 1;

    if ( niveau == 0 )
        niveau= m_max_niveau_visibilite;

    set_niveau_visibilite(niveau);
}

void base_fonction::set_est_active(bool est_active)
{
    if ( est_active )
    {
        if ( get_niveau_visibilite() == 1 )
            set_niveau_visibilite( m_niveau_visibilite_avant_desactivation );
    }
    else
    {
        m_niveau_visibilite_avant_desactivation = get_niveau_visibilite();
        set_niveau_visibilite(1);
    }

    objet_selectionnable::set_est_active( est_active );

    emit signal_activation_fonction_change(this);
}

void base_fonction::set_est_etendu(bool est_etendu)
{
    objet_selectionnable::set_est_etendu( est_etendu );

    emit signal_etendu_change(this);
}

bool base_fonction::a_parametre() const
{
    return ! m_parametres.empty();
}

int base_fonction::get_niveau_visibilite() const
{
    return m_niveau_visibilite;
}

int base_fonction::get_max_niveau_visibilite() const
{
    return m_max_niveau_visibilite;
}

void base_fonction::set_niveau_visibilite(int niveau_visibilite)
{
    m_niveau_visibilite = niveau_visibilite;

    emit signal_niveau_visibilite_change(this);
}

void base_fonction::inverser_activation()
{
    set_est_active( ! m_est_active );
}

int base_fonction::get_position()
{
    if ( m_conteneur == NULL )
        return 0;
    else
        return m_conteneur->get_position(this);
}

base_fonction::parametres_iterateur base_fonction::parametres_begin()
{
    return m_parametres.begin();
}

base_fonction::parametres_iterateur base_fonction::parametres_end()
{
    return m_parametres.end();
}

base_fonction::parametres_const_iterateur base_fonction::parametres_const_begin() const
{
    return m_parametres.begin();
}

base_fonction::parametres_const_iterateur base_fonction::parametres_const_end() const
{
    return m_parametres.end();
}

base_parametre *base_fonction::get_parametre(type_id_parametre id)
{
    return m_parametres.find(id)->second;
}

bool base_fonction::est_fonction_valide(logs_compilation_widget * vue_logs) const
{
    bool result = est_valide(vue_logs);

    for ( parametres_const_iterateur it = parametres_const_begin(); it != parametres_const_end(); ++it )
    {
        bool result_param = it->second->est_valide(vue_logs);
        result = result && result_param;
    }

    return result;
}

void base_fonction::charger(QXmlStreamReader & xml)
{
    while(xml.readNextStartElement())
    {
        if(xml.name() == "nom")
        {
            // ignoré
            QString nom = xml.readElementText();
        }
        else if(xml.name() == "niveau_visibilite")
        {
            QString niveau_visibilite = xml.readElementText();
            set_niveau_visibilite( niveau_visibilite.toInt() );
        }
        else if(xml.name() == "active")
        {
            QString active = xml.readElementText();
            set_est_active( active.toInt() );
        }
        else if(xml.name() == "valeur")
        {
            QString valeur = xml.readElementText();
            if ( get_type() == base_fonction::fonction_source )
                ((fonction_base_source*)this)->set_string_valeur(valeur);
        }
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if(xml.name() == "parametres")
        {
            charger_parametres(xml);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

void base_fonction::charger_parametres(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "parametres");

    while(xml.readNextStartElement())
    {
        if(xml.name() == "parametre")
        {
            charger_parametre(xml);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

void base_fonction::charger_parametre(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "parametre");

    xml.readNextStartElement();

    if(xml.name() == "id")
    {
        int id = xml.readElementText().toInt();
        m_parametres[(type_id_parametre)id]->charger(xml);
    }
}
