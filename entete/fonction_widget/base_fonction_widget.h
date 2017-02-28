#ifndef BASE_FONCTION_WIDGET_H
#define BASE_FONCTION_WIDGET_H

/** \file base_fonction_widget.h
 * \brief Fichier de déclaration de la classe base_fonction_widget.
 * \author Sébastien Angibaud
 */

#include "entete/define.h"

#include <QFrame>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWidget>

class base_fonction;
class base_parametre;
class base_parametre_widget;
class objet_selectionnable;
class texte;

/**
 * \class base_fonction_widget
 * \brief Classe décrivant un widget de base affichant une fonction.
 * \author Sébastien Angibaud
 */
class base_fonction_widget : public QWidget, public QTableWidgetItem
{
    Q_OBJECT

    private:
        /** \brief Type représentant une liste de widgets affichant chacun un paramètre. */
        typedef QList<base_parametre_widget *> type_liste_parametre_widgets;

    public:
        base_fonction_widget( base_fonction* fonction, QWidget *parent = 0 );
        ~base_fonction_widget();

        void paintEvent(QPaintEvent * e);
        base_fonction *get_fonction();
        void mettre_a_jour_verrouillage();

    private:
        void init();
        void update_actif_bouton();
        void update_close_bouton();
        void update_verrouillage_bouton();
        void update_visibilite_bouton();
        void update_visibilite();
        void update_object_name();
        void aide();
        void connecter_fonction();
        void deconnecter_fonction();

    public:
        virtual void informer_verrouillage_change();

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'un changement de taille du widget.
         */
        void signal_bfw_size_change();

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une demande de création de projet avec un texte source donné.
         * \param t La référence du texte source.
         */
        void signal_bfw_demande_creation_projet(const texte & t);

   private slots:
        void on_inverser_activation();        
        void on_inverser_verrouillage();
        void on_fermer();
        void on_visibilite_change();
        void on_aide();
        void on_externe_activation_fonction_change(base_fonction * f);
        void on_externe_verrouillage_change(objet_selectionnable * obj);
        void on_externe_niveau_visibilite_change(base_fonction * f);

    protected:
        /** \brief Un pointeur sur la fonction à afficher. */
        base_fonction* m_fonction;

        /** \brief Un pointeur sur le widget contenant les widgets des classes filles. */
        QWidget * m_specialisation_widget;

        /** \brief Un pointeur sur le layout contenant les widgets des classes filles. */
        QVBoxLayout * m_specialisation_layout;

    private:        
        /** \brief Un pointeur sur le layout contenant les widgets affichant les paramètres. */
        QVBoxLayout * m_parametre_layout;

        /** \brief Un pointeur sur le widget contenant les widgets affichant les paramètres. */
        QWidget * m_parametre_widget;

        /** \brief Un pointeur sur la frame de séparation situés au dessus du widget affichant les paramètres. */
        QFrame * m_separation1;

        /** \brief Un pointeur sur la framme de séparation située au dessus du widget affichant les widgets des classes filles. */
        QFrame * m_separation2;

        /** \brief Un pointeur sur le bouton de niveau de visibilitité de la fonction. */
        QPushButton *m_visibilite_bouton;

        /** \brief Un pointeur sur le bouton de fermeture. */
        QPushButton *m_fermer_bouton;

        /** \brief Un pointeur sur le bouton d'activation de la fonction. */
        QPushButton *m_actif_bouton;

        /** \brief Un pointeur sur le bouton de verrouillage de la fonction. */
        QPushButton *m_verrouillage_bouton;

        /** \brief Un pointeur sur le bouton d'aide. */
        QPushButton *m_aide_bouton;

        /** \brief La liste des widgets affichant les paramètres. */
        type_liste_parametre_widgets m_parametre_widgets;
};

#endif // BASE_FONCTION_WIDGET_H
