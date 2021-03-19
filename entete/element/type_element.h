#ifndef TYPE_ELEMENT_H
#define TYPE_ELEMENT_H

/** \file type_element.h
 * \brief Fichier de déclaration du type type_element.
 * \author Sébastien Angibaud
 */

/** \enum type_element
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différents types d'élément.
 */
enum typeCategorie{
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
inline typeCategorie operator|(typeCategorie a, typeCategorie b)
{return static_cast<typeCategorie>(static_cast<int>(a) | static_cast<int>(b));}

#endif // TYPE_ELEMENT_H
