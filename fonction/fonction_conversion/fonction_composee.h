#ifndef FONCTION_COMPOSEE_H
#define FONCTION_COMPOSEE_H

#include "fonction/base_fonction.h"
#include <list>

/*!
 \brief Classe décrivant une fonction permettant de réaliser un décalage de césar.
 \author Sébastien Angibaud
*/
class fonction_composee : public base_fonction
{
public:
    fonction_composee(fonctions_conteneur * conteneur, const QString & nom);
    ~fonction_composee();

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;

    void ajouter_fonction( const base_fonction * f);

private:
    /*!
     \brief Le tableau des fonctions.
    */
    std::list< const base_fonction* > m_fonctions;
};

#endif // FONCTION_COMPOSEE_H
