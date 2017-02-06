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
    PARAM_ELEMENTS
};

#endif // DEFINE_PARAMETRE_H
