#include "fonction/fonction_conversion/fonction_ecrire_en_morse.h"

#include "old_texte.h"
#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_ecrire_en_morse.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_ecrire_en_morse::fonction_ecrire_en_morse(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_ecrire_en_morse::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    old_texte::element_iterator it;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        if ( it->get_type() == element::retour_ligne )
            resultat.ajout_element(*it);
        else
        {
            std::string str = it->to_string();

            for ( unsigned int i = 0; i != str.size(); ++i )
            {
                char s = str[i];
                if ( s == 'a' || s == 'A' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'b' || s == 'B' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'c' || s == 'C' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'd' || s == 'D' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'e' || s == 'E' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'f' || s == 'F' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'g' || s == 'G' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'h' || s == 'H' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'i' || s == 'I' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'j' || s == 'J' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'k' || s == 'K' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'l' || s == 'L' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'm' || s == 'M' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'n' || s == 'N' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'o' || s == 'O' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'p' || s == 'P' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'q' || s == 'Q' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'r' || s == 'R' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 's' || s == 'S' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 't' || s == 'T' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'u' || s == 'U' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'v' || s == 'V' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'w' || s == 'W' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'x' || s == 'X' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'y' || s == 'Y' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == 'z' || s == 'Z' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '0' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '1' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '2' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '3' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '4' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '5' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '6' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '7' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '8' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '9' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '.' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == ',' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '?' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '\'' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '!' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '/' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '(' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == ')' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '&' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == ':' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == ';' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '=' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '+' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '-' )
                {
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '_' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '"' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '$' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element(' ') );
                }
                else if ( s == '@' )
                {
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element('-') );
                    resultat.ajout_element( element('.') );
                    resultat.ajout_element( element(' ') );
                }
                else
                    resultat.ajout_element( element(s) );
            }
        }
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_ecrire_en_morse::get_info_bulle() const
{
     return QString("Transforme un texte en morse\nParamètre : aucun");
}
