/** \file fonction_sortie_frequence.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_frequence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_sortie_frequence.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_base_sortie_widget.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_frequence.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_sortie_frequence::fonction_sortie_frequence(fonctions_conteneur * conteneur)
    : fonction_base_sortie(conteneur)
{
    set_id(f_sortie_frequence);
    augmenter_max_niveau_visibilite(1);
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_sortie_frequence.
 */
fonction_sortie_frequence::~fonction_sortie_frequence()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_sortie_frequence::generer_fonction_widget()
{
    return new fonction_base_sortie_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_sortie_frequence::executer_sortie_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    m_textes_a_afficher.clear();
    textes_in.calculer_frequence(false);

    for ( textes::iterator it_texte = textes_in.begin(); it_texte != textes_in.end(); ++it_texte )
    {
        texte t;
        for ( texte::type_frequences_texte::const_iterator it = it_texte->get_frequences().begin(); it != it_texte->get_frequences().end(); ++it )
        {
            ligne l;
            l.ajouter_mot( mot( it->get_element().to_string() ) );
            l.ajouter_mot( mot( QString::number( it->get_occurrence() ) ) );
            l.ajouter_mot( mot( QString::number( it->get_occurrence() * 100.0 / it_texte->nb_caracteres() ) + "%" ) );
            t.ajouter_ligne( l );
        }
        m_textes_a_afficher.ajouter_texte( it_texte->get_configuration(), t );
    }
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_sortie_frequence::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_sortie_frequence::get_valeur_courte() const
{
    return base_fonction::tr("[fréquence]");
}

