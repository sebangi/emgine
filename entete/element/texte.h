#ifndef TEXTE_H
#define TEXTE_H

/** \file texte.h
 * \brief Fichier de déclaration de la classe texte.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/configuration.h"
#include "entete/element/ligne.h"

#include <vector>

/**
 * \class texte
 * \brief Classe décrivant un texte, i.e. un tableau de ligne.
 * \author Sébastien Angibaud
 */
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
        /** \brief La configuration des paramètres induisant ce texte. */
        configuration m_configuration;

        /** \brief La configuration des paramètres induisant ce texte sous forme QString. */
        QString m_string_configuration;

        /** \brief Le séparateur de ligne. */
        QString m_separateur_ligne;

        /** \brief Booléen indiquant si la configuration est visible. */
        bool m_configuration_visible;

        /** \brief Le nombre de ligne de la configuration. */
        int m_nb_lignes_configuration;

        /** \brief Le nombre de caractères du texte. */
        size_type m_nb_caracteres;

        /** \brief Le nombre de mots du texte. */
        size_type m_nb_mots;
};

#endif // TEXTE_H
