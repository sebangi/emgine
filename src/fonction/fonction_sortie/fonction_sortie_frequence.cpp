/** \file fonction_sortie_frequence.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_frequence.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_sortie/fonction_sortie_frequence.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/texte.h"
#include "entete/element/type_element.h"
#include "entete/fonction/fonction_sortie/frequence.h"
#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_frequence_widget.h"

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
    return new fonction_sortie_frequence_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_sortie_frequence::executer_sortie_specifique( compilateur &compil, const textes & textes_in, textes & textes_out )
{
    // calcul des fréquences
    for ( textes::const_iterator it_t = textes_in.begin(); it_t != textes_in.end(); ++it_t )
    {
        type_frequences_texte frequences_texte;
        int nb_elements = 0;

        for ( texte::const_iterator it_l = it_t->begin(); it_l !=  it_t->end(); ++it_l )
            for ( ligne::const_iterator it_m = it_l->begin(); it_m != it_l->end(); ++it_m )
                for ( mot::const_iterator it_c = it_m->begin(); it_c != it_m->end(); ++it_c )
                    {
                        nb_elements++;
                        bool trouve = false;
                        for ( type_frequences_texte::iterator it = frequences_texte.begin(); it != frequences_texte.end() && ! trouve; ++it )
                            if ( it->get_element() == *it_c )
                            {
                                trouve = true;
                                it->ajouter_occurrence();
                            }
                        if ( ! trouve )
                            frequences_texte.push_back( frequence(*it_c) );
                    }

        std::sort(frequences_texte.begin(), frequences_texte.end());
        m_frequences.push_back( frequences_texte );

        texte t;
        for ( type_frequences_texte::const_iterator it = frequences_texte.begin(); it != frequences_texte.end(); ++it )
        {
            ligne l;
            l.ajouter_mot( mot( it->get_element().to_string() ) );
            l.ajouter_mot( mot( QString::number( it->get_occurrence() ) ) );
            l.ajouter_mot( mot( QString::number( it->get_occurrence() * 100.0 / nb_elements ) + "%" ) );
            t.ajouter_ligne( l );
        }
        m_frequences_textes.ajouter_texte( it_t->get_configuration(), t );
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
 * \brief Accesseurs des textes de sortie de la fonction.
 * \return Les textes de sortie.
 */
textes & fonction_sortie_frequence::get_frequences_textes()
{
    return m_frequences_textes;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_sortie_frequence::get_valeur_courte() const
{
    return m_textes.to_string_lisible();
}

