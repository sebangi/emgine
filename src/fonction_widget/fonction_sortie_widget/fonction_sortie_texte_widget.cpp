#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include <iostream>
#include <QHBoxLayout>

fonction_sortie_texte_widget::fonction_sortie_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_textes( ((fonction_sortie_texte*)fonction)->get_textes())
{
    init();
}

void fonction_sortie_texte_widget::on_externe_fst_textes_modifie()
{
    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();

    creer_liste_texte();

    /*
    int save_width = width();
    m_liste_texte->updateGeometry();
    adjustSize();
    adjustSize();
    setFixedWidth(save_width);

    signal_bfw_size_change();
    */

    int old_h = m_liste_texte->height();
    m_liste_texte->resize( m_liste_texte->sizeHint() );
    setFixedHeight( height() - old_h + m_liste_texte->height() );
    signal_bfw_size_change();
}

void fonction_sortie_texte_widget::creer_liste_texte()
{
    m_liste_texte->clear();

    for ( textes::iterator it = m_textes.begin(); it != m_textes.end(); ++it )
    {
        texte_widget_item* item = new texte_widget_item(*it);
        m_liste_texte->addItem( item );
    }
}

void fonction_sortie_texte_widget::init()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new liste_texte_widget();

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QListWidgetItem*)));

    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();
    creer_liste_texte();

    m_specialisation_layout->addLayout(layout);

    connect((fonction_sortie_texte*)m_fonction, SIGNAL(signal_fst_textes_modifie()), this, SLOT(on_externe_fst_textes_modifie()));
}

void fonction_sortie_texte_widget::onTexteDoubleClicked(QListWidgetItem* item)
{
    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();
    ((texte_widget_item*)item)->update();

    int old_h = m_liste_texte->height();
    m_liste_texte->resize( m_liste_texte->sizeHint() );
    setFixedHeight( height() - old_h + m_liste_texte->height());
    signal_bfw_size_change();

    // Attention si on utilise la fonction get_configuration() si celle-ci a été détruite
    // std::cout << ((texte_widget_item*)item)->get_texte().get_string_configuration().toStdString() << std::endl;
}
