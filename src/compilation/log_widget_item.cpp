#include "compilation/log_widget_item.h"

#include "fonction/base_fonction.h"
#include "projet.h"

#include <iostream>

log_widget_item::log_widget_item(const log_compilation &log)
    : m_log(log)
{
    init();
}

void log_widget_item::informe_supression_projet(projet * p)
{
    m_log.informe_supression_projet(p);
}

void log_widget_item::informe_supression_fonction(base_fonction * f)
{
    m_log.informe_supression_fonction(f);
}

void log_widget_item::informe_supression_parametre(base_parametre * p)
{
    m_log.informe_supression_parametre(p);
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

