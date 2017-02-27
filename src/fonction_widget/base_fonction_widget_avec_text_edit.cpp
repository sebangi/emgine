/** \file base_fonction_widget_avec_text_edit.cpp
 * \brief Fichier d'implémentation de la classe base_fonction_widget_avec_text_edit.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget_avec_text_edit.h"

#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction_widget/text_edit.h"

#include <QHBoxLayout>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_fonction_widget_avec_text_edit.
 * \param fonction Un pointeur sur la fonction associée au widget.
 * \param parent Un pointeur sur le widget parent.
 */
base_fonction_widget_avec_text_edit::base_fonction_widget_avec_text_edit(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    // Le init doit être appelé depuis les classes filles
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void base_fonction_widget_avec_text_edit::init()
{
    QVBoxLayout * lay = new QVBoxLayout();
    lay->setSizeConstraint(QLayout::SetFixedSize);
    m_text_edit = new text_edit();
    m_text_edit->setPlainText( chercher_valeur() );
    lay->addWidget(m_text_edit);

    connect(m_text_edit, SIGNAL(textChanged()), this, SLOT(on_textChanged()));
    m_specialisation_layout->addLayout(lay);
    informer_verrouillage_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque le texte change.
 */
void base_fonction_widget_avec_text_edit::on_textChanged()
{
    on_nouveau_texte();

    m_fonction->modifier();
    m_text_edit->updateGeometry();

    signal_bfw_size_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque le verrouillage de la fonction associée est modifié.
 */
void base_fonction_widget_avec_text_edit::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
        m_text_edit->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    else
        m_text_edit->setEnabled( false );
}

