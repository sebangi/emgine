#include "entete/explorateur/noeud_fonctions_conteneur.h"

#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/base_fonction.h"

#include <iostream>

noeud_fonctions_conteneur::noeud_fonctions_conteneur( fonctions_conteneur * conteneur, type_noeud type )
    : base_noeud( type )
{

}

noeud_fonctions_conteneur::~noeud_fonctions_conteneur()
{
}
