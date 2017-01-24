#ifndef TEXTE_WIDGET_ITEM_H
#define TEXTE_WIDGET_ITEM_H

#include <QListWidgetItem>

class texte;

class texte_widget_item : public  QListWidgetItem
{
    public:
            texte_widget_item(texte& t);
            void update();

            texte & get_texte() const;
            int get_height() const;

    private:
            texte & m_texte;
};

#endif // TEXTE_WIDGET_ITEM_H
