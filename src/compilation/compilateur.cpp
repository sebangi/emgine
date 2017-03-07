/** \file compilateur.cpp
 * \brief Fichier d'implémentation de la classe compilateur.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/compilateur.h"

#include "entete/compilation/configuration.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/fenetre_principale.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe compilateur.
 * \param vue_logs Un pointeur sur le widget de vue des logs.
 */
compilateur::compilateur( logs_compilation_widget * vue_logs )
    : m_vue_logs(vue_logs)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Compile un projet donné.
 * \param p Un pointeur sur le projet à compiler.
 */
void compilateur::compiler(projet *p)
{
    m_vue_logs->setVisible(true);

    m_vue_logs->marquer_comme_ancien();
    m_vue_logs->ajouter_log
            ( log_compilation( log_compilation::LOG_INFORMATION, p,
                               "----------------------------------------------------------") );
    m_vue_logs->ajouter_log
            ( log_compilation( log_compilation::LOG_IMPORTANT, p,
                               "Compilation du projet \"" + p->get_nom() + "\"...") );

    if ( est_valide( p ) )
    {
        m_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_SUCCES, p, "Le projet \"" + p->get_nom() + "\" est valide.") );
        reset();
        executer_projet(p);
    }
    else
    {
        QString message("compilation");

        m_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, p, "Le projet \"" + p->get_nom() + "\" n'est pas valide.") );
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Teste si un projet donné est valide.
 * \param p Un pointeur sur le projet à tester.
 * \return \b True si le projet est valide, \b False sinon.
 */
bool compilateur::est_valide(projet *p)
{
    return p->est_valide(m_vue_logs);
}

/** --------------------------------------------------------------------------------------
 * \brief Efface la compilation en cours.
 */
void compilateur::reset()
{
    m_en_cours = true;
    m_pile_textes.clear();
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute un projet donné.
 * \param p Un pointeur sur le projet à exécuter.
 */
void compilateur::executer_projet(projet *p)
{
    p->executer();
    m_vue_logs->ajouter_log
            ( log_compilation( log_compilation::LOG_IMPORTANT, "Exécution...") );
    m_pile_textes.push(textes());

    projet::type_fonctions actifs;
    for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        if ( (*it)->est_active() )
           executer_fonction( *it );

    afficher_resultat();
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute une fonction donnée.
 * \param f Un pointeur sur la fonction à exécuter.
 */
void compilateur::executer_fonction(base_fonction* f)
{
    // On exécute d'abord les paramètres de la fonctions
    for ( base_fonction::parametres_iterateur it = f->parametres_begin(); it != f->parametres_end(); ++it )
         executer_parametre( it->second );

    // exécution de la fonction
    textes textes_out;
    f->executer(*this, m_pile_textes.top(), textes_out);
    m_pile_textes.pop();
    m_pile_textes.push(textes_out);
}

/** --------------------------------------------------------------------------------------
 * \brief Exécute un paramètre donné.
 * \param p Un pointeur sur le paramètre à exécuter.
 */
void compilateur::executer_parametre(base_parametre *p)
{
    // On ajoute une liste de textes en haut de la pile
    m_pile_textes.push(textes());

    // On exécute les fonctions actives du paramètre
    for ( base_parametre::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        if ( (*it)->est_active() )
           executer_fonction( *it );

    // on initialise le paramètre avec la tête de la pile
    p->set_textes_out( m_pile_textes.top() );

    // On retire la tête de la pile
    m_pile_textes.pop();
}

/** --------------------------------------------------------------------------------------
 * \brief Affiche le résultat.
 */
void compilateur::afficher_resultat()
{
    textes res = m_pile_textes.top();
    m_pile_textes.pop();

    if ( ! m_pile_textes.empty() )
        m_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_ERREUR, "La pile d'exécution n'est pas vide.") );
    else
    {        
        m_vue_logs->ajouter_log
                ( log_compilation( log_compilation::LOG_IMPORTANT, "Exécution terminée.") );
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la configuration courante.
 * \return La configuration courante.
 */
configuration compilateur::get_configuration() const
{
    return m_configuration;
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un dictionnaire.
 * \param nom_fichier Le nom du fichier du dictionnaire.
 */
void compilateur::ajouter_dictionnaire(const QString & nom_fichier)
{
    m_vue_logs->ajouter_log
            ( log_compilation( log_compilation::LOG_INFORMATION, "Chargement du dictionnaire...") );

    if ( get_dictionnaire( nom_fichier ) == NULL )
        m_dictionnaires[ nom_fichier ] = new dictionnaire( nom_fichier );
    else
        m_dictionnaires[ nom_fichier ]->mettre_a_jour();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur d'un dictionnaire.
 * \param nom_fichier Le nom du fichier du dictionnaire recherché.
 * \return Un pointeur sur le dictionnaire recherché.
 */
const dictionnaire * compilateur::get_dictionnaire(const QString & nom_fichier) const
{
    map_dictionnaire::const_iterator it = m_dictionnaires.find( nom_fichier );

    if ( it == m_dictionnaires.end() )
        return NULL;
    else
        return it->second;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du widget de la vue des logs.
 * \return Un pointeur sur le widget de la vue des logs.
 */
logs_compilation_widget *compilateur::get_vue_logs() const
{
    return m_vue_logs;
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une configuration à un couple (fonction, parametre).
 * \param f Un pointeur sur la fonction à considérer.
 * \param param L'id du paramètre à considérer.
 * \param config La configuration à ajouter.
 */
void compilateur::ajouter_configuration(base_fonction * f, type_id_parametre param, const QString &config)
{
    m_configuration[ type_cle_configuration(f,param) ] = config;
}

/** --------------------------------------------------------------------------------------
 * \brief Efface la configuration d'un couple (fonction/parametre).
 * \param f Un pointeur sur la fonction à considérer.
 * \param param L'id du paramètre à considérer.
 */
void compilateur::retirer_configuration(base_fonction * f, type_id_parametre param)
{
    configuration::iterator it = m_configuration.find( type_cle_configuration(f,param) );
    if ( it != m_configuration.end() )
        m_configuration.erase(it);
}
