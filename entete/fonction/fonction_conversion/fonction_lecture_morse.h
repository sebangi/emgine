#ifndef FONCTION_LECTURE_MORSE_H
#define FONCTION_LECTURE_MORSE_H

/** \file fonction_lecture_morse.h
 * \brief Fichier de déclaration de la classe fonction_lecture_morse.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_substitution.h"

/**
 * \class fonction_substitution
 * \brief Classe décrivant une fonction réalisant la lecture du morse.
 * \author Sébastien Angibaud
 */
class fonction_lecture_morse : public fonction_substitution
{
    public:
        fonction_lecture_morse(fonctions_conteneur * conteneur);

        void initialisation_par_defaut();
};

#endif // FONCTION_LECTURE_MORSE_H
