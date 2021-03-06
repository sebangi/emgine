#ifndef TEXTE_H
#define TEXTE_H

/** \file texte.h
 * \brief Fichier de déclaration de la classe texte.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/configuration.h"
#include "entete/element/ligne.h"
#include "entete/element/frequence.h"

#include <vector>

/**
 * \class texte
 * \brief Classe décrivant un texte, i.e. un tableau de ligne.
 * \author Sébastien Angibaud
 */
class texte : public std::vector< ligne >
{
    public:
        /** \brief Type représentant un ensemble de fréquence d'un texte. */
        typedef std::vector<frequence> type_frequences_texte;

    public:
        texte();
        texte(const configuration& config, const QString & separateur_ligne = "\n");
        texte(const QString& valeur, const QString & separateur_ligne = "\n");
        texte( const texte & t);
        ~texte();

        void ajouter_ligne( const ligne & l);
        void ajouter_texte( const texte & t);
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
        size_type nb_caracteres_alphabet() const;
        size_type nb_mots() const;
        size_type nb_lignes() const;
        bool est_multiple( size_t largeur, size_t hauteur ) const;

        void calculer_frequence( bool force_upper_case );
        void calculer_indice_coincidence();

        const type_frequences_texte & get_frequences() const;
        double get_indice_coincidence() const;
        void fusionner(bool fusion_caracteres, bool fusion_mots, bool fusion_lignes);
        void scinder(bool scission_interne_caracteres, bool scission_caracteres, bool scission_mots);
        void inverser(bool inversion_elements, bool inversion_ordre_caracteres, bool inversion_ordre_mots, bool inversion_ordre_lignes);
        void transposer_mots();
        void transposer_caracteres();
        void inverser_en_diagonale_mots( choix choix_diagonale );
        void inverser_en_diagonale_caracteres( choix choix_diagonale );
        void ecrire_mots_en_diagonale(choix choix_orientation, int nb_lignes_maximales, bool forcer_rectangularite);
        void ecrire_caracteres_en_diagonale(choix choix_orientation, int nb_lignes_maximales, bool forcer_rectangularite);
        void tourner_mots(choix choix_rotation);
        void tourner_caracteres(choix choix_rotation);
        bool est_rectangulaire_selon_mots() const;
        bool est_rectangulaire_selon_caracteres() const;
        size_type get_maximum_mots_dans_ligne() const;
        size_type get_minimum_mots_dans_ligne() const;
        size_type get_maximum_caracteres_dans_ligne() const;
        size_type get_minimum_caracteres_dans_ligne() const;

        QString get_separateur_ligne() const;

    private:
        void maj_comptages();
        void maj_nb_caracteres();
        void maj_nb_mots();

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

        /** \brief Les fréquences des éléments du texte. */
        type_frequences_texte m_frequences;

        /** \brief L'indice de coincidence du texte. */
        double m_indice_coincidence;
};

#endif // TEXTE_H
