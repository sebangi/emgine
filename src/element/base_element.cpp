/**
 * \file base_element.cpp
 * \brief Fichier d'implémentation de la classe base_element.
 * \author Sébastien Angibaud
 */

#include "entete/element/base_element.h"
#include <QRegExp>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 */
base_element::base_element()
    : m_type(type_element_indefini)
{
    m_string = "";
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur entière de l'élément créé.
 */
base_element::base_element(int valeur)
    : m_type(type_element_entier),
      m_entier(valeur)
{
    m_string = QString::number(m_entier);
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur de type QChar de l'élément créé.
 */
base_element::base_element(QChar valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{
    m_string = QString(m_caractere);
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_element.
 * \param valeur La valeur de type QCharRef de l'élément créé.
 */
base_element::base_element(QCharRef valeur)
    : m_type(type_element_caractere),
      m_caractere(valeur)
{
    m_string = QString(m_caractere);
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la class base_element.
 * \param valeur La valeur de type QString de l'élément créé..
 */
base_element::base_element(QString valeur)
    : m_type(type_element_string), m_string(valeur)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par copie de la classe base_element.
 * \param elem L'élément à copier.
 */
base_element::base_element(const base_element &elem)
    :  m_type(elem.m_type), m_booleen(elem.m_booleen), m_entier(elem.m_entier), m_caractere(elem.m_caractere), m_string(elem.m_string)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la class base_element.
 * \param valeur La valeur de type QString de l'élément créé.
 * \param force_upper_case Booléen indiquant s'il faut forcer le upper_case.
 */
base_element::base_element(QString valeur, bool force_upper_case)
    : m_type(type_element_string)
{
    if ( force_upper_case )
        m_string = valeur.toUpper();
    else
        m_string = valeur;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'attribut type.
 * \return Le type de l'élément.
 */
type_element base_element::get_type() const
{
    return m_type;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur booléenne de l'élément.
 * \return La valeur booléenne de l'élément.
 */
bool base_element::get_booleen() const
{
    if ( m_type == type_element_entier )
        return m_entier != 0;
    else if ( m_type == type_element_string )
        return m_string != "0" && m_string != "non";
    else if ( m_type == type_element_caractere )
        return m_caractere != '0';
    else
        return m_booleen;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur entière de l'élément.
 * \return La valeur entière de l'élément.
 */
int base_element::get_entier() const
{
    if ( m_type == type_element_entier )
        return m_entier;
    else
    {
        bool ok;
        int valeur = m_string.toInt( & ok );
        if ( ok )
            return valeur;
        else
        {
            if ( est_lettre_alphabet() )
                return m_string[0].toUpper().toLatin1() - 'A' + 1;
            else
                return 0;
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de type QChar de l'élément.
 * \return La valeur de type QChar de l'élément.
 */
QChar base_element::get_caractere() const
{
    return m_caractere;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de type QString de l'élément.
 * \return La valeur de type QString de l'élément.
 */
QString base_element::to_string() const
{
    return m_string;
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si l'élément est vide.
 * \return \b True si l'élément est vide, \b False sinon.
 */
bool base_element::est_vide() const
{
    return m_string.isEmpty();
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si l'élément est une lettre de l'alphabet.
 * \return \b True si l'élément est une lettre de l'alphabet, \b False sinon.
 */
bool base_element::est_lettre_alphabet() const
{
    if ( m_string.size() != 1 )
        return false;
    else
        return (m_string[0] >= 'A' && m_string[0] <= 'Z') || (m_string[0] >= 'a' && m_string[0] <= 'z');
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si l'élément est un entier.
 * \return \b True si l'élément est un entier, \b False sinon.
 */
bool base_element::est_entier() const
{
    if ( m_type == type_element_entier )
        return true;
    else
    {
        bool ok;
        m_string.toInt( &ok );
        return ok;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Formate l'élément, i.e mets en majuscule, retire les accents et éventuellement la ponctuation.
 * \param retrait_ponctuation Booléen indiquant s'il faut retirer la ponctuation.
 */
void base_element::formater( bool retrait_ponctuation )
{
    m_string = m_string.toUpper();

    m_string.replace( QRegExp( "[ÁÀÂÄ]") , "A" );
    m_string.replace( QRegExp( "[ÉÈÊË]") , "E" );
    m_string.replace( QRegExp( "[ÍÌÎÏ]") , "I" );
    m_string.replace( QRegExp( "[ÓÒÔÖ]") , "O" );
    m_string.replace( QRegExp( "[ÚÙÛÜ]") , "U" );
    m_string.replace( QRegExp( "[Ç]") , "C" );

    if ( retrait_ponctuation )
        retirer_ponctuation();
}

/** --------------------------------------------------------------------------------------
 * \brief Inversion l'élément.
 */
void base_element::inverser()
{
    std::reverse(m_string.begin(), m_string.end());
}

/** --------------------------------------------------------------------------------------
 * \brief Retire la ponctuation.
 */
void base_element::retirer_ponctuation( )
{
    // le caractère * est gardé pour coder caractere_non_trouve
    QString ponct = QRegExp::escape("«»,;:!?./§%^¨$£&~\"#'{([|`_\\^@)]°=}+-");
    m_string.remove( QRegExp( "[" + ponct + "]" ) );
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'infériorité.
 * \param e Le base_element avec qui se comparer.
 * \return \b True si le base_element courant est inférieur strictement au base_element donné, \b False sinon.
 */
bool base_element::operator <(const base_element& e) const
{
    return m_string.compare( e.m_string ) < 0;
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'opérateur d'égalité.
 * \param e Le base_element avec qui se comparer.
 * \return \b True si le base_element courant est égal au base_element donné, \b False sinon.
 */
bool base_element::operator==(const base_element &e) const
{
    return m_string.compare( e.m_string ) == 0;
}

/** --------------------------------------------------------------------------------------
 * \brief Génère un élément inconnu.
 * \return Un élément inconnu.
 */
base_element base_element::element_inconnu()
{
    return base_element("*");
}

/** --------------------------------------------------------------------------------------
 * \brief Génère un élément booléen.
 * \param valeur La valeur booléenne de l'élément créé.
 */
base_element base_element::element_booleen(bool valeur)
{
    base_element e;
    e.m_type == type_element_booleen;
    e.m_booleen = valeur;

    if ( e.m_booleen )
        e.m_string = "oui";
    else
        e.m_string = "non";

    return e;
}

