#ifndef OLD_TEXTE_H
#define OLD_TEXTE_H

#include "element.h"

#include <vector>
#include <string>

class texte_iterator;

/*!
 \brief Classe décrivant un texte.
 \author Sébastien Angibaud
*/
class old_texte
{
public:
    /*!
     \brief Type correspondant à un tableau d'élément.
    */
    typedef std::vector< element > tab_elements;

    /*!
     \brief Type correspondant à un itérateur sur les éléments.
    */
    typedef tab_elements::const_iterator element_iterator;

public:
    old_texte();
    old_texte(const old_texte& t);
    old_texte(const std::string& s);

    void effacer();
    void ajout_element(const element& e);

    std::string to_string() const;

    element_iterator begin() const;
    element_iterator end() const;

private:
    /*!
     \brief Le tableau des éléments.
    */
    tab_elements m_elements;
};

#endif // OLD_TEXTE_H
