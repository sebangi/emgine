/**
 * \file fonction_sortie_frequence_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_frequence_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_frequence_widget.h"

#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/projet/projet.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QStyle>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_frequence_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_sortie_frequence_widget::fonction_sortie_frequence_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_frequences_textes( ((fonction_sortie_frequence*)fonction)->get_frequences_textes())
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la liste de textes à afficher est modifiée.
 */
void fonction_sortie_frequence_widget::on_externe_fbs_textes_modifie()
{
    m_frequences_textes = ((fonction_sortie_frequence*)m_fonction)->get_frequences_textes();

    creer_liste_texte();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Affiche les textes.
 */
void fonction_sortie_frequence_widget::creer_liste_texte()
{
    m_liste_texte->clear();

    int i = 1;
    for ( textes::iterator it = m_frequences_textes.begin(); it != m_frequences_textes.end(); ++it )
    {
        texte_widget_item* item = new texte_widget_item(*it, i);
        m_liste_texte->addItem( item );
        ++i;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void fonction_sortie_frequence_widget::init()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new liste_texte_widget();

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QListWidgetItem*)));

    m_frequences_textes = ((fonction_sortie_frequence*)m_fonction)->get_frequences_textes();
    creer_liste_texte();

    m_specialisation_layout->addLayout(layout);

    connect((fonction_sortie_frequence*)m_fonction, SIGNAL(signal_fbs_textes_modifie()), this, SLOT(on_externe_fbs_textes_modifie()));
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un clique sur un item.
 * \param item L'item cliqué.
 */
void fonction_sortie_frequence_widget::onTexteDoubleClicked(QListWidgetItem* item)
{
    // Attention en cas de modificiation de codage de cette fonction :
    // si on utilise la fonction get_configuration() et si la fonction a été détruite depuis

    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();
    ((texte_widget_item*)item)->update();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();

}
