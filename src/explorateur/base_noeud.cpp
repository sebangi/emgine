/** \file base_noeud.cpp
 * \brief Fichier d'implémentation de la class base_noeud.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/base_noeud.h"

#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/projet.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_noeud.
 * \param obj Un pointeur sur l'objet sélectionnable associé.
 * \param type Le type du noeud.
 */
base_noeud::base_noeud( objet_selectionnable * obj, base_noeud::type_noeud type )
    : QTreeWidgetItem( (int)type ), m_save_expanded(true)
{    
    m_objet = obj;
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe base_noeud.
 */
base_noeud::~base_noeud()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'objet sélectionnable associé au noeud.
 * \return L'objet sélectionnable associé au noeud.
 */
objet_selectionnable *base_noeud::get_objet() const
{
    return m_objet;
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le style du noeud.
 * \param actif Booléen indiquant si l'objet associé est actif.
 */
void base_noeud::mettre_a_jour_style(bool actif)
{
    QFont f = font(0);
    f.setStrikeOut( ! actif );
    setFont(0,f);
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'état d'expansion sauvegardé avant le compactage automatique.
 * \return \b True si l'expansion était active avant le compactage, \b False sinon.
 */
bool base_noeud::get_save_expanded() const
{
    return m_save_expanded;
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde l'état d'expansion.
 */
void base_noeud::save_expanded()
{
    m_save_expanded = isExpanded();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction virtuelle mettant à jour l'icone.
 */
void base_noeud::mise_a_jour_icone()
{
    // Ne rien faire dans la classe mère
    // La fonction sera à définir dans les classes filles SI BESOIN
}

