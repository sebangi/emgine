#ifndef FONCTION_SORTIE_TEXTE_WIDGET_H
#define FONCTION_SORTIE_TEXTE_WIDGET_H

#include "fonction_widget/base_fonction_widget.h"

#include <QPlainTextEdit>

class texte;

class fonction_sortie_texte_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_sortie_texte_widget( base_fonction* fonction, QWidget *parent = 0 );
        void set_texte( const texte & texte_in );

    private:
        void init();
        void update_label();

    private:
        QPlainTextEdit * m_text_edit;
};

#endif // FONCTION_SORTIE_TEXTE_WIDGET_H
