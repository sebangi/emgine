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

    /** \brief Fonction source correspondant à. */
    f_source_LIBRE,

    /** \brief Fonction source correspondant à un dictionnaire. */
    f_source_dictionnaire,

    /** \brief Fin des fonctions sources. */
    fin_fonction_source,

    /** \brief Source générant une permutation. */
    f_source_generateur_permutation, // retiré des propositions pour l'instant car trop gourmandes

    //------------------------------------
    // Fonction source de type choix

    /** \brief Début des fonctions sources de type choix. */
    debut_fonction_source_choix = 900,

    /** \brief Fonction source correspondant à un choix. */
    f_source_choix = 900,

    /** \brief Fin des fonctions sources de type choix. */
    fin_fonction_source_choix,

    //------------------------------------
    // Fonction de conversion

    /** \brief Début des fonctions de conversion. */
    debut_fonction_conversion = 1000,

    /** \brief Fonction de conversion réalisant le décalage de César. */
    f_conversion_cesar = 1000,

    /** \brief Fonction de conversion formatant le texte, i.e. mise en majuscule et retrait des accents. */
    f_conversion_formatage,

    /** \brief Fonction de conversion filtrant le texte selon un dictionnaire. */
    f_conversion_selection_selon_dictionnaire,

    /** \brief Fonction de conversion affichant les anagrammes de chaque mot. */
    f_conversion_anagramme,

    /** \brief Fonction de conversion des entiers en chiffres romain. */
    f_conversion_entier_en_chiffre_romain,

    /** \brief Fonction de conversion ajoutant un esapce entre les mots selon un dictionnaire. */
    f_conversion_ajout_espace_selon_dictionnaire,

    /** \brief Fonction de conversion réalisant la fusion des caractères, mots, lignes et/ou textes. */
    f_conversion_fusion,

    /** \brief Fonction de conversion réalisant une substitution de caractères. */
    f_conversion_substitution,

    /** \brief Fonction écriture en morse. */
    f_conversion_ecriture_morse,

    /** \brief Fonction lecture du morse. */
    f_conversion_lecture_morse,

    /** \brief Fonction de choix des séparateurs. */
    f_conversion_choisir_separateur,

    /** \brief Fonction réalisant la transposition des mots ou des caractères. */
    f_conversion_transposition,

    /** \brief Fonction de conversion réalisant l'inversion des caractères, mots et/ou lignes. */
    f_conversion_inversion,

    /** \brief Fonction de conversions réalisant la concaténation de textes. */
    f_conversion_concatenation,

    /** \brief Fonction réalisant la rotation des mots ou des caractères. */
    f_conversion_rotation,

    /** \brief Fonction réalisant la scission des lignes en textes, des mots en lignes, des caractères en mots ou du contenu des caractères en caractères. */
    f_conversion_scission,

    /** \brief Fonction de conversion réalisant l'écriture en diagonale des mots ou des caractères. */
    f_conversion_ecriture_en_diagonale,

    /** \brief Fonction de conversion réalisant suivant une diagonale l'inversion des mots ou des caractères. */
    f_conversion_inversion_en_diagonale,

    /** \brief Fonction écriture en braille. */
    f_conversion_ecriture_braille,

    /** \brief Fonction lecture du braille. */
    f_conversion_lecture_braille,

    /** \brief Fin des fonctions de conversions. */
    fin_fonction_conversion,

    //------------------------------------
    // Fonction de sortie

    /** \brief Début des fonctions de sortie. */
    debut_fonction_sortie = 2000,

    /** \brief Fonction de sortie affichant simplement les textes. */
    f_sortie_texte = 2000,

    /** \brief Fonction de sortie affichant la fréquence des éléments. */
    f_sortie_frequence,

    /** \brief Fonction de sortie affichant l'indice de coincidence. */
    f_sortie_indice_coincidence,

    /** \brief Fonction de sortie affichant l'analyse de chaque ligne. */
    f_sortie_analyse_ligne,

    /** \brief Fin des fonctions de sortie. */
    fin_fonction_sortie
};


#endif // DEFINE_FONCTION_H
