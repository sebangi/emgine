#ifndef FONCTION_SUBSTITUTION_H
#define FONCTION_SUBSTITUTION_H

#include "fonction/base_fonction.h"
#include <map>
#include <set>

/*!
 \brief Classe décrivant une fonction permettant de faire une substitution lettre à lettre.
 \author Sébastien Angibaud
*/
class fonction_substitution : public base_fonction
{
private:
    typedef std::map< element, std::set<element> > type_correspondances;

public:
    fonction_substitution(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;

private:
        void calcul_correspondances(const old_texte& source, type_correspondances& correspondances) const;
};

#endif // FONCTION_SUBSTITUTION_H
