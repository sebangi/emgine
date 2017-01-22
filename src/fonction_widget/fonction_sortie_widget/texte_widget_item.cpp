#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"

#include "entete/element/texte.h"

texte_widget_item::texte_widget_item(const texte & t)
    : m_texte(t)
{
    init();
}

void texte_widget_item::init()
{
    setText( m_texte.to_string_lisible() );
    this->setToolTip( m_texte.get_string_configuration() );
}

const texte& texte_widget_item::get_texte() const
{
    return m_texte;
}
