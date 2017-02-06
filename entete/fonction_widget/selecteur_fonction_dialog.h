#ifndef SELECTEUR_FONCTION_DIALOG_H
#define SELECTEUR_FONCTION_DIALOG_H

#include "entete/projet/base_fonction.h"
#include "entete/fonction_widget/bouton_choix_fonction.h"
#include "entete/define.h"
#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

class QDialogButtonBox;
class QGridLayout;
class base_fonction;

class selecteur_fonction_dialog : public QDialog
{
        Q_OBJECT

    public:
        explicit selecteur_fonction_dialog(type_fonction type, QWidget *parent = 0);

        base_fonction * get_fonction() const;

    private:
        void init_choix(type_fonction type);
        void ajouter_choix(type_id_fonction nom);

    private slots:
        void choisir();
        void chercher();
        void chercher(const QString &);
        void calcul_nb_colonnes(type_fonction type);

    private:
        QDialogButtonBox *m_buttonBox;
        QGridLayout *m_grid_layout;
        base_fonction * m_fonction;
        QLineEdit * m_recherche;
        int m_nb_colonnes;

        QList< bouton_choix_fonction * > m_boutons;
};

#endif // SELECTEUR_FONCTION_DIALOG_H
