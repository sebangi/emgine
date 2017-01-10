#ifndef FONCTION_BASE_SOURCE_H
#define FONCTION_BASE_SOURCE_H

#include "entete/projet/base_fonction.h"

class fonctions_conteneur;

class fonction_base_source : public base_fonction
{
    public:
        fonction_base_source(fonctions_conteneur * conteneur, const QString & nom);
        ~fonction_base_source();        

        virtual QString get_string_valeur() const = 0;
        virtual void set_string_valeur(const QString & valeur) = 0;
};

#endif // FONCTION_BASE_SOURCE_H
