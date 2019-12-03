/** \file vue_fonctions.cpp
 * \brief Fichier d'implémentation de la classe vue_fonctions.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/vue_fonctions.h"

#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <QApplication>
#include <QHeaderView>
#include <QScrollBar>
#include <QtGui>

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe vue_fonctions.
 * \param parent Un pointeur sur le widgte parent.
 */
vue_fonctions::vue_fonctions(QWidget *parent)
    : QTableWidget(parent), m_conteneur_courant(NULL), m_bloquer_selection(false)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un projet disponible à la vue.
 * \param p Un pointeur sur le projet à ajouter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Initialise la vue.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une fonction disponible à la vue.
 * \param f Un pointeur sur la fonction à ajouter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un paramètre disponible à la vue.
 * \param p Un pointeur sur le paramètre à ajouter.
 */
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
 * \brief Crée la vue à partir du conteneur courant.
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
            icon1.addFile(QString::fromUtf8(":/icons/fleche_haut.png"), QSize(), QIcon::Normal, QIcon::Off);

        horizontalHeaderItem(1)->setIcon(icon1);
        horizontalHeaderItem(1)->setText( QObject::tr( qUtf8Printable( m_conteneur_courant->get_titre() ) ) );

        for ( fonctions_conteneur::fonctions_iterateur it = m_conteneur_courant->fonctions_begin();
              it != m_conteneur_courant->fonctions_end(); ++it )
            ajouter_vue_fonction( *it );
    }
    else
      horizontalHeaderItem(1)->setIcon(QIcon());
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute la vue d'une fonction donnée.
 * \param f Un pointeur sur la fonction à ajouter.
*/
void vue_fonctions::ajouter_vue_fonction(base_fonction* f)
{
    base_fonction_widget * widget = f->generer_fonction_widget();

    connect( widget, SIGNAL(signal_bfw_size_change()),
             this, SLOT(on_externe_fonction_widget_size_change()));
    connect( widget, SIGNAL(signal_bfw_demande_creation_projet(const texte &)),
                            this, SLOT(on_externe_demande_creation_projet(const texte &)));

    int position = f->get_position();
    insertRow(position);

    setCellWidget(position, 1, (QWidget*)widget);
    setItem(position, 2, new QTableWidgetItem("essai"));

    horizontalHeader()->setStretchLastSection(true);
    verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    QPushButton * image = new QPushButton();
    image->setObjectName("NomParametre");
    QIcon icon1;
    if ( f->get_type() == type_fonction::fonction_source )
        icon1.addFile(QString::fromUtf8(":/icons/selection_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    else if ( f->get_type() == type_fonction::fonction_conversion )
        icon1.addFile(QString::fromUtf8(":/icons/selection_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    else
        icon1.addFile(QString::fromUtf8(":/icons/selection_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);

    image->setIcon(icon1);
    image->setIconSize(QSize(32,32));

    setCellWidget(position, 0, image);
    image->setEnabled(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un objet sélectionnable à la vue.
 * \param obj Un pointeur sur l'objet à ajouter.
 */
void vue_fonctions::ajouter_selectionnable(objet_selectionnable *obj)
{
    m_selectionnables.insert(obj);
    connecter_selectionnable(obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connections pour un objet sélectionnable donné.
 * \param obj Un pointeur sur l'objet à connecter.
 */
void vue_fonctions::connecter_selectionnable( objet_selectionnable *obj )
{
    connect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );

    connect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections pour un objet sélectionnable donné.
 * \param obj Un pointeur sur l'objet à déconnecter.
 */
void vue_fonctions::deconnecter_selectionnable( objet_selectionnable *obj )
{
    disconnect( obj, SIGNAL(signal_os_selectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_selectionne(objet_selectionnable*)) );

    disconnect( obj, SIGNAL(signal_os_deselectionne(objet_selectionnable*)),
                this, SLOT(on_externe_objet_deselectionne(objet_selectionnable*)));
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connections pour un projet donné.
 * \param p Un pointeur sur le projet à connecter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections pour un projet donné.
 * \param p Un pointeur sur le projet à déconnecter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections pour un objet sélectionnable donné.
 * \param obj Un pointeur sur l'objet à connecter.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Ajuste la taille de chaque ligne du widget.
 */
void vue_fonctions::adjust_size_vue_fonction()
{
    for ( int i = 0; i < rowCount(); ++i )
    {
        setRowHeight(i, cellWidget(i,1)->size().height());
    }

    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'une fonction est supprimée.
 * \param f Un pointeur sur la fonction supprimée.
 */
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
            disconnect( widget, SIGNAL(signal_bfw_demande_creation_projet(const texte &)),
                        this, SLOT(on_externe_demande_creation_projet(const texte &)));

            trouve = true;
            m_bloquer_selection = true;
            this->removeRow(i);
            m_bloquer_selection = false;
        }
    }

    deconnecter((objet_selectionnable*)f);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de vérrouillage d'un objet change.
 * \param obj Un pointeur sur l'objet modifié.
 */
void vue_fonctions::on_externe_verrouillage_change(objet_selectionnable *obj)
{
    if( m_conteneur_courant == obj )
        for ( int i = 0; i != rowCount(); ++i )
            ((base_fonction_widget*)cellWidget(i,1))->mettre_a_jour_verrouillage();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque le nom d'un projet change.
 * \param p Un pointeur sur le projet modifié.
 */
void vue_fonctions::on_externe_nom_projet_change(projet *p)
{
    if( m_conteneur_courant == p )
        horizontalHeaderItem(1)->setText( m_conteneur_courant->get_titre() );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un projet est supprimé.
 * \param p Un pointeur sur le projet supprimé.
 */
void vue_fonctions::on_externe_destruction_projet(projet *p)
{
    if( m_conteneur_courant == p )
    {
        horizontalHeaderItem(1)->setText("");
        m_conteneur_courant = NULL;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet sélectionnable est sélectionné.
 * \param obj Un pointeur sur l'objet sélectionné.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet est désélectionné.
 * \param obj Un pointeur sur l'objet désélectionné.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'une fonction est créée.
 * \param f Un pointeur sur la fonction créée.
 */
void vue_fonctions::on_externe_creation_fonction(base_fonction* f)
{
    ajouter_fonction(f);

    if ( f->get_conteneur() == m_conteneur_courant )
        ajouter_vue_fonction(f);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la sélection change.
 * \param last_index L'index de l'ancienne sélection.
 * \param new_index L'index de la nouvelle sélection.
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la taille d'un widget fils change.
 */
void vue_fonctions::on_externe_fonction_widget_size_change()
{
    adjust_size_vue_fonction();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de création de projet.
 * \param t Le texte source du projet à créer.
 */
void vue_fonctions::on_externe_demande_creation_projet(const texte & t)
{
    emit signal_vf_demande_creation_projet(t);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un clic sur l'entête horizontale.
 * \param colonne L'indice de la colonne clické.
 */
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
