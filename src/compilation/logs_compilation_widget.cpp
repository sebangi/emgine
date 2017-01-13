#include "entete/compilation/logs_compilation_widget.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/log_widget_item.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/fenetre_principale.h"

#include <QHBoxLayout>
#include <QLabel>
#include <QToolBar>
#include <iostream>
#include <QStyle>
#include <QGroupBox>
#include <QApplication>

logs_compilation_widget::logs_compilation_widget(QWidget *parent)
    : QWidget(parent)
{
    init_widgets();
}

void logs_compilation_widget::ajouter_log(const log_compilation& log)
{
    log_widget_item* item = new log_widget_item(log);

    m_liste->addItem( item );
    m_liste->scrollToBottom();

    if ( item->get_log().get_selectionnable() != NULL )
        connect( item->get_log().get_selectionnable(), SIGNAL(signal_os_destruction_selectionnable(objet_selectionnable*)),
                this, SLOT(on_externe_destruction_selectionnable(objet_selectionnable*)));
}

void logs_compilation_widget::clear()
{
    m_liste->clear();
}

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

void logs_compilation_widget::on_cacher_switch()
{
    setVisible( false );

    QSize save_size = size();
    adjustSize();
    save_size.setHeight( size().height() );

    resize(save_size);
}

void logs_compilation_widget::onLogClicked(QListWidgetItem* item)
{
    objet_selectionnable * obj = ((log_widget_item*)item)->get_log().get_selectionnable() ;
    if ( obj != NULL )
        obj->selectionner();
}

void logs_compilation_widget::on_externe_destruction_selectionnable(objet_selectionnable *obj)
{
    disconnect( obj, SIGNAL(signal_os_destruction_selectionnable(objet_selectionnable*)),
                this, SLOT(on_externe_destruction_selectionnable(objet_selectionnable*)));

    for ( int i = 0; i != m_liste->count(); ++i )
        ((log_widget_item*)m_liste->item(i))->informe_supression_selectionnable(obj);
}
