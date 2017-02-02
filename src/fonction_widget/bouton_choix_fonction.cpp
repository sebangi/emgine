#include "entete/fonction_widget/bouton_choix_fonction.h"
#include "entete/projet/base_fonction.h"
#include "entete/fonction/bibliotheque_fonctions.h"

#include <iostream>

bouton_choix_fonction::bouton_choix_fonction(type_id_fonction id, QWidget *parent)
    : QPushButton(parent), m_id_fonction(id)
{
    setText( bibliotheque_fonctions::get_nom(m_id_fonction) );

    if ( id < debut_fonction_conversion )
        setObjectName("BoutonChoixFonctionSource");
    else if ( id < debut_fonction_sortie )
        setObjectName("BoutonChoixFonctionConversion");
    else
        setObjectName("BoutonChoixFonctionSortie");
}

base_fonction * bouton_choix_fonction::get_fonction()
{
    return bibliotheque_fonctions::get_fonction(m_id_fonction);
}

type_id_fonction bouton_choix_fonction::get_id_fonction() const
{
    return m_id_fonction;
}

void bouton_choix_fonction::mettre_a_jour_visibilite( const QString & cle )
{
    setVisible( bibliotheque_fonctions::contient_mot_cle( m_id_fonction, cle ) );
}
