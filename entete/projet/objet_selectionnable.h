#ifndef OBJET_SELECTIONNABLE_H
#define OBJET_SELECTIONNABLE_H

#include <QObject>

class fonctions_conteneur;
class base_noeud;

class objet_selectionnable : public QObject
{
        Q_OBJECT

    public:
        objet_selectionnable(objet_selectionnable* parent = NULL);

        void selectionner();
        static objet_selectionnable * get_selection();
        static fonctions_conteneur * get_conteneur_courant();
        static bool existe_selection();
        void set_noeud(base_noeud *noeud);

    private:
        void deselectionner();

    signals:
        void signal_os_selectionne();
        void signal_os_deselectionne();

    private:
        // L'obejt actuel sélectionné
        static objet_selectionnable* s_objet_courant;

        objet_selectionnable* m_parent;
        base_noeud * m_noeud;
};

#endif // OBJET_SELECTIONNABLE_H
