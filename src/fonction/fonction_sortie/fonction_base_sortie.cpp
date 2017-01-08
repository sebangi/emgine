#include "fonction/fonction_sortie/fonction_base_sortie.h"

#include "explorateur/noeud_fonction.h"
#include <iostream>

fonction_base_sortie::fonction_base_sortie(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom, fonction_sortie)
{
}

fonction_base_sortie::~fonction_base_sortie()
{

}

void fonction_base_sortie::set_texte(const texte &texte)
{
    m_texte = texte;
}


