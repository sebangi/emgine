#include "entete/fonction_widget/bouton_choix_fonction.h"
#include "entete/projet/base_fonction.h"
#include "entete/fonction/bibliotheque_fonctions.h"

#include <iostream>

bouton_choix_fonction::bouton_choix_fonction(type_id_fonction id, QWidget *parent)
    : QPushButton(parent), m_id_fonction(id)
{
    setText( bibliotheque_fonctions::nom_to_string(m_id_fonction) );
}

base_fonction * bouton_choix_fonction::get_fonction()
{
    return bibliotheque_fonctions::get_fonction(m_id_fonction);
}

type_id_fonction bouton_choix_fonction::get_id_fonction() const
{
    return m_id_fonction;
}


