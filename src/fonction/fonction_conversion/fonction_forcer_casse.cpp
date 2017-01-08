#include "fonction/fonction_conversion/fonction_forcer_casse.h"

#include "old_texte.h"

#include <algorithm>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_forcer_casse.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
 \param t Type de forcage de la casse.
*/
fonction_forcer_casse::fonction_forcer_casse(fonctions_conteneur * conteneur, const QString & nom, type_forcer_casse t)
    : base_fonction(conteneur, nom), m_type_forcage(t)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_forcer_casse::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    old_texte::element_iterator it;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        element elem = *it;

        if ( m_type_forcage == majuscule )
            elem.to_upper();
        else
            elem.to_lower();

        resultat.ajout_element( elem );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_forcer_casse::get_info_bulle() const
{
     if ( m_type_forcage == majuscule )
         return QString("Convertit un texte en majuscule\nParamètre : aucun");
     else
         return QString("Convertit un texte en minuscule\nParamètre : aucun");
}
