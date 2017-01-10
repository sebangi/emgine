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

/**
 \brief Classe décrivant un projet.
 \author Sébastien Angibaud
*/
class projet : public fonctions_conteneur
{
       public:
        projet();
        ~projet();

        void sauvegarder( QXmlStreamWriter & stream );
        void charger(QXmlStreamReader & xml);

        QString get_nom() const;
        QString get_nom_fichier() const;
        QString get_description() const;
        bool est_nouveau() const;

        void set_nom(const QString &nom);
        void set_nom_fichier(const QString &nom_fichier);

        bool est_valide();

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
        QString m_description;

        static unsigned int s_nb_projets;
}; // end projet

#endif // PROJET_H
