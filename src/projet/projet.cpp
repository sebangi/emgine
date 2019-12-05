/** \file projet.cpp
 * \brief Fichier d'implémentation de la classe projet.
 * \author Sébastien Angibaud
 */

#include "entete/projet/projet.h"

#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/projet/base_fonction.h"

#include <QCoreApplication>
#include <QDir>

#include <iostream>

// Initialisation des varaibles membres statiques :
unsigned int projet::s_nb_projets = 0;

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe projet.
 */
projet::projet()
    : fonctions_conteneur(NULL), m_nouveau(true), m_est_modifie(false), m_est_executable(true),
      m_verrouille_par_systeme(false)
{
    s_nb_projets++;

    m_nom = tr("Nouveau projet ") + QString::number( s_nb_projets );
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe projet.
 */
projet::~projet()
{
    clear_fonctions();

    emit signal_p_destruction_projet(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde le projet dans un flux donné.
 * \param stream Le flux Xml dans lequel écrire.
 * \param sauvegarde_reelle \b True si la sauvegarde est une réelle, \b False s'il s'agit uniquement de réaliser une copie via un QXmlStreamWriter
 */
void projet::sauvegarder( QXmlStreamWriter & stream, bool sauvegarde_reelle )
{
    if ( sauvegarde_reelle )
        m_nouveau = false;

    stream.writeStartElement("projet");
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("description", m_description);
    objet_selectionnable::sauvegarder(stream);
    fonctions_conteneur::sauvegarder(stream);
    stream.writeEndElement(); // Projet

    if ( sauvegarde_reelle )
    {
        m_est_modifie = false;
        emit signal_p_projet_etat_modification_change(this, false);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Charge le projet à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void projet::charger(QXmlStreamReader & xml)
{    
    Q_ASSERT( xml.isStartElement() &&
              xml.name() == "projet" );

    Q_ASSERT( m_nouveau );

    m_nouveau = false;

    while (xml.readNextStartElement())
    {
        if (xml.name() == "nom")
            charger_nom(xml);
        else if (xml.name() == "description")
            charger_description(xml);
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if (xml.name() == "fonctions")
            charger_fonctions(xml, NULL);
        else
            xml.skipCurrentElement();
    }

    m_est_modifie = false;
    emit signal_p_projet_etat_modification_change(this, false);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nom du projet.
 * \return Le nom du projet.
 */
QString projet::get_nom() const
{
    return m_nom;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le titre du projet.
 * \return Le titre du projet.
 */
QString projet::get_titre() const
{
    return get_nom();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le nom du projet.
 * \param nom Le nouveau nom du projet.
 */
void projet::set_nom(const QString &nom)
{
    m_nom = nom;

    emit signal_p_nom_projet_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Charge le nom du projet à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void projet::charger_nom(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "nom");

    // ne pas retirer cette ligne : il fait lire l'élément pour charger la suite
    QString nom = xml.readElementText();
    // Le nom est ignoré
}

/** --------------------------------------------------------------------------------------
 * \brief Charge la description du projet à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void projet::charger_description(QXmlStreamReader & xml)
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "description");

    m_description = xml.readElementText();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état de modification du projet.
 * \param est_modifie Le nouvel état de modification.
 */
void projet::set_est_modifie(bool est_modifie)
{
    m_est_modifie = est_modifie;

    emit signal_p_projet_etat_modification_change((projet*)this, est_modifie);
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le projet est enregistrable.
 * \return \b True si le projet est enregistrable, \b False sinon.
 */
bool projet::est_enregistrable() const
{
    return ! est_nouveau() && est_modifie();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état d'exécutabilité du projet.
 * \param executable Le nouvel état d'exécutabilité.
 */
void projet::set_executable( bool executable )
{
    m_est_executable = executable;

    emit signal_p_projet_executable_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le projet est exécutable.
 * \return \b True si le projet est exécutable, \b False sinon.
 */
bool projet::est_executable() const
{
    return m_est_executable;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le projet est verrouillé.
 * \return \b True si le projet est verrouillé, \b False sinon.
 */
bool projet::est_verrouille() const
{
    return fonctions_conteneur::est_verrouille() || m_verrouille_par_systeme;
}

/** --------------------------------------------------------------------------------------
 * \brief Ferme le projet.
 */
void projet::fermer()
{
    emit signal_p_fermeture_projet(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute le projet.
 */
void projet::executer()
{
    set_executable( false );
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le projet a été modifié depuis la dernière sauvegarde.
 * \return \b True si le projet a été modifié, \b False sinon.
 */
bool projet::est_modifie() const
{
    return m_est_modifie;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la description du projet.
 * \return La description du projet.
 */
QString projet::get_description() const
{
    return m_description;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le projet est nouveau.
 * \return \b True si le projet est nouveau, \b False sinon.
 */
bool projet::est_nouveau() const
{
    return m_nouveau;
}

/** --------------------------------------------------------------------------------------
 * \brief Iniduqe si l'objet est un projet.
 * \return \b True.
 */
bool projet::est_projet() const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le chemin relatif du fichier du projet.
 * \return Le chemin relatif du fichier du projet.
 */
QString projet::get_chemin_relatif() const
{
    return m_chemin_relatif;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le chemin absolu du fichier du projet.
 * \return Le chemin absolu du fichier du projet.
 */
QString projet::get_chemin_absolu() const
{
    QDir dir( QCoreApplication::applicationDirPath() );
    QString absolu_path = dir.absoluteFilePath( m_chemin_relatif );

    return absolu_path;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le dossier du projet.
 * \return Le dossier du projet.
 */
QString projet::get_dossier() const
{
    if ( m_chemin_relatif.isEmpty() )
        return "";
    else
        return QFileInfo( get_chemin_absolu() ).absolutePath();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le nom du fchier.
 * \param nom_fichier Le nouveau nom du fichier.
 */
void projet::set_nom_fichier(const QString &nom_fichier)
{
    QFileInfo info(nom_fichier);
    QDir dir( QCoreApplication::applicationDirPath() );
    QString relative_path = dir.relativeFilePath( info.absoluteFilePath() );

    m_chemin_relatif = relative_path;

    QString nom = m_chemin_relatif.split("/").last();
    set_nom( nom.split(".").first() );
}

/** --------------------------------------------------------------------------------------
  \brief Teste si le projet est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si la projet est valide, \b False sinon.
*/
bool projet::est_valide(logs_compilation_widget * vue_logs)
{
    bool result = true;

    type_fonctions actifs;
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        if ( (*it)->est_active() )
            actifs.push_back( *it );

    if ( actifs.size() == 0 )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   tr("Le projet") + " \"" + m_nom + "\" " + tr("n'a aucune fonction active")) );
        result = false;
    }
    else if ( ! ( actifs.front()->get_type() == type_fonction::fonction_source ) )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   tr("Le projet") + " \"" + m_nom + "\" " + tr("doit commencer par une fonction source active")) );
        result = false;
    }

    for ( fonctions_iterateur it = actifs.begin(); it != actifs.end(); ++it )
    {
        bool result_fonction = (*it)->est_fonction_valide(vue_logs);
        result = result && result_fonction;
    }

    return result;
}
