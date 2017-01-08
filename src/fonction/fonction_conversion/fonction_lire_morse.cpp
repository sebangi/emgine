#include "fonction/fonction_conversion/fonction_lire_morse.h"


#include "old_texte.h"
#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_lire_morse.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_lire_morse::fonction_lire_morse(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_lire_morse::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    old_texte::element_iterator it;
    std::string mot;
    bool lecture_morse = false;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        std::string s = it->to_string();

        if ( s == "." || s == "-" )
        {
            mot = mot + s;
            lecture_morse = true;
        }
        else
        {
            if ( lecture_morse )
            {
                resultat.ajout_element( element( from_morse( mot ) ) );
                mot = "";
                lecture_morse = false;
            }
            else
                resultat.ajout_element( element(*it) );
        }
    }

    if ( lecture_morse )
        resultat.ajout_element( element( from_morse(mot) ) );
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie le caractère correspondant à une chaine écrit en morse.
 \param morse La chaine écrite en morse.
*/
char fonction_lire_morse::from_morse( const std::string& morse ) const
{
    if ( morse == ".-" )
        return 'A';
    else if ( morse == "-..." )
        return 'B';
    else if ( morse == "-.-." )
        return 'C';
    else if ( morse == "-.." )
        return 'D';
    else if ( morse == "." )
        return 'E';
    else if ( morse == "..-." )
        return 'F';
    else if ( morse == "--." )
        return 'G';
    else if ( morse == "...." )
        return 'H';
    else if ( morse == ".." )
        return 'I';
    else if ( morse == ".---" )
        return 'J';
    else if ( morse == "-.-" )
        return 'K';
    else if ( morse == ".-.." )
        return 'L';
    else if ( morse == "--" )
        return 'M';
    else if ( morse == "-." )
        return 'N';
    else if ( morse == "---" )
        return 'O';
    else if ( morse == ".--." )
        return 'P';
    else if ( morse == "--.-" )
        return 'Q';
    else if ( morse == ".-." )
        return 'R';
    else if ( morse == "..." )
        return 'S';
    else if ( morse == "-" )
        return 'T';
    else if ( morse == "..-" )
        return 'U';
    else if ( morse == "...-" )
        return 'V';
    else if ( morse == ".--" )
        return 'W';
    else if ( morse == "-..-" )
        return 'X';
    else if ( morse == "-.--" )
        return 'Y';
    else if ( morse == "--.." )
        return 'Z';
    else if ( morse == "-----" )
        return '0';
    else if ( morse == ".----" )
        return '1';
    else if ( morse == "..---" )
        return '2';
    else if ( morse == "...--" )
        return '3';
    else if ( morse == "....-" )
        return '4';
    else if ( morse == "....." )
        return '5';
    else if ( morse == "-...." )
        return '6';
    else if ( morse == "--..." )
        return '7';
    else if ( morse == "---.." )
        return '8';
    else if ( morse == "----." )
        return '9';
    else if ( morse == ".-.-.-" )
        return '.';
    else if ( morse == "--..--" )
        return ',';
    else if ( morse == "..--.." )
        return '?';
    else if ( morse == ".----." )
        return '\'';
    else if ( morse == "-.-.--" )
        return '!';
    else if ( morse == "-..-." )
        return '/';
    else if ( morse == "-.--." )
        return '(';
    else if ( morse == "-.--.-" )
        return ')';
    else if ( morse == ".-..." )
        return '&';
    else if ( morse == "---..." )
        return ':';
    else if ( morse == "-.-.-." )
        return ';';
    else if ( morse == "-...-" )
        return '=';
    else if ( morse == ".-.-." )
        return '+';
    else if ( morse == "-....-" )
        return '-';
    else if ( morse == "..--.-" )
        return '_';
    else if ( morse == ".-..-." )
        return '"';
    else if ( morse == "...-..-" )
        return '$';
    else if ( morse == ".--.-." )
        return '@';
    else
        return '_';
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_lire_morse::get_info_bulle() const
{
    return QString("Lit un texte en morse\nParamètre : aucun");
}

