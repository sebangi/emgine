#ifndef LINE_EDIT_H
#define LINE_EDIT_H

#include <QLineEdit>

class line_edit : public QLineEdit
{
        Q_OBJECT

    public:
        line_edit(QWidget *parent = 0);
        ~line_edit();

    signals:
        void focussed(bool hasFocus);

    protected:
        virtual void focusInEvent(QFocusEvent *e);
        virtual void focusOutEvent(QFocusEvent *e);
};

#endif // LINE_EDIT_H
