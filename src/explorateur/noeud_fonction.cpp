#include "entete/explorateur/noeud_fonction.h"

/** \file noeud_fonction.cpp
 * \brief Fichier d'implémentation de la classe noeud_fonction.
 * \author Sébastien Angibaud
 */

#include "entete/compilation/logs_compilation_widget.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/fonction_source/fonction_base_source.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/objet_selectionnable.h"

#include <QApplication>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe neoud_fonction.
 * \param f Un pointeur sur la fonction associée.
 */
noeud_fonction::noeud_fonction( base_fonction * f )
    : base_noeud( (objet_selectionnable *)f, base_noeud::TYPE_NOEUD_FONCTION )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled );
    setText(0, f->get_nom());

    mise_a_jour_icone();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe noeud_foonction.
 */
noeud_fonction::~noeud_fonction()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne la fonction associée au noeud.
 * \return Un pointeur sur la fonction associée au noeud.
 */
base_fonction* noeud_fonction::get_fonction() const
{
    return (base_fonction *)m_objet;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction mettant à jour l'icone.
 */
void noeud_fonction::mise_a_jour_icone()
{
    QIcon icon1;
    QString fichier = ":/icons/icone_";

    if ( ((base_fonction *)m_objet)->get_type() == type_fonction::fonction_source )
        fichier += QObject::tr("source");
    else if ( ((base_fonction *)m_objet)->get_type() == type_fonction::fonction_conversion )
        fichier += QObject::tr("conversion");
    else if ( ((base_fonction *)m_objet)->get_type() == type_fonction::fonction_sortie )
        fichier += QObject::tr("sortie");

    if ( m_objet->est_verrouille_avec_parent() )
        fichier += "_" + QObject::tr("verrouille");

    fichier += ".png";
    icon1.addFile(fichier, QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}



