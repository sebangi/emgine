#include "explorateur/noeud_projet.h"
#include "explorateur/noeud_fonction.h"
#include "projet.h"
#include "fenetre_principale.h"
#include "compilation/logs_compilation_widget.h"
#include "fonction/base_fonction.h"

#include <iostream>
#include <QApplication>

noeud_projet::noeud_projet( projet * p )
    : base_noeud( base_noeud::type_projet ),
      m_projet(p)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsEditable | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );
    setText(0, p->get_nom());

    QStyle* style = QApplication::style();
    setIcon( 0, style->standardIcon( QStyle::SP_DialogOpenButton ) );
}

noeud_projet::~noeud_projet()
{
}

projet* noeud_projet::get_projet() const
{
    return m_projet;
}

QString noeud_projet::get_nom() const
{
    return  "projet " + m_projet->get_nom();
}

fonctions_conteneur *noeud_projet::get_fonctions_conteneur()
{
    return m_projet;
}

