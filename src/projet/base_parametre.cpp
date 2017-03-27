/** \file base_parametre.cpp
 * \brief Fichier d'implémentation de la classe base_parametre.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_parametre.h"

#include "entete/compilation/log_compilation.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/fonction/fonction_source/fonction_source_booleen.h"
#include "entete/fonction/fonction_source/fonction_source_caractere.h"
#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/fonction/fonction_source/fonction_source_dictionnaire.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/projet/base_fonction.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_parametre.
 * \param parent Un pointeur sur l'objet sélectionnable parent.
 * \param nom Le nom du paramètre.
 * \param aide Le texte d'aide du paramètre.
 * \param mode_contenu_parametre Le mode du contenu initial du paramètre.
 * \param mode_configuration_visibilite Le mode de visibilité initial du paramètre.
 * \param algorithme L'algorithme initial utilisé pour l'exécution du paramètre.
 */
base_parametre::base_parametre( objet_selectionnable * parent, QString nom, QString aide,
                                type_mode_contenu_parametre mode_contenu_parametre,
                                type_mode_configuration_visibilite mode_configuration_visibilite,
                                type_algorithme algorithme)
    : fonctions_conteneur(parent), m_fonction_parent((base_fonction*)parent), m_nom(nom), m_aide(aide), m_editable(true),
      m_mode_contenu_parametre(mode_contenu_parametre), m_textes_out(), m_mode_configuration_visibilite(mode_configuration_visibilite),
      m_algorithme(algorithme), m_type(TYPE_PARAM_BASE)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe base_parametre.
 */
base_parametre::~base_parametre()
{
    clear_fonctions();
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde le paramètre dans un flux donné.
 * \param stream Le flux Xml dans lequel écrire.
 */
void base_parametre::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("parametre");
    stream.writeTextElement("id", QString::number(m_id));
    stream.writeTextElement("nom", m_nom);
    stream.writeTextElement("dans_configuration", QString::number(m_mode_configuration_visibilite) );
    objet_selectionnable::sauvegarder(stream);
    fonctions_conteneur::sauvegarder(stream);
    stream.writeEndElement(); // Paramètre
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du nom du paramètre.
 * \return Le nom du paramètre.
 */
QString base_parametre::get_nom() const
{
    return m_nom;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le titre du paramètre.
 * \return Le titre du paramètre.
 */
QString base_parametre::get_titre() const
{
    return get_fonction_parent()->get_nom() + " : paramètre " + get_nom();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la valeur du paramètre en version raccourci.
 * \return La valeur courte du paramètre.
 */
QString base_parametre::get_valeur_courte() const
{
    int nb_fonctions_actives = get_nb_fonctions_actives();

    if ( nb_fonctions_actives == 0 )
        return "aucun";
    else if ( nb_fonctions_actives == 1 )
        return premiere_fonction_active()->get_valeur_courte();
    else
        return "complexe";
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le texte d'aide du paramètre.
 * \return Le texte d'aide du paramètre.
 */
QString base_parametre::get_aide() const
{
    return m_aide;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le texte d'aide de l'algorithme utilisé pour le paramètre.
 * \return Le texte d'aide de l'algorithme utilisé.
 */
QString base_parametre::get_aide_algorithme() const
{
    if ( m_algorithme == ALGO_AUCUN )
        return "aucun algorithme. Tout le texte est considéré d'un coup. Aucune itération.";
    else if ( m_algorithme == ALGO_IPL )
        return "Chaque ligne génère une nouvelle configuration.";
    else
        return "inconnu";
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est un paramètre.
 * \return \b True.
 */
bool base_parametre::est_parametre() const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la fonction parente.
 * \return Un pointeur sur le fonction parente.
 */
base_fonction *base_parametre::get_fonction_parent() const
{
    return m_fonction_parent;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le paramètre est requis, i.e. peut être non vide.
 * \return \b True si le paramaètre ne peut pas être vide, \b False sinon.
 */
bool base_parametre::est_requis() const
{
    return m_mode_contenu_parametre;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le paramètre à partir d'une valeur booléenne donnée.
 * \param valeur La valeur à utiliser.
 */
void base_parametre::set_booleen_par_defaut(bool valeur)
{
    base_fonction * f = new fonction_source_booleen(this,valeur);
    ajouter_fonction(f, NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le paramètre à partir d'un texte donné.
 * \param texte Le texte à utiliser.
 * \param separ_caractere Le séparateur de caractères.
 * \param separ_mot Le séparateur de mots.
 * \param separ_ligne Le séparateur de lignes.
 */
void base_parametre::set_texte_par_defaut
(QString texte, QString separ_caractere, QString separ_mot, QString separ_ligne)
{
    base_fonction * f = new fonction_source_texte(this,texte);
    ((fonction_source_texte *)f)->initialisation_par_defaut( separ_caractere, separ_mot, separ_ligne );
    ajouter_fonction(f, NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le paramètre à partir d'une valeur au format QString.
 * \param s La chaîne de caractères à utiliser.
 */
void base_parametre::set_caractere_par_defaut(QString s)
{
    base_fonction * f = new fonction_source_caractere(this,s);
    ajouter_fonction(f, NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le paramètre à partir d'un dictionnaire donné.
 * \param dico Le dictionnaire à utiliser.
 */
void base_parametre::set_dictionnaire_par_defaut(QString dico)
{
    base_fonction * f = new fonction_source_dictionnaire(this, dico);
    ajouter_fonction(f, NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le paramètre à partir d'une liste de choix donnée.
 * \param selection La liste des choix.
 */
void base_parametre::set_choix_par_defaut(const QStringList& selection)
{
    base_fonction * f = new fonction_source_choix(this,selection);
    ajouter_fonction(f, NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur des textes de sortie calculés lors de la dernière exécution.
 * \return Les textes de sortie.
 */
const textes & base_parametre::get_textes_out() const
{
    return m_textes_out;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les textes de sortie.
 * \param textes_out Les nouveaux textes de sortie.
 */
void base_parametre::set_textes_out(const textes &textes_out)
{
    m_textes_out = textes_out;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'identifiant du paramètre.
 * \param id Le nouvel identifiant du paramètre.
 */
void base_parametre::set_id(const type_id_parametre &id)
{
    m_id = id;
}

/** --------------------------------------------------------------------------------------
  \brief Teste si le paramètre est valide.
  \param vue_logs Un pointeur sur le widget de vue des logs.
  \return \b True si le paramètre est valide, \b False sinon.
*/
bool base_parametre::est_valide(logs_compilation_widget * vue_logs)
{
    bool result = true;

    type_fonctions actifs;
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        if ( (*it)->est_active() )
            actifs.push_back(*it);

    if ( actifs.size() == 0 )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le parametre \"" + m_nom +
                                   "\" de la fonction \"" + m_fonction_parent->get_nom() +
                                   "\" n'a aucune fonction active") );
        result = false;
    }
    else if ( ! ( actifs.front()->get_type() == type_fonction::fonction_source ) )
    {
        vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, this,
                                   "Le parametre \"" + m_nom +
                                   "\" de la fonction \"" + m_fonction_parent->get_nom() +
                                   "\" doit commencer par une fonction source active") );
        result = false;
    }

    for ( fonctions_iterateur it = actifs.begin(); it != actifs.end(); ++it )
        result = result && (*it)->est_fonction_valide(vue_logs);

    return result;
}

/** --------------------------------------------------------------------------------------
 * \brief Charge le paramètre à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void base_parametre::charger(QXmlStreamReader & xml)
{
    while( xml.readNextStartElement() )
    {
        if(xml.name() == "nom")
        {
            QString nom = xml.readElementText();
            // on n'en fait rien; c'est seulement pour la lisibilité du fichier
        }
        else if(xml.name() == "dans_configuration")
        {
            QString dans_configuration = xml.readElementText();
            if ( dans_configuration.toInt() == 1 )
                set_mode_configuration_visibilite( CONFIGURATION_VISIBLE );
            else
                set_mode_configuration_visibilite( CONFIGURATION_INVISIBLE );
        }
        else if (xml.name() == "objet_selectionnable")
            objet_selectionnable::charger(xml);
        else if(xml.name() == "fonctions")
        {
            charger_fonctions(xml, NULL);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le paramètre est visible dans la configuration.
 * \return \b True si le paramètre est visible dans la configuration, \b False sinon.
 */
bool base_parametre::configuration_visible() const
{
    return m_mode_configuration_visibilite == CONFIGURATION_VISIBLE;
}

/** --------------------------------------------------------------------------------------
 * \brief Inverse l'état de visibilité du paramètre dans la configuration.
 */
void base_parametre::inverser_configuration_visibilite()
{
    if ( m_mode_configuration_visibilite == CONFIGURATION_INVISIBLE )
        m_mode_configuration_visibilite = CONFIGURATION_VISIBLE;
    else
        m_mode_configuration_visibilite = CONFIGURATION_INVISIBLE;

    modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le mode de visibilité du paramètre dans la configuration.
 * \param mode_configuration_visibilite Le nouveau mode de visibilité.
 */
void base_parametre::set_mode_configuration_visibilite(type_mode_configuration_visibilite mode_configuration_visibilite)
{
    m_mode_configuration_visibilite = mode_configuration_visibilite;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le paramètre peut être vide.
 * \return \b True si le paramètre peut être vide, \b False sinon.
 */
bool base_parametre::peut_etre_vide() const
{
    return m_mode_contenu_parametre == CONTENU_PARAM_VIDE_POSSIBLE;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état editable du paramètre.
 * \param editable Le nouvel état éditable.
 */
void base_parametre::set_editable(bool editable)
{
    m_editable = editable;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'état éditable du paramètre.
 * \return \b True si le paramètre est éditable, \b False sinon.
 */
bool base_parametre::editable() const
{
    return m_editable;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type du paramètre.
 * \return Le type du paramètre.
 */
type_type_parametre base_parametre::get_type() const
{
    return m_type;
}
