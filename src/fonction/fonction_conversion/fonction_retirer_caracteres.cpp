#include "fonction/fonction_conversion/fonction_retirer_caracteres.h"

#include "old_texte.h"

#include <algorithm>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_retirer_caracteres.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_retirer_caracteres::fonction_retirer_caracteres(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Le texte source.
 \param resultat Le texte résultat.
 \param t Le texte paramètre (les caractères à retirer).
*/
void fonction_retirer_caracteres::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    old_texte::element_iterator it;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        element elem = *it;

        if ( elem.get_type() == element::caractere )
        {
            std::string str(elem.to_string());
            std::size_t found = parametre.to_string().find_first_of(str);

            if ( found == std::string::npos)
                resultat.ajout_element( elem );
        }
        else
            resultat.ajout_element( elem );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_retirer_caracteres::get_info_bulle() const
{
    return QString("Retire d'un texte un ensemble de caractères\nParamètre :\n\tles caractères à retirer");
}
