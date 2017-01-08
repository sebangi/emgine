#ifndef FONCTION_FREQUENCE_H
#define FONCTION_FREQUENCE_H

#include "fonction/base_fonction.h"
#include <map>

/*!
 \brief Classe décrivant une fonction permettant de calculer les fréquences de lettres.
 \author Sébastien Angibaud
*/
class fonction_frequence : public base_fonction
{
private:
    /*!
     \brief Type correspondant à une map de fréquence.
    */
    typedef std::map< std::string, unsigned int > type_map_frequence;

public:
    fonction_frequence(fonctions_conteneur * conteneur, const QString & nom);

    void appliquer(const old_texte & source, old_texte & resultat, const old_texte & base_parametre) const;
    QString get_info_bulle() const;
};

#endif // FONCTION_FREQUENCE_H
