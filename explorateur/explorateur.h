#ifndef EXPLORATEUR_H
#define EXPLORATEUR_H

#include <QTreeWidget>
#include <explorateur/base_noeud.h>

class fenetre_principale;
class noeud_projet;
class projet;
class base_fonction;
class base_parametre;
class base_noeud;

class explorateur : public QTreeWidget
{
        Q_OBJECT

    public:
        explorateur(fenetre_principale* f, QWidget *parent = 0);

        void set_projet_courant(projet * p);
        void set_parametre_courant(base_parametre * p);

        base_noeud * get_projet_selon_nom_fichier(const QString& nom_fichier);
        void ajouter_noeud_projet(projet* p);
        void ajouter_noeud_fonction(base_noeud *n, base_fonction* f);

        bool set_noeud_courant(base_noeud *noeud_courant);
        base_noeud *get_noeud_courant() const;

        void set_noeud_context(base_noeud *noeud_context);
        base_noeud *get_noeud_context() const;

        noeud_projet * get_noeud_projet(base_noeud * n);
        noeud_projet * get_projet_courant();

    private:
        void ajouter_noeud_parametre(base_noeud *n, base_parametre* f);
        bool chercher_noeud_fonction(base_fonction *f, QTreeWidgetItemIterator& it_rep);

    private:
        void dragMoveEvent(QDragMoveEvent *e);
        void dropEvent(QDropEvent * event);

    signals:
        void noeud_courant_change( base_noeud * );

    private slots:
        void on_externe_supprimer_fonction(base_fonction * f);
        void on_externe_activation_fonction_change(base_fonction * f);

        void on_itemClicked(QTreeWidgetItem *item, int column);
        void on_customContextMenuRequested(const QPoint &pos);
        void on_currentItemChanged(QTreeWidgetItem *item);

        void on_set_noeud_courant();
        void on_ajout_source();
        void on_ajout_sortie();
        void on_ajout_fonction();

    private:
        /** \brief Le noeud courant. */
        base_noeud* m_noeud_courant;

        /** \brief Le noeud du context actuel. */
        base_noeud* m_noeud_context;

        fenetre_principale* m_fenetre_principale;
};

#endif // EXPLORATEUR_H
