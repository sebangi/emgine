#ifndef BASE_FONCTION_WIDGET_H
#define BASE_FONCTION_WIDGET_H

#include <QPushButton>
#include <QToolBar>
#include <QFrame>
#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

class base_fonction;
class base_parametre;

class base_fonction_widget : public QWidget, public QTableWidgetItem
{
    Q_OBJECT

    public:
        base_fonction_widget( base_fonction* fonction, QWidget *parent = 0 );
        ~base_fonction_widget();
        void paintEvent(QPaintEvent *);
        base_fonction *get_fonction();

    private:
        void init();
        void update_actif_bouton();
        void update_parametre_bouton();
        void update_object_name();
        void aide();
        void init_connect();

    signals:
        void signal_bfw_size_change();

   private slots:
        void on_inverser_activation();
        void on_fermer();
        void on_parametre_switch();
        void on_aide();

        void on_externe_activation_fonction_change(base_fonction * f);

    protected:
        base_fonction* m_fonction;
        QVBoxLayout * m_parametre_layout;
        QWidget * m_parametre_widget;

    private:
        QFrame * m_separation;        
        QPushButton *m_parametre_bouton;
        QPushButton *m_fermer_bouton;
        QPushButton *m_actif_bouton;
        QPushButton *m_aide_bouton;

        int m_ligne;
};

#endif // BASE_FONCTION_WIDGET_H
