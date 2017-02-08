#ifndef FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
#define FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H

#include "entete/fonction_widget/base_fonction_widget_avec_text_edit.h"

#include <QLabel>
#include <QPushButton>

class fonction_source_fichier_texte_widget : public base_fonction_widget_avec_text_edit
{
        Q_OBJECT

    private:
        typedef base_fonction_widget_avec_text_edit super;

    public:
        fonction_source_fichier_texte_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void on_nouveau_texte();
        QString chercher_valeur() const;
        void informer_verrouillage_change();
        void init();
        void choisir_nom_fichier();
        void charger_fichier();
        void sauvegarder_fichier();
        void update_boutons();

    private slots :
        void on_choisir_click();
        void on_charger_click();
        void on_sauvegarder_click();

    private:
        QLabel * m_nom_fichier_label;
        QPushButton * m_choix_bouton;
        QPushButton * m_charger_bouton;
        QPushButton * m_sauvegarder_bouton;

        bool m_modifie;
        bool m_choisi;
        bool m_charge;
};


#endif // FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
