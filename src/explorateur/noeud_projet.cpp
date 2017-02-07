/** \file noeud_projet.cpp
 * \brief Fichier d'implémentation de la classe noeud_projet.
 * \author Sébastien Angibaud
 */

#include "entete/explorateur/noeud_projet.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/fenetre_principale.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/objet_selectionnable.h"
#include "entete/projet/projet.h"

#include <QApplication>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe noeud_projet.
 * \param p Un pointeur sur le projet associé au noeud.
 */
noeud_projet::noeud_projet( projet * p )
    : noeud_fonctions_conteneur( (fonctions_conteneur*)p, base_noeud::TYPE_NOEUD_PROJET )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );
    setText(0, p->get_nom());

    mise_a_jour_icone();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe noeud_projet.
 */
noeud_projet::~noeud_projet()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le projet associé au noeud.
 * \return Un pointeur sur le projet associé au noeud.
 */
projet* noeud_projet::get_projet() const
{
    return (projet*)m_objet;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction mettant à jour l'icône.
 */
void noeud_projet::mise_a_jour_icone()
{
    QIcon icon1;
    if ( m_objet->est_verrouille() )
        icon1.addFile(QString::fromUtf8("icons/projet_verrouille.png"), QSize(), QIcon::Normal, QIcon::Off);
    else
        icon1.addFile(QString::fromUtf8("icons/projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}
