#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/base_noeud.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/projet/projet.h"
#include "entete/fenetre_principale.h"
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <iostream>

explorateur::explorateur(fenetre_principale* f, QWidget *parent)
    : QTreeWidget(parent), m_noeud_courant(NULL), m_noeud_context(NULL), m_fenetre_principale(f)
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

void explorateur::set_projet_courant(projet *p)
{
    QTreeWidgetItemIterator it(this);
    bool trouve = false;

    while (*it && ! trouve )
    {
        if ( (*it)->type() == base_noeud::type_projet )
        {
            if ( ((noeud_projet*)(*it))->get_projet() == p )
            {
                trouve = true;
                set_noeud_courant((noeud_projet*)*it);
            }
        }

        ++it;
    }
}

void explorateur::set_parametre_courant(base_parametre *p)
{
    QTreeWidgetItemIterator it(this);
    bool trouve = false;

    while (*it && ! trouve )
    {
        if ( (*it)->type() == base_noeud::type_parametre )
        {
            if ( ((noeud_parametre*)(*it))->get_parametre() == p )
            {
                trouve = true;
                set_noeud_courant((noeud_parametre*)*it);
            }
        }

        ++it;
    }
}

base_noeud * explorateur::get_noeud_courant() const
{
    return m_noeud_courant;
}

noeud_projet *explorateur::get_noeud_projet(base_noeud * n)
{
    if ( n == NULL )
        return NULL;
    else if ( n->type() == base_noeud::type_projet )
        return (noeud_projet *)n;
    else
        return get_noeud_projet( (base_noeud*)n->parent() );
}


noeud_projet *explorateur::get_projet_courant()
{
    return get_noeud_projet( m_noeud_courant );
}

bool explorateur::chercher_noeud_fonction(base_fonction *f, QTreeWidgetItemIterator& it_rep)
{
    QTreeWidgetItemIterator it = QTreeWidgetItemIterator(this);
    bool trouve = false;

    while (*it && ! trouve )
    {
        if ( (*it)->type() == base_noeud::type_fonction )
        {
            if ( ((noeud_fonction*)(*it))->get_fonction() == f )
            {
                it_rep = it;
                trouve = true;
            }
        }
        ++it;
    }

    return trouve;
}

void explorateur::on_externe_activation_fonction_change(base_fonction * f)
{
    QTreeWidgetItemIterator it(this);

    if ( chercher_noeud_fonction( f, it ) )
        ((noeud_fonction*)(*it))->update_style();
}

void explorateur::on_externe_supprimer_fonction(base_fonction *f)
{
    QTreeWidgetItemIterator it(this);

    if ( chercher_noeud_fonction( f, it ) )
        (*it)->parent()->removeChild(*it);
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

void explorateur::ajouter_noeud_projet(projet *p)
{
    if ( p != NULL )
    {
        base_noeud* noeud = new noeud_projet( p );

        insertTopLevelItem( 0, noeud );

        for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
            ajouter_noeud_fonction( noeud, *it );

        expandItem(noeud);
    }
}

void explorateur::ajouter_noeud_fonction(base_noeud *n, base_fonction* f)
{
    base_noeud* noeud = new noeud_fonction( f );

    n->addChild(noeud);

    for ( base_fonction::parametres_iterateur it = f->parametres_begin(); it != f->parametres_end(); ++it )
        ajouter_noeud_parametre( noeud, it->second );

    expandItem(noeud);

    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    connect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
             this, SLOT(on_externe_activation_fonction_change(base_fonction *)));
}

void explorateur::ajouter_noeud_parametre(base_noeud *n, base_parametre* p)
{
    base_noeud* noeud = new noeud_parametre( p );

    n->addChild(noeud);

    for ( base_parametre::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        ajouter_noeud_fonction( noeud, *it );

    expandItem(noeud);
}

base_noeud *explorateur::get_noeud_context() const
{
    return m_noeud_context;
}

void explorateur::set_noeud_context(base_noeud *noeud_context)
{
    m_noeud_context = noeud_context;
}

bool explorateur::set_noeud_courant(base_noeud *noeud_courant)
{
    if ( noeud_courant == NULL )
        return false;

    if ( noeud_courant->type() == base_noeud::type_fonction )
    {
        bool result = set_noeud_courant((base_noeud*)noeud_courant->parent());
        clearSelection();
        setItemSelected((QTreeWidgetItem*)noeud_courant, true);
        return result;
    }

    if ( noeud_courant == m_noeud_courant )
        return false;

    if ( m_noeud_courant != NULL )
    {
        QFont font = m_noeud_courant->font(0);
        font.setBold(false);
        m_noeud_courant->setFont(0, font);
    }

    m_noeud_courant = noeud_courant;
    emit noeud_courant_change( m_noeud_courant );

    QFont font = m_noeud_courant->font(0);
    font.setBold(true);
    m_noeud_courant->setFont(0, font);

    clearSelection();
    setItemSelected((QTreeWidgetItem*)m_noeud_courant, true);

    return true;
}

/** --------------------------------------------------------------------------------------
 \brief Evénément click sur un item de l'explorateur de projets.
*/
void explorateur::on_itemClicked(QTreeWidgetItem *item, int column)
{
    set_noeud_courant((base_noeud*)item);
    // TODO : event change selection
    // m_fenetre_principale->update_selection();
}

/** --------------------------------------------------------------------------------------
 \brief Changement de sélection l'explorateur de projets.
*/
void explorateur::on_currentItemChanged(QTreeWidgetItem *item)
{
    set_noeud_courant((base_noeud*)item);
    // TODO : event change selection
    // m_fenetre_principale->update_selection();
}

void explorateur::on_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *node = itemAt( pos );

    set_noeud_context( (base_noeud*)node );
    base_noeud* noeud_context = get_noeud_context();

    QMenu menu(this);

    if ( noeud_context == NULL )
        return;

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

            m_fenetre_principale->set_noeud_courant((base_noeud*)save_current);
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
    set_noeud_courant( m_noeud_context );
}

void explorateur::on_ajout_source()
{
    m_fenetre_principale->ajouter_source( m_noeud_context );
}

void explorateur::on_ajout_sortie()
{
    m_fenetre_principale->ajouter_sortie( m_noeud_context );
}

void explorateur::on_ajout_fonction()
{
    m_fenetre_principale->ajouter_conversion( m_noeud_context );
}

