#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

/** \file fenetre_principale.h
 * \brief Déclaration de la classe fenetre_principale.
 * \author Sébastien Angibaud
 */

#include <QMainWindow>
#include <QPushButton>
#include <QStyle>
#include <QTableWidget>
#include <QTextEdit>
#include <QTreeWidgetItem>
#include <QVBoxLayout>
#include <QXmlStreamReader>

class base_fonction;
class base_noeud;
class compilateur;
class explorateur;
class fonctions_conteneur;
class logs_compilation_widget;
class noeud_projet;
class objet_selectionnable;
class projet;
class texte;
class vue_fonctions;
enum type_fonction;

/*!
 *  \addtogroup Ui
 *  @{
 */
namespace Ui
{
     /** \brief Ajout de la classe fenetre_principale à l'espace de nom Ui. */
     class fenetre_principale;
}
/*! @} End of Doxygen Groups*/

/**
  * \class fenetre_principale
  * \brief Classe représentant la fenètre principale du projet Emgine.
  * \author Sébastien Angibaud
 */
class fenetre_principale : public QMainWindow
{
        Q_OBJECT

    public:
        /** \brief Définition d'un type <b>liste de projets</b>. */
        typedef QList<projet *> type_projets;

        /** \brief Définition d'un type <b>itérateur sur une liste de projets</b>. */
        typedef type_projets::iterator projets_iterateur;

        /** \brief Type d'un type <b>itérateur constant sur une liste de projets</b>. */
        typedef type_projets::const_iterator projets_const_iterateur;

    public:
        explicit fenetre_principale(QWidget *parent = 0);
        ~fenetre_principale();

        void ajouter_source();
        void ajouter_conversion();
        void ajouter_sortie();
        void ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, type_fonction type );
        void ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, base_fonction* f, bool init_defaut );

    private:
        void init_test();
        void init_widgets();
        void creer_toolbar();
        void creer_widgets();

        void ajouter_projet( projet * p );
        bool on_enregistrer_projet( const QString & nom_fichier, projet * p);
        projet * get_projet_selon_nom_fichier(const QString &nom_fichier);
        void ouvrir_projet();
        void creer_projet(QXmlStreamReader & xml, const QString & nom_fichier);
        void creer_projet(const texte & t);
        void executer( projet* p );
        void mettre_a_jour_boutons_projet( projet * p );
        void mettre_a_jour_bouton_execution( projet * p );
        void mettre_a_jour_boutons_fonctions( objet_selectionnable * obj, bool etat );
        void connecter_projet(projet * p);
        void deconnecter_projet(projet * p);
        void deconnecter_projets();
        void deconnecter();

    private slots:
        bool on_enregistrer_projet_sous(projet * p);
        bool on_enregistrer_projet( projet* p );
        void on_ajouter_fonction_source_click();
        void on_ajouter_fonction_conversion_click();
        void on_ajouter_fonction_sortie_click();
        void on_nouveau_projet_click();
        void on_enregistrer_projet_sous_click();
        void on_enregistrer_projet_click();
        void on_ouvrir_projet_click();
        void on_executer_click();

        void on_externe_demande_ajout_fonction(fonctions_conteneur * conteneur, objet_selectionnable* obj_ref, type_fonction type);
        void on_externe_verrouillage_change(objet_selectionnable *obj);
        void on_externe_projet_etat_modification_change(projet * p, bool etat);
        void on_externe_projet_executable_change(projet * p);
        void on_externe_objet_selectionne(objet_selectionnable* obj);
        void on_externe_objet_deselectionne(objet_selectionnable* obj);        
        void on_externe_fermeture_projet(projet * p);
        void on_externe_dupliquer_projet(projet * p);
        void on_externe_demande_creation_projet(const texte & t);

    private:
        /** \brief La table des fonctions. */
        static vue_fonctions * s_vue_fonctions;

        /** \brief L'explorateur de projets. */
        static explorateur * s_explorateur;

        /** \brief Le compilateur. */
        static compilateur * s_compilateur;

        /** \brief La liste des projets ouverts. */
        static type_projets s_projets;

        /** \brief Le widget affichant l'état de la compilation. */
        static logs_compilation_widget * s_vue_logs;

    private:
        /** \brief La référence sur la fenetre elle-même. */
        Ui::fenetre_principale *m_ui;

        /** \brief Le bouton de la barre d'outil pour créer un nouveau projet.*/
        QPushButton *m_toolbar_bouton_nouveau_projet;

        /** \brief Le bouton de la barre d'outil pour ouvrir un projet.*/
        QPushButton *m_toolbar_bouton_ouvrir_projet;

        /** \brief Le bouton de la barre d'outil pour sauvegarder un projet.*/
        QPushButton *m_toolbar_bouton_sauvegarder_projet;

        /** \brief Le bouton de la barre d'outil pour sauvegarder un projet sous.*/
        QPushButton *m_toolbar_bouton_sauvegarder_projet_sous;

        /** \brief Le bouton de la barre d'outil pour ajouter une fonction source.*/
        QPushButton *m_toolbar_bouton_ajout_fonction_source;

        /** \brief Le bouton de la barre d'outil pour ajouter une fonction de conversion.*/
        QPushButton *m_toolbar_bouton_ajout_fonction_conversion;

        /** \brief Le bouton de la barre d'outil pour ajouter une fonction de sortie.*/
        QPushButton *m_toolbar_bouton_ajout_fonction_sortie;

        /** \brief Le bouton de la barre d'outil pour exécuter le projet courant.*/
        QPushButton *m_toolbar_bouton_executer;
};

#endif // FENETRE_PRINCIPALE_H
