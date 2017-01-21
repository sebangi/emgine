#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/base_noeud.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/projet/projet.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include <QAction>
#include <QMenu>
#include <QKeyEvent>
#include <iostream>
#include <QApplication>
#include <QXmlStreamReader>
#include <QHeaderView>
#include <QMessageBox>

explorateur::explorateur(QWidget *parent)
    : QTreeWidget(parent), m_noeud_context(NULL), m_objet_a_couper(NULL)
{
    setSelectionMode(QAbstractItemView::SingleSelection);
    setAcceptDrops(true);
    setDragEnabled(true);
    setDragDropMode(QAbstractItemView::InternalMove);
    setDropIndicatorShown(true);
    setContextMenuPolicy(Qt::CustomContextMenu);
    setHeaderLabel("Explorateur de projets");
    QFont font = headerItem()->font(0);
    font.setBold(true);
    font.setPointSize(10);
    headerItem()->setFont(0,font);

    setExpandsOnDoubleClick(false);
    setMaximumWidth(400);
    header()->setFixedHeight(25);

    QTreeWidgetItem* rooItem = invisibleRootItem();
    rooItem->setFlags( rooItem->flags() ^ Qt::ItemIsDropEnabled );

    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(on_customContextMenuRequested(const QPoint &)));
    connect(this, SIGNAL(itemClicked(QTreeWidgetItem*, int)),
            this, SLOT(on_itemClicked(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemDoubleClicked(QTreeWidgetItem*, int)),
            this, SLOT(on_itemDoubleClicked(QTreeWidgetItem*, int)));
    connect(this, SIGNAL(itemExpanded(QTreeWidgetItem*)),
            this, SLOT(on_itemExpanded(QTreeWidgetItem*)));
    connect(this, SIGNAL(itemCollapsed(QTreeWidgetItem*)),
            this, SLOT(on_itemCollapsed(QTreeWidgetItem*)));
    connect(this,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),
            this,SLOT(on_currentItemChanged(QTreeWidgetItem*)));
}

explorateur::~explorateur()
{
}

projet * explorateur::get_projet_selon_nom_fichier(const QString &nom_fichier)
{
    projet * p = NULL;

    QTreeWidgetItemIterator it(this);
    while (*it)
    {
        if ( (*it)->type() == base_noeud::type_projet )
        {
            if ( ((noeud_projet*)(*it))->get_projet()->get_nom_fichier() == nom_fichier )
                p = ((noeud_projet*)(*it))->get_projet();
        }

        ++it;
    }

    return p;
}

void explorateur::on_externe_activation_fonction_change(base_fonction * f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
        mettre_a_jour_activation(it->second, ((noeud_fonction*)(it->second))->get_fonction()->est_active(), true );
}

void explorateur::on_externe_etendu_change(base_fonction *f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
        mettre_a_jour_etendu(it->second, ((noeud_fonction*)(it->second))->get_fonction()->est_etendu() );
}

void explorateur::mettre_a_jour_activation( base_noeud* n, bool actif, bool change_expansion )
{
    if ( change_expansion )
    {
        if ( actif )
        {
            if ( ! n->isExpanded() )
                n->setExpanded( n->get_save_expanded() );
        }
        else
        {
            n->save_expanded();
            n->setExpanded(false);
        }
    }

    for ( int i = 0; i != n->childCount(); ++i )
    {
        bool change = true;

        if ( actif )
            if ( n->child(i)->type() == base_noeud::type_fonction )
                if ( ! ((noeud_fonction*)(n->child(i)))->get_fonction()->est_active() )
                    change = false;

        if ( change )
            mettre_a_jour_activation( (base_noeud*)n->child(i), actif, false );
    }

    n->update_style( actif );
}

void explorateur::mettre_a_jour_etendu( base_noeud* n, bool etendu )
{
    if ( n->isExpanded() != etendu )
        n->setExpanded(etendu);
}

void explorateur::creer_copie( const objet_selectionnable* obj, QString & copie )
{
    copie.clear();

    QXmlStreamWriter XmlWriter(&copie);
    XmlWriter.setAutoFormatting(true);
    XmlWriter.writeStartDocument();

    if ( obj->est_conteneur() )
        obj->get_conteneur()->sauvegarder(XmlWriter);
    else
        ((const base_fonction*)obj)->sauvegarder(XmlWriter);

    XmlWriter.writeEndDocument();
}

void explorateur::faire_coller(objet_selectionnable * conteneur, QString & copie, objet_selectionnable * obj_ref)
{
    QXmlStreamReader xmlReader(copie);
    xmlReader.readNextStartElement();

    if ( xmlReader.name() == "fonctions" )
        conteneur->get_conteneur()->charger_fonctions( xmlReader, obj_ref );
    else if ( xmlReader.name() == "fonction" )
        conteneur->get_conteneur()->charger_fonction( xmlReader, obj_ref );
}

void explorateur::faire_couper(objet_selectionnable * obj)
{
    if ( obj->est_conteneur() )
    {
        for ( fonctions_conteneur::fonctions_const_iterateur it = obj->get_conteneur()->fonctions_const_begin();
              it != obj->get_conteneur()->fonctions_const_end(); ++it )
            delete *it;
    }
    else
        delete obj;
}

void explorateur::faire_drop(base_noeud * n_a_couper, base_noeud * n_conteneur, bool shift)
{
    QString copie;
    creer_copie(n_a_couper->get_objet(), copie);
    if ( ! shift )
        faire_couper(n_a_couper->get_objet());
    n_conteneur->get_objet()->selectionner();
    faire_coller(n_conteneur->get_objet(), copie, n_conteneur->get_objet());
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
        emit signal_e_objet_selectionne( obj );
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
        emit signal_e_objet_deselectionne( obj );
    }
}

void explorateur::on_externe_creation_fonction(base_fonction* f)
{
    ajouter_fonction(f);
}

void explorateur::on_externe_nom_projet_change(projet *p)
{
    map_selectionnable::iterator it = m_selectionnables.find(p);

    if ( it != m_selectionnables.end() )
    {
        it->second->setText(0, p->get_nom() );
    }
}

void explorateur::on_externe_destruction_projet(projet *p)
{
    map_selectionnable::iterator it = m_selectionnables.find(p);

    if ( it != m_selectionnables.end() )
    {
        deconnecter_projet(p);
        delete it->second;
        m_selectionnables.erase(it);
    }
}

void explorateur::on_externe_supprimer_fonction(base_fonction *f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
    {
        it->second->parent()->removeChild(it->second);
        m_selectionnables.erase(it);
    }
}

void explorateur::ajouter_projet(projet *p)
{
    if ( p != NULL )
    {
        base_noeud* noeud = new noeud_projet( p );
        ajouter_selectionnable((objet_selectionnable*)p, noeud);
        connecter_projet(p);
        insertTopLevelItem( 0, noeud );

        for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
            ajouter_fonction( *it );

        noeud->setExpanded( p->est_etendu() );
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

        //noeud_parent->addChild(noeud);
        noeud_parent->insertChild(f->get_position(), noeud);

        for ( base_fonction::parametres_iterateur it_p = f->parametres_begin(); it_p != f->parametres_end(); ++it_p )
            ajouter_parametre( it_p->second );

        mettre_a_jour_activation(noeud, f->est_active(), false);
        noeud->setExpanded( f->est_etendu() );

        connecter_fonction(f);
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

        noeud->setExpanded( p->est_etendu() );
    }
}

void explorateur::ajouter_selectionnable(objet_selectionnable *obj, base_noeud *noeud)
{
    m_selectionnables[obj] = noeud;
    connecter_selectionnable(obj);
}

base_noeud *explorateur::get_noeud_context() const
{
    return m_noeud_context;
}

void explorateur::set_noeud_context(base_noeud *noeud_context)
{
    m_noeud_context = noeud_context;
}

void explorateur::on_itemExpanded(QTreeWidgetItem *item)
{
    ((base_noeud*)item)->get_objet()->set_est_etendu( true );
}

void explorateur::on_itemCollapsed(QTreeWidgetItem *item)
{
    ((base_noeud*)item)->get_objet()->set_est_etendu( false );
}

/** --------------------------------------------------------------------------------------
 \brief Evénément click sur un item de l'explorateur de projets.
*/
void explorateur::on_itemClicked(QTreeWidgetItem *item, int column)
{
    ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Evénément double click sur un item de l'explorateur de projets.
*/
void explorateur::on_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    item->setExpanded( ! item->isExpanded() );
    ((base_noeud*)item)->get_objet()->set_est_etendu( item->isExpanded() );
    ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Changement de sélection l'explorateur de projets.
*/
void explorateur::on_currentItemChanged(QTreeWidgetItem *item)
{
    if ( item != NULL )
        ((base_noeud*)item)->get_objet()->selectionner();
}

void explorateur::on_customContextMenuRequested(const QPoint &pos)
{
    QStyle* style = QApplication::style();
    QTreeWidgetItem *node = itemAt( pos );

    set_noeud_context( (base_noeud*)node );
    base_noeud* noeud_context = get_noeud_context();

    QMenu menu(this);

    if ( noeud_context == NULL )
        return;

    if ( noeud_context->get_objet()->est_projet() )
    {
        QAction *newAct_enregistrer = new QAction(style->standardIcon( QStyle::SP_DialogSaveButton ), tr("Enregistrer le projet"), this);
        newAct_enregistrer->setStatusTip(tr("Enregistrer le projet"));
        newAct_enregistrer->setEnabled( noeud_context->get_objet()->get_projet()->est_enregistrable() );
        connect(newAct_enregistrer, SIGNAL(triggered()), this, SLOT(on_enregistrer()));
        menu.addAction(newAct_enregistrer);

        QAction *newAct_enregistrer_sous = new QAction(style->standardIcon( QStyle::SP_DialogSaveButton ), tr("Enregistrer le projet sous"), this);
        newAct_enregistrer_sous->setStatusTip(tr("Enregistrer le projet sous"));
        connect(newAct_enregistrer_sous, SIGNAL(triggered()), this, SLOT(on_enregistrer_sous()));
        menu.addAction(newAct_enregistrer_sous);

        QIcon icon_dupliquer;
        icon_dupliquer.addFile(QString::fromUtf8("icons/coller.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct_dupliquer = new QAction(icon_dupliquer, tr("Dupliquer le projet"), this);
        newAct_dupliquer->setStatusTip(tr("Dupliquer le projet"));
        connect(newAct_dupliquer, SIGNAL(triggered()), this, SLOT(on_dupliquer_projet()));
        menu.addAction(newAct_dupliquer);

        menu.addSeparator();
    }

    if ( noeud_context->get_objet()->est_conteneur() )
    {
        QIcon icon_source;
        icon_source.addFile(QString::fromUtf8("icons/ajout_source.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct2 = new QAction(icon_source, tr("Ajouter une source"), this);
        newAct2->setStatusTip(tr("Ajouter une source"));
        connect(newAct2, SIGNAL(triggered()), this, SLOT(on_ajout_source()));
        menu.addAction(newAct2);

        QIcon icon_conversion;
        icon_conversion.addFile(QString::fromUtf8("icons/ajout_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct3 = new QAction(icon_conversion, tr("Ajouter une conversion"), this);
        newAct3->setStatusTip(tr("Ajouter une conversion"));
        connect(newAct3, SIGNAL(triggered()), this, SLOT(on_ajout_fonction_conversion()));
        menu.addAction(newAct3);

        QIcon icon_sortie;
        icon_sortie.addFile(QString::fromUtf8("icons/ajout_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
        QAction *newAct4 = new QAction(icon_sortie, tr("Ajouter une sortie"), this);
        newAct4->setStatusTip(tr("Ajouter une sortie"));
        connect(newAct4, SIGNAL(triggered()), this, SLOT(on_ajout_sortie()));
        menu.addAction(newAct4);
    }
    else
    {
        QIcon icon_activer;
        QString texte_activer;
        base_fonction* f = (base_fonction*)noeud_context->get_objet();
        if ( f->est_active() )
        {
            icon_activer.addFile(QString::fromUtf8("icons/non_compile.png"), QSize(), QIcon::Normal, QIcon::Off);
            texte_activer = "Désactiver la fonction";
        }
        else
        {
            icon_activer.addFile(QString::fromUtf8("icons/compile.png"), QSize(), QIcon::Normal, QIcon::Off);
            texte_activer = "Activer la fonction";
        }
        QAction *newAct_activer = new QAction(icon_activer, texte_activer, this);
        newAct_activer->setStatusTip(texte_activer);
        connect(newAct_activer, SIGNAL(triggered()), this, SLOT(on_activer_fonction()));
        newAct_activer->setEnabled( f->parents_actifs()  );
        menu.addAction(newAct_activer);
    }

    menu.addSeparator();

    QIcon icon_copier;
    icon_copier.addFile(QString::fromUtf8("icons/copier.png"), QSize(), QIcon::Normal, QIcon::Off);
    QString texte_copier;
    if ( noeud_context->get_objet()->est_conteneur() )
        texte_copier = tr("Copier le contenu");
    else
        texte_copier = tr("Copier la fonction");
    QAction *newAct_copier = new QAction(icon_copier, texte_copier, this);
    newAct_copier->setStatusTip(texte_copier);
    connect(newAct_copier, SIGNAL(triggered()), this, SLOT(on_copier()));
    menu.addAction(newAct_copier);

    QIcon icon_couper;
    icon_couper.addFile(QString::fromUtf8("icons/couper.png"), QSize(), QIcon::Normal, QIcon::Off);
    QString texte_couper;
    if ( noeud_context->get_objet()->est_conteneur() )
        texte_couper = tr("Couper le contenu");
    else
        texte_couper = tr("Couper la fonction");
    QAction *newAct_couper = new QAction(icon_couper, texte_couper, this);
    newAct_couper->setStatusTip(texte_couper);
    connect(newAct_couper, SIGNAL(triggered()), this, SLOT(on_couper()));
    menu.addAction(newAct_couper);

    QIcon icon_coller;
    icon_coller.addFile(QString::fromUtf8("icons/coller.png"), QSize(), QIcon::Normal, QIcon::Off);
    QString texte_coller;
    if ( noeud_context->get_objet()->est_conteneur() )
        texte_coller = tr("Coller au début");
    else
        texte_coller = tr("Coller après");
    QAction *newAct_coller = new QAction(icon_coller, texte_coller, this);
    newAct_coller->setStatusTip(texte_coller);
    if ( m_a_copier == NULL )
        newAct_coller->setEnabled(false);
    else if ( m_objet_a_couper != NULL )
        newAct_coller->setEnabled( ! noeud_context->get_objet()->a_ancetre((objet_selectionnable*)m_objet_a_couper) );
    connect(newAct_coller, SIGNAL(triggered()), this, SLOT(on_coller()));
    menu.addAction(newAct_coller);


    if ( noeud_context->get_objet()->est_projet() )
    {
        menu.addSeparator();

        QAction *newAct_fermer = new QAction(style->standardIcon( QStyle::SP_DialogCloseButton ), tr("Fermer le projet"), this);
        newAct_fermer->setStatusTip(tr("Fermer le projet"));
        connect(newAct_fermer, SIGNAL(triggered()), this, SLOT(on_fermer_projet()));
        menu.addAction(newAct_fermer);
    }

    if ( ! noeud_context->get_objet()->est_conteneur() )
    {
        menu.addSeparator();
        QAction *newAct_supprimer_fonction = new QAction(style->standardIcon( QStyle::SP_DialogCloseButton ), "Supprimer la fonction", this);
        newAct_supprimer_fonction->setStatusTip("Supprimer la fonction");
        connect(newAct_supprimer_fonction, SIGNAL(triggered()), this, SLOT(on_supprimer_fonction()));
        menu.addAction(newAct_supprimer_fonction);
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
        accept = true;
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
        faire_drop((base_noeud *)currentItem(), (base_noeud *)item, event->keyboardModifiers() && Qt::ShiftModifier);
    }
    else
        event->ignore();
}

void explorateur::connecter_selectionnable(objet_selectionnable *obj)
{
    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

void explorateur::deconnecter_selectionnable(objet_selectionnable *obj)
{
    disconnect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    disconnect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

void explorateur::connecter_fonction(base_fonction *f)
{
    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    connect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
             this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

    connect( f, SIGNAL(signal_etendu_change(base_fonction *)),
             this, SLOT(on_externe_etendu_change(base_fonction *)));
}

void explorateur::deconnecter_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    disconnect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

    disconnect( f, SIGNAL(signal_etendu_change(base_fonction *)),
                this, SLOT(on_externe_etendu_change(base_fonction *)));

    deconnecter_selectionnable(f);
}

void explorateur::connecter_projet(projet *p)
{
    connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
             this, SLOT(on_externe_creation_fonction(base_fonction*)));
    connect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
             this, SLOT(on_externe_nom_projet_change(projet *)));
    connect( p, SIGNAL(signal_p_destruction_projet(projet *)),
             this, SLOT(on_externe_destruction_projet(projet *)));
}

void explorateur::deconnecter_projet(projet *p)
{
    disconnect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                this, SLOT(on_externe_creation_fonction(base_fonction*)));
    disconnect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
                this, SLOT(on_externe_nom_projet_change(projet *)));
    disconnect( p, SIGNAL(signal_p_destruction_projet(projet *)),
                this, SLOT(on_externe_destruction_projet(projet *)));

    deconnecter_selectionnable(p);
}

void explorateur::on_ajout_source()
{
    emit signal_e_ajout_source(m_noeud_context->get_fonctions_conteneur(), base_fonction::fonction_source);
}

void explorateur::on_ajout_sortie()
{
    emit signal_e_ajout_source(m_noeud_context->get_fonctions_conteneur(), base_fonction::fonction_sortie);
}

void explorateur::on_ajout_fonction_conversion()
{
    emit signal_e_ajout_source(m_noeud_context->get_fonctions_conteneur(), base_fonction::fonction_conversion);
}

void explorateur::on_activer_fonction()
{
    ((base_fonction*)(m_noeud_context->get_objet()))->inverser_activation();
}

void explorateur::on_enregistrer()
{
    emit signal_e_enregistrer_projet(m_noeud_context->get_objet()->get_projet());
}

void explorateur::on_enregistrer_sous()
{
    emit signal_e_enregistrer_projet_sous(m_noeud_context->get_objet()->get_projet());
}

void explorateur::on_dupliquer_projet()
{
    emit signal_e_dupliquer_projet(m_noeud_context->get_objet()->get_projet());
}

void explorateur::on_copier()
{
    creer_copie( m_noeud_context->get_objet(), m_a_copier );
    m_objet_a_couper = NULL;
}

void explorateur::on_couper()
{
    creer_copie(m_noeud_context->get_objet(), m_a_copier);
    m_objet_a_couper = m_noeud_context->get_objet();
}

void explorateur::on_coller()
{
    if ( m_objet_a_couper != NULL )
    {
        faire_couper(m_objet_a_couper);
        m_objet_a_couper = NULL;
    }

    faire_coller(m_noeud_context->get_objet(), m_a_copier, m_noeud_context->get_objet());
}

void explorateur::on_fermer_projet()
{
    if ( m_noeud_context->type() == base_noeud::type_projet )
        m_noeud_context->get_objet()->get_projet()->fermer();
}


/** --------------------------------------------------------------------------------------
 \brief Le bouton fermer est activé.
*/
void explorateur::on_supprimer_fonction()
{
    if ( ! m_noeud_context->get_objet()->est_conteneur() )
    {
        base_fonction * fonction = (base_fonction*)m_noeud_context->get_objet();

        QMessageBox msgBox;
        msgBox.setWindowTitle("Fonction " + fonction->get_nom());
        msgBox.setText("Voulez-vous vraiment supprimer la fonction " + fonction->get_nom() + " ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes,tr("Oui"));
        msgBox.setButtonText(QMessageBox::Cancel,tr("Non"));
        int ret = msgBox.exec();

        switch (ret)
        {
            case QMessageBox::Yes:
                delete fonction;
                break;
        }
    }
}
