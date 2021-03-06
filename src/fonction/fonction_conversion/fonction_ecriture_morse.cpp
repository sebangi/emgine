/**
 * \file fonction_ecriture_morse.cpp
 * \brief Fichier d'implémentation de la classe fonction_ecriture_morse.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_conversion/fonction_ecriture_morse.h"

/** --------------------------------------------------------------------------------------
 \brief Constructeur de la classe fonction_ecriture_morse.
 \param conteneur Pointeur sur le conteneur de la fonction.
*/
fonction_ecriture_morse::fonction_ecriture_morse( fonctions_conteneur * conteneur )
    : fonction_substitution(conteneur)
{
    set_id(f_conversion_ecriture_morse);

    m_parametres[PARAM_CARACTERES_ENTREE]->set_editable(false);
    m_parametres[PARAM_CARACTERES_SORTIE]->set_editable(false);
    m_parametres[PARAM_NUMERO_CHOIX]->set_editable(false);

    diminuer_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialisation par défaut de la fonction.
 */
void fonction_ecriture_morse::initialisation_par_defaut()
{
    m_parametres[PARAM_CARACTERES_ENTREE]->set_texte_par_defaut( "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789" );
    m_parametres[PARAM_CARACTERES_SORTIE]->set_texte_par_defaut
            ( ".- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. .- -... -.-. -.. . ..-. --. .... .. .--- -.- .-.. -- -. --- .--. --.- .-. ... - ..- ...- .-- -..- -.-- --.. ----- .---- ..--- ...-- ....- ..... -.... --... ---.. ----.", " ", "\n", "\n");
    m_parametres[PARAM_NUMERO_CHOIX]->set_texte_par_defaut("");
}
