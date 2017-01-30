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
    m_liste_texte->updateGeometry();

    int save_width = width();
    adjustSize();
    adjustSize();
    setFixedWidth(save_width);
    */

    m_liste_texte->updateGeometry();
    int save_width = width();
    adjustSize();
    setFixedWidth(save_width);

    signal_bfw_size_change();
}

void fonction_sortie_texte_widget::creer_liste_texte()
{
    m_liste_texte->clear();

    for ( textes::iterator it = m_textes.begin(); it != m_textes.end(); ++it )
    {        
        texte_widget_item* item = new texte_widget_item(*it);

        int ligne =  m_liste_texte->rowCount();
        std::cout << ligne << std::endl;
        m_liste_texte->insertRow( ligne );
        m_liste_texte->setItem(ligne, 0, item);

        m_liste_texte->setItem(ligne, 1, new QTableWidgetItem("nb"));
    }

    m_liste_texte->setWordWrap(false);
    m_liste_texte->resizeRowsToContents();
}

void fonction_sortie_texte_widget::init()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new liste_texte_widget();

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QTableWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QTableWidgetItem*)));

    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();
    creer_liste_texte();

    m_specialisation_layout->addLayout(layout);

    connect((fonction_sortie_texte*)m_fonction, SIGNAL(signal_fst_textes_modifie()), this, SLOT(on_externe_fst_textes_modifie()));
}

void fonction_sortie_texte_widget::onTexteDoubleClicked(QTableWidgetItem* item)
{
    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();

    ((texte_widget_item*)item)->update();

    m_liste_texte->resizeRowsToContents();
    m_liste_texte->updateGeometry();
    int save_width = width();
    adjustSize();
    setFixedWidth(save_width);

    signal_bfw_size_change();

    // Attention si on utilise la fonction get_configuration() si la fonction a été détruite depuis
    // std::cout << ((texte_widget_item*)item)->get_texte().get_string_configuration().toStdString() << std::endl;
}

