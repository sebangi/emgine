/** \file log_compilation.cpp
 * \brief Fichier d'implémentation de la class log_compilation.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/log_compilation.h"

#include "entete/projet/objet_selectionnable.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe log_compilation.
 * \param type Le type du message.
 * \param message Le message.
 */
log_compilation::log_compilation(type_log type, QString message)
    : m_type(type), m_objet(NULL), m_message(message)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe log_compilation.
 * \param type Le type du message.
 * \param obj Un pointeur sur l'objet associé au message.
 * \param message Le message.
 */
log_compilation::log_compilation(type_log type, objet_selectionnable *obj, QString message)
    : m_type(type), m_objet(obj), m_message(message)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Constructeur par recopie de la classe log_compilation.
 * \param log Le log_compilation à copier.
 */
log_compilation::log_compilation(const log_compilation &log)
    : m_type(log.m_type), m_objet(log.m_objet), m_message(log.m_message)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors de la suppression d'un objet.
 * \param obj Un pointeur sur l'objet sélectionné.
 */
void log_compilation::informe_supression_selectionnable(objet_selectionnable *obj)
{
    if ( m_objet == obj)
        m_objet = NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Calcul et retourne le message du log.
 * \return Le message du log.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'objet associé.
 * \return Pointeur sur l'objet associé.
 */
objet_selectionnable *log_compilation::get_selectionnable()
{
    return m_objet;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type de message.
 * \return Le type du message.
 */
log_compilation::type_log log_compilation::get_type() const
{
    return m_type;
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur du type sous forme QString.
 * \return Le type sous forme QString.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Retourne la couleur associée au message (dépendant du type).
 * \return La couleur associée au message.
 */
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

