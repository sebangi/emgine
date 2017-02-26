/** \file objet_selectionnable.cpp
 * \brief Fichier d'implémentation de la classe objet_selectionnable.
 * \author Sébastien Angibaud
 */

#include "entete/projet/base_fonction.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/projet.h"

#include <iostream>

// Initialisation des variables membres statiques :
objet_selectionnable* objet_selectionnable::s_objet_courant = NULL;

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe objet_selectionnable.
 * \param parent Un pointeur sur l'objet parent.
 */
objet_selectionnable::objet_selectionnable(objet_selectionnable* parent)
    : m_objet_parent(parent), m_est_active(true), m_est_etendu(true), m_verrouille(false)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe objet_selectionnable.
 */
objet_selectionnable::~objet_selectionnable()
{
    emit signal_os_destruction_selectionnable(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Sélectionne l'objet.
 */
void objet_selectionnable::selectionner()
{
    // déselectionner l'objet actuellement sélectionné
    if ( s_objet_courant != NULL )
    {
        if ( s_objet_courant != this )
            s_objet_courant->deselectionner();
    }

    // sélection de l'objet
    if ( s_objet_courant != this )
    {
        s_objet_courant = this;
        emit signal_os_selectionne(this);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le fonctions_conteneur le plus proche : l'objet lui-même s'il est un conteneur, ou le conteneur parent sinon.
 * \return Un pointeur sur le fonctions_conteneur le plus proche.
 */
fonctions_conteneur * objet_selectionnable::get_conteneur()
{
    if ( est_conteneur() )
        return (fonctions_conteneur *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_conteneur();
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le fonctions_conteneur parent.
 * \return Le fonctions_conteneur parent.
 */
fonctions_conteneur * objet_selectionnable::get_conteneur_precedant()
{
    if ( m_objet_parent == NULL )
        return NULL;
    else
        return m_objet_parent->get_conteneur();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le fonctions_conteneur \b constant le plus proche : l'objet lui-même s'il est un conteneur, ou le conteneur parent sinon.
 * \return Un pointeur sur le fonctions_conteneur le plus proche.
 */
const fonctions_conteneur * objet_selectionnable::get_conteneur() const
{
    if ( est_conteneur() )
        return (fonctions_conteneur *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_conteneur();
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le projet contenant l'objet sélectionnable.
 * \return Un pointeur sur le projet. On retourne la valeur \b NULL si l'objet n'est pas dans un projet.
 */
projet * objet_selectionnable::get_projet()
{
    if ( est_projet() )
        return (projet *)this;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->get_projet();
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est dans un projet.
 * \return \b True si l'objet est dans un projet, \b False sinon.
 */
bool objet_selectionnable::est_dans_projet() const
{
    // ne pas utiliser get_projet() == NULL Sinon bugs
    if ( est_projet() )
        return true;
    else if ( m_objet_parent != NULL )
        return m_objet_parent->est_dans_projet();
    else
        return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est un conteneur.
 * \return \b False.
 */
bool objet_selectionnable::est_conteneur() const
{
    return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est un projet.
 * \return \b False.
 */
bool objet_selectionnable::est_projet() const
{
    return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est une fonction.
 * \return \b False.
 */
bool objet_selectionnable::est_fonction() const
{
    return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est un paramètre.
 * \return \b False.
 */
bool objet_selectionnable::est_parametre() const
{
    return false;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état d'activation de l'objet.
 * \param active Le nouvel état d'activation.
 */
void objet_selectionnable::set_est_active(bool active)
{    
    m_est_active = active;
    modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'état d'activation de l'objet.
 * \return \b True si l'objet est actif, \b False sinon.
 */
bool objet_selectionnable::est_active() const
{
    return m_est_active;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'état d'activation de l'objet en considérant également les objets parents.
 * \return \b True si l'objet est actif avec ses objets parents, \b False sinon..
 */
bool objet_selectionnable::est_active_avec_parent() const
{
    if ( m_objet_parent == NULL )
        return est_active();
    else
        return est_active() && m_objet_parent->est_active_avec_parent();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'état d'activation de l'objet parent.
 * \return \b True si l'objet parent est actif, \b False sinon..
 */
bool objet_selectionnable::parents_actifs() const
{
    if ( m_objet_parent == NULL )
        return true;
    else
        return m_objet_parent->est_active_avec_parent();
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet a comme ancêtre un objet donné.
 * \param obj Un pointeur sur l'objet recherché.
 * \return \b True si l'objet recherché est un ancètre, \b False sinon.
 */
bool objet_selectionnable::a_ancetre(objet_selectionnable *obj) const
{
    if ( this == obj )
        return true;
    else if ( m_objet_parent == NULL )
        return false;
    else
        return m_objet_parent->a_ancetre(obj);
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est vérrouillé, i.e. non éditable.
 * \return \b True si l'objet est vérrouillé, \b False sinon.
 */
bool objet_selectionnable::est_verrouille() const
{
    return m_verrouille;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état de verrouillage de l'objet.
 * \param verrouille Le nouvel état de verrouillage.
 */
void objet_selectionnable::set_verrouille(bool verrouille)
{
    m_verrouille = verrouille;
    modifier(false);

    emit signal_verrouillage_change(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Inverse l'état de verrouillage.
 */
void objet_selectionnable::inverser_verrouillage()
{
    set_verrouille( ! m_verrouille );
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est verrouillé en considérant également ses parents.
 * \return \b True si l'objet est vérrouillé avec ses parents, \b False sinon.
 */
bool objet_selectionnable::est_verrouille_avec_parent() const
{
    if ( m_objet_parent == NULL )
        return est_verrouille();
    else
        return est_verrouille() || m_objet_parent->est_verrouille_avec_parent();
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si le paret de l'objet est verrouillé.
 * \return \b True si l'objet parent est vérrouillé, \b False sinon.
 */
bool objet_selectionnable::parents_verrouilles() const
{
    if ( m_objet_parent == NULL )
        return false;
    else
        return m_objet_parent->est_verrouille_avec_parent();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne l'objet sélectionné.
 * \return Un pointeur sur l'objet sélectionné.
 */
objet_selectionnable *objet_selectionnable::get_selection()
{
    return s_objet_courant;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le conteneur de la sélection courante.
 * \return Un pointeur sur le conteneur de la sélection courante. On renvoie la valeur \b NULL s'il n'y a pas de sélection.
 */
fonctions_conteneur *objet_selectionnable::get_conteneur_courant()
{
    if ( existe_selection() )
    {
        if ( s_objet_courant->est_conteneur() )
            return (fonctions_conteneur *)s_objet_courant;
        else
            return (fonctions_conteneur *)s_objet_courant->m_objet_parent;
    }
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le projet de la sélection courante.
 * \return Un pointeur sur le projet de la sélection courante. On renvoie la valeur \b NULL s'il n'y a pas de sélection.
 */
projet * objet_selectionnable::get_projet_courant()
{
    if ( existe_selection() )
    {
        return get_projet_courant(s_objet_courant);
    }
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique s'il existe un objet sélectionné.
 * \return \b True si un objet est sélectionné, \b False sinon.
 */
bool objet_selectionnable::existe_selection()
{
    return s_objet_courant != NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Désélectionne l'objet sélectionné.
 */
void objet_selectionnable::forcer_deselection()
{
    if ( s_objet_courant != NULL )
        s_objet_courant->deselectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Désélectionne l'objet sélectionné.
 */
void objet_selectionnable::deselectionner()
{
    if ( s_objet_courant == this )
    {
        emit signal_os_deselectionne(this);
        s_objet_courant = NULL;
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le projet d'e la sélection courante'un objet donné.
 * \param obj Un pointeur sur l'objet à considérer.
 * \return Un pointeur sur le projet de la sélection courante. On renvoie la valeur \b NULL s'il n'y a pas de sélection.
 */
projet * objet_selectionnable::get_projet_courant(objet_selectionnable * obj)
{
    if ( obj == NULL )
        return NULL;
    else if ( obj->est_projet() )
        return (projet *)obj;
    else
        return get_projet_courant( obj->m_objet_parent );
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise l'état étendu de l'objet.
 * \param est_etendu Le nouvel état.
 */
void objet_selectionnable::set_est_etendu(bool est_etendu)
{
    m_est_etendu = est_etendu;
}

/** --------------------------------------------------------------------------------------
 * \brief Modifie l'objet.
 * \param change_executable Booléen indiquant s'il faut changer l'état d'exécutabilité du projet.
 */
void objet_selectionnable::modifier( bool change_executable )
{
    if( est_projet() )
    {
        if ( ! ((projet*)this)->est_modifie() )
            ((projet*)this)->set_est_modifie(true);

        if ( change_executable )
            ((projet*)this)->set_executable(true);
    }
    else if ( m_objet_parent != NULL )
        m_objet_parent->modifier(change_executable);
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est étendu.
 * \return \b True si l'objet est étendu, \b False sinon.
 */
bool objet_selectionnable::est_etendu() const
{
    return m_est_etendu;
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde l'objet sélectionnable dans un flux donné.
 * \param stream Le flux Xml dans lequel écrire.
 */
void objet_selectionnable::sauvegarder( QXmlStreamWriter & stream ) const
{
    stream.writeStartElement("objet_selectionnable");
    stream.writeTextElement("est_etendu", QString::number(m_est_etendu));    
    stream.writeTextElement("verrouille", QString::number(m_verrouille));
    stream.writeEndElement();
}

/** --------------------------------------------------------------------------------------
 * \brief Crée une copie de l'objet au format QString.
 * \return La copie au format QString.
 */
QString objet_selectionnable::creer_copie() const
{
    QString copie;

    QXmlStreamWriter XmlWriter(&copie);
    XmlWriter.setAutoFormatting(true);
    XmlWriter.writeStartDocument();

    if ( est_conteneur() )
        get_conteneur()->sauvegarder(XmlWriter);
    else
        ((const base_fonction*)this)->sauvegarder(XmlWriter);

    XmlWriter.writeEndDocument();

    return copie;
}

/** --------------------------------------------------------------------------------------
 * \brief Charge l'objet à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 */
void objet_selectionnable::charger(QXmlStreamReader & xml)
{
    Q_ASSERT( xml.isStartElement() &&
              xml.name() == "objet_selectionnable" );

    while (xml.readNextStartElement())
    {
        if (xml.name() == "est_etendu")
        {
            QString est_etendu = xml.readElementText();
            set_est_etendu( est_etendu.toInt() );
        }
        else if (xml.name() == "verrouille")
        {
            QString verrouille = xml.readElementText();
            set_verrouille( verrouille.toInt() );
        }
        else
            xml.skipCurrentElement();
    }
}
