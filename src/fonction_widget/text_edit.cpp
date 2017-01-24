#include "entete/fonction_widget/text_edit.h"
#include <iostream>

text_edit::text_edit()
{
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setMinimumHeight(20);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

QSize text_edit::sizeHint() const
{
    return minimumSizeHint();
}

QSize text_edit::minimumSizeHint() const
{
    QFontMetrics fm(this->font());

    return QSize(maximumWidth(), (document()->lineCount() + 2) * fm.lineSpacing());
}
