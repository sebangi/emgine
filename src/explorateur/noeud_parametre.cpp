#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/base_parametre.h"
#include "entete/projet/base_fonction.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/projet/objet_selectionnable.h"

#include <iostream>
#include <QApplication>

noeud_parametre::noeud_parametre( base_parametre * p )
    : base_noeud( (objet_selectionnable *)p, base_noeud::type_parametre )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );

    setText(0, p->get_nom());

    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/icone_parametre.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}

noeud_parametre::~noeud_parametre()
{
}

base_parametre* noeud_parametre::get_parametre() const
{
    return (base_parametre*)m_objet;
}

fonctions_conteneur *noeud_parametre::get_fonctions_conteneur()
{
    return (fonctions_conteneur*)m_objet;
}


