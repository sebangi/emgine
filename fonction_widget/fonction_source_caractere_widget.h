#ifndef FONCTION_SOURCE_CARACTERE_WIDGET_H
#define FONCTION_SOURCE_CARACTERE_WIDGET_H

#include "fonction_widget/base_fonction_widget.h"
#include <QTextEdit>

class fonction_source_caractere_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_caractere_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();
        void update_label();

    private slots :
        void on_textChanged();

    private:
        QTextEdit * m_text_edit;
};

#endif // FONCTION_SOURCE_CARACTERE_WIDGET_H
