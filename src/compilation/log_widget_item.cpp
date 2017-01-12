#include "entete/compilation/log_widget_item.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <iostream>

log_widget_item::log_widget_item(const log_compilation &log)
    : m_log(log)
{
    init();
}

void log_widget_item::init()
{
    this->setTextColor( m_log.get_couleur() );
    this->setText( m_log.get_message() );
}

log_compilation& log_widget_item::get_log()
{
    return m_log;
}

void log_widget_item::informe_supression_selectionnable(objet_selectionnable *obj)
{
}

