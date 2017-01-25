#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/projet.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/objet_selectionnable.h"

#include <iostream>
#include <QApplication>

noeud_projet::noeud_projet( projet * p )
    : noeud_fonctions_conteneur( (fonctions_conteneur*)p, base_noeud::type_projet )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );
    setText(0, p->get_nom());

    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}

noeud_projet::~noeud_projet()
{
}

projet* noeud_projet::get_projet() const
{
    return (projet*)m_objet;
}

fonctions_conteneur *noeud_projet::get_fonctions_conteneur()
{
    return (fonctions_conteneur*)m_objet;
}
