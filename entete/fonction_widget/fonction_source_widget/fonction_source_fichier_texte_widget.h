#ifndef FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
#define FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H

/** \file fonction_source_fichier_texte_widget.h
 * \brief Fichier de déclaration de la classe fonction_source_fichier_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget_avec_text_edit.h"

#include <QLabel>
#include <QPushButton>

/**
 * \class fonction_source_fichier_texte_widget
 * \brief Classe décrivant un widget affichant une fonction de type fonction_source_fichier_texte_widget.
 * \author Sébastien Angibaud
 */
class fonction_source_fichier_texte_widget : public base_fonction_widget_avec_text_edit
{
        Q_OBJECT

    private:
        /** \brief Type de la classe parent. */
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
        /** \brief Un pointeur sur le label affichant le nom du fichier. */
        QLabel * m_nom_fichier_label;

        /** \brief Un pointeur sur le bouton de choix. */
        QPushButton * m_choix_bouton;

        /** \brief Un pointeur sur le bouton de chargement. */
        QPushButton * m_charger_bouton;

        /** \brief Un pointeur sue le bouton de sauvegarde. */
        QPushButton * m_sauvegarder_bouton;

        /** \brief Booléen indiquant si le texte a été modifié. */
        bool m_modifie;

        /** \brief Booléen indiquant si le nom du fichier a été choisi. */
        bool m_choisi;

        /** \brief Booléen indiquant si le fichier a été chargé. */
        bool m_charge;
};


#endif // FONCTION_SOURCE_FICHIER_TEXTE_WIDGET_H
