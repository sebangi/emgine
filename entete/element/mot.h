#ifndef MOT_H
#define MOT_H

#include "entete/element/base_element.h"

#include <vector>

class mot : public std::vector< base_element >
{
    public:
        mot();
        mot(const QString &valeur);
        QString to_string() const;
};

#endif // MOT_H
