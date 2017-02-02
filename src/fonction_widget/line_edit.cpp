#include "entete/fonction_widget/line_edit.h"

line_edit::line_edit(QWidget *parent)
 : QLineEdit(parent)
{}

line_edit::~line_edit()
{}

void line_edit::focusInEvent(QFocusEvent *e)
{
  QLineEdit::focusInEvent(e);
  emit(focussed(true));
}

void line_edit::focusOutEvent(QFocusEvent *e)
{
  QLineEdit::focusOutEvent(e);
  emit(focussed(false));
}
