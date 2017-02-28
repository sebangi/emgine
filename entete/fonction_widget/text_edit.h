#ifndef TEXT_EDIT_H
#define TEXT_EDIT_H

/** \file text_edit.h
 * \brief Fichier de déclaration de la classe texte_edit.
 * \author Sébastien Angibaud
 */

#include <QPlainTextEdit>

/**
 * \class text_edit
 * \brief Classe décrivant un widget de type QPlainTextEdit dont la taille est ajustable suivant son contenu.
 * \author Sébastien Angibaud
 */
class text_edit : public QPlainTextEdit
{
    public:
        text_edit();

        QSize sizeHint() const;
        QSize minimumSizeHint() const;
};

#endif // TEXT_EDIT_H
