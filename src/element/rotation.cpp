/**
 * \file rotation.cpp
 * \brief Fichier d'implémentation de la classe rotation.
 * \author Sébastien Angibaud
 */

#include "entete/element/rotation.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe rotation.
 * \param s La rotation au format QString.
 */
rotation::rotation(QString s)
{
    if ( s == "0 degré" )
        m_type = rotation_0;
    else if ( s == "90 degrés" )
        m_type = rotation_90;
    else if ( s == "180 degrés" )
        m_type = rotation_180;
    else if ( s == "270 degrés" )
        m_type = rotation_270;
    else
        m_type = rotation_invalide;
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe rotation.
 * \return \b True si la rotation est valide, \b False sinon.
 */
bool rotation::est_valide() const
{
    return m_type != rotation_invalide;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type de rotation.
 * \return \b Le type de la rotation.
 */
rotation::type_rotation rotation::get_type() const
{
    return m_type;
}

/** --------------------------------------------------------------------------------------
 * \brief .
 * \return La lise des rotations valides au format QString.
 */
QStringList rotation::liste_rotations_valides()
{
    QStringList l;

    l.push_back( "0 degré" );
    l.push_back( "90 degrés" );
    l.push_back( "180 degrés" );
    l.push_back( "270 degrés" );

    return l;
}

/** --------------------------------------------------------------------------------------
 * \brief .
 * \return La lise des rotations valides au format QString.
 */
QStringList rotation::liste_rotations_par_defaut()
{
    QStringList l;

    l.push_back( "90 degrés" );

    return l;
}
