#ifndef COMPILATION_WIDGET_H
#define COMPILATION_WIDGET_H

/** \file logs_compilation_widget.h
 * \brief Fichier de déclaration de la classe logs_compilation_widget.
 * \author Sébastien Angibaud
 */

#include <QListWidget>
#include <QPushButton>
#include <QWidget>

class log_compilation;
class objet_selectionnable;

/**
 * \class logs_compilation_widget
 * \brief Classe décrivant le widget affichant l'ensemble des logs.
 * \author Sébastien Angibaud
 */
class logs_compilation_widget : public QWidget
{
    Q_OBJECT

    public:
        logs_compilation_widget( QWidget *parent = 0 );

        void ajouter_log(const log_compilation& log);
        void marquer_comme_ancien();

    private:
        void clear();
        void init_widgets();

    private slots:
        void on_cacher_switch();
        void on_effacer();
        void onLogClicked(QListWidgetItem* item);
        void on_externe_destruction_selectionnable(objet_selectionnable* obj);

    private:
        /** \brief Le bouton pour cacher les logs. */
        QPushButton * m_cacher_bouton;

        /** \brief Le bouton pour effacer les logs. */
        QPushButton * m_effacer_bouton;

        /** \brief Le widget central. */
        QWidget * m_vue_widget;

        /** \brief La liste des widgets internes. */
        QListWidget* m_liste;

        /** \brief La position du dernier message ancien dans la liste. */
        int m_pos_marque_ancien;
};

#endif // COMPILATION_WIDGET_H
