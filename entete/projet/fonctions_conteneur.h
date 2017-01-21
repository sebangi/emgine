#ifndef FONCTIONS_CONTENEUR_H
#define FONCTIONS_CONTENEUR_H

#include <QList>
#include "entete/projet/objet_selectionnable.h"
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

class base_fonction;

class fonctions_conteneur : public objet_selectionnable
{
        Q_OBJECT

    public:
        typedef QList<base_fonction *> type_fonctions;
        typedef type_fonctions::iterator fonctions_iterateur;
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

        virtual QString get_titre() const = 0;
        int get_position(base_fonction* f);

        bool est_conteneur() const;
        objet_selectionnable * charger_fonction( QXmlStreamReader & xml, objet_selectionnable * obj_ref );
        void charger_fonctions( QXmlStreamReader & xml, objet_selectionnable * obj_ref );
        void sauvegarder( QXmlStreamWriter & stream ) const;

    protected:
        void clear_fonctions();

    signals:
         void signal_fc_creation_fonction(base_fonction*);

    private slots:
        void on_supprimer_fonction(base_fonction *f);

    protected:
        type_fonctions m_fonctions;
};

#endif // FONCTIONS_CONTENEUR_H
