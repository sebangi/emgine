#ifndef FONCTION_SOURCE_BOOLEEN_WIDGET_H
#define FONCTION_SOURCE_BOOLEEN_WIDGET_H

#include "fonction_widget/base_fonction_widget.h"

#include <QCheckBox>

class fonction_source_booleen_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_booleen_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();

    private slots :
        void on_oui_stateChanged(int checkState);
        void on_non_stateChanged(int checkState);

    private:
        QCheckBox * m_check_oui;
        QCheckBox * m_check_non;
};

#endif // FONCTION_SOURCE_BOOLEEN_WIDGET_H
