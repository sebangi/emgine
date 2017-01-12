#ifndef LOG_WIDGET_ITEM_H
#define LOG_WIDGET_ITEM_H

#include "entete/compilation/log_compilation.h"

#include <QListWidgetItem>

class log_widget_item : public  QListWidgetItem
{
    public:
            log_widget_item(const log_compilation& get_log);

            log_compilation& get_log();

            void informe_supression_selectionnable(objet_selectionnable * obj);

    private:
            void init();

    private:
            log_compilation m_log;
};

#endif // LOG_WIDGET_ITEM_H
