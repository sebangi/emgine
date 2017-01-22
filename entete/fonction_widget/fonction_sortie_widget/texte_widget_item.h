#ifndef TEXTE_WIDGET_ITEM_H
#define TEXTE_WIDGET_ITEM_H

#include <QListWidgetItem>

class texte;

class texte_widget_item : public  QListWidgetItem
{
    public:
            texte_widget_item(const texte& t);

            const texte& get_texte() const;

    private:
            void init();

    private:
            const texte & m_texte;
};

#endif // TEXTE_WIDGET_ITEM_H
