#ifndef OBJET_SELECTIONNABLE_H
#define OBJET_SELECTIONNABLE_H

#include <QObject>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class fonctions_conteneur;
class projet;

class objet_selectionnable : public QObject
{
        Q_OBJECT

    public:
        objet_selectionnable(objet_selectionnable* parent = NULL);
        ~objet_selectionnable();

        void selectionner();
        fonctions_conteneur *get_conteneur();
        projet * get_projet();
        virtual bool est_conteneur() const;
        virtual bool est_projet() const;

        bool est_active() const;
        virtual void set_est_active(bool est_active);
        bool est_active_avec_parent() const;
        bool parents_actifs() const;

        static objet_selectionnable * get_selection();
        static fonctions_conteneur * get_conteneur_courant();
        static projet * get_projet_courant();
        static bool existe_selection();

        bool est_entendu() const;
        void set_est_etendu(bool est_entendu);

    protected:
        void deselectionner();
        void sauvegarder( QXmlStreamWriter & stream ) const;
        void charger(QXmlStreamReader & xml);

    private:
        static projet * get_projet_courant(objet_selectionnable * obj);

    signals:
        void signal_os_selectionne(objet_selectionnable*);
        void signal_os_deselectionne(objet_selectionnable*);
        void signal_os_destruction_selectionnable(objet_selectionnable*);

    protected:
        // L'objet actuellement sélectionné
        static objet_selectionnable* s_objet_courant;

        objet_selectionnable* m_objet_parent;

        bool m_est_active;
        bool m_est_etendu;
};

#endif // OBJET_SELECTIONNABLE_H
