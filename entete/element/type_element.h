#ifndef TYPE_ELEMENT_H
#define TYPE_ELEMENT_H

/** \brief Type décrivant les différents types d'élément. */
enum type_element{
    type_element_indefini = 0,
    type_element_booleen = 1,
    type_element_entier = 2,
    type_element_caractere = 4,
    type_element_string = 8
};

inline type_element operator|(type_element a, type_element b)
{return static_cast<type_element>(static_cast<int>(a) | static_cast<int>(b));}

#endif // TYPE_ELEMENT_H
