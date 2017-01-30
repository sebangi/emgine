#ifndef FONCTION_SORTIE_TEXTE_WIDGET_H
#define FONCTION_SORTIE_TEXTE_WIDGET_H

#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/element/textes.h"
#include <QListWidgetItem>

class liste_texte_widget;

class fonction_sortie_texte_widget : public base_fonction_widget
{
        Q_OBJECT

    private:
        typedef base_fonction_widget super;

    public:
        fonction_sortie_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private slots:
        void on_externe_fst_textes_modifie();
        void onTexteDoubleClicked(QTableWidgetItem* item);

    private:
        void creer_liste_texte();
        void init();

    private:
        textes & m_textes;
        liste_texte_widget* m_liste_texte;
};

#endif // FONCTION_SORTIE_TEXTE_WIDGET_H
