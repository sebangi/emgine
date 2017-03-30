/**
 * \file fonction_base_sortie_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_base_sortie_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.h"

#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/fonction/fonction_sortie/fonction_base_sortie.h"
#include "entete/projet/projet.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QStyle>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_base_sortie_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_base_sortie_widget::fonction_base_sortie_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_textes_a_afficher( ((fonction_base_sortie*)fonction)->get_textes_a_afficher())
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la liste de textes à afficher est modifiée.
 */
void fonction_base_sortie_widget::on_externe_fbs_textes_modifie()
{
    m_textes_a_afficher = ((fonction_base_sortie*)m_fonction)->get_textes_a_afficher();

    creer_liste_texte();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Affiche les textes.
 */
void fonction_base_sortie_widget::creer_liste_texte()
{
    m_liste_texte->clear();

    int i = 1;
    for ( textes::iterator it = m_textes_a_afficher.begin(); it != m_textes_a_afficher.end(); ++it )
    {
        texte_widget_item* item = new texte_widget_item(*it, i);
        m_liste_texte->addItem( item );
        ++i;
    }

    init_nom();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void fonction_base_sortie_widget::init()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new liste_texte_widget();

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QListWidgetItem*)));

    m_textes_a_afficher = ((fonction_base_sortie*)m_fonction)->get_textes_a_afficher();
    creer_liste_texte();

    m_specialisation_layout->addLayout(layout);

    connect((fonction_base_sortie*)m_fonction, SIGNAL(signal_fbs_textes_modifie()), this, SLOT(on_externe_fbs_textes_modifie()));
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction retournant le nom de la fonction à afficher.
 */
QString fonction_base_sortie_widget::get_nom() const
{
    if ( m_textes_a_afficher.size() <= 1 )
        return super::get_nom();
    else
        return super::get_nom() + " ( " + QString::number(  m_textes_a_afficher.size() ) + " textes )";
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un clique sur un item.
 * \param item L'item cliqué.
 */
void fonction_base_sortie_widget::onTexteDoubleClicked(QListWidgetItem* item)
{
    // Attention en cas de modificiation de codage de cette fonction :
    // si on utilise la fonction get_configuration() et si la fonction a été détruite depuis

    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();
    ((texte_widget_item*)item)->update();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();

}
