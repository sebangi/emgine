#include "fonction/fonction_conversion/fonction_sur_ligne.h"
#include <iostream>
/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_sur_ligne.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_sur_ligne::fonction_sur_ligne(fonctions_conteneur * conteneur, const QString & nom)
    : base_fonction(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Récupère les lignes d'un texte.
 \param source Le texte source.
 \param lignes Les lignes du texte.
*/
void fonction_sur_ligne::get_lignes(const old_texte & source, type_lignes& lignes) const
{
    old_texte::element_iterator it;
    type_ligne ligne;

    for ( it = source.begin(); it != source.end(); ++it )
    {
        if ( it->get_type() == element::retour_ligne )
        {
            lignes.push_back(ligne);
            ligne.clear();
        }
        else
            ligne.push_back( element(*it) );
    }

    if ( ! ligne.empty() )
        lignes.push_back(ligne);
}
