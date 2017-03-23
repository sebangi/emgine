#ifndef FONCTION_ECRITURE_MORSE_H
#define FONCTION_ECRITURE_MORSE_H

/** \file fonction_ecriture_morse.h
 * \brief Fichier de déclaration de la classe fonction_ecriture_morse.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_substitution.h"

/**
 * \class fonction_substitution
 * \brief Classe décrivant une fonction réalisant l'écriture en morse.
 * \author Sébastien Angibaud
 */
class fonction_ecriture_morse : public fonction_substitution
{
    public:
        fonction_ecriture_morse(fonctions_conteneur * conteneur);

        void initialisation_par_defaut();
};

#endif // FONCTION_ECRITURE_MORSE_H
