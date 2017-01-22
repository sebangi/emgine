#ifndef TEXTE_H
#define TEXTE_H

#include "entete/element/ligne.h"
#include "entete/compilation/configuration.h"

#include <vector>

class texte : public std::vector< ligne >
{
    public:
        texte();
        texte(const QString& valeur);

        QString to_string() const;
        QString to_string_lisible() const;        

        void set_configuration(const configuration &config);

    private:
        configuration m_configuration;
};

#endif // TEXTE_H
