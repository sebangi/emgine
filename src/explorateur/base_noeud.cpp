#include "explorateur/base_noeud.h"

#include "projet.h"
#include "fenetre_principale.h"
#include "compilation/log_compilation.h"
#include "compilation/logs_compilation_widget.h"

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

