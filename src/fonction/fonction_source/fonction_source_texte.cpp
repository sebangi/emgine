/** \file fonction_source_texte.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_texte.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_texte.h"

#include "entete/compilation/compilateur.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_texte_widget.h"

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_texte.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 * \param texte Le texte de la fonction.
 */
fonction_source_texte::fonction_source_texte(fonctions_conteneur * conteneur, QString texte)
    : fonction_base_source(conteneur), m_texte(texte)
{
    set_id(f_source_texte);
    augmenter_max_niveau_visibilite(2);
    set_niveau_visibilite(2);

    ajouter_parametre( PARAM_CARACTERE_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur d'élément"),
                                           base_parametre::tr("Les séparateurs d'éléments."),
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_MOT_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur de mot"),
                                           base_parametre::tr("Les séparateurs de mot."),
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_LIGNE_SEPARATEUR,
                       new base_parametre( this,
                                           base_parametre::tr("Séparateur de ligne"),
                                           base_parametre::tr("Les séparateurs de ligne."),
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_texte.
 */
fonction_source_texte::~fonction_source_texte()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialise par défaut la fonction.
 */
void fonction_source_texte::initialisation_par_defaut()
{
    initialisation_par_defaut("", " ","\n");
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les paramètres de la fonction.
 * \param separ_caractere Le séparateur de caractères.
 * \param separ_mot Le séparateur de mots.
 * \param separ_ligne Le séparateur de lignes.
 */
void fonction_source_texte::initialisation_par_defaut(QString separ_caractere, QString separ_mot, QString separ_ligne )
{
    m_parametres[PARAM_CARACTERE_SEPARATEUR]->set_caractere_par_defaut(separ_caractere);
    m_parametres[PARAM_MOT_SEPARATEUR]->set_caractere_par_defaut(separ_mot);
    m_parametres[PARAM_LIGNE_SEPARATEUR]->set_caractere_par_defaut(separ_ligne);
}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_texte::generer_fonction_widget()
{
    return new fonction_source_texte_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_texte::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    textes_out = textes_in;

    algo_IPL_iteration_par_ligne
        ( PARAM_LIGNE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_LIGNE_SEPARATEUR.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_texte::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
        ( PARAM_MOT_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_2 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_MOT_SEPARATEUR.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_texte::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
        ( PARAM_CARACTERE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>fonction_texte</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_texte::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString t_caractere = m_map_IPL[PARAM_CARACTERE_SEPARATEUR].it_mot_courant->to_string();
    QString t_mot = m_map_IPL[PARAM_MOT_SEPARATEUR].it_mot_courant->to_string();
    QString t_ligne = m_map_IPL[PARAM_LIGNE_SEPARATEUR].it_mot_courant->to_string();

    texte t("", t_ligne );
    QStringList lignes = m_texte.split( t_ligne );
    for ( QStringList::const_iterator it_l = lignes.constBegin(); it_l != lignes.constEnd(); ++it_l )
    {
        ligne l("", t_mot );
        QStringList mots = it_l->split( t_mot );
        for ( QStringList::const_iterator it_m = mots.constBegin(); it_m != mots.constEnd(); ++it_m )
        {
            mot m("", t_caractere );
            QStringList caracteres = it_m->split( t_caractere );
            for ( QStringList::const_iterator it_c = caracteres.constBegin(); it_c != caracteres.constEnd(); ++it_c )
            {
                if ( it_c->size() != 0 )
                {
                    base_element e(*it_c);
                    m.push_back(e);
                }
            }
            if ( ! m.empty() )
                l.ajouter_mot(m);
        }
        if ( ! l.empty() )
            t.ajouter_ligne(l);
    }
    textes_out.ajouter_texte(compil.get_configuration(), t);
}

/** --------------------------------------------------------------------------------------
  \brief Teste si la fonction est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la fonction est valide, \b False sinon.
*/
bool fonction_source_texte::est_valide(logs_compilation_widget * vue_logs)
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_texte::get_valeur_courte() const
{
    return m_texte;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nom de fichier source.
 * \return Le nom du fichier source.
 */
QString fonction_source_texte::get_valeur() const
{
    return m_texte;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction.
 * \param texte Le nouveau texte de la fonction.
 */
void fonction_source_texte::set_valeur(QString texte)
{
    m_texte = texte;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_texte::get_string_valeur() const
{
    return m_texte;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param valeur La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_texte::set_string_valeur(const QString &valeur)
{
    m_texte = valeur;
}
