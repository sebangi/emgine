#include "entete/explorateur/noeud_fonction.h"
#include "entete/projet/base_fonction.h"
#include <iostream>
#include "entete/fenetre_principale.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/projet/objet_selectionnable.h"

#include <QApplication>

noeud_fonction::noeud_fonction( base_fonction * f )
    : base_noeud( (objet_selectionnable *)f, base_noeud::type_fonction )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled );
    setText(0, f->get_nom());

    mise_a_jour_icone();
}

noeud_fonction::~noeud_fonction()
{
}

base_fonction* noeud_fonction::get_fonction() const
{
    return (base_fonction *)m_objet;
}

void noeud_fonction::mise_a_jour_icone()
{
    QIcon icon1;
    QString fichier = "icons/icone_";

    if ( ((base_fonction *)m_objet)->get_type() == base_fonction::fonction_source )
        fichier += "source";
    else if ( ((base_fonction *)m_objet)->get_type() == base_fonction::fonction_conversion )
        fichier += "conversion";
    else if ( ((base_fonction *)m_objet)->get_type() == base_fonction::fonction_sortie )
        fichier += "sortie";

    if ( m_objet->est_verrouille_avec_parent() )
        fichier += "_verrouille";

    fichier += ".png";
    icon1.addFile(fichier, QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}



