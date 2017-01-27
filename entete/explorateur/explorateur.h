#ifndef EXPLORATEUR_H
#define EXPLORATEUR_H

#include <QTreeWidget>
#include "entete/explorateur/base_noeud.h"
#include <map>
#include "entete/projet/base_fonction.h"

class fenetre_principale;
class noeud_projet;
class projet;
class base_parametre;
class base_fonction;
class base_noeud;
class objet_selectionnable;

class explorateur : public QTreeWidget
{
        Q_OBJECT

    private:
        typedef std::map< objet_selectionnable*, base_noeud*> map_selectionnable;

    public:
        explorateur(QWidget *parent = 0);
        ~explorateur();

        projet * get_projet_selon_nom_fichier(const QString& nom_fichier);
        void ajouter_projet(projet* p);

    private:
        void ajouter_fonction(base_fonction* f);
        void set_noeud_context(base_noeud *noeud_context);
        base_noeud *get_noeud_context() const;
        void ajouter_parametre(base_parametre* p);
        void ajouter_selectionnable(objet_selectionnable * obj, base_noeud* noeud);
        void mettre_a_jour_activation( base_noeud* n, bool actif, bool change_expansion );
        void mettre_a_jour_verrouillage( base_noeud* n, bool verrouillage );
        void mettre_a_jour_etendu( base_noeud* n, bool etendu );
        void creer_copie( const objet_selectionnable* obj, QString & copie );
        void faire_coller( objet_selectionnable* conteneur, QString & copie, objet_selectionnable * obj_ref );
        void faire_couper( objet_selectionnable* obj );
        void faire_drop(base_noeud * n_a_couper, base_noeud * n_conteneur, bool shift);
        void dragMoveEvent(QDragMoveEvent *e);
        void dropEvent(QDropEvent * event);
        void connecter_selectionnable(objet_selectionnable * f);
        void deconnecter_selectionnable(objet_selectionnable * f);
        void connecter_fonction(base_fonction * f);
        void deconnecter_fonction(base_fonction * f);
        void connecter_projet(projet * p);
        void deconnecter_projet(projet * p);

        void ajouter_menu_projet(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_conteneur(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_fonction(QMenu & menu, objet_selectionnable * obj );

        void ajouter_menu_supprimer_projet(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_supprimer_fonction(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_ajout_fonction(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_enregistrement(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_copier_coller(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_activation(QMenu & menu, objet_selectionnable * obj );
        void ajouter_menu_verrouillage(QMenu & menu, objet_selectionnable * obj );

    signals:
        void signal_e_ajout_source(fonctions_conteneur *, base_fonction::type_fonction);
        void signal_e_objet_selectionne(objet_selectionnable*);
        void signal_e_objet_deselectionne(objet_selectionnable*);
        void signal_e_enregistrer_projet(projet *);
        void signal_e_enregistrer_projet_sous(projet *);
        void signal_e_dupliquer_projet(projet *);

    private slots:
        void on_externe_supprimer_fonction(base_fonction * f);
        void on_externe_activation_fonction_change(base_fonction * f);
        void on_externe_verrouillage_change(objet_selectionnable * obj);
        void on_externe_etendu_change(base_fonction * f);
        void on_externe_objet_selectionne(objet_selectionnable* obj);
        void on_externe_objet_deselectionne(objet_selectionnable* obj);
        void on_externe_creation_fonction(base_fonction* f);
        void on_externe_nom_projet_change(projet * p);
        void on_externe_destruction_projet(projet * p);

        void on_itemExpanded(QTreeWidgetItem *item);
        void on_itemCollapsed(QTreeWidgetItem *item);
        void on_itemClicked(QTreeWidgetItem *item, int column);
        void on_itemDoubleClicked(QTreeWidgetItem *item, int column);
        void on_customContextMenuRequested(const QPoint &pos);
        void on_currentItemChanged(QTreeWidgetItem *item);

        void on_ajout_source();
        void on_ajout_sortie();
        void on_ajout_fonction_conversion();
        void on_activer_fonction();
        void on_verrouiller_selectionnable();
        void on_enregistrer();
        void on_enregistrer_sous();
        void on_copier();
        void on_couper();
        void on_coller();
        void on_fermer_projet();
        void on_dupliquer_projet();
        void on_supprimer_fonction();

    private:
        /** \brief Le noeud du context actuel. */
        base_noeud* m_noeud_context;

        /** \brief Le fonction à copier sous forme de chaine (en XML ). */
        QString m_a_copier;

        /** \brief Le noeud à couper. */
        objet_selectionnable* m_objet_a_couper;

        fenetre_principale* m_fenetre_principale;

        /** \brief La map reliant les objet sélectionnable au noeud. */
        map_selectionnable m_selectionnables;
};

#endif // EXPLORATEUR_H
