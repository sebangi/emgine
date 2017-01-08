#include "explorateur/noeud_parametre.h"
#include "explorateur/noeud_fonction.h"
#include "parametre/base_parametre.h"
#include "fonction/base_fonction.h"
#include "fenetre_principale.h"
#include "compilation/logs_compilation_widget.h"

#include <iostream>
#include <QApplication>

noeud_parametre::noeud_parametre( base_parametre * p )
    : base_noeud( base_noeud::type_parametre ),
      m_parametre(p)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );

    setText(0, p->get_nom());

    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/icone_parametre.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}

noeud_parametre::~noeud_parametre()
{
    if ( m_parametre != NULL )
        delete m_parametre;
}

base_parametre* noeud_parametre::get_parametre() const
{
    return m_parametre;
}

QString noeud_parametre::get_nom() const
{
    return m_parametre->get_fonction_parent()->get_nom() + " : paramètre " + m_parametre->get_nom();
}

fonctions_conteneur *noeud_parametre::get_fonctions_conteneur()
{
    return m_parametre;
}


