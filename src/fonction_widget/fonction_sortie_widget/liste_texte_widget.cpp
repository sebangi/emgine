/**
 * \file liste_texte_widget.cpp
 * \brief Fichier d'implémentation de la classe liste_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"

#include "entete/element/texte.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"

#include <QHeaderView>
#include <QLayout>
#include <QScrollBar>
#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe liste_texte_widget.
 */
liste_texte_widget::liste_texte_widget()
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de la fonction sizeHint retournant la taille désirée du composant.
 * \return La taille désirée du composant.
 */
QSize liste_texte_widget::sizeHint() const
{
    int height = 10 + horizontalScrollBar()->height();

    for ( int i = 0; i != count(); ++i )
        height += ((texte_widget_item*)item(i))->get_height() + 1;

    return QSize(maximumWidth(), height);
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de la fonction minimumSizeHint retournant la taille minimum désirée du composant.
 * \return La taille minimum désirée du composant.
 */
QSize liste_texte_widget::minimumSizeHint() const
{
    return QSize(maximumWidth(), minimumHeight());
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void liste_texte_widget::init()
{
    setContextMenuPolicy(Qt::CustomContextMenu);
    setObjectName("ListeTexte");
    setWrapping(false);
    setMinimumHeight(25);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
    verticalScrollBar()->setSingleStep(20);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

