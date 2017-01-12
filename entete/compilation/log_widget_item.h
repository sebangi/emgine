#ifndef LOG_WIDGET_ITEM_H
#define LOG_WIDGET_ITEM_H

#include "entete/compilation/log_compilation.h"

#include <QListWidgetItem>

class projet;
class base_fonction;

class log_widget_item : public  QListWidgetItem
{
    public:
            log_widget_item(const log_compilation& get_log);

            log_compilation& get_log();

    private:
            void init();

    private:
            log_compilation m_log;
};

#endif // LOG_WIDGET_ITEM_H
