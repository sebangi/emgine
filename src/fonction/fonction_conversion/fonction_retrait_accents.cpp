#include "fonction/fonction_conversion/fonction_retrait_accents.h"
#include "old_texte.h"

#include <iostream>
/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_retirer_accents.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_retrait_accents::fonction_retrait_accents(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Le texte source.
 \param resultat Le texte résultat.
 \param parametre Le texte parametre.
*/
void fonction_retrait_accents::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    old_texte::element_iterator it;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        element elem = *it;

        if ( elem.get_type() == element::caractere )
        {
            std::string str(elem.to_string());

            if( str == "à" || str == "â" )
                elem = element('a');
            else if ( str == "À" || str == "Â" )
                elem = element('A');
            else if( str == "é" || str == "è" || str == "ê" || str == "ë" )
                elem = element('e');
            else if( str == "È" || str == "É" || str == "Ê" || str == "Ë" )
                elem = element('E');
            else if( str == "î" || str == "ï" )
                elem = element('i');
            else if ( str == "Î" || str == "Ï" )
                elem = element('I');
            else if( str == "ù" )
                elem = element('u');
            else if ( str == "Ù" )
                elem = element('U');
            else if( str == "ç" )
                elem = element('c');
            else if ( str == "Ç" )
                elem = element('C');

            resultat.ajout_element( elem );
        }
        else
            resultat.ajout_element( elem );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_retrait_accents::get_info_bulle() const
{
    return QString("Retire d' un texte les accents\nParamètre : aucun");
}
