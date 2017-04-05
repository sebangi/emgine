/** \file ligne.cpp
 * \brief Fichier d'implémentation de la classe ligne.
 * \author Sébastien Angibaud
 */

#include "entete/element/ligne.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe ligne.
 */
ligne::ligne()
    : vector<mot>(), m_separateur_mot(" "), m_nb_caracteres(0)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe ligne.
 * \param valeur La chaîne de caractères représentant la ligne.
 * \param separateur_mot Le séparateur des mots.
 */
ligne::ligne(const QString &valeur, const QString & separateur_mot)
    : vector<mot>(), m_separateur_mot(separateur_mot), m_nb_caracteres(0)
{
    if ( ! valeur.isEmpty() )
    {
        mot m(valeur);
        ajouter_mot(m);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par copie de la classe ligne.
 * \param l La ligne à copier.
 */
ligne::ligne(const ligne &l)
    : vector<mot>(l), m_separateur_mot(l.m_separateur_mot), m_nb_caracteres(l.m_nb_caracteres)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un mot à la ligne.
 * \param m Le mot à ajouter.
 */
void ligne::ajouter_mot( const mot & m)
{
    push_back(m);
    m_nb_caracteres += m.nb_caracteres();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le séparateur de mot.
 * \param separateur_mot Le séparateur de mot.
 */
void ligne::set_separateur_mot(const QString &separateur_mot)
{
    m_separateur_mot = separateur_mot;
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit et retourne la ligne au format QString.
 * \return La ligne en format QString.
 */
QString ligne::to_string() const
{
    QString result;

    for ( size_type i = 0; i < size(); ++i )
        result += this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Convertit et retourne la ligne au format QString avec l'ajout de séparateur.
 * \return La ligne en format QString.
 */
QString ligne::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( size_type i = 1; i < size(); ++i )
        result += m_separateur_mot + this->at(i).to_string_lisible();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractères de la ligne.
 * \return Le nombre de caractères de la ligne.
 */
std::vector<mot>::size_type ligne::nb_caracteres() const
{
    return m_nb_caracteres;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de caractère alphabet du mot.
 * \return Le nombre de caractères alphabet du mot.
 */
std::vector<mot>::size_type ligne::nb_caracteres_alphabet() const
{
    std::vector<mot>::size_type nb = 0;

    for ( size_type i = 0; i < size(); ++i )
        nb += this->at(i).nb_caracteres_alphabet();

    return nb;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de mots de la ligne.
 * \return Le nombre de mots de la ligne.
 */
std::vector<mot>::size_type ligne::nb_mots() const
{
    return size();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'infériorité stricte.
 * \param l La ligne comparée.
 * \return \b True si la ligne courante est inférieur strictement, \b False sinon.
 */
bool ligne::operator<(const ligne & l) const
{
    return to_string() < l.to_string();
}

/** --------------------------------------------------------------------------------------
 * \brief Fusion des mots et/ou des caractères.
 * \param fusion_caracteres Indique s'il faut fusionner les caractères.
 * \param fusion_mots Indique s'il faut fusionner les mots.
 */
void ligne::fusionner(bool fusion_caracteres, bool fusion_mots)
{
    if ( fusion_mots && ! empty() )
    {
        iterator it_premier = begin();
        iterator it = begin();

        for ( ++it; it != end(); ++it )
            for ( mot::iterator it_m = it->begin(); it_m != it->end(); ++it_m )
                it_premier->push_back(*it_m);

        it = begin();
        ++it;
        erase(it,end());

    }

    if( fusion_caracteres )
        for ( iterator it = begin(); it != end(); ++it )
            it->fusionner();

    maj_nb_caracteres();
}

/** --------------------------------------------------------------------------------------
 * \brief Scinder les caractères et/ou le contenu des caractères.
 * \param scission_interne_caracteres Indique s'il faut scinder le contenu des caractères.
 * \param scission_caracteres Indique s'il faut scinder les caractères.
 */
void ligne::scinder(bool scission_interne_caracteres, bool scission_caracteres)
{
    if ( scission_interne_caracteres )
        for ( iterator it = begin(); it != end(); ++it )
            it->scinder_contenu_caracteres();

    if ( scission_caracteres && ! empty() )
    {
        ligne l;

        for ( iterator it = begin(); it != end(); ++it )
            for ( mot::iterator it_m = it->begin(); it_m != it->end(); ++it_m )
            {
                mot m;
                m.push_back(*it_m);
                l.ajouter_mot(m);
            }

        swap(l);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Inversion des lignes, des mots et/ou des caractères.
 * \param inversion_elements Indique s'il faut inverser les elements.
 * \param inversion_ordre_caracteres Indique s'il faut inverser l'ordre des caractères.
 * \param inversion_ordre_mots Indique s'il faut inverser l'ordre des mots.
 */
void ligne::inverser(bool inversion_elements, bool inversion_ordre_caracteres, bool inversion_ordre_mots)
{
   if ( inversion_ordre_caracteres || inversion_elements )
        for ( iterator it = begin(); it != end(); ++it )
            it->inverser(inversion_elements, inversion_ordre_caracteres);

    if ( inversion_ordre_mots )
        std::reverse(begin(), end());
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le nombre de caractères de la ligne.
 */
void ligne::maj_nb_caracteres()
{
    m_nb_caracteres = 0;

    for ( size_type i = 0; i < size(); ++i )
        m_nb_caracteres += this->at(i).nb_caracteres();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du séparateur de mots.
 * \return Le séparateur de mot.
 */
QString ligne::get_separateur_mot() const
{
    return m_separateur_mot;
}

