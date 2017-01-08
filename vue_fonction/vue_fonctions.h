#ifndef VUE_FONCTIONS_H
#define VUE_FONCTIONS_H

#include <QTableWidget>

class base_fonction;
class base_noeud;
class base_parametre;

class vue_fonctions : public QTableWidget
{
        Q_OBJECT

    public:
        vue_fonctions(QWidget *parent);

        void ajouter_vue_fonction(base_fonction* fonction);
        void update_vue_fonction(base_noeud* courant);
        void update_selection(base_noeud* courant);

    signals:
        void signal_vf_parametre_selectionne(base_parametre* p);

    private slots:
        void on_externe_supprimer_fonction(base_fonction *f);
        void on_externe_parametre_selectionne(base_parametre* p);
};

#endif // VUE_FONCTIONS_H
