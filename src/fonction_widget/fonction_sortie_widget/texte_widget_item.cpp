#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"

#include <iostream>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>

texte_widget_item::texte_widget_item(texte & t)
    : m_texte(t)
{
    update();
}

void texte_widget_item::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void texte_widget_item::update()
{
    if ( m_texte.get_configuration_visible() )
        setText( m_texte.get_string_configuration() + "\n\n" + m_texte.to_string_lisible() );
    else
        setText( m_texte.to_string_lisible() );
}

texte &texte_widget_item::get_texte() const
{
    return m_texte;
}
