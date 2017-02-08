#ifndef LOG_WIDGET_ITEM_H
#define LOG_WIDGET_ITEM_H

/** \file log_widget_item.h
 * \brief Fichier de déclaration de la classe log_widget_item.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/log_compilation.h"

#include <QListWidgetItem>

/**
 * \class log_widget_item
 * \brief Classe décrivant le widget item affichant un message de log.
 * \author Sébastien Angibaud
 */
class log_widget_item : public  QListWidgetItem
{
    public:
            log_widget_item(const log_compilation& get_log);

            log_compilation& get_log();

            void informe_supression_selectionnable(objet_selectionnable * obj);
            void marquer_comme_ancien();

    private:
            void init();

    private:
            /** \brief Le log associé. */
            log_compilation m_log;
};

#endif // LOG_WIDGET_ITEM_H
