#include "fonction/fonction_conversion/fonction_inverser_phrases.h"

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_inverser_phrases.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param nom Le nom de la fonction.
*/
fonction_inverser_phrases::fonction_inverser_phrases(fonctions_conteneur * conteneur, const QString & nom)
    : fonction_sur_ligne(conteneur, nom)
{
}

/*! --------------------------------------------------------------------------------------
 \brief Application de la fonction.
 \param source Texte source.
 \param resultat Texte
 \param parametre Le texte parametre.
*/
void fonction_inverser_phrases::appliquer(const old_texte & source, old_texte & resultat, const old_texte & parametre) const
{
    resultat.effacer();

    type_lignes lignes;
    get_lignes(source, lignes);

    type_ligne::reverse_iterator it_ligne;
    type_lignes::iterator it_lignes;

    for ( it_lignes = lignes.begin(); it_lignes != lignes.end(); ++it_lignes)
    {
        for ( it_ligne = it_lignes->rbegin(); it_ligne != it_lignes->rend(); ++it_ligne )
            if ( it_ligne->get_type() != element::retour_ligne )
                resultat.ajout_element( *it_ligne );

        resultat.ajout_element( element( element::retour_ligne ) );
    }
}

/*! --------------------------------------------------------------------------------------
 \brief Renvoie un chaine décrivant la fonction.
*/
QString fonction_inverser_phrases::get_info_bulle() const
{
    return QString("Inverse les phrases de chaque ligne d'un texte\nParamètre : aucun");
}
