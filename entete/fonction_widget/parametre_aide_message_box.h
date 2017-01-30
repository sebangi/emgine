#ifndef PARAMETRE_AIDE_MESSAGE_BOX_H
#define PARAMETRE_AIDE_MESSAGE_BOX_H

#include <QDialog>

class base_parametre;

class parametre_aide_message_box : public QDialog
{
    public:
        parametre_aide_message_box(QWidget *parent, const base_parametre* parametre);

    private:
        void init();

    private:
        const base_parametre* m_parametre;
};

#endif // PARAMETRE_AIDE_MESSAGE_BOX_H
