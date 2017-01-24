#ifndef base_fonction_widget_avec_text_edit_H
#define base_fonction_widget_avec_text_edit_H


#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/fonction_widget/text_edit.h"

class base_fonction_widget_avec_text_edit : public base_fonction_widget
{
        Q_OBJECT

    protected:
        text_edit * m_text_edit;

    public:
        base_fonction_widget_avec_text_edit( base_fonction* fonction, QWidget *parent = 0 );

    protected:
        void init();
        QString get_valeur() const { return m_text_edit->toPlainText(); };

    private:
        virtual void on_nouveau_texte() = 0;
        virtual QString chercher_valeur() const = 0;

    private slots :
        void on_textChanged();

};


#endif // base_fonction_widget_avec_text_edit_H
