#ifndef FONCTIONS_CONTENEUR_H
#define FONCTIONS_CONTENEUR_H

#include <QList>
#include "entete/projet/objet_selectionnable.h"
#include <QXmlStreamWriter>

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
        void ajouter_fonction(base_fonction * f);
        void supprimer_fonction(base_fonction * f);

        fonctions_iterateur fonctions_begin();
        fonctions_iterateur fonctions_end();
        fonctions_const_iterateur fonctions_const_begin() const;
        fonctions_const_iterateur fonctions_const_end() const;

        virtual QString get_titre() const = 0;

        bool est_conteneur() const;
        void charger_fonction( QXmlStreamReader & xml );

    protected:
        void charger_fonctions( QXmlStreamReader & xml );

    signals:
         void signal_fc_creation_fonction(base_fonction*);

    private slots:
        void on_supprimer_fonction(base_fonction *f);

    protected:
        type_fonctions m_fonctions;
};

#endif // FONCTIONS_CONTENEUR_H
