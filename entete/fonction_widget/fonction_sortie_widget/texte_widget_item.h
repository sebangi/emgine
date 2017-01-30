#ifndef TEXTE_WIDGET_ITEM_H
#define TEXTE_WIDGET_ITEM_H

#include <QTableWidgetItem>
#include <QWidget>
#include <QFrame>

#include "entete/element/texte.h"

class texte;

class texte_widget_item : public QWidget, public  QTableWidgetItem
{
        Q_OBJECT

    private:
            texte & m_texte;

    public:
            texte_widget_item(texte& t);
            void update();
            void paintEvent(QPaintEvent *);

            texte & get_texte() const;

            /*
            inline int get_height() const
            {
                QFontMetrics fm(this->font());
                return m_texte.get_nb_lignes_avec_configuration() * (fm.lineSpacing() + 3);
            }
            */
};

#endif // TEXTE_WIDGET_ITEM_H
