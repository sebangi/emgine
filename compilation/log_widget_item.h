#ifndef LOG_WIDGET_ITEM_H
#define LOG_WIDGET_ITEM_H

#include "compilation/log_compilation.h"

#include <QListWidgetItem>

class projet;
class base_fonction;

class log_widget_item : public  QListWidgetItem
{
    public:
            log_widget_item(const log_compilation& get_log);

            log_compilation& get_log();

            // TODO : utiliser les 3 méthodes ci-dessous
            void informe_supression_projet(projet * p);
            void informe_supression_fonction(base_fonction * f);
            void informe_supression_parametre(base_parametre * p);

    private:
            void init();

    private:
            log_compilation m_log;
};

#endif // LOG_WIDGET_ITEM_H
