#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"

#include "entete/explorateur/noeud_fonction.h"
#include <iostream>

fonction_base_sortie::fonction_base_sortie(fonctions_conteneur * conteneur)
    : base_fonction(conteneur, fonction_sortie)
{
}

fonction_base_sortie::~fonction_base_sortie()
{

}

void fonction_base_sortie::set_textes(const textes &textes)
{
    m_textes = textes;
}


