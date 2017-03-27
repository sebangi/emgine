#ifndef MOT_H
#define MOT_H

/** \file mot.h
 * \brief Fichier de déclaration de la classe mot.
 * \author Sébastien Angibaud
 */

#include "entete/element/base_element.h"

#include <vector>

/**
 * \class mot
 * \brief Classe décrivant un mot, i.e. un tableau d'élément.
 * \author Sébastien Angibaud
 */
class mot : public std::vector< base_element >
{
    public:
        mot();
        mot(const QString &valeur, const QString & separateur_caractere = "");
        mot( const mot& m);

        void set_separateur_caractere( const QString & separateur_caractere = " " );
        QString to_string() const;
        QString to_string_lisible() const;
        size_type nb_caracteres() const;
        size_type nb_caracteres_alphabet() const;
        void fusionner();

    private:
        /** \brief Le séparateur de caractères. */
        QString m_separateur_caractere;
};

#endif // MOT_H
