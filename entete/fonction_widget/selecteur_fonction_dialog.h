#ifndef SELECTEUR_FONCTION_DIALOG_H
#define SELECTEUR_FONCTION_DIALOG_H

/** \file selecteur_fonction_dialog.h
 * \brief Fichier de déclaration de la classe selecteur_fonction_dialog.
 * \author Sébastien Angibaud
 */

#include "entete/define.h"
#include "entete/fonction_widget/bouton_choix_fonction.h"
#include "entete/projet/base_fonction.h"

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class base_fonction;
class QDialogButtonBox;
class QGridLayout;

/**
 * \class selecteur_fonction_dialog
 * \brief Classe décrivant une fenêtre de dialog permettant de sélectionner une fonction, puis de l'instancier.
 * \author Sébastien Angibaud
 */
class selecteur_fonction_dialog : public QDialog
{
        Q_OBJECT

    public:
        explicit selecteur_fonction_dialog(type_fonction type, fonctions_conteneur * conteneur, QWidget *parent = 0);

        base_fonction * get_fonction() const;

    private:
        void init_choix(type_fonction type, fonctions_conteneur * conteneur);
        void ajouter_choix(type_id_fonction id);

    private slots:
        void on_choix();
        void chercher();
        void on_chercher(const QString &);
        void calcul_nb_colonnes(type_fonction type, fonctions_conteneur * conteneur);

    private:
        /** \brief Le bouton d'annulation. */
        QDialogButtonBox *m_cancel_button;

        /** \brief Le layout comprenant l'ensemble des choix. */
        QGridLayout *m_grid_layout;

        /** \brief Un pointeur sur la fonction créée. */
        base_fonction * m_fonction;

        /** \brief Le widget de recherche. */
        QLineEdit * m_recherche;

        /** \brief Le nombre de colonnes de choix. */
        int m_nb_colonnes;

        /** \brief La liste des boutons de choix. */
        QList< bouton_choix_fonction * > m_boutons;
};

#endif // SELECTEUR_FONCTION_DIALOG_H
