#ifndef BASE_ELEMENT_H
#define BASE_ELEMENT_H

/** \file base_element.h
 * \brief Fichier de déclaration de la classe base_element.
 * \author Sébastien Angibaud
 */

#include "type_element.h"

#include <QString>

/**
 * \class base_element
 * \brief Classe décrivant un élément de texte. Cela peut être un caractère, un entier, un booléen ou une chaine de caractère.
 * \author Sébastien Angibaud
 */
class base_element
{
    public:
        base_element();
        base_element( int valeur );
        base_element( QChar valeur );
        base_element( QCharRef valeur );
        base_element( QString valeur );
        base_element( QString valeur, bool sensible_a_la_casse );
        base_element( bool valeur );
        base_element( const base_element & elem );

        type_element get_type() const;
        bool get_booleen() const;
        int get_entier() const;
        QChar get_caractere() const;
        QString to_string() const;
        bool est_vide() const;
        bool est_lettre_alphabet() const;
        bool est_entier() const;

        void formater( bool retrait_ponctuation );
        void retirer_ponctuation();

        bool operator<(const base_element& e) const;
        bool operator==(const base_element& e) const;

    private:
        /** \brief Le type de l'élément. */
        type_element m_type;

        /** \brief La valeur booléenne de l'élément. */
        bool m_booleen;

        /** \brief La valeur entière de l'élément. */
        int m_entier;

        /** \brief La valeur de type caractère de l'élément. */
        QChar m_caractere;

        /** \brief La valeur de string de l'élément. */
        QString m_string;
};

#endif // BASE_ELEMENT_H
