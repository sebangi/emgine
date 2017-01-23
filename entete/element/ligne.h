#ifndef LIGNE_H
#define LIGNE_H

#include "entete/element/mot.h"
#include <vector>

class ligne : public std::vector< mot >
{
    public:
        ligne();
        ligne(const QString &valeur, const QString & separateur_mot = " ");
        QString to_string() const;
        QString to_string_lisible() const;

    private:
        QString m_separateur_mot;
};

#endif // LIGNE_H
