#ifndef FONCTION_FORCER_CASSE_H
#define FONCTION_FORCER_CASSE_H

#include "fonction/base_fonction.h"

/*!
 \brief Classe décrivant une fonction permettant de mettre un texte en majuscule ou en minuscule.
 \author Sébastien Angibaud
*/
class fonction_forcer_casse : public base_fonction
{
public:
    /*!
     \brief Enumération des différents type de forcage de casse.
    */
    enum type_forcer_casse{ majuscule, minuscule };

public:
    fonction_forcer_casse(fonctions_conteneur * conteneur, const QString & nom, type_forcer_casse t);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;

private:
    /*!
     \brief Type de forcage de casse choisi.
    */
    type_forcer_casse m_type_forcage;
};

#endif // FONCTION_FORCER_CASSE_H
