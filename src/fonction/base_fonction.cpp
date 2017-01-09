#include "fonction/base_fonction.h"
#include "fonction/fonction_source/fonction_base_source.h"
#include "explorateur/noeud_fonction.h"
#include "explorateur/noeud_parametre.h"
#include "fonction_widget/base_fonction_widget.h"
#include "parametre/base_parametre.h"
#include <iostream>

/** --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction.
 \author Sébastien Angibaud
*/

/** --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
base_fonction::base_fonction(fonctions_conteneur * conteneur, const QString & nom, type_fonction type)
    : m_nom(nom), m_type(type), m_id(fonction_indefini), m_est_active(true), m_parametre_visible(true),
      m_conteneur(conteneur)
{

}

base_fonction::~base_fonction()
{
    for ( parametres_iterateur it = m_parametres.begin(); it != m_parametres.end(); ++it )
        delete it->second;
    m_parametres.clear();

    emit signal_destruction_fonction(this);

    // TODO : est-ce fait ?
//   for ( type_set_widgets::iterator it = m_widgets.begin();
//         it != m_widgets.end(); ++it )
//        (*it)->reset_fonction();
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
    if ( m_type == fonction_source )
        stream.writeTextElement( "valeur", ((fonction_base_source*)(this))->get_string_valeur() );

    stream.writeStartElement("parametres");
    parametres_const_iterateur it;
    for ( it = m_parametres.begin(); it != m_parametres.end(); ++it )
        it->second->sauvegarder(stream);

    stream.writeEndElement(); // Fonction
    stream.writeEndElement(); // Parametre
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
    // TODO : fonction bizarre : retour si pb ? la fonction est-elle appelée ?
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

void base_fonction::set_id(const type_id_fonction &id)
{
    m_id = id;
}

void base_fonction::set_parametre_visible(bool parametre_visible)
{
    m_parametre_visible = parametre_visible;
}

bool base_fonction::get_parametre_visible() const
{
    return m_parametre_visible;
}

void base_fonction::set_est_active(bool est_active)
{
    m_est_active = est_active;
}

void base_fonction::inverser_activation()
{
    m_est_active = ! m_est_active;
    emit signal_activation_fonction_change(this);
}

void base_fonction::add_widget(base_fonction_widget *widget)
{
    m_widgets.insert( widget );
}

void base_fonction::remove_widget( base_fonction_widget* widget )
{
    type_set_widgets::iterator it = m_widgets.find(widget);
    if ( it != m_widgets.end() )
        m_widgets.erase(it);
}

bool base_fonction::has_widget() const
{
    return ! m_widgets.empty();
}

base_fonction_widget * base_fonction::get_first_widget()
{
    if ( has_widget() )
        return *(m_widgets.begin());
    else
        return NULL;
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

bool base_fonction::est_active() const
{
    return m_est_active;
}

bool base_fonction::est_fonction_valide() const
{
    bool result = est_valide();

    for ( parametres_const_iterateur it = parametres_const_begin(); it != parametres_const_end(); ++it )
    {
        bool result_param = it->second->est_valide();
        result = result && result_param;
    }

    return result;
}


void base_fonction::charger(QXmlStreamReader & xml)
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
