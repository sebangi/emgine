/** \file textes.cpp
 * \brief Fichier d'implémentation de la classe textes.
 * \author Sébastien Angibaud
 */

#include "entete/element/textes.h"

/** --------------------------------------------------------------------------------------
 * \brief Construteur par défaut de la classe textes.
 */
textes::textes()
    : vector<texte>()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la class textes.
 * \param valeur La chaîne de caractères induisant l'ensemble de textes.
 */
textes::textes(const QString &valeur)
{
    texte t(valeur);

    push_back(t);
}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par copie de la classe textes.
 * \param t Les textes à copier.
 */
textes::textes(const textes &t)
    : vector<texte>(t)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'ensemble de textes au format QString.
 * \return L'ensemble de textes au format QString.
 */
QString textes::to_string() const
{
    QString result;

    for ( int i = 0; i != size(); ++i )
        result += this->at(i).to_string();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'ensemble de textes au format QString avec séparation des textes.
 * \return L'ensemble de textes au format QString.
 */
QString textes::to_string_lisible() const
{
    QString result;

    if ( ! empty() )
        result += this->at(0).to_string_lisible();

    for ( int i = 1; i < size(); ++i )
        result += "\n---------------------------------------\n" + this->at(i).to_string_lisible();

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un texte donné.
 * \param config La configuration à associer au texte ajouté.
 * \param t Le texte à ajouter.
 */
void textes::ajouter_texte(const configuration& config, const texte &t)
{
    push_back(t);
    this->back().ajouter_configuration( config );
}


/** --------------------------------------------------------------------------------------
 * \brief Calcule la fréquence des éléments.
 * \param force_upper_case Booléen indiquant s'il faut forcer le upper_case.
 */
void textes::calculer_frequence( bool force_upper_case )
{
    for ( int i = 0; i != size(); ++i )
        this->at(i).calculer_frequence(force_upper_case);
}

/** --------------------------------------------------------------------------------------
 * \brief Calcule l'indice de coincidence des textes.
 */
void textes::calculer_indice_coincidence()
{
    for ( int i = 0; i != size(); ++i )
        this->at(i).calculer_indice_coincidence();
}

/** --------------------------------------------------------------------------------------
 * \brief Fusion des textes, des lignes, des mots et/ou des caractères.
 * \param fusion_caracteres Indique s'il faut fusionner les caractères.
 * \param fusion_mots Indique s'il faut fusionner les mots.
 * \param fusion_lignes Indique s'il faut fusionner les lignes.
 * \param fusion_textes Indique s'il faut fusionner les textes.
 */
void textes::fusionner(bool fusion_caracteres, bool fusion_mots, bool fusion_lignes, bool fusion_textes)
{
    if ( fusion_textes && ! empty() )
    {
        iterator it_premier = begin();
        iterator it = begin();

        for ( ++it; it != end(); ++it )
            for ( texte::iterator it_t = it->begin(); it_t != it->end(); ++it_t )
                it_premier->ajouter_ligne(*it_t);
        it = begin();
        ++it;
        erase(it,end());
    }

    if ( fusion_caracteres || fusion_mots || fusion_lignes)
        for ( iterator it = begin(); it != end(); ++it )
            it->fusionner(fusion_caracteres, fusion_mots, fusion_lignes);
}

/** --------------------------------------------------------------------------------------
 * \brief Transpose les mots de chaque texte.
 */
void textes::transposer_mots()
{
    for ( iterator it = begin(); it != end(); ++it )
        it->transposer_mots();
}

/** --------------------------------------------------------------------------------------
 * \brief Transpose les caracteres de chaque texte.
 */
void textes::transposer_caracteres()
{
    for ( iterator it = begin(); it != end(); ++it )
        it->transposer_caracteres();
}

