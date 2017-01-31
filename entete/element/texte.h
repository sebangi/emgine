#ifndef TEXTE_H
#define TEXTE_H

#include "entete/element/ligne.h"
#include "entete/compilation/configuration.h"

#include <vector>

class texte : public std::vector< ligne >
{
    public:
        texte();
        texte(const configuration& config, const QString & separateur_ligne = "\n");
        texte(const QString& valeur, const QString & separateur_ligne = "\n");
        ~texte();

        void ajouter_ligne( const ligne & l);
        QString to_string() const;
        QString to_string_lisible() const;

        QString get_string_information_taille() const;
        QString get_string_configuration() const;
        QString get_string_separation() const;
        void ajouter_configuration(const configuration &config);
        void ajouter_string_configuration(const configuration &config);
        const configuration& get_configuration() const;

        bool get_configuration_visible() const;
        void inverser_configuration_visibilite();

        int get_nb_lignes_avec_information() const;

        size_type nb_caracteres() const;
        size_type nb_mots() const;
        size_type nb_lignes() const;

    private:
        configuration m_configuration;
        QString m_string_configuration;
        QString m_separateur_ligne;
        bool m_configuration_visible;
        int m_max_taille_configuration;

        size_type m_nb_caracteres;
        size_type m_nb_mots;
};

#endif // TEXTE_H
