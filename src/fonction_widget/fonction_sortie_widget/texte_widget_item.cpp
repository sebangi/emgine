#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"

#include <iostream>

texte_widget_item::texte_widget_item(texte & t, int num)
    : m_texte(t), m_num(num)
{
    update();
}

void texte_widget_item::update()
{
    if ( m_texte.get_configuration_visible() )
        setText( "Texte n°" + QString::number(m_num) + ":\n" +
                 m_texte.get_string_separation() +
                 m_texte.get_string_information_taille() + "\n" + m_texte.get_string_configuration() +
                 m_texte.get_string_separation() + m_texte.to_string_lisible() );
    else
        setText( m_texte.to_string_lisible() );
}

texte &texte_widget_item::get_texte() const
{
    return m_texte;
}
