/** \file fonctions_conteneur.cpp
 * \brief Fichier d'implémentation de la classe fonctions_conteneur.
 * \author Sébastien Angibaud
 */

#include "entete/projet/fonctions_conteneur.h"

#include "entete/fonction/bibliotheque_fonctions.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/projet.h"

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonctions_conteneur.
 * \param parent Un pointeur sur l'objet parent.
 */
fonctions_conteneur::fonctions_conteneur( objet_selectionnable * parent )
    : objet_selectionnable(parent)
{

}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fonctions_conteneur.
 */
fonctions_conteneur::~fonctions_conteneur( )
{

}

// obj_ref :
//   - NULL : ajouter en fin
//   - est conteneur : ajouter en début
//   - fonction du conteneur : ajouter après la fonction
//   - sinon ajouter en fin
/** --------------------------------------------------------------------------------------
 * \brief Ajoute une fonction donnée dans le conteneur.
 * \param f Un pointeur sur la fonction à ajouter.
 * \param obj_ref Un pointeur sur l'objet de référence.
 * \remark La position de l'ajout dépend de l'objet de référence :
 *   - l'objet de référence est NULL : ajout de la fonction en fin de liste ;
 *   - l'objet de référence est le conteneur lui-même : ajout de la fonction en début de liste ;
 *   - l'objet est une fonction du conteneur : ajout de la fonction après l'a fonction'objet de référence ;
 *   - Autre cas : ajout de la fonction en fin de liste.
 */
void fonctions_conteneur::ajouter_fonction(base_fonction *f, objet_selectionnable * obj_ref)
{
    f->set_conteneur(this);

    if ( obj_ref == NULL )
        m_fonctions.push_back(f);
    else if ( obj_ref->est_conteneur() )
        m_fonctions.push_front(f);
    else if ( m_fonctions.contains((base_fonction*)obj_ref) )
        m_fonctions.insert( m_fonctions.indexOf((base_fonction*)obj_ref) + 1, f);
    else
        m_fonctions.push_back(f);

    connect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
             this, SLOT(on_supprimer_fonction(base_fonction*)));

    emit signal_fc_creation_fonction(f);

    if ( est_dans_projet() )
        get_projet()->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Supprime une fonction donnée.
 * \param f Un pointeur sur la fonction à supprimer.
 */
void fonctions_conteneur::supprimer_fonction(base_fonction *f)
{
    disconnect( f, SIGNAL(signal_destruction_fonction(base_fonction*)),
                this, SLOT(on_supprimer_fonction(base_fonction*)));

    m_fonctions.removeOne(f);
    get_projet()->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de suppression d'une fonction donnée.
 * \param f Un pointeur sur la fonction à supprimer.
 */
void fonctions_conteneur::on_supprimer_fonction(base_fonction *f)
{
    supprimer_fonction(f);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'itérateur de début de liste des fonctions.
 * \return L'itérateur de début de liste des fonctions.
 */
fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_begin()
{
    return m_fonctions.begin();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'itérateur de fin de liste des fonctions.
 * \return L'itérateur de fin de liste des fonctions.
 */
fonctions_conteneur::fonctions_iterateur fonctions_conteneur::fonctions_end()
{
    return m_fonctions.end();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'itérateur constant de début de liste des fonctions.
 * \return L'itérateur constant de début de liste des fonctions.
 */
fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_begin() const
{
    return m_fonctions.constBegin();
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de l'itérateur constant de fin de liste des fonctions.
 * \return L'itérateur constant de fin de liste des fonctions.
 */
fonctions_conteneur::fonctions_const_iterateur fonctions_conteneur::fonctions_const_end() const
{
    return m_fonctions.constEnd();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la position d'une fonction donnée.
 * \param f Un pointeur sur la fonction à rechercher.
 * \return La position de la fonction recherchée. On retourne \b O si la fonction n'est pas dans le conteneur.
 */
int fonctions_conteneur::get_position(base_fonction *f)
{
    if ( m_fonctions.contains(f) )
        return m_fonctions.indexOf(f);
    else
        return 0;
}

/** --------------------------------------------------------------------------------------
 * \brief Indique si l'objet est un conteneur.
 * \return \b True.
 */
bool fonctions_conteneur::est_conteneur() const
{
    return true;
}

/** --------------------------------------------------------------------------------------
 * \brief Charge une fonction à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 * \param obj_ref Un pointeur sur l'objet_selectionnable de référence.
 * \return Un pointeur sur la fonction nouvellement créée, ou la valeur b NULL si la source xml est erronée.
 */
objet_selectionnable * fonctions_conteneur::charger_fonction( QXmlStreamReader & xml, objet_selectionnable * obj_ref )
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonction");

    xml.readNextStartElement();

    if(xml.name() == "id")
    {
        QString id = xml.readElementText();
        base_fonction * f = bibliotheque_fonctions::get_fonction( (type_id_fonction)id.toInt() );

        f->charger(xml);
        ajouter_fonction(f, obj_ref);
        return f;
    }
    else
        return NULL;
}

/** --------------------------------------------------------------------------------------
 * \brief Charge des fonctions à partir d'une source xml donnée.
 * \param xml Le flux xml d'entrée à lire.
 * \param obj_ref Un pointeur sur l'objet_selectionnable de référence.
 */
void fonctions_conteneur::charger_fonctions(QXmlStreamReader & xml, objet_selectionnable * obj_ref )
{
    Q_ASSERT(xml.isStartElement() &&
             xml.name() == "fonctions");

    while(xml.readNextStartElement())
    {
        if(xml.name() == "fonction")
        {
            obj_ref = charger_fonction(xml, obj_ref);
        }
        else
        {
            std::cout << "\t\t ignore : " << xml.name().toString().toStdString() << std::endl;
            xml.skipCurrentElement();
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde le fonctions_conteneur dans un flux donné.
 * \param stream Le flux Xml dans lequel écrire.
 */
void fonctions_conteneur::sauvegarder(QXmlStreamWriter &stream) const
{
    stream.writeStartElement("fonctions");

    for ( fonctions_const_iterateur it = m_fonctions.constBegin(); it != m_fonctions.constEnd(); ++it )
        (*it)->sauvegarder(stream);

    stream.writeEndElement(); // Fonctions
}

/** --------------------------------------------------------------------------------------
 * \brief Retire l'ensemble des fonctions du conteneur.
 */
void fonctions_conteneur::clear_fonctions()
{
    for ( fonctions_iterateur it = m_fonctions.begin(); it != m_fonctions.end(); ++it )
        delete *it;
    m_fonctions.clear();
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le nombre de fonctions actives du conteneur.
 * \return Le nombre de fonctions actives du conteneur.
 */
int fonctions_conteneur::get_nb_fonctions_actives() const
{
    int resultat = 0;

    for ( fonctions_const_iterateur it = m_fonctions.constBegin(); it != m_fonctions.constEnd(); ++it )
        if ( (*it)->est_active_avec_parent() )
            resultat++;

    return resultat;
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la première fonction active du conteneur.
 * \return Un pointeur sur la première fonction active du conteneur; on retourne la valeur \b NULL s'il n'y a aucune fonction active.
 */
const base_fonction *fonctions_conteneur::premiere_fonction_active() const
{
    for ( fonctions_const_iterateur it = m_fonctions.constBegin(); it != m_fonctions.constEnd(); ++it )
        if ( (*it)->est_active_avec_parent() )
            return *it;

    return NULL;
}
