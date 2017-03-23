/** \file noeud_parametre.cpp
 * \brief Fichier d'implémentation de la classe noeud_parametre.
 * \author Sébastien Angibaud
 */
#include "entete/explorateur/noeud_parametre.h"

#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/fenetre_principale.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/base_parametre.h"
#include "entete/projet/objet_selectionnable.h"

#include <QApplication>
#include <QFont>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe noeud_parametre.
 * \param p Un pointeur sur le paramètre associé au noeud.
 */
noeud_parametre::noeud_parametre( base_parametre * p )
    : base_noeud( (objet_selectionnable *)p, base_noeud::TYPE_NOEUD_PARAMETRE )
{
    setFlags(Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDropEnabled );

    setText(0, p->get_nom());
    QFont font = this->font(0);
    font.setItalic(true);
    setFont(0, font);

    mise_a_jour_icone();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe noeud_parametre.
 */
noeud_parametre::~noeud_parametre()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Retourne le paramètre associé au noeud.
 * \return Un pointeur sur le paramètre associé au noeud.
 */
base_parametre* noeud_parametre::get_parametre() const
{
    return (base_parametre*)m_objet;
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction mettant à jour l'icône.
 */
void noeud_parametre::mise_a_jour_icone()
{
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/parameters.png"), QSize(), QIcon::Normal, QIcon::Off);
    setIcon( 0, icon1 );
}


