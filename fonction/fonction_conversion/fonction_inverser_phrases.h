#ifndef FONCTION_INVERSER_PHRASES_H
#define FONCTION_INVERSER_PHRASES_H

#include "fonction_sur_ligne.h"

/*!
 \brief Classe décrivant une fonction permettant d'inverser les phrases de chaque ligne d'un texte.
 \author Sébastien Angibaud
*/

class fonction_inverser_phrases : public fonction_sur_ligne
{
public:
    fonction_inverser_phrases(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;
};

#endif // FONCTION_INVERSER_PHRASES_H
