#ifndef SELECTEUR_FONCTION_DIALOG_H
#define SELECTEUR_FONCTION_DIALOG_H

#include "fonction/base_fonction.h"
#include "bouton_choix_fonction.h"
#include "define.h"
#include <QDialog>

class QDialogButtonBox;
class QGridLayout;
class base_fonction;

class selecteur_fonction_dialog : public QDialog
{
        Q_OBJECT

    public:
        explicit selecteur_fonction_dialog(base_fonction::type_fonction type, QWidget *parent = 0);

        base_fonction * get_fonction() const;

    private:
        void init_choix(base_fonction::type_fonction type);
        void ajouter_choix(type_id_fonction nom);

    private slots:
        void choisir();

    private:
        QDialogButtonBox *m_buttonBox;
        QGridLayout *m_grid_layout;
        base_fonction * m_fonction;
};

#endif // SELECTEUR_FONCTION_DIALOG_H
