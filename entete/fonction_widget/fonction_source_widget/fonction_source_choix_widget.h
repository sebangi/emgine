#ifndef FONCTION_SOURCE_CHOIX_WIDGET_H
#define FONCTION_SOURCE_CHOIX_WIDGET_H

#include "entete/fonction_widget/base_fonction_widget.h"

#include <QListWidget>

class fonction_source_choix_widget : public base_fonction_widget
{
        Q_OBJECT

    public:
        fonction_source_choix_widget( base_fonction* fonction, QWidget *parent = 0 );

    private:
        void init();
        void construire_liste();
        void informer_verrouillage_change();

    private slots :
        void on_itemChanged(QListWidgetItem * item);

    private:
        QListWidget * m_liste;
        bool m_verrou_boucle_signaux;
};

#endif // FONCTION_SOURCE_CHOIX_WIDGET_H
