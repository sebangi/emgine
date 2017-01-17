#include "entete/projet/fonctions_conteneur.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"
#include <iostream>

fonctions_conteneur::fonctions_conteneur( objet_selectionnable * parent )
    : objet_selectionnable(parent)
{

}

void fonctions_conteneur::ajouter_fonction(base_fonction *f)
{
    f->set_conteneur(this);
    m_fonctions.push_back(f);

    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_supprimer_fonction(base_fonction*)));

    emit signal_fc_creation_fonction(f);
    get_projet()->modifier();
}

void fonctions_conteneur::supprimer_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_supprimer_fonction(base_fonction*)));

    m_fonctions.removeOne(f);
    get_projet()->modifier();
}


void fonctions_conteneur::on_supprimer_fonction(base_fonction *f)
{
    supprimer_fonction(f);
}


fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_begin()
{
    return m_fonctions.begin();
}

fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_end()
{
    return m_fonctions.end();
}

fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_begin() const
{
    return m_fonctions.constBegin();
}

fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_end() const
{
    return m_fonctions.constEnd();
}

bool fonctions_conteneur::est_conteneur() const
{
    return true;
}
