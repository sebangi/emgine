#ifndef PROJET_H
#define PROJET_H

/** \file projet.h
 * \brief Fichier de déclaration de la classe projet.
 * \author Sébastien Angibaud
 */

#include "fonctions_conteneur.h"

#include <QList>
#include <QString>
#include <QXmlStreamWriter>

class base_fonction;
class base_noeud;
class base_parametre;
class logs_compilation_widget;
class noeud_projet;

/**
 * \class projet
 * \brief Classe décrivant un projet.
 * \author Sébastien Angibaud
 */
class projet : public fonctions_conteneur
{
        Q_OBJECT

       public:
        projet();
        ~projet();

        void sauvegarder( QXmlStreamWriter & stream, bool sauvegarde_reelle = true );
        void charger(QXmlStreamReader & xml);
        void executer();
        void fermer();

        QString get_nom() const;
        QString get_titre() const;
        QString get_nom_fichier() const;
        QString get_dossier() const;
        QString get_description() const;

        void set_nom(const QString &nom);
        void set_nom_fichier(const QString &nom_fichier);
        void set_est_modifie(bool est_modifie);
        void set_executable( bool executable );

        bool est_nouveau() const;
        bool est_projet() const;
        bool est_valide(logs_compilation_widget * vue_logs);
        bool est_modifie() const;
        bool est_enregistrable() const;
        bool est_executable() const;
        bool est_verrouille() const;

    signals:
        void signal_p_projet_etat_modification_change( projet *, bool);
        void signal_p_nom_projet_change( projet * );
        void signal_p_projet_executable_change( projet * );
        void signal_p_fermeture_projet( projet * );
        void signal_p_destruction_projet( projet * );

    private:
        void charger_nom(QXmlStreamReader & xml);
        void charger_description(QXmlStreamReader & xml);
        void charger_parametres(QXmlStreamReader & xml, base_fonction* f);
        void charger_parametre(QXmlStreamReader & xml, base_fonction* f);

    private:
        /** \brief Le nom du projet. */
        QString m_nom;

        /** \brief Le nom du fichier du projet. */
        QString m_nom_fichier;

        /** \brief Booléen indiquant si le projet est nouveau, i.e. non enregistré. */
        bool m_nouveau;

        /** \brief Booléen indiquant si le projet a été modifié depuis la dernière sauvegarde. */
        bool m_est_modifie;

        /** \brief Booléen indiquant si le projet est exécutable. */
        bool m_est_executable;

        /** \brief La description du projet. */
        QString m_description;

        /** \brief Booléen indiquant si le projet est verrouillé automatiquement par le système. */
        bool m_verrouille_par_systeme;

        /** \brief Le nombre de projets actuel. */
        static unsigned int s_nb_projets;
}; // end projet

#endif // PROJET_H
