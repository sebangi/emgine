/** \file parametre_aide_message_box.cpp
 * \brief Fichier d'implémentation de la classe parametre_aide_message_box.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/parametre_aide_message_box.h"

#include "entete/projet/base_fonction.h"
#include "entete/projet/base_parametre.h"

#include <QLabel>
#include <QListWidget>
#include <QVBoxLayout>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe parametre_aide_message_box.
 * \param parent Un pointeur sur le widget parent.
 * \param parametre Un pointeur sur le paramètre dont il faut afficher l'aide.
 */
parametre_aide_message_box::parametre_aide_message_box(QWidget *parent, const base_parametre* parametre)
    : QDialog(parent), m_parametre( parametre )
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void parametre_aide_message_box::init()
{
    setWindowTitle("Fonction " + m_parametre->get_fonction_parent()->get_nom());

    QVBoxLayout * central_layout = new QVBoxLayout();
    central_layout->setMargin(5);
    central_layout->setSpacing(0);

    QLabel * item_nom = new QLabel("Paramètre " + m_parametre->get_nom());
    item_nom->setObjectName( "AideNomParametre" );
    central_layout->addWidget( item_nom );

    QLabel * item_aide = new QLabel(m_parametre->get_aide());
    item_aide->setObjectName( "AideParametre" );
    central_layout->addWidget( item_aide );

    QLabel * item_algo = new QLabel("Algorithme : " + m_parametre->get_aide_algorithme());
    item_algo->setObjectName( "AideAlgoParametre" );
    central_layout->addWidget( item_algo );

    setLayout( central_layout );
    resize(QSize(800,200));
}
