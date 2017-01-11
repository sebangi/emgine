#include "entete/fonction_widget/vue_fonctions.h"

#include "entete/projet/base_fonction.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/projet/projet.h"

#include <QtGui>
#include <QApplication>
#include <QHeaderView>
#include <iostream>

vue_fonctions::vue_fonctions(QWidget *parent)
    : QTableWidget(parent), m_conteneur_courant(NULL)
{
    init();
}

void vue_fonctions::ajouter_projet(projet *p)
{
    if ( p != NULL )
    {
        ajouter_selectionnable((objet_selectionnable*)p);

        connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                 this, SLOT(on_externe_creation_fonction(base_fonction*)));

        creer_vue_conteneur();
    }
}

void vue_fonctions::init()
{
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setColumnCount(3);
    setColumnHidden(2,true);
    setColumnWidth(0,50);
    horizontalHeader()->setStretchLastSection(true);
    setShowGrid(false);

    setRowCount(0);
    setHorizontalHeaderItem(0, new QTableWidgetItem());
    horizontalHeaderItem(0)->setText("");
    setHorizontalHeaderItem(1, new QTableWidgetItem());
    horizontalHeaderItem(1)->setText("");

    connect( selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
             SLOT(on_vue_fonction_selectionChanged(const QItemSelection &, const QItemSelection &))
             );
}

/** --------------------------------------------------------------------------------------
 \brief On crée la vue.
*/
void vue_fonctions::creer_vue_conteneur()
{
    clearContents();
    setRowCount(0);
    horizontalHeaderItem(1)->setText("");

    if ( m_conteneur_courant != NULL )
    {
        horizontalHeaderItem(1)->setText( m_conteneur_courant->get_titre() );

        for ( fonctions_conteneur::fonctions_iterateur it = m_conteneur_courant->fonctions_begin();
              it != m_conteneur_courant->fonctions_end(); ++it )
            ajouter_vue_fonction( *it );
    }
}

/** --------------------------------------------------------------------------------------
 \brief Gestion d'un clic sur le bouton bouton_decoder.
*/
/*
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
*/

/** --------------------------------------------------------------------------------------
 \brief Ajoute la vue de la fonction.
*/
void vue_fonctions::ajouter_vue_fonction(base_fonction* fonction)
{
    base_fonction_widget * widget = fonction->generer_fonction_widget();
    ajouter_selectionnable((objet_selectionnable*)fonction);

    for ( base_fonction::parametres_iterateur it = fonction->parametres_begin();
          it != fonction->parametres_end(); ++it )
        ajouter_selectionnable((objet_selectionnable*)it->second);

    connect( fonction, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    setRowCount(rowCount() + 1);
    setCellWidget(rowCount() -1, 1, (QWidget*)widget);
    setItem(rowCount() -1, 2, new QTableWidgetItem("essai"));

    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QStyle* style = QApplication::style();
    QPushButton * image = new QPushButton();
    image->setObjectName("NomParametre");
    image->setIcon(style->standardIcon( QStyle::SP_MediaPlay ));
    image->setIconSize(QSize(32,32));
    setCellWidget(rowCount() -1, 0, image);
    image->setEnabled(false);
}

void vue_fonctions::ajouter_selectionnable(objet_selectionnable *obj)
{
    m_selectionnables.insert(obj);

    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

void vue_fonctions::deconnecter(objet_selectionnable* obj)
{
    // déconnection de base de l'objet
    disconnect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    disconnect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));

    if ( obj->est_conteneur() )
    {
        // déconnection des contenus
        for ( fonctions_conteneur::fonctions_iterateur it = ((fonctions_conteneur *)(obj->get_conteneur()))->fonctions_begin();
              it != ((fonctions_conteneur *)(obj->get_conteneur()))->fonctions_end(); ++it )
            deconnecter(*it);
    }
    else
    {
        // déconnection des fonctions
        disconnect( (base_fonction*)obj, SIGNAL(signal_destruction_fonction(base_fonction*)),
                    this, SLOT(on_externe_supprimer_fonction(base_fonction*)));
    }

    // suppression de l'objet
    liste_selectionnable::iterator it = m_selectionnables.find(obj);
    if ( it != m_selectionnables.end() )
        m_selectionnables.erase(it);
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

    deconnecter((objet_selectionnable*)f);
}

void vue_fonctions::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    if ( obj->get_conteneur() != m_conteneur_courant )
    {
        m_conteneur_courant = (fonctions_conteneur*)obj->get_conteneur();
        creer_vue_conteneur();
    }
    else
    {
        for ( int i = 0; i != rowCount(); ++i )
        {
            if ( (objet_selectionnable *)((base_fonction_widget*)(cellWidget(i,1)))->get_fonction() == obj )
            {
                ((QPushButton*)(cellWidget(i,0)))->setEnabled( true );

                QTableWidgetItem * tableItem = item(i,2);
                setColumnHidden(2,false);
                scrollToItem( tableItem );
                setColumnHidden(2,true);
            }
        }
    }
}

void vue_fonctions::on_externe_objet_deselectionne(objet_selectionnable *obj)
{
    if ( obj->get_conteneur() != m_conteneur_courant )
    {
        m_conteneur_courant = NULL;
        clearContents();
    }
    else
    {
        for ( int i = 0; i != rowCount(); ++i )
            ((QPushButton*)(cellWidget(i,0)))->setEnabled( false );
    }
}

void vue_fonctions::on_externe_creation_fonction(base_fonction* f)
{
    ajouter_vue_fonction(f);
}

/** --------------------------------------------------------------------------------------
 \brief La sélection de la vue_fonction change.
*/
void vue_fonctions::on_vue_fonction_selectionChanged(const QItemSelection &last_index, const QItemSelection & new_index)
{
    int row = currentRow();

    if ( row >= 0 )
        ( (objet_selectionnable *)( ( (base_fonction_widget*)( cellWidget(row,1) ) )->get_fonction() ) ) ->selectionner();
}


