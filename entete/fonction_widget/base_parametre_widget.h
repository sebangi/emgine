#ifndef BASE_PARAMETRE_WIDGET_H
#define BASE_PARAMETRE_WIDGET_H

/** \file base_parametre_widget.h
 * \brief Fichier de déclaration de la classe base_parametre_widget.
 * \author Sébastien Angibaud
 */

#include <QLabel>
#include <QMouseEvent>
#include <QPushButton>
#include <QWidget>

class base_parametre;

/**
 * \class base_parametre_widget
 * \brief Classe décrivant un widget de base affichant un paramètre.
 * \author Sébastien Angibaud
 */
class base_parametre_widget : public QWidget
{
    Q_OBJECT

    public:
        base_parametre_widget( base_parametre* param, QWidget *parent = 0 );
        ~base_parametre_widget();

        void paintEvent(QPaintEvent *);
        void informer_verrouillage_change();
        void maj_langues();

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
        /** \brief Un pointeur sur le paramètre à afficher. */
        base_parametre* m_parametre;

        /** \brief Un pointeur sur le bouton gérant la configuration du paramètre. */
        QPushButton *m_configuration_bouton;

        /** \brief Un pointeur sur le bouton d'aide du paramètre. */
        QPushButton *m_aide_bouton;

        /** \brief Un pointeur sur le label du nom du paramètre. */
        QLabel * m_nom_label;

        /** \brief Un pointeur sur le label de la valeur du paramètre. */
        QLabel * m_valeur_label;
};

#endif // BASE_PARAMETRE_WIDGET_H
