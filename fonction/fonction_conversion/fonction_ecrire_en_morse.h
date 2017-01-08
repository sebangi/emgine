#ifndef FONCTION_ECRIRE_EN_MORSE_H
#define FONCTION_ECRIRE_EN_MORSE_H

#include "fonction/base_fonction.h"

/*!
 \brief Classe décrivant une fonction permettant d'écrire en morse.
 \author Sébastien Angibaud
*/
class fonction_ecrire_en_morse : public base_fonction
{
public:
    fonction_ecrire_en_morse(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;
};

#endif // FONCTION_ECRIRE_EN_MORSE_H
