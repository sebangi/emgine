/** \file logs_compilation_widget.cpp
 * \brief Fichier d'implémentation de la class logs_compilation_widget.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/fenetre_principale.h"
#include "entete/projet/objet_selectionnable.h"

#include <iostream>
#include <QApplication>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QToolBar>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe logs_compilation_widget.
 * \param parent Un pointeur sur le widget parent.
 */
logs_compilation_widget::logs_compilation_widget(QWidget *parent)
    : QWidget(parent), m_pos_marque_ancien(0)
{
    init_widgets();
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un log à la liste des logs.
 * \param log Le log à ajouter.
 */
void logs_compilation_widget::ajouter_log(const log_compilation& log)
{
    log_widget_item* item = new log_widget_item(log);

    m_effacer_bouton->setEnabled(true);
    m_liste->addItem( item );
    m_liste->scrollToBottom();

    if ( item->get_log().get_selectionnable() != NULL )
        connect( item->get_log().get_selectionnable(), SIGNAL(signal_os_destruction_selectionnable(objet_selectionnable*)),
                this, SLOT(on_externe_destruction_selectionnable(objet_selectionnable*)));
}

/** --------------------------------------------------------------------------------------
 * \brief Marque tous logs comme étant ancien.
 */
void logs_compilation_widget::marquer_comme_ancien()
{
    for ( int i = m_pos_marque_ancien; i < m_liste->count(); ++i )
    {
         ((log_widget_item*)m_liste->item(i))->marquer_comme_ancien();
    }

    m_pos_marque_ancien = m_liste->count();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void logs_compilation_widget::init_widgets()
{
    setObjectName("logs_compilation_widget");

    QStyle* style = QApplication::style();
    QHBoxLayout * lay = new QHBoxLayout();
    lay->setMargin(0);
    lay->setSpacing(0);

    QGroupBox * groupbox = new QGroupBox;
    groupbox->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    groupbox->setLayout(lay);

    QToolBar * toolbar = new QToolBar();
    toolbar->setOrientation(Qt::Vertical);
    toolbar->setMovable(false);

    m_cacher_bouton = new QPushButton();
    m_cacher_bouton->setObjectName("BoutonFonctionWidget");    
    m_cacher_bouton->setIcon( style->standardIcon( QStyle::SP_DialogCloseButton ) );
    m_cacher_bouton->setIconSize(QSize(24,24));
    m_cacher_bouton->setFixedHeight(32);
    connect(m_cacher_bouton, SIGNAL(released()), this, SLOT(on_cacher_switch()));
    toolbar->addWidget(m_cacher_bouton);

    QIcon icone_effacer;
    icone_effacer.addFile(QString::fromUtf8("icons/balai.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_effacer_bouton = new QPushButton();
    m_effacer_bouton->setObjectName("BoutonFonctionWidget");
    m_effacer_bouton->setIcon( icone_effacer );
    m_effacer_bouton->setIconSize(QSize(24,24));
    m_effacer_bouton->setFixedHeight(32);
    m_effacer_bouton->setEnabled(false);
    connect(m_effacer_bouton, SIGNAL(released()), this, SLOT(on_effacer()));
    toolbar->addWidget(m_effacer_bouton);

    lay->addWidget(toolbar);

    m_vue_widget = new QWidget();
    QHBoxLayout* vue_layout = new QHBoxLayout();
    vue_layout->setMargin(0);
    vue_layout->setSpacing(0);
    m_vue_widget->setLayout(vue_layout);

    m_liste = new QListWidget();
    m_liste->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_liste->setWrapping(false);
    vue_layout->addWidget(m_liste);
    connect( m_liste, SIGNAL(itemClicked(QListWidgetItem*)),
             this, SLOT(onLogClicked(QListWidgetItem*)));

    lay->addWidget(m_vue_widget);

    QVBoxLayout * centralLayout = new QVBoxLayout();
    centralLayout->setMargin(0);
    centralLayout->setSpacing(0);
    centralLayout->addWidget(groupbox);
    setLayout(centralLayout);
    setVisible( false );
}

/** --------------------------------------------------------------------------------------
 * \brief Efface l'ensemble des logs.
 */
void logs_compilation_widget::clear()
{
    m_liste->clear();
    m_pos_marque_ancien = 0;
    m_effacer_bouton->setEnabled(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'effacement des logs.
 */
void logs_compilation_widget::on_effacer()
{
    clear();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée pour demander à cacher des logs.
 */
void logs_compilation_widget::on_cacher_switch()
{
    setVisible( false );

    QSize save_size = size();
    adjustSize();
    save_size.setHeight( size().height() );

    resize(save_size);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un click sur un item de la liste.
 * \param item L'item clické.
 */
void logs_compilation_widget::onLogClicked(QListWidgetItem* item)
{
    objet_selectionnable * obj = ((log_widget_item*)item)->get_log().get_selectionnable() ;
    if ( obj != NULL )
        obj->selectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors de la destruction d'un objet sélectionnable.
 * \param obj Un pointeur sur l'objet détruit.
 */
void logs_compilation_widget::on_externe_destruction_selectionnable(objet_selectionnable *obj)
{
    disconnect( obj, SIGNAL(signal_os_destruction_selectionnable(objet_selectionnable*)),
                this, SLOT(on_externe_destruction_selectionnable(objet_selectionnable*)));

    for ( int i = 0; i != m_liste->count(); ++i )
        ((log_widget_item*)m_liste->item(i))->informe_supression_selectionnable(obj);
}
