#ifndef FONCTIONS_CONTENEUR_H
#define FONCTIONS_CONTENEUR_H

/** \file fonctions_conteneur.h
 * \brief Fichier de déclaration de la classe fonctions_conteneur.
 * \author Sébastien Angibaud
 */

#include "entete/projet/objet_selectionnable.h"

#include <QList>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class base_fonction;

/**
 * \class fonctions_conteneur
 * \brief Classe décrivant un conteneur de fonctions.
 * \author Sébastien Angibaud
 */
class fonctions_conteneur : public objet_selectionnable
{
        Q_OBJECT

    public:
        /** \brief Type pour stocker une liste de fonctions. */
        typedef QList<base_fonction *> type_fonctions;

        /** \brief Type itérateur sur une liste de fonctions. */
        typedef type_fonctions::iterator fonctions_iterateur;

        /** \brief Type itérateur constant sur une liste de fonctions. */
        typedef type_fonctions::const_iterator fonctions_const_iterateur;

    public:
        fonctions_conteneur(objet_selectionnable * parent);
        ~fonctions_conteneur();

        void ajouter_fonction(base_fonction * f, objet_selectionnable * obj_ref);
        void supprimer_fonction(base_fonction * f);

        fonctions_iterateur fonctions_begin();
        fonctions_iterateur fonctions_end();
        fonctions_const_iterateur fonctions_const_begin() const;
        fonctions_const_iterateur fonctions_const_end() const;

        /** --------------------------------------------------------------------------------------
         * \brief Fonction virtuelle retournant le titre du conteneur.
         * \return Le titre du conteneur au format QString.
         */
        virtual QString get_titre() const = 0;

        int get_position(base_fonction* f);
        bool est_conteneur() const;
        objet_selectionnable * charger_fonction( QXmlStreamReader & xml, objet_selectionnable * obj_ref );
        void charger_fonctions( QXmlStreamReader & xml, objet_selectionnable * obj_ref );
        void sauvegarder( QXmlStreamWriter & stream ) const;

    protected:
        void clear_fonctions();
        int get_nb_fonctions_actives() const;
        const base_fonction * premiere_fonction_active() const;

    signals:
        /** --------------------------------------------------------------------------------------
         * \brief Signal informant de la création d'une fonction.
         * \param f Un pointeur sur la fonction créée.
         */
         void signal_fc_creation_fonction(base_fonction* f);

    private slots:
        void on_supprimer_fonction(base_fonction *f);

    protected:
        /** \brief La liste des fonctions du conteneur. */
        type_fonctions m_fonctions;
};

#endif // FONCTIONS_CONTENEUR_H
