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
        const fonctions_conteneur *get_conteneur() const;
        projet * get_projet();
        bool est_dans_projet() const;
        virtual bool est_conteneur() const;
        virtual bool est_projet() const;
        virtual bool est_fonction() const;

        bool est_active() const;
        virtual void set_est_active(bool active);
        bool est_active_avec_parent() const;
        bool parents_actifs() const;

        bool a_ancetre( objet_selectionnable * obj ) const;

        virtual bool est_verrouille() const;
        virtual void set_verrouille(bool verrouille);
        void inverser_verrouillage();
        bool est_verrouille_avec_parent() const;
        bool parents_verrouilles() const;

        static objet_selectionnable * get_selection();
        static fonctions_conteneur * get_conteneur_courant();
        static projet * get_projet_courant();
        static bool existe_selection();
        static void forcer_deselection();

        bool est_etendu() const;
        virtual void set_est_etendu(bool est_etendu);
        void modifier();
        void sauvegarder( QXmlStreamWriter & stream ) const;

    protected:
        void deselectionner();
        void charger(QXmlStreamReader & xml);

    private:
        static projet * get_projet_courant(objet_selectionnable * obj);

    signals:
        void signal_os_selectionne(objet_selectionnable*);
        void signal_os_deselectionne(objet_selectionnable*);
        void signal_os_destruction_selectionnable(objet_selectionnable*);
        void signal_verrouillage_change(objet_selectionnable * f);

    protected:
        // L'objet actuellement sélectionné
        static objet_selectionnable* s_objet_courant;

        objet_selectionnable* m_objet_parent;

        bool m_est_active;
        bool m_est_etendu;
        bool m_verrouille;
};

#endif // OBJET_SELECTIONNABLE_H
