#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/base_fonction.h"

#include <iostream>

objet_selectionnable* objet_selectionnable::s_objet_courant = NULL;

objet_selectionnable::objet_selectionnable(objet_selectionnable* parent)
    : m_objet_parent(parent), m_est_active(true)
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

objet_selectionnable *objet_selectionnable::get_conteneur()
{
    if ( est_conteneur() )
        return this;
    else
        return m_objet_parent->get_conteneur();
}

bool objet_selectionnable::est_conteneur() const
{
    return false;
}

bool objet_selectionnable::est_projet() const
{
    return false;
}

void objet_selectionnable::set_est_active(bool est_active)
{
    m_est_active = est_active;
}

bool objet_selectionnable::est_active() const
{
    return m_est_active;
}

bool objet_selectionnable::est_active_avec_parent() const
{
    if ( m_objet_parent == NULL )
        return m_est_active;
    else
        return m_est_active && m_objet_parent->est_active_avec_parent();
}

bool objet_selectionnable::parents_actifs() const
{
    if ( m_objet_parent == NULL )
        return true;
    else
        return m_objet_parent->est_active_avec_parent();
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
