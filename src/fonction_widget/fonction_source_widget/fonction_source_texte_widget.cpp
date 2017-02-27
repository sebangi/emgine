/**
 * \file fonction_source_texte_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_source_widget/fonction_source_texte_widget.h"

#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction_widget/text_edit.h"

#include <QHBoxLayout>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_texte_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_source_texte_widget::fonction_source_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget_avec_text_edit(fonction, parent)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque le texte change.
 */
void fonction_source_texte_widget::on_nouveau_texte()
{
    ((fonction_source_texte*)m_fonction)->set_valeur( get_valeur() );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction retournant la valeur de la fonction associée.
 * \return La valeur de la fonction associée au format QString.
 */
QString fonction_source_texte_widget::chercher_valeur() const
{
    return ((fonction_source_texte*)m_fonction)->get_valeur();
}





