/** \file explorateur.cpp
 * \brief Fichier d'implémentation de la classe explorateur.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/explorateur.h"

#include "entete/explorateur/base_noeud.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/projet.h"

#include <QAction>
#include <QApplication>
#include <QHeaderView>
#include <QKeyEvent>
#include <QMenu>
#include <QMessageBox>
#include <QXmlStreamReader>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe explorateur.
 * \param parent Un pointeur sur le widget parent.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe explorateur.
 */
explorateur::~explorateur()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un projet dans l'explorateur.
 * \param p Un pointeur sur le projet à ajouter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état d'activation d'une fonction change.
 * \param f Un pointeur sur la fonction dont l'activation vient de changer.
 */
void explorateur::on_externe_activation_fonction_change(base_fonction * f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
        mettre_a_jour_activation(it->second, ((noeud_fonction*)(it->second))->get_fonction()->est_active(), true );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque le vérouillage d'un objet change.
 * \param obj Un pointeur sur l'objet dont le verrouillage vient de changer.
 */
void explorateur::on_externe_verrouillage_change(objet_selectionnable *obj)
{
    map_selectionnable::iterator it = m_selectionnables.find(obj);

    if ( it != m_selectionnables.end() )
        mettre_a_jour_verrouillage(it->second, it->second->get_objet()->est_verrouille() );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état d'expansion d'une fonction change.
 * \param f Un pointeur sur la fonction dont l'expansion vient de changer.
 */
void explorateur::on_externe_etendu_change(base_fonction *f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
        mettre_a_jour_etendu(it->second, ((noeud_fonction*)(it->second))->get_fonction()->est_etendu() );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour l'activation d'un noeud.
 * \param n Un pointeur sur le noeud à mettre à jour.
 * \param actif Booléen indiquant si le noeud est actif.
 * \param change_expansion Booléen indiquant si l'état d'activation vient d'être modifié.
 */
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
            if ( n->child(i)->type() == base_noeud::TYPE_NOEUD_FONCTION )
                if ( ! ((noeud_fonction*)(n->child(i)))->get_fonction()->est_active() )
                    change = false;

        if ( change )
            mettre_a_jour_activation( (base_noeud*)n->child(i), actif, false );
    }

    n->mettre_a_jour_style( actif );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le verouillage d'un noeud.
 * \param n Un pointeur sur le noeud à mettre à jour.
 * \param verrouillage Booléen indiquant si le noeud doit être verrouillé.
 */
void explorateur::mettre_a_jour_verrouillage( base_noeud* n, bool verrouillage )
{
    for ( int i = 0; i != n->childCount(); ++i )
    {
        bool change = true;

        if ( verrouillage )
            if ( n->child(i)->type() == base_noeud::TYPE_NOEUD_FONCTION )
                if ( ((noeud_fonction*)(n->child(i)))->get_fonction()->est_verrouille() )
                    change = false;

        if ( change )
            mettre_a_jour_verrouillage( (base_noeud*)n->child(i), verrouillage );
    }

    n->mise_a_jour_icone();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour l'état d'expansion d'un noeud.
 * \param n Un pointeur sur le noeud à mettre à jour.
 * \param etendu Booléen indiquant si le noeud doit être étendu.
 */
void explorateur::mettre_a_jour_etendu( base_noeud* n, bool etendu )
{
    if ( n->isExpanded() != etendu )
        n->setExpanded(etendu);
}

/** --------------------------------------------------------------------------------------
 * \brief Applique le collage.
 * \param conteneur Un poiinteur sur le conteneur recvant le collage.
 * \param copie L'élément à copier au format QString (xml).
 * \param obj_ref Un pointeur sur l'objet après lequel déposer la copie.
 */
void explorateur::faire_coller(objet_selectionnable * conteneur, QString & copie, objet_selectionnable * obj_ref)
{
    QXmlStreamReader xmlReader(copie);
    xmlReader.readNextStartElement();

    if ( xmlReader.name() == "fonctions" )
        conteneur->get_conteneur()->charger_fonctions( xmlReader, obj_ref );
    else if ( xmlReader.name() == "fonction" )
        conteneur->get_conteneur()->charger_fonction( xmlReader, obj_ref );
}

/** --------------------------------------------------------------------------------------
 * \brief Applique le couper.
 * \param obj Un pointeur sur l'objet à couper.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Controle si le drag and drop est valide.
 * \param n_a_couper Un pointeur sur le noeud à couper.
 * \param n_conteneur Un pointeur sur le conteneur recevant la copie.
 * \param shift Booléen indiquant si la touche \i shift est pressée.
 * \return \b True si le drag and drop est valide, \b False sinon.
 */
bool explorateur::controler_drag_drop(base_noeud * n_a_couper, base_noeud * n_conteneur, bool shift)
{
    bool autorise = true;

    if ( ! shift && n_a_couper->get_objet()->est_verrouille_avec_parent() )
        autorise = false;

    if ( n_conteneur->get_objet()->est_conteneur() && n_conteneur->get_objet()->est_verrouille_avec_parent() )
        autorise = false;

    if ( n_conteneur->get_objet()->est_fonction() && n_conteneur->get_objet()->parents_verrouilles() )
        autorise = false;

    return autorise;
}

/** --------------------------------------------------------------------------------------
 * \brief Applique le drop.
 * \param n_a_couper Un poiteur sur le noeud à couper.
 * \param n_conteneur Un pointeur sur le conteneur recevant la copie.
 * \param shift Booléen indiquant si la touche \i shift est pressée.
 */
void explorateur::faire_drop(base_noeud * n_a_couper, base_noeud * n_conteneur, bool shift)
{
    if ( controler_drag_drop(n_a_couper, n_conteneur, shift) )
    {
        QString copie = n_a_couper->get_objet()->creer_copie();

        if ( ! shift )
            faire_couper(n_a_couper->get_objet());
        n_conteneur->get_objet()->selectionner();
        faire_coller(n_conteneur->get_objet(), copie, n_conteneur->get_objet());
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet est sélectionné.
 * \param obj Un pointeur sur l'objet sélectionné.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet est désélectionné.
 * \param obj Un pointeur sur l'objet désélectionné.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un fonction est créée.
 * \param f Un pointeur sur la fonction créée.
 */
void explorateur::on_externe_creation_fonction(base_fonction* f)
{
    ajouter_fonction(f);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un nom de projet change.
 * \param p Un pointeur sur le projet dont le nom change.
 */
void explorateur::on_externe_nom_projet_change(projet *p)
{
    map_selectionnable::iterator it = m_selectionnables.find(p);

    if ( it != m_selectionnables.end() )
    {
        it->second->setText(0, p->get_nom() );
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un projet est détruit.
 * \param Un pointeur sur le projet détruit.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'une fonction est détruite.
 * \param f Un pointeur sur la fonction détruite.
 */
void explorateur::on_externe_supprimer_fonction(base_fonction *f)
{
    map_selectionnable::iterator it = m_selectionnables.find(f);

    if ( it != m_selectionnables.end() )
    {
        it->second->parent()->removeChild(it->second);
        m_selectionnables.erase(it);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une fonction à l'explorateur.
 * \param Un pointeur sur la fonction à ajouter.
 */
void explorateur::ajouter_fonction(base_fonction* f)
{    
    map_selectionnable::iterator it = m_selectionnables.find(f->get_conteneur());
    if ( it != m_selectionnables.end() )
    {
        base_noeud* noeud_parent = it->second;
        base_noeud* noeud = new noeud_fonction( f );
        ajouter_selectionnable((objet_selectionnable*)f, noeud);

        noeud_parent->insertChild(f->get_position(), noeud);

        for ( base_fonction::parametres_iterateur it_p = f->parametres_begin(); it_p != f->parametres_end(); ++it_p )
            ajouter_parametre( it_p->second );

        mettre_a_jour_activation(noeud, f->est_active(), false);
        noeud->setExpanded( f->est_etendu() );

        connecter_fonction(f);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un paramètre à l'explorateur.
 * \param p Un pointeur sur le paramètre à ajouter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un objet sélectionnable à l'explorateur.
 * \param obj Un pointeur sur l'objet sélectionnable à ajouter.
 * \param noeud Un pointeur sur le noeud associé à l'objet.
 */
void explorateur::ajouter_selectionnable(objet_selectionnable *obj, base_noeud *noeud)
{
    m_selectionnables[obj] = noeud;
    connecter_selectionnable(obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du noeud_context, i.e le noeud pour lequel le menu a été créé (par un click droit).
 * \return Un pointeur sur le noeud_context.
 */
base_noeud *explorateur::get_noeud_context() const
{
    return m_noeud_context;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialiser le noeud_context, i.e le noeud pour lequel le menu a été créé (par un click droit).
 * \param noeud_context Un pointeur sur le nouveau noeud_context.
 */
void explorateur::set_noeud_context(base_noeud *noeud_context)
{
    m_noeud_context = noeud_context;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un noeud de l'explorateur est étendu.
 * \param item Un pointeur sur le noeud étendu.
 */
void explorateur::on_itemExpanded(QTreeWidgetItem *item)
{
    ((base_noeud*)item)->get_objet()->set_est_etendu( true );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un noeud de l'explorateur n'est plus étendu.
 * \param item Un pointeur sur le noeud modifié.
 */
void explorateur::on_itemCollapsed(QTreeWidgetItem *item)
{
    ((base_noeud*)item)->get_objet()->set_est_etendu( false );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un click sur un noeud de l'explorateur.
 * \param item Un pointeur sur le noeud clické.
 * \param column La colonne clickée (Non utilisée, mais nécessaire car méthode virtuelle parente).
 */
void explorateur::on_itemClicked(QTreeWidgetItem *item, int column)
{
    ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un double click sur un noeud de l'explorateur.
 * \param item Un pointeur sur le noeud double clické.
 * \param column La colonne double clickée (Non utilisée, mais nécessaire car méthode virtuelle parente).
 */
void explorateur::on_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    item->setExpanded( ! item->isExpanded() );
    ((base_noeud*)item)->get_objet()->set_est_etendu( item->isExpanded() );
    ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un changement de sélection dans l'explorateur.
 * \param item Un pointeur sur le noeud nouvellement sélectionné.
 */
void explorateur::on_currentItemChanged(QTreeWidgetItem *item)
{
    if ( item != NULL )
        ((base_noeud*)item)->get_objet()->selectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'ouverture de menu.
 * \param pos La position du click.
 */
void explorateur::on_customContextMenuRequested(const QPoint &pos)
{
    QTreeWidgetItem *node = itemAt( pos );

    set_noeud_context( (base_noeud*)node );
    base_noeud* noeud_context = get_noeud_context();

    QMenu menu(this);

    if ( noeud_context == NULL )
        return;

    if ( noeud_context->get_objet()->est_projet() )
        ajouter_menu_projet(menu, noeud_context->get_objet());
    else if ( noeud_context->get_objet()->est_conteneur() )
        ajouter_menu_conteneur(menu, noeud_context->get_objet());
    else
        ajouter_menu_fonction(menu, noeud_context->get_objet());

    QPoint pt(pos);
    menu.exec( mapToGlobal(pos) );
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions d'un projet.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_projet(QMenu & menu, objet_selectionnable * obj )
{
    ajouter_menu_enregistrement(menu, obj);

    menu.addSeparator();

    ajouter_menu_verrouillage(menu, obj);

    menu.addSeparator();

    ajouter_menu_ajout_fonction(menu, obj);

    menu.addSeparator();

    ajouter_menu_copier_coller(menu, obj);

    menu.addSeparator();

    ajouter_menu_supprimer_projet(menu, obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions d'un conteneur.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_conteneur(QMenu & menu, objet_selectionnable * obj )
{
    ajouter_menu_ajout_fonction(menu, obj);

    menu.addSeparator();

    ajouter_menu_copier_coller(menu, obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions d'une fonction.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_fonction(QMenu & menu, objet_selectionnable * obj )
{
    ajouter_menu_activation(menu, obj);
    ajouter_menu_verrouillage(menu, obj);

    menu.addSeparator();

    ajouter_menu_ajout_fonction(menu, obj);

    menu.addSeparator();

    ajouter_menu_copier_coller(menu, obj);

    menu.addSeparator();

    ajouter_menu_supprimer_fonction(menu, obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné l'action de supression d'un projet.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_supprimer_projet(QMenu & menu, objet_selectionnable * obj )
{
    QStyle * style = QApplication::style();

    QAction *newAct_fermer = new QAction(style->standardIcon( QStyle::SP_DialogCloseButton ), tr("Fermer le projet"), this);
    newAct_fermer->setStatusTip(tr("Fermer le projet"));
    connect(newAct_fermer, SIGNAL(triggered()), this, SLOT(on_fermer_projet()));
    menu.addAction(newAct_fermer);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné l'action de suppression d'une fonction.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_supprimer_fonction(QMenu & menu, objet_selectionnable * obj )
{
    QStyle * style = QApplication::style();

    menu.addSeparator();
    QAction *newAct_supprimer_fonction = new QAction(style->standardIcon( QStyle::SP_DialogCloseButton ), "Supprimer la fonction", this);
    newAct_supprimer_fonction->setStatusTip("Supprimer la fonction");
    connect(newAct_supprimer_fonction, SIGNAL(triggered()), this, SLOT(on_supprimer_fonction()));
    menu.addAction(newAct_supprimer_fonction);

    newAct_supprimer_fonction->setEnabled( ! obj->est_verrouille_avec_parent() );
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions d'enregistrement d'un projet.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_enregistrement(QMenu & menu, objet_selectionnable * obj )
{
    QStyle * style = QApplication::style();

    QAction *newAct_enregistrer = new QAction(style->standardIcon( QStyle::SP_DialogSaveButton ), tr("Enregistrer le projet"), this);
    newAct_enregistrer->setStatusTip(tr("Enregistrer le projet"));
    newAct_enregistrer->setEnabled( obj->get_projet()->est_enregistrable() );
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
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions de copier/couper/coller.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_copier_coller(QMenu & menu, objet_selectionnable * obj )
{
    QIcon icon_copier;
    icon_copier.addFile(QString::fromUtf8("icons/copier.png"), QSize(), QIcon::Normal, QIcon::Off);
    QString texte_copier;
    if ( obj->est_conteneur() )
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
    if ( obj->est_conteneur() )
        texte_couper = tr("Couper le contenu");
    else
        texte_couper = tr("Couper la fonction");
    QAction *newAct_couper = new QAction(icon_couper, texte_couper, this);
    newAct_couper->setStatusTip(texte_couper);
    connect(newAct_couper, SIGNAL(triggered()), this, SLOT(on_couper()));
    menu.addAction(newAct_couper);
    newAct_couper->setEnabled( ! obj->est_verrouille_avec_parent() );

    QIcon icon_coller;
    icon_coller.addFile(QString::fromUtf8("icons/coller.png"), QSize(), QIcon::Normal, QIcon::Off);
    QString texte_coller;
    if ( obj->est_conteneur() )
        texte_coller = tr("Coller au début");
    else
        texte_coller = tr("Coller après");
    QAction *newAct_coller = new QAction(icon_coller, texte_coller, this);
    newAct_coller->setStatusTip(texte_coller);
    bool enabled = true;
    if ( m_a_copier == NULL )
        enabled = false;
    else if ( m_objet_a_couper != NULL )
        enabled = ! obj->a_ancetre((objet_selectionnable*)m_objet_a_couper);

    connect(newAct_coller, SIGNAL(triggered()), this, SLOT(on_coller()));
    menu.addAction(newAct_coller);

    if ( obj->est_conteneur() && obj->est_verrouille_avec_parent() )
        enabled = false;

    if ( obj->est_fonction() && obj->parents_verrouilles() )
        enabled = false;
    newAct_coller->setEnabled(enabled);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné les actions d'ajout de fonctions.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_ajout_fonction(QMenu & menu, objet_selectionnable * obj )
{
    bool enabled = true;

    if ( obj->est_conteneur() && obj->est_verrouille_avec_parent() )
        enabled = false;

    if ( obj->est_fonction() && obj->parents_verrouilles() )
        enabled = false;

    QString fin_texte;
    if ( obj->est_fonction() )
        fin_texte = tr(" à la suite");
    else
        fin_texte = tr(" en début de liste");

    QString texte_source = tr("Ajouter une source") + fin_texte;
    QIcon icon_source;
    icon_source.addFile(QString::fromUtf8("icons/ajout_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    QAction *newAct2 = new QAction(icon_source, texte_source, this);
    newAct2->setStatusTip(texte_source);
    connect(newAct2, SIGNAL(triggered()), this, SLOT(on_ajout_source()));
    menu.addAction(newAct2);
    newAct2->setEnabled( enabled );

    QString texte_conversion = tr("Ajouter une conversion") + fin_texte;
    QIcon icon_conversion;
    icon_conversion.addFile(QString::fromUtf8("icons/ajout_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    QAction *newAct3 = new QAction(icon_conversion, texte_conversion, this);
    newAct3->setStatusTip(texte_conversion);
    connect(newAct3, SIGNAL(triggered()), this, SLOT(on_ajout_fonction_conversion()));
    menu.addAction(newAct3);
    newAct3->setEnabled( enabled );

    QString texte_sortie = tr("Ajouter une sortie") + fin_texte;
    QIcon icon_sortie;
    icon_sortie.addFile(QString::fromUtf8("icons/ajout_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
    QAction *newAct4 = new QAction(icon_sortie, texte_sortie, this);
    newAct4->setStatusTip(texte_sortie);
    connect(newAct4, SIGNAL(triggered()), this, SLOT(on_ajout_sortie()));
    menu.addAction(newAct4);
    newAct4->setEnabled( enabled );
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné l'action d'activation.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_activation(QMenu & menu, objet_selectionnable * obj )
{
    QIcon icon_activer;
    QString texte_activer;
    base_fonction* f = (base_fonction*)obj;
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
    newAct_activer->setEnabled( ! obj->est_verrouille_avec_parent() );
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute dans un menu donné l'action de verrouillage.
 * \param menu Le menu à considérer.
 * \param obj Un pointeur sur l'objet contexte du menu.
 */
void explorateur::ajouter_menu_verrouillage(QMenu & menu, objet_selectionnable * obj )
{
    QIcon icon;
    QString texte;

    if ( obj->est_verrouille_avec_parent() )
    {
        icon.addFile(QString::fromUtf8("icons/deverrouille.png"), QSize(), QIcon::Normal, QIcon::Off);
        texte = "Déverrouiller";
    }
    else
    {
        icon.addFile(QString::fromUtf8("icons/verrouille.png"), QSize(), QIcon::Normal, QIcon::Off);
        texte = "Verrouiller";
    }

    if ( obj->est_fonction() )
        texte += " la fonction";
    else
        texte += " le projet";

    QAction *newAct = new QAction(icon, texte, this);
    newAct->setStatusTip(texte);
    connect(newAct, SIGNAL(triggered()), this, SLOT(on_verrouiller_selectionnable()));
    newAct->setEnabled( ! obj->parents_verrouilles() );
    menu.addAction(newAct);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un événement dragMove.
 * \param e Un pointeur sur l'événement.
 */
void explorateur::dragMoveEvent(QDragMoveEvent *e)
{
    QTreeWidgetItem *item = itemAt(e->pos());

    bool accept = false;

    if ( item )
        accept = controler_drag_drop
                ((base_noeud *)currentItem(), (base_noeud *)item, e->keyboardModifiers() && Qt::ShiftModifier);

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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un événement drop.
 * \param e Un pointeur sur l'événement.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connects pour un objet donné.
 * \param obj Un pointeur sur l'objet à connecter.
 */
void explorateur::connecter_selectionnable(objet_selectionnable *obj)
{
    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connects pour un objet donné.
 * \param obj Un pointeur sur l'objet à déconnecter.
 */
void explorateur::deconnecter_selectionnable(objet_selectionnable *obj)
{
    disconnect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );
    disconnect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connects pour un fonction donnée.
 * \param f Un pointeur sur la fonction à connecter.
 */
void explorateur::connecter_fonction(base_fonction *f)
{
    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    connect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
             this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

    connect( f, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
             this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

    connect( f, SIGNAL(signal_etendu_change(base_fonction *)),
             this, SLOT(on_externe_etendu_change(base_fonction *)));
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connects pour un fonction donnée.
 * \param f Un pointeur sur la fonction à déconnecter.
 */
void explorateur::deconnecter_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    disconnect( f, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

    disconnect( f, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
                this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

    disconnect( f, SIGNAL(signal_etendu_change(base_fonction *)),
                this, SLOT(on_externe_etendu_change(base_fonction *)));

    deconnecter_selectionnable(f);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connects pour un projet donné.
 * \param p Un pointeur sur le projet à connecter.
 */
void explorateur::connecter_projet(projet *p)
{
    connect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
             this, SLOT(on_externe_creation_fonction(base_fonction*)));
    connect( p, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
             this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));
    connect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
             this, SLOT(on_externe_nom_projet_change(projet *)));
    connect( p, SIGNAL(signal_p_destruction_projet(projet *)),
             this, SLOT(on_externe_destruction_projet(projet *)));
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connects pour un projet donné.
 * \param p Un pointeur sur le projet à déconnecter.
 */
void explorateur::deconnecter_projet(projet *p)
{
    disconnect( (fonctions_conteneur*)p, SIGNAL(signal_fc_creation_fonction(base_fonction*)),
                this, SLOT(on_externe_creation_fonction(base_fonction*)));
    disconnect( p, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
                this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));
    disconnect( p, SIGNAL(signal_p_nom_projet_change(projet *)),
                this, SLOT(on_externe_nom_projet_change(projet *)));
    disconnect( p, SIGNAL(signal_p_destruction_projet(projet *)),
                this, SLOT(on_externe_destruction_projet(projet *)));

    deconnecter_selectionnable(p);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'ajout de fonction source.
 */
void explorateur::on_ajout_source()
{
    emit signal_e_demande_ajout_fonction(m_noeud_context->get_objet()->get_conteneur(), m_noeud_context->get_objet(), type_fonction::fonction_source);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'ajout de fonction de sortie.
 */
void explorateur::on_ajout_sortie()
{
    emit signal_e_demande_ajout_fonction(m_noeud_context->get_objet()->get_conteneur(), m_noeud_context->get_objet(), type_fonction::fonction_sortie);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'ajout de fonction de conversion.
 */
void explorateur::on_ajout_fonction_conversion()
{
    emit signal_e_demande_ajout_fonction(m_noeud_context->get_objet()->get_conteneur(), m_noeud_context->get_objet(), type_fonction::fonction_conversion);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de changement d'activation d'une fonction.
 */
void explorateur::on_activer_fonction()
{
    ((base_fonction*)(m_noeud_context->get_objet()))->inverser_activation();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de verrouillage d'un objet.
 */
void explorateur::on_verrouiller_selectionnable()
{
    m_noeud_context->get_objet()->inverser_verrouillage();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'enregistrement.
 */
void explorateur::on_enregistrer()
{
    emit signal_e_enregistrer_projet(m_noeud_context->get_objet()->get_projet());
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'enregistrement sous.
 */
void explorateur::on_enregistrer_sous()
{
    emit signal_e_enregistrer_projet_sous(m_noeud_context->get_objet()->get_projet());
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de duplication.
 */
void explorateur::on_dupliquer_projet()
{
    emit signal_e_dupliquer_projet(m_noeud_context->get_objet()->get_projet());
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de copie.
 */
void explorateur::on_copier()
{
    m_a_copier = m_noeud_context->get_objet()->creer_copie();
    m_objet_a_couper = NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de coupé.
 */
void explorateur::on_couper()
{
    m_a_copier = m_noeud_context->get_objet()->creer_copie();
    m_objet_a_couper = m_noeud_context->get_objet();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de collé.
 */
void explorateur::on_coller()
{
    if ( m_objet_a_couper != NULL )
    {
        faire_couper(m_objet_a_couper);
        m_objet_a_couper = NULL;
    }

    faire_coller(m_noeud_context->get_objet(), m_a_copier, m_noeud_context->get_objet());
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de fermeture de projet.
 */
void explorateur::on_fermer_projet()
{
    if ( m_noeud_context->type() == base_noeud::TYPE_NOEUD_PROJET )
        m_noeud_context->get_objet()->get_projet()->fermer();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de suppression de fonction.
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
