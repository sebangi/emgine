#ifndef TEXTE_H
#define TEXTE_H

#include "entete/element/ligne.h"
#include "entete/compilation/configuration.h"

#include <vector>

class texte : public std::vector< ligne >
{
    public:
        texte();
        texte(const configuration& config);
        texte(const QString& valeur);

        QString to_string() const;
        QString to_string_lisible() const;
        QString get_string_configuration() const;

        void ajouter_configuration(const configuration &config);
        const configuration& get_configuration() const;

    private:
        configuration m_configuration;
};

#endif // TEXTE_H
