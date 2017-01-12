#ifndef COMPILATION_WIDGET_H
#define COMPILATION_WIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QListWidget>

class log_compilation;
class projet;
class base_fonction;
class base_parametre;

class logs_compilation_widget : public QWidget
{
    Q_OBJECT

    public:
        logs_compilation_widget( QWidget *parent = 0 );

        void ajouter_log(const log_compilation& log);
        void clear();

    private:
        void init_widgets();
        void update_vue_bouton();

    private slots:
        void on_cacher_switch();
        void onLogClicked(QListWidgetItem* item);

    private:
        QPushButton * m_cacher_bouton;
        QWidget * m_vue_widget;
        QListWidget* m_liste;
};

#endif // COMPILATION_WIDGET_H
