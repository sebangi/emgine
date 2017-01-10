#include "entete/explorateur/base_noeud.h"

#include "entete/projet/projet.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"

#include <iostream>

base_noeud::base_noeud( base_noeud::type_noeud type )
    : QTreeWidgetItem( (int)type )
{    

}

base_noeud::~base_noeud()
{
}

fonctions_conteneur * base_noeud::get_fonctions_conteneur()
{
    return NULL;
}

