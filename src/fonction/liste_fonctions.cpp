#include "fonction/liste_fonctions.h"

#include "fonction/fonction_conversion/fonction_cesar.h"
#include "fonction/fonction_conversion/fonction_ecrire_en_morse.h"
#include "fonction/fonction_conversion/fonction_forcer_casse.h"
#include "fonction/fonction_conversion/fonction_frequence.h"
#include "fonction/fonction_conversion/fonction_inverser_lignes.h"
#include "fonction/fonction_conversion/fonction_inverser_phrases.h"
#include "fonction/fonction_conversion/fonction_composee.h"
#include "fonction/fonction_conversion/fonction_lire_morse.h"
#include "fonction/fonction_conversion/fonction_retirer_caracteres.h"
#include "fonction/fonction_conversion/fonction_retrait_accents.h"
#include "fonction/fonction_conversion/fonction_substitution.h"
#include "old_texte.h"

#include <iostream>


/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe liste_fonctions.
 \author Sébastien Angibaud
*/

old_liste_fonctions::type_tableau_fonctions old_liste_fonctions::s_fonctions;

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
*/
old_liste_fonctions::old_liste_fonctions()
{
    std::cout << "old_liste_fonctions" << std::endl;

    s_init_fonctions();
}

/*! --------------------------------------------------------------------------------------
 \brief Destructeur.
*/
old_liste_fonctions::~old_liste_fonctions()
{
    std::cout << "~old_liste_fonctions" << std::endl;
    type_tableau_fonctions::iterator it;

    for ( it = s_fonctions.begin(); it != s_fonctions.end(); ++it )
        delete *it;
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne le nombre de fonctions possibles.
*/
unsigned int old_liste_fonctions::get_nb_fonctions()
{
    return s_fonctions.size();
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne la fonction d'un index donné.
*/
const base_fonction *old_liste_fonctions::get_fonction(unsigned int index)
{
    if ( index <= s_fonctions.size() )
        return s_fonctions[ index ];
    else
        return NULL;
}

/*! --------------------------------------------------------------------------------------
 \brief Initialise l'ensemble des fonctions.
*/
void old_liste_fonctions::s_init_fonctions()
{
    s_fonctions.push_back( new fonction_forcer_casse( "Mise majuscule", fonction_forcer_casse::majuscule ) );
    s_fonctions.push_back( new fonction_forcer_casse( "Mise en minuscule", fonction_forcer_casse::minuscule ) );
    s_fonctions.push_back( new fonction_retirer_caracteres( "Retrait d'éléments" ) );


    fonction_composee* f1 = new fonction_composee( "Inversion du texte" );
    f1->ajouter_fonction( new fonction_inverser_lignes( "Inversion des lignes" ));
    f1->ajouter_fonction( new fonction_inverser_phrases( "Inversion des phrases" ));
    s_fonctions.push_back( f1 );

    s_fonctions.push_back( new fonction_substitution( "Substitution d'éléments" ) );
}

