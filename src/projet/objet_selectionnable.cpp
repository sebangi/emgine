#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/fonctions_conteneur.h"

objet_selectionnable* objet_selectionnable::s_objet_courant = NULL;

objet_selectionnable::objet_selectionnable(objet_selectionnable* parent)
    : m_parent(parent)
{

}

void objet_selectionnable::selectionner()
{
    if ( s_objet_courant != NULL )
        if ( s_objet_courant != this )
        {
            s_objet_courant->deselectionner();

            s_objet_courant = this;
            emit signal_os_selectionne();
        }
}

objet_selectionnable *objet_selectionnable::get_selection()
{
    return s_objet_courant;
}

fonctions_conteneur *objet_selectionnable::get_conteneur_courant()
{
    // TODO
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
        emit signal_os_deselectionne();
        s_objet_courant = NULL;
    }
}
