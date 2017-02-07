#ifndef TYPE_ELEMENT_H
#define TYPE_ELEMENT_H

/** \enum type_fonction
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différents types d'élément.
 */
enum type_element{
    /** \brief Valeur pour les éléments indéfinis. */
    type_element_indefini = 0,

    /** \brief Valeur pour les éléments booléens. */
    type_element_booleen = 1,

    /** \brief Valeur pour les éléments entiers. */
    type_element_entier = 2,

    /** \brief Valeur pour les éléments de type caractère. */
    type_element_caractere = 4,

    /** \brief Valeur pour les éléments de tyupe QString. */
    type_element_string = 8
};

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur ou binaire entre deux type_element.
 * \param a Le premier type_element à considérer.
 * \param b Le second type_element à considérer.
 * \return Le type_element résultant.
 */
inline type_element operator|(type_element a, type_element b)
{return static_cast<type_element>(static_cast<int>(a) | static_cast<int>(b));}

#endif // TYPE_ELEMENT_H
