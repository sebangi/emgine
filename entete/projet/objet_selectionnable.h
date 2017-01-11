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
        objet_selectionnable *get_conteneur();
        virtual bool est_conteneur() const;

        static objet_selectionnable * get_selection();
        static fonctions_conteneur * get_conteneur_courant();
        static bool existe_selection();

    private:
        void deselectionner();

    signals:
        void signal_os_selectionne(objet_selectionnable*);
        void signal_os_deselectionne(objet_selectionnable*);

    protected:
        // L'objet actuellement sélectionné
        static objet_selectionnable* s_objet_courant;

        objet_selectionnable* m_objet_parent;
};

#endif // OBJET_SELECTIONNABLE_H
