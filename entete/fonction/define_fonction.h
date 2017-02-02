#ifndef DEFINE_FONCTION_H
#define DEFINE_FONCTION_H

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
    fin_fonction_source,
    f_source_generateur_permutation, // retiré temporairement

    debut_fonction_conversion = 1000,
    f_conversion_cesar = 1000,
    fin_fonction_conversion,

    debut_fonction_sortie = 2000,
    f_sortie_texte = 2000,
    fin_fonction_sortie
};


#endif // DEFINE_FONCTION_H
