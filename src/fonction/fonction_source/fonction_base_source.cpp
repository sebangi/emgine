#include "fonction/fonction_source/fonction_base_source.h"

#include "explorateur/noeud_fonction.h"
#include <iostream>

fonction_base_source::fonction_base_source(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom, fonction_source)
{
}

fonction_base_source::~fonction_base_source()
{

}
