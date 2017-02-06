#include "entete/fonction/fonction_source/fonction_base_source.h"

#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/fonctions_conteneur.h"
#include <iostream>

fonction_base_source::fonction_base_source(fonctions_conteneur * conteneur)
    : base_fonction(conteneur, type_fonction::fonction_source)
{
    set_est_etendu(false);
}

fonction_base_source::~fonction_base_source()
{

}
