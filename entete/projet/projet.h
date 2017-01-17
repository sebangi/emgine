#ifndef PROJET_H
#define PROJET_H

#include "fonctions_conteneur.h"
#include <QString>
#include <QList>
#include <QXmlStreamWriter>

class noeud_projet;
class base_noeud;
class base_fonction;
class base_parametre;
class logs_compilation_widget;

/**
 \brief Classe décrivant un projet.
 \author Sébastien Angibaud
*/
class projet : public fonctions_conteneur
{
        Q_OBJECT

       public:
        projet();
        ~projet();

        void sauvegarder( QXmlStreamWriter & stream );
        void charger(QXmlStreamReader & xml);

        QString get_nom() const;
        QString get_titre() const;
        QString get_nom_fichier() const;
        QString get_description() const;
        bool est_nouveau() const;

        bool est_projet() const;

        void set_nom(const QString &nom);
        void set_nom_fichier(const QString &nom_fichier);

        bool est_valide(logs_compilation_widget * vue_logs);
        bool est_modifie() const;
        void set_est_modifie(bool est_modifie);
        bool enregistrable() const;

    signals:
        void signal_p_projet_etat_modification_change( projet *, bool);
        void signal_p_nom_projet_change( projet * );

    private:
        void charger_nom(QXmlStreamReader & xml);
        void charger_description(QXmlStreamReader & xml);
        void charger_fonctions(QXmlStreamReader & xml);
        void charger_fonction(QXmlStreamReader & xml);
        void charger_parametres(QXmlStreamReader & xml, base_fonction* f);
        void charger_parametre(QXmlStreamReader & xml, base_fonction* f);

    private:
        QString m_nom;
        QString m_nom_fichier;
        bool m_nouveau;
        bool m_est_modifie;
        QString m_description;

        static unsigned int s_nb_projets;
}; // end projet

#endif // PROJET_H
