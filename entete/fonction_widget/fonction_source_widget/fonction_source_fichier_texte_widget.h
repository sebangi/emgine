#ifndef FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
#define FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QLabel>
#include <QPushButton>

class fonction_source_fichier_texte_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_fichier_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void informer_verrouillage_change();
        void init();
        void choisir_nom_fichier();

    private slots :
        void on_choisir_click();

    protected:
        QLabel * m_nom_fichier_label;
        QPushButton * m_choix_bouton;
};


#endif // FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
