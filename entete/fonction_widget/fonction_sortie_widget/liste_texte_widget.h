#ifndef LISTE_TEXTE_WIDGET_H
#define LISTE_TEXTE_WIDGET_H

/** \file liste_texte_widget.h
 * \brief Fichier de déclaration de la classe liste_texte_widget.
 * \author Sébastien Angibaud
 */

#include <QListWidget>

/**
 * \class liste_texte_widget
 * \brief Classe décrivant un widget affichant une liste de texte.
 * \author Sébastien Angibaud
 */
class liste_texte_widget : public QListWidget
{
    public:
        liste_texte_widget();

        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        void init();
};

#endif // LISTE_TEXTE_WIDGET_H
