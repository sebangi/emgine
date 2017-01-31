#ifndef LISTE_TEXTE_WIDGET_H
#define LISTE_TEXTE_WIDGET_H

#include <QListWidget>

class liste_texte_widget : public QListWidget
{
    public:
        liste_texte_widget();

        QSize sizeHint() const;
        QSize minimumSizeHint() const;

    private:
        void init();
};

#endif // LISTE_TEXTE_WIDGET_H
