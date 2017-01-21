#include "entete/compilation/log_compilation.h"
#include "entete/projet/projet.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/base_parametre.h"

#include <iostream>

log_compilation::log_compilation(type_log type, QString message)
    : m_type(type), m_projet(NULL), m_fonction(NULL), m_parametre(NULL), m_message(message)
{

}

log_compilation::log_compilation(type_log type, projet *p, QString message)
    : m_type(type), m_projet(p), m_fonction(NULL), m_parametre(NULL), m_message(message)
{

}

log_compilation::log_compilation(type_log type, base_fonction *f, QString message)
    : m_type(type), m_projet(NULL), m_fonction(f), m_parametre(NULL), m_message(message)
{
    if ( f != NULL )
    {
        connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                 this, SLOT(on_externe_supprimer_fonction(base_fonction*)));
    }
}

log_compilation::log_compilation(type_log type, base_parametre *p, QString message)
    : m_type(type), m_projet(NULL), m_fonction(NULL), m_parametre(p), m_message(message)
{

}

log_compilation::log_compilation(const log_compilation &log)
    : m_type(log.m_type), m_projet(log.m_projet), m_fonction(log.m_fonction),
      m_parametre(log.m_parametre), m_message(log.m_message)
{

}

void log_compilation::informe_supression_selectionnable(objet_selectionnable *obj)
{
    if ( (objet_selectionnable *)m_fonction == obj)
        m_fonction = NULL;
    else if ( (objet_selectionnable *)m_parametre == obj )
        m_parametre = NULL;
    else if ( (objet_selectionnable *)m_projet == obj )
        m_projet = NULL;
}

QString log_compilation::get_message() const
{
    switch ( m_type )
    {
        case LOG_ERREUR:
            return "Erreur : " + m_message;
            break;

        case LOG_WARNING:
            return "Danger : " + m_message;
            break;

        default :
            return m_message;
    }
}

projet *log_compilation::get_projet()
{
    return m_projet;
}

base_fonction *log_compilation::get_fonction()
{
    return m_fonction;
}

base_parametre *log_compilation::get_parametre()
{
    return m_parametre;
}

objet_selectionnable *log_compilation::get_selectionnable()
{
    if ( m_fonction != NULL )
        return (objet_selectionnable*)m_fonction;
    else if ( m_parametre != NULL )
        return (objet_selectionnable*)m_parametre;
    else if ( m_projet != NULL )
        return (objet_selectionnable*)m_projet;
    else
        return NULL;
}

log_compilation::type_log log_compilation::get_type() const
{
    return m_type;
}

QString log_compilation::get_type_string() const
{
    switch ( m_type )
    {
        case LOG_INFORMATION:
            return "LOG_INFORMATION";
            break;

        case LOG_ERREUR:
            return "LOG_ERREUR";
            break;

        case LOG_SUCCES:
            return "LOG_SUCCES";
            break;

        case LOG_WARNING:
            return "LOG_WARNING";
            break;

        case LOG_IMPORTANT:
            return "LOG_IMPORTANT";
            break;

        default:
            return "LOG_NO_TYPE";
    }
}

QColor log_compilation::get_couleur() const
{
    switch ( m_type )
    {
        case LOG_INFORMATION:
            return QColor("black");
            break;

        case LOG_ERREUR:
            return QColor("red");
            break;

        case LOG_SUCCES:
            return QColor("green");
            break;

        case LOG_WARNING:
            return QColor("orange");
            break;

        case LOG_IMPORTANT:
            return QColor("blue");
            break;

        default:
            return QColor("silver");
    }
}

void log_compilation::on_externe_supprimer_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                this, SLOT(on_externe_supprimer_fonction(base_fonction*)));

    m_fonction = NULL;
}
