#ifndef EXPLORATEUR_H
#define EXPLORATEUR_H

#include <QTreeWidget>
#include "entete/explorateur/base_noeud.h"
#include <map>

class fenetre_principale;
class noeud_projet;
class projet;
class base_fonction;
class base_parametre;
class base_noeud;
class objet_selectionnable;

class explorateur : public QTreeWidget
{
        Q_OBJECT

    private:
        typedef std::map< objet_selectionnable*, base_noeud*> map_selectionnable;

    public:
        explorateur(QWidget *parent = 0);

        projet * get_projet_selon_nom_fichier(const QString& nom_fichier);
        void ajouter_projet(projet* p);

    private:
        void ajouter_fonction(base_fonction* f);
        void set_noeud_context(base_noeud *noeud_context);
        base_noeud *get_noeud_context() const;
        void ajouter_parametre(base_parametre* f);
        void ajouter_selectionnable(objet_selectionnable * obj, base_noeud* noeud);
        void mettre_a_jour_activation( base_noeud* n, bool actif, bool change_expansion );

    private:
        void dragMoveEvent(QDragMoveEvent *e);
        void dropEvent(QDropEvent * event);

    private slots:
        void on_externe_supprimer_fonction(base_fonction * f);
        void on_externe_activation_fonction_change(base_fonction * f);
        void on_externe_objet_selectionne(objet_selectionnable* obj);
        void on_externe_objet_deselectionne(objet_selectionnable* obj);
        void on_externe_creation_fonction(base_fonction* f);

        void on_itemExpanded(QTreeWidgetItem *item);
        void on_itemCollapsed(QTreeWidgetItem *item);
        void on_itemClicked(QTreeWidgetItem *item, int column);
        void on_customContextMenuRequested(const QPoint &pos);
        void on_currentItemChanged(QTreeWidgetItem *item);

        void on_ajout_source();
        void on_ajout_sortie();
        void on_ajout_fonction();

    private:
        /** \brief Le noeud du context actuel. */
        base_noeud* m_noeud_context;

        fenetre_principale* m_fenetre_principale;

        /** \brief La map reliant les objet sélectionnable au noeud. */
        map_selectionnable m_selectionnables;
};

#endif // EXPLORATEUR_H
