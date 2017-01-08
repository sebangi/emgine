#include "vue_fonction/vue_fonctions.h"

#include "fonction/base_fonction.h"
#include "fonction_widget/base_fonction_widget.h"
#include "explorateur/base_noeud.h"
#include "explorateur/noeud_fonction.h"

#include <QtGui>
#include <iostream>

vue_fonctions::vue_fonctions(QWidget *parent)
    : QTableWidget(parent)
{

}

/** --------------------------------------------------------------------------------------
 \brief Ajoute la vue de la fonction.
*/
void vue_fonctions::ajouter_vue_fonction(base_fonction* fonction)
{
    base_fonction_widget * widget = fonction->generer_fonction_widget();

    connect( fonction, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    connect( (base_fonction_widget *)widget, SIGNAL(signal_bfw_parametre_selectionne(base_parametre*)),
             this, SLOT(on_externe_parametre_selectionne(base_parametre*)));

    setRowCount(rowCount() + 1);
    setCellWidget(rowCount() -1, 1, (QWidget*)widget);
    setItem(rowCount() -1, 2, new QTableWidgetItem("essai"));

    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setResizeMode(QHeaderView::ResizeToContents);

    QStyle* style = QApplication::style();
    QPushButton * image = new QPushButton();
    image->setObjectName("NomParametre");
    image->setIcon(style->standardIcon( QStyle::SP_MediaPlay ));
    image->setIconSize(QSize(32,32));
    setCellWidget(rowCount() -1, 0, image);
    image->setEnabled(false);
}


/** --------------------------------------------------------------------------------------
 \brief Gestion d'un clic sur le bouton bouton_decoder.
*/
void vue_fonctions::update_vue_fonction( base_noeud* courant )
{
    clear();
    setRowCount(0);
    setHorizontalHeaderItem(0, new QTableWidgetItem());
    horizontalHeaderItem(0)->setText("");
    setHorizontalHeaderItem(1, new QTableWidgetItem());
    horizontalHeaderItem(1)->setText("");

    if ( courant != NULL )
    {
        horizontalHeaderItem(1)->setText( courant->get_nom() );

        fonctions_conteneur * conteneur = courant->get_fonctions_conteneur();
        if ( conteneur != NULL )
        {
            for ( fonctions_conteneur::fonctions_iterateur it = conteneur->fonctions_begin();
                  it != conteneur->fonctions_end(); ++it )
                ajouter_vue_fonction( *it );
        }
    }

    update_selection( courant );
}

/** --------------------------------------------------------------------------------------
 \brief Gestion d'un clic sur le bouton bouton_decoder.
*/
void vue_fonctions::update_selection( base_noeud* courant )
{
    if ( courant != NULL )
    {
        for ( int i = 0; i != courant->childCount(); ++i )
            if ( i < rowCount() )
            {
                ((QPushButton*)(cellWidget(i,0)))->setEnabled
                        ( courant->child(i)->isSelected( ) );

                if ( courant->child(i)->isSelected( ) )
                {
                    QTableWidgetItem * tableItem = item(i,2);

                    setColumnHidden(2,false);
                    scrollToItem( tableItem );
                    setColumnHidden(2,true);
                }
            }
    }
}

void vue_fonctions::on_externe_supprimer_fonction(base_fonction *f)
{
    bool trouve = false;

    for ( int i = 0; ! trouve && i != rowCount(); ++i )
        if ( ((base_fonction_widget *)(this->cellWidget(i,1)))->get_fonction() == f )
        {
            trouve = true;
            this->removeRow(i);
        }
}

void vue_fonctions::on_externe_parametre_selectionne(base_parametre* p)
{
    emit signal_vf_parametre_selectionne(p);
}

