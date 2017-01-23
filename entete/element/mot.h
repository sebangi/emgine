#ifndef MOT_H
#define MOT_H

#include "entete/element/base_element.h"

#include <vector>

class mot : public std::vector< base_element >
{
    public:
        mot();
        mot(const QString &valeur, const QString & separateur_caractere = "");
        QString to_string() const;
        QString to_string_lisible() const;

    private:
        QString m_separateur_caractere;
};

#endif // MOT_H
