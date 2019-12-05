/**
 * \file liste_choix.cpp
 * \brief Fichier d'implémentation de la classe liste_choix.
 * \author Sébastien Angibaud
 */

#include "entete/element/liste_choix.h"

const QString liste_choix::choix_invalide = "CHOIX INVALIDE";

const QString liste_choix::rotation_0 = liste_choix::tr("0 degré");
const QString liste_choix::rotation_90 = liste_choix::tr("90 degrés");
const QString liste_choix::rotation_180 = liste_choix::tr("180 degrés");
const QString liste_choix::rotation_270 = liste_choix::tr("270 degrés");

const QString liste_choix::appliquer_sur_caracteres = liste_choix::tr("caractères");
const QString liste_choix::appliquer_sur_mots = liste_choix::tr("mots");
const QString liste_choix::appliquer_sur_lignes = liste_choix::tr("lignes");
const QString liste_choix::appliquer_sur_textes = liste_choix::tr("textes");

const QString liste_choix::de_haut_en_bas = liste_choix::tr("de haut en bas");
const QString liste_choix::de_bas_en_haut = liste_choix::tr("de bas en haut");
const QString liste_choix::de_gauche_a_droite = liste_choix::tr("de gauche a droite");
const QString liste_choix::de_droite_a_gauche = liste_choix::tr("de droite à gauche");

const QString liste_choix::diagonale_haut_gauche_bas_droit = liste_choix::tr("diagonale_haut_gauche_bas_droit");
const QString liste_choix::diagonale_bas_gauche_haut_droit = liste_choix::tr("diagonale_bas_gauche_haut_droit");

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par défaut de la classe liste_choix.
 */
liste_choix::liste_choix()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par recopie de la classe liste_choix.
 * \param l_choix La liste des choix à copier.
 */
liste_choix::liste_choix(const liste_choix &l_choix)
    : m_liste_choix_possibles( l_choix.m_liste_choix_possibles ),
      m_liste_choix_par_defaut( l_choix.m_liste_choix_par_defaut )
{

}


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
 * \brief Destructeur par défaut de la classe liste_choix.
 */
liste_choix::~liste_choix()
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
