#ifndef LIGNE_H
#define LIGNE_H

/** \file ligne.h
 * \brief Fichier de déclaration de la classe ligne.
 * \author Sébastien Angibaud
 */

#include "entete/element/mot.h"

#include <vector>

/**
 * \class ligne
 * \brief Classe décrivant une ligne, i.e. un tableau de mots.
 * \author Sébastien Angibaud
 */
class ligne : public std::vector< mot >
{
    private:
        /** \brief Alias de la classe mère. */
        typedef std::vector< mot > super;

    public:
        ligne();
        ligne(const QString &valeur, const QString & separateur_mot = " ");
        ligne( const ligne & l);

        void ajouter_mot( const mot & m);
        void set_separateur_mot( const QString & separateur_mot = " " );
        const mot & mot_a_la_position(size_type pos, const mot & mot_par_defaut) const;

        QString to_string() const;
        QString to_string_lisible() const;

        size_type nb_caracteres() const;
        size_type nb_caracteres_alphabet() const;
        size_type nb_mots() const;        

        bool operator<(const ligne & l) const;
        void fusionner(bool fusion_caracteres, bool fusion_mots);
        void scinder(bool scission_interne_caracteres, bool scission_caracteres);
        void inverser(bool inversion_elements, bool inversion_ordre_caracteres, bool inversion_ordre_mots);
        QString get_separateur_mot() const;

    private:
        void maj_nb_caracteres();

    private:
        /** \brief Le séparateur de mot. */
        QString m_separateur_mot;

        /** \brief Le nombre de caractères dans la ligne. */
        size_type m_nb_caracteres;
};

#endif // LIGNE_H
