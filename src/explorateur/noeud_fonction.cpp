#include "explorateur/noeud_fonction.h"
#include "fonction/base_fonction.h"
#include <iostream>
#include <fenetre_principale.h>
#include "fonction/fonction_source/fonction_base_source.h"
#include "compilation/logs_compilation_widget.h"

#include <QApplication>

noeud_fonction::noeud_fonction( base_fonction * f )
    : base_noeud( base_noeud::type_fonction ),
      m_fonction(f)
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled );
    setText(0, f->get_nom());

    QIcon icon1;
    if ( f->get_type() == base_fonction::fonction_source )
        icon1.addFile(QString::fromUtf8("icons/icone_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if ( f->get_type() == base_fonction::fonction_conversion )
        icon1.addFile(QString::fromUtf8("icons/icone_fonction.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if ( f->get_type() == base_fonction::fonction_sortie )
        icon1.addFile(QString::fromUtf8("icons/icone_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );


}

noeud_fonction::~noeud_fonction()
{
}

base_fonction* noeud_fonction::get_fonction() const
{
    return m_fonction;
}

void noeud_fonction::update_style()
{
    QFont f = font(0);
    f.setStrikeOut( ! m_fonction->est_active() );
    setFont(0,f);
}


QString noeud_fonction::get_nom() const
{
    return m_fonction->get_nom();
}


