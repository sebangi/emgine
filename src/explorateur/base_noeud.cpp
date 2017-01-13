#include "entete/explorateur/base_noeud.h"

#include "entete/projet/projet.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/projet/objet_selectionnable.h"

#include <iostream>

base_noeud::base_noeud( objet_selectionnable * obj, base_noeud::type_noeud type )
    : QTreeWidgetItem( (int)type ), m_save_expanded(true)
{    
    m_objet = obj;
}

base_noeud::~base_noeud()
{
}

fonctions_conteneur * base_noeud::get_fonctions_conteneur()
{
    return NULL;
}

objet_selectionnable *base_noeud::get_objet() const
{
    return m_objet;
}

void base_noeud::update_style(bool actif)
{
    QFont f = font(0);
    f.setStrikeOut( ! actif );
    setFont(0,f);
}

bool base_noeud::get_save_expanded() const
{
    return m_save_expanded;
}

void base_noeud::save_expanded()
{
    m_save_expanded = isExpanded();
}

