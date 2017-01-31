#include "entete/parametre/parametre_choix.h"

#include <iostream>

class base_parametre;

parametre_choix::parametre_choix( objet_selectionnable * parent, QString nom, QString aide,
                                  bool peut_etre_vide, bool dans_configuration, type_algorithme algorithme,
                                  const QStringList & choix, bool multiple_selection )
    : base_parametre(parent, nom, aide, peut_etre_vide, dans_configuration, algorithme),
      m_choix(choix), m_multiple_selection(multiple_selection)
{
    m_type = TYPE_PARAM_CHOIX;
}

parametre_choix::~parametre_choix()
{

}

QStringList parametre_choix::get_choix() const
{
    return m_choix;
}

bool parametre_choix::multiple_selection() const
{
    return m_multiple_selection;
}
