/**
 * \file liste_choix.cpp
 * \brief Fichier d'implémentation de la classe liste_choix.
 * \author Sébastien Angibaud
 */

#include "entete/element/liste_choix.h"

const QString liste_choix::choix_invalide = "CHOIX INVALIDE";

const QString liste_choix::rotation_0 = "0 degré";
const QString liste_choix::rotation_90 = "90 degrés";
const QString liste_choix::rotation_180 = "180 degrés";
const QString liste_choix::rotation_270 = "270 degrés";

const QString liste_choix::appliquer_sur_caracteres = "caractères";
const QString liste_choix::appliquer_sur_mots = "mots";

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe liste_choix.
 * \param liste_choix_possibles La liste des choix possibles au format QStringList.
 * \param liste_choix_par_defaut La liste des choix par défaut au format QStringList.
 */
liste_choix::liste_choix(const QStringList & liste_choix_possibles, const QStringList & liste_choix_par_defaut)
    : m_liste_choix_possibles( liste_choix_possibles ), m_liste_choix_par_defaut( liste_choix_par_defaut )
{

}

/** --------------------------------------------------------------------------------------
 * \brief Test si une liste de choix donnée est valide.
 * \return \b True si la liste de choix est valide, \b False sinon.
 */
bool liste_choix::est_valide( const QStringList & c ) const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Test si un  choix donné est valide.
 * \return \b True si le choix est valide, \b False sinon.
 */
bool liste_choix::est_valide(const QString & c) const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs de la liste de choix possibles.
 * \return La liste des choix possibles au format QStringList.
 */
const QStringList& liste_choix::liste_choix_possibles() const
{
    return m_liste_choix_possibles;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs de la liste de liste_choix par défaut.
 * \return La liste des liste_choix par défaut au format QStringList.
 */
const QStringList& liste_choix::liste_choix_par_defaut() const
{
    return m_liste_choix_par_defaut;
}
