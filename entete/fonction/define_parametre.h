#ifndef DEFINE_PARAMETRE_H
#define DEFINE_PARAMETRE_H

/** \file define_parametre.h
 * \brief Déclaration des énumérations utiles aux parametres.
 * \author Sébastien Angibaud
 */

/** \enum type_type_parametre
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différents types de paramètres.
 */
enum type_type_parametre{
    /** \brief Type de base pour les paramètres. */
    TYPE_PARAM_BASE = 0,

    /** \brief Type de paramètre représentant un choix. */
    TYPE_PARAM_CHOIX
};

/** \enum type_id_parametre
 *  \author Sébastien Angibaud
 *  \brief Enumération représentant les différents paramètres possible des fonctions.
 */
enum type_id_parametre{
    /** \brief Paramètre séparateur de caractères. */
    PARAM_CARACTERE_SEPARATEUR = 0,

    /** \brief Paramètre séparateur de mot. */
    PARAM_MOT_SEPARATEUR,

    /** \brief Paramètre séparateur de ligne. */
    PARAM_LIGNE_SEPARATEUR,

    /** \brief Paramètre pour l'alphabet utilisé. */
    PARAM_ALPHABET,

    /** \brief Paramètre le décalage à effectuer. */
    PARAM_DECALAGE,

    /** \brief Paramètre pour indiquer l'état additif (par opposition à soustractif). */
    PARAM_ADDITIF,

    /** \brief Paramètre pour les éléments à considérer. */
    PARAM_ELEMENTS,

    /** \brief Paramètre pour indiquer si la ponctuation est à retirer. */
    PARAM_RETRAIT_PONCTUATION,

    /** \brief Paramètre pour indiquer le dictionnaire à utiliser. */
    PARAM_DICTIONNAIRE,

    /** \brief Paramètre pour indiquer que le traitement doit se faire pour chaque ligne. */
    PARAM_TRAITER_PAR_LIGNE,

    /** \brief Paramètre dédié aux caractères. */
    PARAM_CARACTERES,

    /** \brief Paramètre dédié aux mots. */
    PARAM_MOTS,

    /** \brief Paramètre dédié aux lignes. */
    PARAM_LIGNES,

    /** \brief Paramètre dédié aux textes. */
    PARAM_TEXTES,

    /** \brief Paramètre pour indiquer les caractères d'entrée d'un paramètre quelconque. */
    PARAM_CARACTERES_ENTREE,

    /** \brief Paramètre pour indiquer les caractères de sortie d'un paramètre quelconque. */
    PARAM_CARACTERES_SORTIE,

    /** \brief Paramètre pour indiquer les numéro des choix. */
    PARAM_NUMERO_CHOIX,

    /** \brief Paramètre pour indiquer s'il faut transposer selon les mots. */
    PARAM_TRANSPOSITION_MOTS,

    /** \brief Paramètre pour indiquer s'il faut réaliser la rotation selon les mots. */
    PARAM_ROTATION_MOTS,

    /** \brief Paramètre pour indiquer quel rotation réaliser. */
    PARAM_ROTATION
};

#endif // DEFINE_PARAMETRE_H
