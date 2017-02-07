/** \file log_widget_item.cpp
 * \brief Fichier d'implémentation de la classe log_widget_item.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/log_widget_item.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Construteur de la classe log_widget_item.
 * \param log Le log à afficher.
 */
log_widget_item::log_widget_item(const log_compilation &log)
    : m_log(log)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void log_widget_item::init()
{
    setTextColor( m_log.get_couleur() );
    setText( m_log.get_message() );
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du log associé.
 * \return Le log associé.
 */
log_compilation& log_widget_item::get_log()
{
    return m_log;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors de la suppression d'un objet sélectionnable.
 * \param obj Un pointeur sur l'objet supprimé.
 */
void log_widget_item::informe_supression_selectionnable(objet_selectionnable *obj)
{
    m_log.informe_supression_selectionnable(obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Marque tous les messages comme ancien.
 */
void log_widget_item::marquer_comme_ancien()
{
    setTextColor( QColor("grey") );
}
