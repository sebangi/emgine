#ifndef FONCTION_LIRE_MORSE_H
#define FONCTION_LIRE_MORSE_H

#include <string>
#include "old_texte.h"
#include "fonction/base_fonction.h"

/*!
 \brief Classe décrivant une fonction permettant de lire le morse.
 \author Sébastien Angibaud
*/
class fonction_lire_morse : public base_fonction
{
public:    
    fonction_lire_morse(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;

private:
    char from_morse( const std::string& morse ) const;
};

#endif // FONCTION_LIRE_MORSE_H
