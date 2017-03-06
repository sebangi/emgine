/** \file fonction_sortie_analyse_ligne.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_analyse_ligne.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_sortie_analyse_ligne.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_analyse_ligne.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_sortie_analyse_ligne::fonction_sortie_analyse_ligne(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur)
{
    set_id(f_sortie_analyse_ligne);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_sortie_analyse_ligne.
 */
fonction_sortie_analyse_ligne::~fonction_sortie_analyse_ligne()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_sortie_analyse_ligne::generer_fonction_widget()
{
    return new fonction_base_sortie_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_sortie_analyse_ligne::executer_sortie_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    m_textes_a_afficher.clear();

    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        texte t( it_t->get_configuration() );
        int i = 1;
        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
        {
            ligne l;

            l.ajouter_mot( mot( QString::number( i ) + " : " ) );
            l.ajouter_mot( mot( QString::number( it_l->nb_mots() ) + " mots, " ) );
            l.ajouter_mot( mot( QString::number( it_l->nb_caracteres()) +  " caractères" ) );

            t.ajouter_ligne(l);
            ++i;
        }

        m_textes_a_afficher.ajouter_texte(compil.get_configuration(), t);
    }
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_sortie_analyse_ligne::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_sortie_analyse_ligne::get_valeur_courte() const
{
    return "[analyse ligne]";
}

