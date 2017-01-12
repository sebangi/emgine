#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/base_noeud.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/projet/projet.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/fenetre_principale.h"
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <iostream>

explorateur::explorateur(QWidget *parent)
    : QTreeWidget(parent), m_noeud_context(NULL)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setDropIndicatorShown(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setHeaderLabel("Explorateur de projets");
    setExpandsOnDoubleClick(false);

    QTreeWidgetItem* rooItem = invisibleRootItem();
    rooItem->setFlags( rooItem->flags() ^ Qt::ItemIsDropEnabled );

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(on_customContextMenuRequested(const QPoint &)));
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this, SLOT(on_itemClicked(QTreeWidgetItem*, int)));
    connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this,SLOT(on_currentItemChanged(QTreeWidgetItem*)));
}

void explorateur::on_externe_activation_fonction_change(base_fonction * f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
    {
        ((noeud_fonction*)(it->second))->update_style();
    }
}

void explorateur::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    map_selectionnable::iterator it = m_selectionnables.find(obj);

    if ( it != m_selectionnables.end() )
    {
        map_selectionnable::iterator it_conteneur = m_selectionnables.find(obj->get_conteneur());
        if ( it_conteneur != m_selectionnables.end() )
        {
            QFont font = it_conteneur->second->font(0);
            font.setBold(true);
            it_conteneur->second->setFont(0, font);
        }

        setItemSelected((QTreeWidgetItem*)(it->second), true);
    }
}

void explorateur::on_externe_objet_deselectionne(objet_selectionnable *obj)
{
    map_selectionnable::iterator it = m_selectionnables.find(obj->get_conteneur());

    if ( it != m_selectionnables.end() )
    {
        QFont font = it->second->font(0);
        font.setBold(false);
        it->second->setFont(0, font);

        clearSelection();
    }
}

void explorateur::on_externe_creation_fonction(base_fonction* f)
{
    ajouter_fonction(f);
}

void explorateur::on_externe_supprimer_fonction(base_fonction *f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
        it->second->parent()->removeChild(it->second);
}

base_noeud *explorateur::get_projet_selon_nom_fichier(const QString &nom_fichier)
{
    base_noeud * n = NULL;

    QTreeWidgetItemIterator it(this);
    while (*it)
    {
        if ( (*it)->type() == base_noeud::type_projet )
        {
            if ( ((noeud_projet*)(*it))->get_projet()->get_nom_fichier() == nom_fichier )
                n = (base_noeud*)(*it);
        }

        ++it;
    }

    return n;
}

void explorateur::ajouter_projet(projet *p)
{
    if ( p != NULL )
    {
        base_noeud* noeud = new noeud_projet( p );
        ajouter_selectionnable((objet_selectionnable*)p, noeud);

        connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                 this, SLOT(on_externe_creation_fonction(base_fonction*)));

        insertTopLevelItem( 0, noeud );

        for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
            ajouter_fonction( *it );

        expandItem(noeud);
    }
}

void explorateur::ajouter_fonction(base_fonction* f)
{    
    map_selectionnable::iterator it = m_selectionnables.find(f->get_conteneur());
    if ( it != m_selectionnables.end() )
    {
        base_noeud* noeud_parent = it->second;
        base_noeud* noeud = new noeud_fonction( f );
        ajouter_selectionnable((objet_selectionnable*)f, noeud);

        noeud_parent->addChild(noeud);

        for ( base_fonction::parametres_iterateur it_p = f->parametres_begin(); it_p != f->parametres_end(); ++it_p )
            ajouter_parametre( it_p->second );

        expandItem(noeud);

        connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                 this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

        connect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                 this, SLOT(on_externe_activation_fonction_change(base_fonction *)));
    }
}

void explorateur::ajouter_parametre(base_parametre* p)
{
    map_selectionnable::iterator it = m_selectionnables.find(p->get_fonction_parent());
    if ( it != m_selectionnables.end() )
    {
        base_noeud* noeud_parent = it->second;
        base_noeud* noeud = new noeud_parametre( p );
        ajouter_selectionnable((objet_selectionnable*)p, noeud);

        connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                 this, SLOT(on_externe_creation_fonction(base_fonction*)));

        noeud_parent->addChild(noeud);

        for ( base_parametre::fonctions_iterateur it_f = p->fonctions_begin(); it_f != p->fonctions_end(); ++it_f )
            ajouter_fonction( *it_f );

        expandItem(noeud);
    }
}

void explorateur::ajouter_selectionnable(objet_selectionnable *obj, base_noeud *noeud)
{
    m_selectionnables[obj] = noeud;

    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

base_noeud *explorateur::get_noeud_context() const
{
    return m_noeud_context;
}

void explorateur::set_noeud_context(base_noeud *noeud_context)
{
    m_noeud_context = noeud_context;
}

/** --------------------------------------------------------------------------------------
 \brief Evénément click sur un item de l'explorateur de projets.
*/
void explorateur::on_itemClicked(QTreeWidgetItem *item, int column)
{
    ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Changement de sélection l'explorateur de projets.
*/
void explorateur::on_currentItemChanged(QTreeWidgetItem *item)
{
    ((base_noeud*)item)->get_objet()->selectionner();
}

void explorateur::on_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *node = itemAt( pos );

    set_noeud_context( (base_noeud*)node );
    base_noeud* noeud_context = get_noeud_context();

    QMenu menu(this);

    if ( noeud_context == NULL )
        return;

    // TODO
    /*
    if ( noeud_context->type() == base_noeud::type_projet && get_noeud_courant() != noeud_context )
    {
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("/usr/share/icons/oxygen/32x32/actions/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct1 = new QAction(icon1, tr("&Définir comme projet actif"), this);
        newAct1->setStatusTip(tr("Définir comme projet actif"));
        connect(newAct1, SIGNAL(triggered()), this, SLOT(on_set_noeud_courant()));
        menu.addAction(newAct1);
    }

    if ( noeud_context->type() == base_noeud::type_projet || noeud_context->type() == base_noeud::type_parametre )
    {
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("/usr/share/icons/oxygen/32x32/actions/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct2 = new QAction(icon2, tr("&Ajouter une source"), this);
        newAct2->setStatusTip(tr("Ajouter une source"));
        connect(newAct2, SIGNAL(triggered()), this, SLOT(on_ajout_source()));
        menu.addAction(newAct2);

        QIcon icon3;
        icon3.addFile(QString::fromUtf8("/usr/share/icons/oxygen/32x32/actions/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct3 = new QAction(icon3, tr("&Ajouter une fonction"), this);
        newAct3->setStatusTip(tr("Ajouter une fonction"));
        connect(newAct3, SIGNAL(triggered()), this, SLOT(on_ajout_fonction()));
        menu.addAction(newAct3);

        QIcon icon4;
        icon4.addFile(QString::fromUtf8("/usr/share/icons/oxygen/32x32/actions/arrow-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct4 = new QAction(icon4, tr("&Ajouter une sortie"), this);
        newAct4->setStatusTip(tr("Ajouter une source"));
        connect(newAct4, SIGNAL(triggered()), this, SLOT(on_ajout_sortie()));
        menu.addAction(newAct4);
    }
    */

    QPoint pt(pos);
    menu.exec( mapToGlobal(pos) );
}

void explorateur::dragMoveEvent(QDragMoveEvent *e)
{
    QTreeWidgetItem *item = itemAt(e->pos());

    bool accept = false;

    if ( item )
    {
        if ( item != currentItem()->parent()  )
        {
            accept = true;
        }
    }

    if ( accept )
    {
        e->accept();
    }
    else
    {
        e->ignore();
        e->setDropAction(Qt::IgnoreAction);
    }

    QTreeWidget::dragMoveEvent(e);
}

void explorateur::dropEvent(QDropEvent * event)
{
    QTreeWidgetItem * item = itemAt( event->pos() );

    if( item )
    {
        if ( item != currentItem()->parent() )
        {
            QTreeWidgetItem * save_current = currentItem();
            bool save_expanded = save_current->isExpanded();

            QTreeWidget::dropEvent(event);

            ((base_noeud*)save_current)->get_objet()->selectionner();
            save_current->parent()->setExpanded(save_expanded);
            save_current->setExpanded(save_expanded);
            // TODO : event change selection
            // m_fenetre_principale->update_vue_fonction();
        }
        else
        {
            event->ignore();
        }
    }
    else
    {
        event->ignore();
    }
}

void explorateur::on_set_noeud_courant()
{
    m_noeud_context->get_objet()->selectionner();
}

void explorateur::on_ajout_source()
{
    // TODO ?
    // m_fenetre_principale->ajouter_source( m_noeud_context );
}

void explorateur::on_ajout_sortie()
{
    // TODO ?
    // m_fenetre_principale->ajouter_sortie( m_noeud_context );
}

void explorateur::on_ajout_fonction()
{
    // TODO ?
    // m_fenetre_principale->ajouter_conversion( m_noeud_context );
}

