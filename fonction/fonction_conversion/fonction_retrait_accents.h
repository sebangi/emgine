#ifndef FONCTION_RETRAIT_ACCENTS_H
#define FONCTION_RETRAIT_ACCENTS_H

#include "fonction/base_fonction.h"

/*!
 \brief Classe décrivant une fonction permettant de retirer des accents.
 \author Sébastien Angibaud
*/
class fonction_retrait_accents : public base_fonction
{
public:
    fonction_retrait_accents(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;
};

#endif // FONCTION_RETRAIT_ACCENTS_H
