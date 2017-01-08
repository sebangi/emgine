#ifndef FONCTION_SUR_LIGNE_H
#define FONCTION_SUR_LIGNE_H

#include "fonction/base_fonction.h"

/*!
 \brief Classe décrivant une fonction sur les lignes du texte.
 \author Sébastien Angibaud
*/
class fonction_sur_ligne : public base_fonction
{
protected:
    typedef std::vector<element> type_ligne;
    typedef std::vector< type_ligne > type_lignes;

public:
    fonction_sur_ligne(fonctions_conteneur * conteneur, const QString & nom);

protected:
    void get_lignes(const old_texte & source, type_lignes& lignes) const;
};

#endif // FONCTION_SUR_LIGNE_H
