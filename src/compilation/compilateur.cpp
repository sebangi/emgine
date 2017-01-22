#include "entete/compilation/compilateur.h"

#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/projet/base_fonction.h"
#include "entete/fenetre_principale.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/projet/projet.h"

#include <iostream>

compilateur::compilateur( logs_compilation_widget * vue_logs )
    : m_vue_logs(vue_logs)
{

}

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

bool compilateur::est_valide(projet *p)
{
    return p->est_valide(m_vue_logs);
}

void compilateur::reset()
{
    m_en_cours = true;
    m_pile_textes.clear();
}

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

void compilateur::executer_fonction(base_fonction* f)
{
    for ( base_fonction::parametres_iterateur it = f->parametres_begin(); it != f->parametres_end(); ++it )
         executer_parametre( it->second );

    // exécution de la fonction
    textes textes_out;
    f->executer(*this, m_pile_textes.top(), textes_out);
    m_pile_textes.pop();
    m_pile_textes.push(textes_out);
}

void compilateur::executer_parametre(base_parametre *p)
{
    m_pile_textes.push(textes());

    base_parametre::type_fonctions actifs;
    for ( base_parametre::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        if ( (*it)->est_active() )
           executer_fonction( *it );

    p->set_textes_out( m_pile_textes.top() );
    m_pile_textes.pop();
}

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

logs_compilation_widget *compilateur::get_vue_logs() const
{
    return m_vue_logs;
}
