/**
 * \file frequence.cpp
 * \brief Fichier d'implémentation de la classe frequence.
 * \author Sébastien Angibaud
 */

#include "entete/element/frequence.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe frequence.
 * \param e L'élément compté.
 * \param force_upper_case Booléen indiquant s'il faut forcer le upper_case.
 */
frequence::frequence(base_element e, bool force_upper_case)
    : m_occurrence(1), m_element(e.to_string(), force_upper_case)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'infériorité.
 * \param f La fréquence comparé.
 * \return \b True si la fréquence courante est inférieure à la fréquence donnée, \b False sinon.
 */
bool frequence::operator<(const frequence &f) const
{
    if ( m_occurrence == f.m_occurrence )
        return m_element < f.m_element;
    else
        return m_occurrence > f.m_occurrence;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nombre d'occurrence.
 * \return Le nombre d'occurrence de l'élément.
 */
int frequence::get_occurrence() const
{
    return m_occurrence;
}

/** --------------------------------------------------------------------------------------
 * \brief Augmente le nombre d'occurrence d'une unité.
 */
void frequence::ajouter_occurrence()
{
     m_occurrence++;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'élément compté.
 * \return L'élément compté.
 */
base_element frequence::get_element() const
{
    return m_element;
}
