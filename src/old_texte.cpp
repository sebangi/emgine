#include "old_texte.h"

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe texte.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
*/
old_texte::old_texte()
{
}

/*! --------------------------------------------------------------------------------------
 \brief Constructeur par copie.
 \param t Le texte copié.
*/
old_texte::old_texte(const old_texte &t)
    : m_elements(t.m_elements)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param str La chaine de caractères du texte.
*/
old_texte::old_texte(const std::string &str)
{
    std::string::const_iterator its;
    int nb = 0;
    bool lecture_entier(false);

    for ( its = str.begin(); its != str.end(); ++its )
    {
        if ( *its >= '0' && *its <= '9' )
        {
            lecture_entier = true;
            nb = 10 * nb + (*its - '0');
        }
        else
        {
            if ( lecture_entier )
            {
                ajout_element( element(nb) );
                nb = 0;
                lecture_entier = false;
            }
            else
                ajout_element( element(*its) );
        }
    }

    if ( lecture_entier )
        ajout_element( element(nb) );
}

/*! --------------------------------------------------------------------------------------
 \brief Réinitialise le texte.
*/
void old_texte::effacer()
{
    m_elements.clear();
}

/*! --------------------------------------------------------------------------------------
 \brief Ajoute un élément au texte.
*/
void old_texte::ajout_element(const element& e)
{
    m_elements.push_back(e);
}

/*! --------------------------------------------------------------------------------------
 \brief Convertit le texte en chaine de carcatères.
*/
std::string old_texte::to_string() const
{
    element_iterator it;
    std::string s;

    for ( it = begin(); it != end(); ++it )
        s = s + it->to_string();

    return s;

}

/*! --------------------------------------------------------------------------------------
 \brief Retourne un itérateur sur le début du texte.
*/
old_texte::element_iterator old_texte::begin() const
{
    return m_elements.begin();
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne un itérateur sur la fin du texte.
*/
old_texte::element_iterator old_texte::end() const
{
    return m_elements.end();
}
