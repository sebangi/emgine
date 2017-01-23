#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include <iostream>
#include <QHBoxLayout>

fonction_sortie_texte_widget::fonction_sortie_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_textes( ((fonction_sortie_texte*)fonction)->get_textes())
{
    init();
}

void fonction_sortie_texte_widget::set_textes(const textes &textes_in)
{
    m_textes = textes_in;

    creer_liste_texte();
}

void fonction_sortie_texte_widget::on_externe_fst_textes_modifie()
{
    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();

    creer_liste_texte();
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
    QHBoxLayout* layout = new QHBoxLayout();
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new QListWidget();
    m_liste_texte->setToolTipDuration(500);
    m_liste_texte->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_liste_texte->setObjectName("ListeTexte");
    m_liste_texte->setWrapping(false);
    m_liste_texte->setFixedHeight(400);

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QListWidgetItem*)));

    m_specialisation_layout->addLayout(layout);

    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();
    creer_liste_texte();

    connect((fonction_sortie_texte*)m_fonction, SIGNAL(signal_fst_textes_modifie()), this, SLOT(on_externe_fst_textes_modifie()));
}


void fonction_sortie_texte_widget::onTexteDoubleClicked(QListWidgetItem* item)
{
    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();
    ((texte_widget_item*)item)->update();

    // Attention si on utilise la fonction get_configuration() si celle-ci a été détruite
    // std::cout << ((texte_widget_item*)item)->get_texte().get_string_configuration().toStdString() << std::endl;
}
