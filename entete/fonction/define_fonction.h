#ifndef DEFINE_FONCTION_H
#define DEFINE_FONCTION_H

/** \file define_fonction.h
 * \brief Déclaration des énumérations utiles aux fonctions.
 * \author Sébastien Angibaud
 */

/** \enum type_fonction
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différents types de fonction.
 */
enum type_fonction
{
    /** \brief Le type des fonctions sources. */
    fonction_source = 0,

    /** \brief Le type des fonctions de conversions. */
    fonction_conversion,

    /** \brief Le type des fonctions de sorties. */
    fonction_sortie
};


/** \enum type_id_fonction
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différentes fonctions.
 */
enum type_id_fonction{
    //------------------------------------
    // Fonction indéfinie
    /** \brief Fonction indéfinie.*/
    fonction_indefini = 0,

    //------------------------------------
    // Fonction source
    /** \brief Début des fonctions sources. */
    debut_fonction_source = 1,

    /** \brief Fonction source correspondant à un texte à éditer. */
    f_source_texte = 1,

    /** \brief Fonction source correspondant à un fichier textuel. */
    f_source_fichier_texte,

    /** \brief Fonction source correspondant à des caratères. */
    f_source_caractere,

    /** \brief Fonction source correspondant à des booléens (0 ou 1 / Oui ou Non). */
    f_source_booleen,

    /** \brief Fonction source correspondant à un entier. */
    f_source_entier,

    /** \brief Fonction source correspondant à un choix. */
    f_source_choix,

    /** \brief Fin des fonctions sources. */
    fin_fonction_source,

    /** \brief Source générant une permutation. */
    f_source_generateur_permutation, // retiré des propositions pour l'instant car trop gourmandes

    //------------------------------------
    // Fonction de conversion

    /** \brief Début des fonctions de conversion. */
    debut_fonction_conversion = 1000,

    /** \brief Fonction de conversion réalisant le décalage de César. */
    f_conversion_cesar = 1000,

    /** \brief Fin des fonctions de conversions. */
    fin_fonction_conversion,

    //------------------------------------
    // Fonction de sortie

    /** \brief Début des fonctions de sortie. */
    debut_fonction_sortie = 2000,

    /** \brief Fonction de sortie affichant simplement les textes. */
    f_sortie_texte = 2000,

    /** \brief Fin des fonctions de sortie. */
    fin_fonction_sortie
};


#endif // DEFINE_FONCTION_H
