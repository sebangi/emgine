/**
 * \file texte_widget_item.cpp
 * \brief Fichier d'implémentation de la classe texte_widget_item.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe texte_widget_item.
 * \param t La référence du texte à afficher.
 * \param num La place de l'item dans la liste conteneur.
 */
texte_widget_item::texte_widget_item(texte & t, int num)
    : m_texte(t), m_num(num)
{
    update();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le widget.
 */
void texte_widget_item::update()
{
    if ( m_texte.get_configuration_visible() )
        setText( "Texte n°" + QString::number(m_num) + ":\n" +
                 m_texte.get_string_separation() +
                 m_texte.get_string_information_taille() + "\n" + m_texte.get_string_configuration() +
                 m_texte.get_string_separation() + m_texte.to_string_lisible() );
    else
        setText( m_texte.to_string_lisible() );
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du texte affiché.
 * \return La référence du texte affiché.
 */
texte &texte_widget_item::get_texte() const
{
    return m_texte;
}
