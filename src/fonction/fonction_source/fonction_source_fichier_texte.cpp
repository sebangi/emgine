/** \file fonction_source_fichier_texte.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_fichier_texte.
 * \author Sébastien Angibaud
 */

#include "entete/fonction/fonction_source/fonction_source_fichier_texte.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/element/type_element.h"
#include "entete/fonction_widget/fonction_source_widget/fonction_source_fichier_texte_widget.h"

#include <QCoreApplication>
#include <QDir>
#include <QFile>
#include <QTextStream>

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_fichier_texte.
 * \param conteneur Un pointeur sur le conteneur de la fonction.
 */
fonction_source_fichier_texte::fonction_source_fichier_texte(fonctions_conteneur * conteneur)
    : fonction_base_source(conteneur), m_chemin_relatif_fichier("")
{
    set_id(f_source_fichier_texte);
    augmenter_max_niveau_visibilite(2);
    set_niveau_visibilite(2);

    ajouter_parametre( PARAM_CARACTERE_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur d'élément",
                                           "Les séparateurs d'éléments.",
                                           base_parametre::CONTENU_PARAM_VIDE_POSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_MOT_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur de mot",
                                           "Les séparateurs de mot.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );

    ajouter_parametre( PARAM_LIGNE_SEPARATEUR,
                       new base_parametre( this,
                                           "Séparateur de ligne",
                                           "Les séparateurs de ligne.",
                                           base_parametre::CONTENU_PARAM_VIDE_IMPOSSIBLE,
                                           base_parametre::CONFIGURATION_INVISIBLE,
                                           base_parametre::ALGO_IPL) );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonction_source_fichier_texte.
 */
fonction_source_fichier_texte::~fonction_source_fichier_texte()
{

}

/** --------------------------------------------------------------------------------------
 * \brief Initialise par défaut la fonction.
 */
void fonction_source_fichier_texte::initialisation_par_defaut()
{
    initialisation_par_defaut("", " ","\n");
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les paramètres de la fonction.
 * \param separ_caractere Le séparateur de caractères.
 * \param separ_mot Le séparateur de mots.
 * \param separ_ligne Le séparateur de lignes.
 */
void fonction_source_fichier_texte::initialisation_par_defaut(QString separ_caractere, QString separ_mot, QString separ_ligne )
{
    m_parametres[PARAM_CARACTERE_SEPARATEUR]->set_caractere_par_defaut(separ_caractere);
    m_parametres[PARAM_MOT_SEPARATEUR]->set_caractere_par_defaut(separ_mot);
    m_parametres[PARAM_LIGNE_SEPARATEUR]->set_caractere_par_defaut(separ_ligne);
}

/** --------------------------------------------------------------------------------------
 * \brief Construit et retourne le widget associé à cette fonction.
 * \return Un pointeur sur le widget créé.
 */
base_fonction_widget *fonction_source_fichier_texte::generer_fonction_widget()
{
    return new fonction_source_fichier_texte_widget(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Execute la fonction.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_fichier_texte::executer( compilateur &compil, textes & textes_in, textes & textes_out )
{
    if ( m_chemin_relatif_fichier.isEmpty() )
        return;

    QFile file(get_chemin_absolu());
    if (! file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    m_contenu_fichier = in.readAll();
    file.close();

    algo_IPL_iteration_par_ligne
        ( PARAM_LIGNE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::callback_param_1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le paramètre PARAM_LIGNE_SEPARATEUR.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_fichier_texte::callback_param_1( compilateur &compil, textes & textes_in, textes & textes_out )
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
void fonction_source_fichier_texte::callback_param_2( compilateur &compil, textes & textes_in, textes & textes_out )
{
    algo_IPL_iteration_par_ligne
        ( PARAM_CARACTERE_SEPARATEUR, compil, textes_in, textes_out, & base_fonction::execution_specifique );
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute la fonction <b>fonction_fichier_texte</b>.
 * \param compil Le compilateur utilisé.
 * \param textes_in Le texte source en entrée.
 * \param textes_out Le texte de sortie généré.
 */
void fonction_source_fichier_texte::execution_specifique( compilateur &compil, textes & textes_in, textes & textes_out )
{
    QString t_caractere = m_map_IPL[PARAM_CARACTERE_SEPARATEUR].it_mot_courant->to_string();
    QString t_mot = m_map_IPL[PARAM_MOT_SEPARATEUR].it_mot_courant->to_string();
    QString t_ligne = m_map_IPL[PARAM_LIGNE_SEPARATEUR].it_mot_courant->to_string();

    texte t("", t_ligne );
    QStringList lignes = m_contenu_fichier.split( t_ligne );
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
bool fonction_source_fichier_texte::est_valide(logs_compilation_widget * vue_logs)
{
    QFile file(get_chemin_absolu());

    if (! file.open(QIODevice::ReadOnly))
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "La fonction \"" + get_nom() +
                                   "\" charge un fichier inexistant ou erroné.") );
        return false;
    }

    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur de la fonction en version raccourci.
 * \return La valeur courte de la fonction.
 */
QString fonction_source_fichier_texte::get_valeur_courte() const
{
    return "Fichier " + m_chemin_relatif_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du chemin absolu du fichier source.
 * \return Le chemin absolu du fichier source.
 */
QString fonction_source_fichier_texte::get_chemin_absolu() const
{
    QDir dir( QCoreApplication::applicationDirPath() );
    QString absolu_path = dir.absoluteFilePath( m_chemin_relatif_fichier );

    return absolu_path;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du chemin relatif de fichier source.
 * \return Le chemin relatif du fichier source.
 */
QString fonction_source_fichier_texte::get_chemin_relatif() const
{
    return m_chemin_relatif_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le nom du fichier source.
 * \param nom_fichier Le nouveau nom de fichier source.
 */
void fonction_source_fichier_texte::set_nom_fichier(QString nom_fichier)
{
    QFileInfo info(nom_fichier);
    QDir dir( QCoreApplication::applicationDirPath() );
    QString relative_path = dir.relativeFilePath( info.absoluteFilePath() );

    m_chemin_relatif_fichier = relative_path;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la valeur de la fonction au format QString.
 * \return La valeur de la fonction au format QString.
 */
QString fonction_source_fichier_texte::get_string_valeur() const
{
    return m_chemin_relatif_fichier;
}

/** --------------------------------------------------------------------------------------
 * \brief Initilialise la valeur de la fonction à partir d'un QString donné.
 * \param nom_fichier La nouvelle valeur de la fonction au format QString.
 */
void fonction_source_fichier_texte::set_string_valeur(const QString &nom_fichier)
{
    set_nom_fichier( nom_fichier );
}
