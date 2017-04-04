/** \file fonction_source_choix.cpp
 * \brief Fichier d'implémentationde la classe fonction_source_choix.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_choix.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h"
#include "entete/parametre/parametre_choix.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_choix.
 * \param conteneur Un pointeur sur le conteneur de al fonction.
 * \param sur_une_seule_ligne Indique si les choix doivent être écrits sur une seule ligne.
 * \param selection La sélection initiale.
 */
fonction_source_choix::fonction_source_choix( fonctions_conteneur * conteneur, bool sur_une_seule_ligne, const QStringList & selection )
    : fonction_base_source(conteneur), m_selection(selection), m_sur_une_seule_ligne(sur_une_seule_ligne),
      m_multiple_selection(false)
{
    set_id(f_source_choix);
    augmenter_max_niveau_visibilite(1);

    init_choix();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_choix.
 */
fonction_source_choix::~fonction_source_choix()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le conteneur de la fonction.
 * \param conteneur Un pointeur sur le nouveau conteneur.
 */
void fonction_source_choix::set_conteneur(fonctions_conteneur *conteneur)
{
    super::set_conteneur(conteneur);

    init_choix();
}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_choix::generer_fonction_widget()
{
    return new fonction_source_choix_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_choix::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    texte t;

    if ( m_sur_une_seule_ligne )
    {
        ligne l;

        for ( QStringList::iterator it = m_selection.begin(); it != m_selection.end(); ++it )
        {
            mot m( *it );
            l.ajouter_mot(m);
        }

        t.ajouter_ligne(l);
    }
    else
    {
        for ( QStringList::iterator it = m_selection.begin(); it != m_selection.end(); ++it )
        {
            mot m( *it );
            ligne l;
            l.ajouter_mot(m);
            t.ajouter_ligne(l);
        }
    }

    textes_out.push_back(t);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_choix::est_valide(logs_compilation_widget * vue_logs)
{
    if ( get_conteneur() != NULL )
        if ( get_conteneur()->est_parametre() )
            if ( ((base_parametre *)get_conteneur())->get_type() == TYPE_PARAM_CHOIX )
                return true;

    vue_logs->ajouter_log
            ( log_compilation( log_compilation::LOG_ERREUR, this,
                               "La fonction \"" + get_nom() +
                               "\" n'est pas situé dans un parametre de type choix") );

    return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseurs des choix possibles.
 * \return La liste des choix possibles.
 */
const QStringList & fonction_source_choix::get_choix() const
{
    return m_choix;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne si la sélection peut être multiple.
 * \return \b True si la sélection peut être multiple, \b False sinon.
 */
bool fonction_source_choix::get_multiple_selection() const
{
    return m_multiple_selection;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_choix::get_valeur_courte() const
{
    QString resultat;

    if ( ! m_selection.empty() )
    {
        QStringList::const_iterator it = m_selection.constBegin();
        resultat += *it;

        for ( ++it; it != m_selection.constEnd(); ++it )
            if ( m_sur_une_seule_ligne )
                resultat += " et " + *it;
            else
                resultat += "\n" + *it;
    }

    return resultat;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la sélection de choix courante.
 * \return La liste des choix sélectionnés.
 */
const QStringList& fonction_source_choix::get_selection() const
{
    return m_selection;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise la sélection des choix.
 * \param selection La nouvelle sélection.
 */
void fonction_source_choix::set_selection(const QStringList & selection)
{
    m_selection = selection;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_choix::get_string_valeur() const
{
    QString resultat;

    if ( ! m_selection.empty() )
    {
        QStringList::const_iterator it = m_selection.constBegin();
        resultat += *it;

        for ( ++it; it != m_selection.constEnd(); ++it )
            if ( m_sur_une_seule_ligne )
                resultat += " " + *it;
            else
                resultat += "\n" + *it;
    }

    return resultat;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_choix::set_string_valeur(const QString &valeur)
{
    m_selection = valeur.split( "\n" );
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise les choix.
 */
void fonction_source_choix::init_choix()
{
    if ( get_conteneur() != NULL )
        if ( get_conteneur()->est_parametre() )
            if ( ((base_parametre *)get_conteneur())->get_type() == TYPE_PARAM_CHOIX )
            {
                m_multiple_selection = ((parametre_choix *)get_conteneur())->multiple_selection();
                m_choix = ((parametre_choix *)get_conteneur())->get_choix();
            }
}
