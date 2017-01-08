#ifndef FONCTION_RETIRER_CARACTERES_H
#define FONCTION_RETIRER_CARACTERES_H

#include "fonction/base_fonction.h"
#include <string>

/*!
 \brief Classe décrivant une fonction permettant de retirer un ou plusieurs caractères.
 \author Sébastien Angibaud
*/
class fonction_retirer_caracteres : public base_fonction
{
public:
    fonction_retirer_caracteres(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;
};

#endif // FONCTION_RETIRER_CARACTERES_H
