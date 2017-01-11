#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/explorateur/base_noeud.h"

#include <iostream>

objet_selectionnable* objet_selectionnable::s_objet_courant = NULL;

objet_selectionnable::objet_selectionnable(objet_selectionnable* parent)
    : m_objet_parent(parent)
{

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

objet_selectionnable *objet_selectionnable::get_selection()
{
    return s_objet_courant;
}

fonctions_conteneur *objet_selectionnable::get_conteneur_courant()
{
    if ( existe_selection() )
        return (fonctions_conteneur *)s_objet_courant;
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

