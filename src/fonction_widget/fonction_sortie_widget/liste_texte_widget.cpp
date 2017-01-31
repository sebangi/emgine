#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"

#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/element/texte.h"
#include <iostream>
#include <QLayout>
#include <QHeaderView>
#include <QScrollBar>

liste_texte_widget::liste_texte_widget()
{
    init();
}

QSize liste_texte_widget::sizeHint() const
{
    int height = 10;

    for ( int i = 0; i != count(); ++i )
        height += ((texte_widget_item*)item(i))->get_height() + 1;

    return QSize(maximumWidth(), height);
}

QSize liste_texte_widget::minimumSizeHint() const
{
    return QSize(maximumWidth(), minimumHeight());
}

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
}

