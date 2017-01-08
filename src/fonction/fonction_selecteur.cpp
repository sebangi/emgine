#include "fonction/fonction_selecteur.h"

#include "liste_choix.h"
#include "fonction/liste_fonctions.h"
#include <iostream>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe fonction_selecteur.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param indice L'indice du sélecteur.
 \param indice_fonction L'indice de la fonction du sélecteur.
*/
fonction_selecteur::fonction_selecteur( unsigned int indice, unsigned int indice_fonction )
    : m_indice(indice)
{
    creer_liste();

    if ( indice_fonction < old_liste_fonctions::get_nb_fonctions() )
    {
        int index = findText( old_liste_fonctions::get_fonction(indice_fonction)->get_nom() );
        setCurrentIndex(index);
    }
    else
        setCurrentIndex( -1 );
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne l'indice du sélecteur.
*/
unsigned int fonction_selecteur::get_indice() const
{
    return m_indice;
}

/*! --------------------------------------------------------------------------------------
 \brief Crée la liste des fonctions possibles.
*/
void fonction_selecteur::creer_liste()
{
    for ( unsigned int i = 0; i != old_liste_fonctions::get_nb_fonctions(); ++i )
        addItem( old_liste_fonctions::get_fonction(i)->get_nom() );
}
