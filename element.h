#ifndef ELEMENT_H
#define ELEMENT_H

#include <string>

/*!
 \brief Classe décrivant un élément d'un texte.
 \author Sébastien Angibaud
*/
class element
{
    public:
        /*!
        \brief Type décrivant les différents type d'élément.
        */
        enum type_element{
            caractere,
            entier,
            retour_ligne
        };

    public:
        element(char c);
        element(int nb);
        element(type_element t);

        type_element get_type() const;
        std::string to_string() const;
        char to_char() const;
        int to_int() const;
        bool est_separateur() const;
        bool est_separateur(const char separateur) const;

        void to_upper();
        void to_lower();

        bool operator< (const element& e) const;

    private:
        /** \brief La valeur de l'élément caractère. */
        char m_caractere;

        /** \brief La valeur de l'élément entier. */
        int m_entier;

        /** \brief Le type de l'élément. */
        type_element m_type;
};

#endif // ELEMENT_H
