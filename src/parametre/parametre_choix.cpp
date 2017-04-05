/** \file parametre_choix.cpp
 * \brief Fichier d'implémentation de la classe parametre_choix.
 * \author Sébastien Angibaud
 */

#include "entete/parametre/parametre_choix.h"

#include <iostream>

class base_parametre;

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe parametre_choix.
 * \param parent Un pointeur sur l'objet sélectionnable parent.
 * \param nom Le nom du paramètre.
 * \param aide Le texte d'aide du paramètre.
 * \param mode_contenu_parametre Indique si le paramètre peut être vide.
 * \param mode_configuration_visibilite Mode de visibilité de la configuration.
 * \param algorithme Algorithme utilisé pour l'exécution du paramètre.
 * \param choix Liste des choix possibles.
 * \param multiple_selection Indique si la sélection des choix peut être multiple.
 */
parametre_choix::parametre_choix( objet_selectionnable * parent, QString nom, QString aide,
                                  type_mode_contenu_parametre mode_contenu_parametre,
                                  type_mode_configuration_visibilite mode_configuration_visibilite,
                                  type_algorithme algorithme,
                                  const liste_choix & choix, bool multiple_selection )
    : base_parametre(parent, nom, aide, mode_contenu_parametre, mode_configuration_visibilite, algorithme),
      m_choix(choix), m_multiple_selection(multiple_selection)
{
    m_type = TYPE_PARAM_CHOIX;
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe parametre_choix.
 */
parametre_choix::~parametre_choix()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs des choix en cours.
 * \return La liste des choix courants.
 */
QStringList parametre_choix::get_choix() const
{
    return m_choix.liste_choix_possibles();
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si la sélection peut être multiple.
 * \return \b True si la sélection peut être multiple, \b False sinon.
 */
bool parametre_choix::multiple_selection() const
{
    return m_multiple_selection;
}
