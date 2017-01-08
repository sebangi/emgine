#include "fonction/fonction_conversion/fonction_inverser_lignes.h"

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_inverser_lignes.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_inverser_lignes::fonction_inverser_lignes(fonctions_conteneur * conteneur, const QString & nom)
    : fonction_sur_ligne(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_inverser_lignes::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    type_lignes lignes;
    get_lignes(source, lignes);

    type_ligne::iterator it_ligne;
    type_lignes::reverse_iterator it_lignes;

    for ( it_lignes = lignes.rbegin(); it_lignes != lignes.rend(); )
    {
        for ( it_ligne = it_lignes->begin(); it_ligne != it_lignes->end(); ++it_ligne )
            resultat.ajout_element( *it_ligne );

        ++it_lignes;
        if ( it_lignes != lignes.rend() )
            resultat.ajout_element( element( element::retour_ligne ) );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_inverser_lignes::get_info_bulle() const
{
    return QString("Inverse les lignes d'un texte\nParamètre : aucun");
}
