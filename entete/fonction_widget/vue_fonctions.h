#ifndef VUE_FONCTIONS_H
#define VUE_FONCTIONS_H

#include <QTableWidget>

class base_fonction;
class base_parametre;
class projet;
class objet_selectionnable;
class fonctions_conteneur;
class texte;

class vue_fonctions : public QTableWidget
{
        Q_OBJECT

    private:
        typedef QSet< objet_selectionnable* > liste_selectionnable;

    public:
        vue_fonctions(QWidget *parent);

        void ajouter_projet(projet * p);

    private:
        void init();
        void ajouter_fonction(base_fonction *f);
        void ajouter_parametre(base_parametre *f);
        void creer_vue_conteneur();
        void ajouter_vue_fonction(base_fonction* fonction);
        void ajouter_selectionnable(objet_selectionnable *obj);
        void connecter_selectionnable(objet_selectionnable *obj);
        void deconnecter_selectionnable(objet_selectionnable *obj);
        void connecter_projet(projet *p);
        void deconnecter_projet(projet *p);
        void deconnecter(objet_selectionnable *obj);
        void adjust_size_vue_fonction();

    signals:
        void signal_vf_demande_creation_projet(const texte & t);

    private slots:
        void on_externe_supprimer_fonction(base_fonction *f);
        void on_externe_verrouillage_change(objet_selectionnable *obj);
        void on_externe_nom_projet_change(projet * p);
        void on_externe_destruction_projet(projet * p);
        void on_externe_objet_selectionne(objet_selectionnable*);
        void on_externe_objet_deselectionne(objet_selectionnable*);
        void on_externe_creation_fonction(base_fonction*);
        void on_vue_fonction_selectionChanged(const QItemSelection &last_index, const QItemSelection & new_index);
        void on_externe_fonction_widget_size_change();
        void on_externe_demande_creation_projet(const texte & t);
        void on_hheaderclicked( int colonne );

    private:
        liste_selectionnable m_selectionnables;
        fonctions_conteneur * m_conteneur_courant;
        bool m_bloquer_selection;
};

#endif // VUE_FONCTIONS_H
