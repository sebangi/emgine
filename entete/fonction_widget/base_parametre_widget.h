#ifndef BASE_PARAMETRE_WIDGET_H
#define BASE_PARAMETRE_WIDGET_H

#include <QPushButton>
#include <QWidget>
#include <QMouseEvent>

class base_parametre;

class base_parametre_widget : public QWidget
{
    Q_OBJECT

    public:
        base_parametre_widget( base_parametre* param, QWidget *parent = 0 );
        ~base_parametre_widget();
        void paintEvent(QPaintEvent *);

    private:
        void init();
        void mettre_a_jour_configuration();
        void update_object_name();
        void aide();
        QString calcul_valeur_courte() const;

    protected:
        bool event(QEvent* e) override;

    private slots:
        void on_aide();
        void on_inverser_configuration();
        void mouseDoubleClickEvent( QMouseEvent * e );
        void mouseReleaseEvent( QMouseEvent * e );

    private:
        base_parametre* m_parametre;
        QPushButton *m_configuration_bouton;
        QPushButton *m_aide_bouton;
};

#endif // BASE_PARAMETRE_WIDGET_H
