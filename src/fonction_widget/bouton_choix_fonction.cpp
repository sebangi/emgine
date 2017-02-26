/** \file bouton_choix_fonction.cpp
 * \brief Fichier d'implémentation de la classe bouton_choix_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/bouton_choix_fonction.h"
#include "entete/projet/base_fonction.h"
#include "entete/fonction/bibliotheque_fonctions.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe bouton_choix_fonction.
 * \param id L'identifiant de la fonction associée au bouton.
 * \param parent Un pointeur sur l'objet parent.
 */
bouton_choix_fonction::bouton_choix_fonction(type_id_fonction id, QWidget *parent)
    : QPushButton(parent), m_id_fonction(id)
{
    setText( bibliotheque_fonctions::get_nom(m_id_fonction) );

    if ( id < debut_fonction_conversion )
        setObjectName("BoutonChoixFonctionSource");
    else if ( id < debut_fonction_sortie )
        setObjectName("BoutonChoixFonctionConversion");
    else
        setObjectName("BoutonChoixFonctionSortie");
}

/** --------------------------------------------------------------------------------------
 * \brief Instancie et retourne une fonction associé au bouton.
 * \return Un pointeur sur la fonction créée.
 */
base_fonction * bouton_choix_fonction::get_fonction()
{
    return bibliotheque_fonctions::get_fonction(m_id_fonction);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type de la fonction associée au bouton.
 * \return Le type de la fonction associée au bouton.
 */
type_id_fonction bouton_choix_fonction::get_id_fonction() const
{
    return m_id_fonction;
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour la visibilité du bouton en fonction d'une clé de recherche.
 * \param cle La clé de recherche.
 */
void bouton_choix_fonction::mettre_a_jour_visibilite( const QString & cle )
{
    setVisible( bibliotheque_fonctions::contient_mot_cle( m_id_fonction, cle ) );
}
