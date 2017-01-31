#include "entete/fonction_widget/vue_fonctions.h"

#include "entete/projet/base_fonction.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/projet/projet.h"

#include <QtGui>
#include <QApplication>
#include <QHeaderView>
#include <iostream>
#include <QScrollBar>

vue_fonctions::vue_fonctions(QWidget *parent)
    : QTableWidget(parent), m_conteneur_courant(NULL), m_bloquer_selection(false)
{
    init();
}

void vue_fonctions::ajouter_projet(projet *p)
{
    if ( p != NULL )
    {
        ajouter_selectionnable((objet_selectionnable*)p);
        connecter_projet(p);

        for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
            ajouter_fonction( *it );

        creer_vue_conteneur();
    }
}

void vue_fonctions::init()
{
    setObjectName("vue_fonctions");
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
    verticalHeader()->hide();
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    setSelectionMode(QAbstractItemView::SingleSelection);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setColumnCount(3);
    setColumnHidden(2,true);
    setColumnWidth(0,50);
    horizontalHeader()->setStretchLastSection(true);
    horizontalHeader()->setHighlightSections(false);
    setShowGrid(false);

    horizontalHeader()->setFixedHeight(25);
    setRowCount(0);
    setHorizontalHeaderItem(0, new QTableWidgetItem());
    setHorizontalHeaderItem(1, new QTableWidgetItem());
    horizontalHeaderItem(1)->setText("");
    QFont font = horizontalHeaderItem(1)->font();
    font.setBold(true);
    font.setPointSize(10);
    horizontalHeaderItem(1)->setFont(font);

    connect( selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
             SLOT(on_vue_fonction_selectionChanged(const QItemSelection &, const QItemSelection &))
             );

    connect(horizontalHeader(),SIGNAL(sectionDoubleClicked(int)), this,SLOT(on_hheaderclicked(int)));
    connect(horizontalHeader(),SIGNAL(sectionClicked(int)), this,SLOT(on_hheaderclicked(int)));
}

void vue_fonctions::ajouter_fonction(base_fonction *f)
{
    if ( f != NULL )
    {
        ajouter_selectionnable((objet_selectionnable*)f);

        for ( base_fonction::parametres_iterateur it_p = f->parametres_begin(); it_p != f->parametres_end(); ++it_p )
            ajouter_parametre( it_p->second );

        connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                 this, SLOT(on_externe_supprimer_fonction(base_fonction*)));
    }
}

void vue_fonctions::ajouter_parametre(base_parametre* p)
{
    if ( p != NULL )
    {
        ajouter_selectionnable((objet_selectionnable*)p);

        connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                 this, SLOT(on_externe_creation_fonction(base_fonction*)));

        for ( base_parametre::fonctions_iterateur it_f = p->fonctions_begin(); it_f != p->fonctions_end(); ++it_f )
            ajouter_fonction( *it_f );
    }
}

/** --------------------------------------------------------------------------------------
 \brief On crée la vue.
*/
void vue_fonctions::creer_vue_conteneur()
{
    m_bloquer_selection = true;
    clearContents();
    m_bloquer_selection = false;

    setRowCount(0);
    horizontalHeaderItem(1)->setText("");

    if ( m_conteneur_courant != NULL )
    {
        QIcon icon1;
        if ( ! m_conteneur_courant->est_projet() )
            icon1.addFile(QString::fromUtf8("icons/fleche_haut.png"), QSize(), QIcon::Normal, QIcon::Off);

        horizontalHeaderItem(1)->setIcon(icon1);

        horizontalHeaderItem(1)->setText( m_conteneur_courant->get_titre() );

        for ( fonctions_conteneur::fonctions_iterateur it = m_conteneur_courant->fonctions_begin();
              it != m_conteneur_courant->fonctions_end(); ++it )
            ajouter_vue_fonction( *it );
    }
    else
      horizontalHeaderItem(1)->setIcon(QIcon());
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute la vue de la fonction.
*/
void vue_fonctions::ajouter_vue_fonction(base_fonction* fonction)
{
    base_fonction_widget * widget = fonction->generer_fonction_widget();

    connect( widget, SIGNAL(signal_bfw_size_change()),
             this, SLOT(on_externe_fonction_widget_size_change()));

    int position = fonction->get_position();
    insertRow(position);

    setCellWidget(position, 1, (QWidget*)widget);
    setItem(position, 2, new QTableWidgetItem("essai"));

    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QPushButton * image = new QPushButton();
    image->setObjectName("NomParametre");
    QIcon icon1;
    if ( fonction->get_type() == base_fonction::fonction_source )
        icon1.addFile(QString::fromUtf8("icons/selection_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if ( fonction->get_type() == base_fonction::fonction_conversion )
        icon1.addFile(QString::fromUtf8("icons/selection_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    else
        icon1.addFile(QString::fromUtf8("icons/selection_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);

    image->setIcon(icon1);
    image->setIconSize(QSize(32,32));

    setCellWidget(position, 0, image);
    image->setEnabled(false);
}

void vue_fonctions::ajouter_selectionnable(objet_selectionnable *obj)
{
    m_selectionnables.insert(obj);
    connecter_selectionnable(obj);
}

void vue_fonctions::connecter_selectionnable( objet_selectionnable *obj )
{
    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );

    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

void vue_fonctions::deconnecter_selectionnable( objet_selectionnable *obj )
{
    disconnect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );

    disconnect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

void vue_fonctions::connecter_projet( projet *p )
{
    connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
             this, SLOT(on_externe_creation_fonction(base_fonction*)));

    connect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
             this, SLOT(on_externe_nom_projet_change(projet *)));    

    connect( p, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
             this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

    connect( p, SIGNAL(signal_p_destruction_projet(projet *)),
             this, SLOT(on_externe_destruction_projet(projet *)));
}

void vue_fonctions::deconnecter_projet( projet *p )
{
    disconnect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                this, SLOT(on_externe_creation_fonction(base_fonction*)));

    disconnect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
                this, SLOT(on_externe_nom_projet_change(projet *)));

    disconnect( p, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
             this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

    disconnect( p, SIGNAL(signal_p_destruction_projet(projet *)),
                this, SLOT(on_externe_destruction_projet(projet *)));
}

void vue_fonctions::deconnecter(objet_selectionnable* obj)
{
    // déconnection de base de l'objet
    deconnecter_selectionnable(obj);

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

void vue_fonctions::adjust_size_vue_fonction()
{
    for ( int i = 0; i < rowCount(); ++i )
    {
        setRowHeight(i, cellWidget(i,1)->size().height());
    }

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

void vue_fonctions::on_externe_supprimer_fonction(base_fonction *f)
{
    bool trouve = false;

    for ( int i = 0; ! trouve && i != rowCount(); ++i )
    {
        base_fonction_widget * widget = ((base_fonction_widget *)(this->cellWidget(i,1)));

        if ( widget->get_fonction() == f )
        {
            disconnect( widget, SIGNAL(signal_bfw_size_change()),
                        this, SLOT(on_externe_fonction_widget_size_change()));

            trouve = true;
            m_bloquer_selection = true;
            this->removeRow(i);
            m_bloquer_selection = false;
        }
    }

    deconnecter((objet_selectionnable*)f);
}

void vue_fonctions::on_externe_verrouillage_change(objet_selectionnable *obj)
{
    if( m_conteneur_courant == obj )
        for ( int i = 0; i != rowCount(); ++i )
            ((base_fonction_widget*)cellWidget(i,1))->mettre_a_jour_verrouillage();
}

void vue_fonctions::on_externe_nom_projet_change(projet *p)
{
    if( m_conteneur_courant == p )
        horizontalHeaderItem(1)->setText( m_conteneur_courant->get_titre() );
}

void vue_fonctions::on_externe_destruction_projet(projet *p)
{
    if( m_conteneur_courant == p )
    {
        horizontalHeaderItem(1)->setText("");
        m_conteneur_courant = NULL;
    }
}

void vue_fonctions::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    if ( obj->get_conteneur() != m_conteneur_courant )
    {
        m_conteneur_courant = (fonctions_conteneur*)obj->get_conteneur();
        creer_vue_conteneur();
    }

    for ( int i = 0; i != rowCount(); ++i )
    {
        if ( (objet_selectionnable *)((base_fonction_widget*)(cellWidget(i,1)))->get_fonction() == obj )
        {
            ((QPushButton*)(cellWidget(i,0)))->setEnabled( true );

            if ( i == rowCount() - 1 )
            {
                scrollToBottom();
            }
            else
            {
                QTableWidgetItem * tableItem = item(i,2);
                setColumnHidden(2,false);
                scrollToItem( tableItem, EnsureVisible);
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
    ajouter_fonction(f);

    if ( f->get_conteneur() == m_conteneur_courant )
        ajouter_vue_fonction(f);
}

/** --------------------------------------------------------------------------------------
 \brief La sélection de la vue_fonction change.
*/
void vue_fonctions::on_vue_fonction_selectionChanged(const QItemSelection &last_index, const QItemSelection & new_index)
{
    if ( ! m_bloquer_selection )
    {
        int row = currentRow();

        if ( row >= 0 )
            ( (objet_selectionnable *)( ( (base_fonction_widget*)( cellWidget(row,1) ) )->get_fonction() ) )->selectionner();
    }
}

void vue_fonctions::on_externe_fonction_widget_size_change()
{
    adjust_size_vue_fonction();
}

void vue_fonctions::on_hheaderclicked(int colonne)
{
    if ( colonne == 1 )
    {
        if ( m_conteneur_courant != NULL )
        {
            if ( ! m_conteneur_courant->est_projet() )
                m_conteneur_courant->get_conteneur_precedant()->selectionner();
        }
    }
}


