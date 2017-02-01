#ifndef DEFINE_H
#define DEFINE_H

/*!
\brief Enumération décrivant les différentes fonctions.
*/
enum type_id_fonction{
    fonction_indefini = 0,

    debut_fonction_source = 1,
    f_source_booleen = 1,
    f_source_entier,
    f_source_texte,
    f_source_caractere,
    f_source_choix,
    f_source_generateur_permutation,
    fin_fonction_source,

    debut_fonction_conversion = 1000,
    f_conversion_cesar = 1000,
    fin_fonction_conversion,

    debut_fonction_sortie = 2000,
    f_sortie_texte = 2000,
    fin_fonction_sortie
};

/** \brief Enumération décrivant les différents type de paramètres. */
enum type_type_parametre{
    TYPE_PARAM_BASE = 0,
    TYPE_PARAM_CHOIX
};

/** \brief Enumération décrivant les différents paramètres. */
enum type_id_parametre{
    PARAM_CARACTERE_SEPARATEUR = 0,
    PARAM_MOT_SEPARATEUR,
    PARAM_LIGNE_SEPARATEUR,
    PARAM_ALPHABET,
    PARAM_DECALAGE,
    PARAM_ADDITIF,
    PARAM_ELEMENTS
};


#endif // DEFINE_H
