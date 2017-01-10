#ifndef FENETRE_PRINCIPALE_H
#define FENETRE_PRINCIPALE_H

#include <QMainWindow>
#include <QTextEdit>
#include <QTableWidget>
#include <QTreeWidgetItem>
#include <QPushButton>
#include <QVBoxLayout>
#include <QStyle>

#include "entete/fonction_widget/selecteur_fonction_dialog.h"

class explorateur;
class compilateur;
class logs_compilation_widget;
class projet;
class base_noeud;
class noeud_projet;
class base_fonction;
class vue_fonctions;

namespace Ui
{
    class fenetre_principale;
}


/**
 \brief Classe décrivant un texte.
 \author Sébastien Angibaud
*/
class fenetre_principale : public QMainWindow
{
        Q_OBJECT

    public:
        typedef QList<projet *> type_projets;
        typedef type_projets::iterator projets_iterateur;
        typedef type_projets::const_iterator projets_const_iterateur;

    public:
        explicit fenetre_principale(QWidget *parent = 0);
        ~fenetre_principale();

        static void adjust_size_vue_fonction();
        void set_projet_courant( projet * p );

        void ajouter_source( base_noeud * n );
        void ajouter_conversion( base_noeud * n );
        void ajouter_sortie( base_noeud * n );
        void ajouter_fonction( fonctions_conteneur * conteneur, base_fonction::type_fonction type );
        void ajouter_fonction( fonctions_conteneur * conteneur, base_fonction* f, bool init_defaut, bool afficher_vue );
        static void informe_supression_projet(projet * p);
        static void informe_supression_fonction(base_fonction * f);
        static void informe_supression_parametre(base_parametre * p);

    private:
        void init_test();
        void init_widgets();
        void creer_toolbar();
        void creer_widgets();

        void ajouter_vue_fonction(base_fonction* fonction);
        void creer_projet();
        void selectionner_projet();
        void sauvegarder_projet_sous(projet * p);
        void sauvegarder_projet( projet* p );
        void sauvegarder_projet( const QString & nom_fichier, projet * p);
        void ouvrir_projet();
        void ouvrir_projet(projet * p);
        void compiler( projet* p );

    private slots:
        void on_ajouter_fonction_source_click();
        void on_ajouter_fonction_conversion_click();
        void on_ajouter_fonction_sortie_click();
        void on_nouveau_projet_click();
        void on_sauvegarder_projet_sous_click();
        void on_sauvegarder_projet_click();
        void on_ouvrir_projet_click();
        void on_compiler_click();
        void on_vue_fonction_selectionChanged(const QItemSelection &last_index, const QItemSelection & new_index);

        void on_externe_noeud_courant_change( base_noeud * noeud_courant );
        void on_externe_parametre_selectionne(base_parametre* p);

    private:
        /** \brief La table des fonctions. */
        static vue_fonctions * s_vue_fonctions;

        /** \brief L'explorateur de projets. */
        static explorateur * s_explorateur;

        /** \brief Le compilateur. */
        static compilateur * s_compilateur;

        /** \brief La liste des projets ouverts. */
        static type_projets s_projets;

    public:
        /** \brief Le composant de compilation. */
        static logs_compilation_widget * s_vue_logs;

    private:
        /** \brief La référence sur la fenetre elle-meme. */
        Ui::fenetre_principale *m_ui;

        /** \brief Les éléments de la barre de menu.*/
        QPushButton *m_toolbar_bouton_nouveau_projet;
        QPushButton *m_toolbar_bouton_ouvrir_projet;
        QPushButton *m_toolbar_bouton_sauvegarder_projet;
        QPushButton *m_toolbar_bouton_sauvegarder_projet_sous;

        QPushButton *m_toolbar_bouton_ajout_fonction_source;
        QPushButton *m_toolbar_bouton_ajout_fonction_conversion;
        QPushButton *m_toolbar_bouton_ajout_fonction_sortie;

        QPushButton *m_toolbar_bouton_compiler;

        /** \brief Le style de l'application.*/
        QStyle* m_style;
};

#endif // FENETRE_PRINCIPALE_H
