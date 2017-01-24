#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

#include <QPlainTextEdit>

class text_edit : public QPlainTextEdit
{
    public:
        text_edit();

        QSize sizeHint() const;
        QSize minimumSizeHint() const;
};

#endif // TEXT_EDIT_H
