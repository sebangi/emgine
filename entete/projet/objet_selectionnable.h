#ifndef OBJET_SELECTIONNABLE_H
#define OBJET_SELECTIONNABLE_H

/** \file objet_selectionnable.h
 * \brief Fichier de déclaration de la classe objet_selectionnable.
 * \author Sébastien Angibaud
 */

#include <QObject>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class fonctions_conteneur;
class projet;

/**
 * \class objet_selectionnable
 * \brief Classe décrivant un objet sélectionnable dans l'explorateur.
 * \author Sébastien Angibaud
 */
class objet_selectionnable : public QObject
{
        Q_OBJECT

    public:
        objet_selectionnable(objet_selectionnable* parent = NULL);
        ~objet_selectionnable();

        void selectionner();
        fonctions_conteneur *get_conteneur();
        const fonctions_conteneur *get_conteneur() const;
        fonctions_conteneur *get_conteneur_precedant();
        projet * get_projet();
        bool est_dans_projet() const;
        virtual bool est_conteneur() const;
        virtual bool est_projet() const;
        virtual bool est_fonction() const;
        virtual bool est_parametre() const;

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
        void modifier(bool change_executable = true);
        void sauvegarder( QXmlStreamWriter & stream ) const;
        QString creer_copie() const;

    protected:
        void deselectionner();
        void charger(QXmlStreamReader & xml);

    private:
        static projet * get_projet_courant(objet_selectionnable * obj);

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant qu'un objet est sélectionné.
         * \param obj Un pointeur sur l'objet sélectionné.
         */
        void signal_os_selectionne(objet_selectionnable* obj);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant qu'un objet est désélectionné.
         * \param obj Un pointeur sur l'objet désélectionné.
         */
        void signal_os_deselectionne(objet_selectionnable* obj);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant de la destruction d'un objet.
         * \param obj Un pointeur sur l'objet détruit.
         */
        void signal_os_destruction_selectionnable(objet_selectionnable* obj);

        /** --------------------------------------------------------------------------------------
         * \brief Signal informant que le verrouillage d'un objet est modifié.
         * \param obj Un pointeur sur l'objet modifié.
         */
        void signal_verrouillage_change(objet_selectionnable * obj);

    protected:
        /** \brief L'objet actuellement sélectionné. */
        static objet_selectionnable* s_objet_courant;

        /** \brief Un pointeur sur l'objet parent. */
        objet_selectionnable* m_objet_parent;

        /** \brief Indique si l'objet est actif. */
        bool m_est_active;

        /** \brief Indique si l'objet est étendu, i.e. ses enfants sont visibles. */
        bool m_est_etendu;

        /** \brief Indique si l'objet est verrouillé, i.e. est non modifiable. */
        bool m_verrouille;
};

#endif // OBJET_SELECTIONNABLE_H
