#ifndef LIGNE_H
#define LIGNE_H

#include "entete/element/mot.h"
#include <vector>

class ligne : public std::vector< mot >
{
    public:
        ligne();
        ligne(const QString &valeur, const QString & separateur_mot = " ");

        void ajouter_mot( const mot & m);
        QString to_string() const;
        QString to_string_lisible() const;

        size_type nb_caracteres() const;
        size_type nb_mots() const;

    private:
        QString m_separateur_mot;

        size_type m_nb_caracteres;
};

#endif // LIGNE_H
