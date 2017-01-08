#ifndef TEXTE_H
#define TEXTE_H

#include "element/ligne.h"

#include <vector>

class texte : public std::vector< ligne >
{
    public:
        texte();
        texte(const QString& valeur);

        QString to_string() const;
        QString to_string_lisible() const;
};

#endif // TEXTE_H
