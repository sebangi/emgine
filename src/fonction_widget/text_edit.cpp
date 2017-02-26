/** \file texte_edit.cpp
 * \brief Fichier d'implémentation de la classe texte_edit.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/text_edit.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe texte_edit.
 */
text_edit::text_edit()
{
    setLineWrapMode(QPlainTextEdit::NoWrap);
    setMinimumHeight(20);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de la méthode sizeHint.
 * \return La taille désirée du widget.
 */
QSize text_edit::sizeHint() const
{
    return minimumSizeHint();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de la méthode minimumSizeHint.
 * \return La taille minimum désirée.
 */
QSize text_edit::minimumSizeHint() const
{
    QFontMetrics fm(this->font());

    return QSize(maximumWidth(), (document()->lineCount() + 2) * fm.lineSpacing());
}
