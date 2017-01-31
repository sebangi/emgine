#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <iostream>

objet_selectionnable* objet_selectionnable::s_objet_courant = NULL;

objet_selectionnable::objet_selectionnable(objet_selectionnable* parent)
    : m_objet_parent(parent), m_est_active(true), m_est_etendu(true), m_verrouille(false)
{

}

objet_selectionnable::~objet_selectionnable()
{
    emit signal_os_destruction_selectionnable(this);
}

void objet_selectionnable::selectionner()
{
    // déselectionner l'objet actuellement sélectionné
    if ( s_objet_courant != NULL )
    {
        if ( s_objet_courant != this )
            s_objet_courant->deselectionner();
    }

    // sélection de l'objet
    if ( s_objet_courant != this )
    {
        s_objet_courant = this;
        emit signal_os_selectionne(this);
    }
}

fonctions_conteneur * objet_selectionnable::get_conteneur()
{
    if ( est_conteneur() )
        return (fonctions_conteneur *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_conteneur();
    else
        return NULL;
}

fonctions_conteneur * objet_selectionnable::get_conteneur_precedant()
{
    if ( m_objet_parent == NULL )
        return NULL;
    else
        return m_objet_parent->get_conteneur();
}

const fonctions_conteneur * objet_selectionnable::get_conteneur() const
{
    if ( est_conteneur() )
        return (fonctions_conteneur *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_conteneur();
    else
        return NULL;
}

projet * objet_selectionnable::get_projet()
{
    if ( est_projet() )
        return (projet *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_projet();
    else
        return NULL;
}

bool objet_selectionnable::est_dans_projet() const
{
    // ne pas utiliser get_projet() == NULL Sinon bugs
    if ( est_projet() )
        return true;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->est_dans_projet();
    else
        return false;
}

bool objet_selectionnable::est_conteneur() const
{
    return false;
}

bool objet_selectionnable::est_projet() const
{
    return false;
}

bool objet_selectionnable::est_fonction() const
{
    return false;
}

bool objet_selectionnable::est_parametre() const
{
    return false;
}

void objet_selectionnable::set_est_active(bool active)
{    
    m_est_active = active;
    modifier();
}

bool objet_selectionnable::est_active() const
{
    return m_est_active;
}

bool objet_selectionnable::est_active_avec_parent() const
{
    if ( m_objet_parent == NULL )
        return est_active();
    else
        return est_active() && m_objet_parent->est_active_avec_parent();
}

bool objet_selectionnable::parents_actifs() const
{
    if ( m_objet_parent == NULL )
        return true;
    else
        return m_objet_parent->est_active_avec_parent();
}

bool objet_selectionnable::a_ancetre(objet_selectionnable *obj) const
{
    if ( this == obj )
        return true;
    else if ( m_objet_parent == NULL )
        return false;
    else
        return m_objet_parent->a_ancetre(obj);
}

bool objet_selectionnable::est_verrouille() const
{
    return m_verrouille;
}

void objet_selectionnable::set_verrouille(bool verrouille)
{
    m_verrouille = verrouille;
    modifier(false);

    emit signal_verrouillage_change(this);
}

void objet_selectionnable::inverser_verrouillage()
{
    set_verrouille( ! m_verrouille );
}

bool objet_selectionnable::est_verrouille_avec_parent() const
{
    if ( m_objet_parent == NULL )
        return est_verrouille();
    else
        return est_verrouille() || m_objet_parent->est_verrouille_avec_parent();
}

bool objet_selectionnable::parents_verrouilles() const
{
    if ( m_objet_parent == NULL )
        return false;
    else
        return m_objet_parent->est_verrouille_avec_parent();
}

objet_selectionnable *objet_selectionnable::get_selection()
{
    return s_objet_courant;
}

fonctions_conteneur *objet_selectionnable::get_conteneur_courant()
{
    if ( existe_selection() )
    {
        if ( s_objet_courant->est_conteneur() )
            return (fonctions_conteneur *)s_objet_courant;
        else
            return (fonctions_conteneur *)s_objet_courant->m_objet_parent;
    }
    else
        return NULL;
}

projet * objet_selectionnable::get_projet_courant()
{
    if ( existe_selection() )
    {
        return get_projet_courant(s_objet_courant);
    }
    else
        return NULL;
}

bool objet_selectionnable::existe_selection()
{
    return s_objet_courant != NULL;
}

void objet_selectionnable::forcer_deselection()
{
    if ( s_objet_courant != NULL )
        s_objet_courant->deselectionner();
}

void objet_selectionnable::deselectionner()
{
    if ( s_objet_courant == this )
    {
        emit signal_os_deselectionne(this);
        s_objet_courant = NULL;
    }
}

projet * objet_selectionnable::get_projet_courant(objet_selectionnable * obj)
{
    if ( obj == NULL )
        return NULL;
    else if ( obj->est_projet() )
        return (projet *)obj;
    else
        return get_projet_courant( obj->m_objet_parent );
}

void objet_selectionnable::set_est_etendu(bool est_entendu)
{
    m_est_etendu = est_entendu;
}

void objet_selectionnable::modifier( bool change_executable )
{
    if( est_projet() )
    {
        if ( ! ((projet*)this)->est_modifie() )
            ((projet*)this)->set_est_modifie(true);

        if ( change_executable )
            ((projet*)this)->set_executable(true);
    }
    else if ( m_objet_parent != NULL )
        m_objet_parent->modifier(change_executable);
}

bool objet_selectionnable::est_etendu() const
{
    return m_est_etendu;
}

void objet_selectionnable::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("objet_selectionnable");
    stream.writeTextElement("est_etendu", QString::number(m_est_etendu));    
    stream.writeTextElement("verrouille", QString::number(m_verrouille));
    stream.writeEndElement();
}

void objet_selectionnable::charger(QXmlStreamReader & xml)
{
    Q_ASSERT( xml.isStartElement() &&
              xml.name() == "objet_selectionnable" );

    while (xml.readNextStartElement())
    {
        if (xml.name() == "est_etendu")
        {
            QString est_etendu = xml.readElementText();
            set_est_etendu( est_etendu.toInt() );
        }
        else if (xml.name() == "verrouille")
        {
            QString verrouille = xml.readElementText();
            set_verrouille( verrouille.toInt() );
        }
        else
            xml.skipCurrentElement();
    }
}
