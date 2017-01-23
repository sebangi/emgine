#ifndef FONCTION_SORTIE_TEXTE_WIDGET_H
#define FONCTION_SORTIE_TEXTE_WIDGET_H

#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/element/textes.h"

#include <QPlainTextEdit>
#include <QListWidget>

class fonction_sortie_texte_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_sortie_texte_widget( base_fonction* fonction, QWidget *parent = 0 );
        void set_textes( const textes & textes_in );

    private slots:
        void on_externe_fst_textes_modifie();
        void onTexteDoubleClicked(QListWidgetItem* item);

    private:
        void creer_liste_texte();
        void init();
        void update_label();

    private:
        textes & m_textes;
        QListWidget* m_liste_texte;
};

#endif // FONCTION_SORTIE_TEXTE_WIDGET_H
