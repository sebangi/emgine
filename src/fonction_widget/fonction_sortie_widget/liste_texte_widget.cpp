#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"

#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/element/texte.h"
#include <iostream>
#include <QLayout>
#include <QHeaderView>

liste_texte_widget::liste_texte_widget()
{
    init();

    /*
    setObjectName("ListeTexte");
    setWrapping(false);
    setMinimumHeight(25);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    */
}

/*
QSize liste_texte_widget::sizeHint() const
{
    return minimumSizeHint();
}

QSize liste_texte_widget::minimumSizeHint() const
{
    int height = 150;
    for ( int i = 0; i != count(); ++i )
        height += ((texte_widget_item*)item(i))->get_height() + 1;

    return QSize(maximumWidth(), height);
}
*/


void liste_texte_widget::init()
{
    setMinimumHeight(25);
    setMaximumHeight(400);
    setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setColumnCount(3);

    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    horizontalHeader()->setHighlightSections(false);
    setShowGrid(true);

    horizontalHeader()->setFixedHeight(25);
    horizontalHeader()->hide();
    setRowCount(0);
    //setHorizontalHeaderItem(0, new QTableWidgetItem());
    //setHorizontalHeaderItem(1, new QTableWidgetItem());
    //horizontalHeaderItem(1)->setText("");
}
