#ifndef TEXTE_WIDGET_ITEM_H
#define TEXTE_WIDGET_ITEM_H

/** \file texte_widget_item.h
 * \brief Fichier de déclaration de la classe texte_widget_item.
 * \author Sébastien Angibaud
 */

#include <QListWidgetItem>

#include "entete/element/texte.h"

class texte;

/**
 * \class texte_widget_item
 * \brief Classe décrivant un item d'un widget de type liste_texte_widget.
 * \author Sébastien Angibaud
 */
class texte_widget_item : public QListWidgetItem
{
   public:
            texte_widget_item(texte& t, int num);
            void update();

            texte & get_texte() const;

            /** --------------------------------------------------------------------------------------
             * \brief Accesseur de la hauteur de l'item.
             * \return La hauteur de l'item.
             */
            inline int get_height() const
            {
                QFontMetrics fm(this->font());
                return m_texte.get_nb_lignes_avec_information() * (fm.lineSpacing() + 3);
            }

    private:
            /** \brief La référence du texte à afficher. */
            texte & m_texte;

            /** \brief La place de l'item dans la liste conteneur. */
            int m_num;
};

#endif // TEXTE_WIDGET_ITEM_H
