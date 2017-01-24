#ifndef TEXTES_H
#define TEXTES_H

#include "entete/element/texte.h"

#include <vector>

class textes : public std::vector< texte >
{
    public:
        textes();
        textes(const QString& valeur);

        QString to_string() const;
        QString to_string_lisible() const;

        void ajouter_texte(const configuration & config, const texte& t);
};

#endif // TEXTES_Hs