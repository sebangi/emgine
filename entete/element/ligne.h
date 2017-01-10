#ifndef LIGNE_H
#define LIGNE_H

#include "entete/element/mot.h"
#include <vector>

class ligne : public std::vector< mot >
{
    public:
        ligne();
        ligne(const QString &valeur);
        QString to_string() const;
        QString to_string_lisible() const;
};

#endif // LIGNE_H
