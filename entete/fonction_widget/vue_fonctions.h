#ifndef VUE_FONCTIONS_H
#define VUE_FONCTIONS_H

/** \file vue_fonctions.h
 * \brief Fichier de déclaration de la classe vue_fonctions.
 * \author Sébastien Angibaud
 */

#include <QTableWidget>

class base_fonction;
class base_parametre;
class fonctions_conteneur;
class objet_selectionnable;
class projet;
class texte;

/**
 * \class vue_fonctions
 * \brief Classe décrivant le widget affichant les fonctions.
 * \author Sébastien Angibaud
 */
class vue_fonctions : public QTableWidget
{
        Q_OBJECT

    private:
        /** \brief Type stockant un ensemble d'objets sélectionnables. */
        typedef QSet< objet_selectionnable* > liste_selectionnable;

    public:
        vue_fonctions(QWidget *parent);

        void ajouter_projet(projet * p);
        void maj_langues();

    private:
        void init();
        void ajouter_fonction(base_fonction *f);
        void ajouter_parametre(base_parametre *f);
        void creer_vue_conteneur();
        void ajouter_vue_fonction(base_fonction* f);
        void ajouter_selectionnable(objet_selectionnable *obj);
        void connecter_selectionnable(objet_selectionnable *obj);
        void deconnecter_selectionnable(objet_selectionnable *obj);
        void connecter_projet(projet *p);
        void deconnecter_projet(projet *p);
        void deconnecter(objet_selectionnable *obj);
        void adjust_size_vue_fonction();

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant d'une demande de création de projet avec un texte source donné.
         * \param t La référence du texte source.
         */
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
        /** \brief La liste des objets sélectionnables. */
        liste_selectionnable m_selectionnables;

        /** \brief Un pointeur sur le conteneur courant. */
        fonctions_conteneur * m_conteneur_courant;

        /** \brief Booléen indiquant que la sélection est bloquée; ceci afin d'éviter un plantage dû à des appels récursifs en boucle. */
        bool m_bloquer_selection;
};

#endif // VUE_FONCTIONS_H
