#include "texte_edition_dialog.h"
#include "utils.h"

#include <QtGui>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QApplication>
#include <QStyle>

/*! --------------------------------------------------------------------------------------
 \file Implémentation de la classe texte_edition_dialog.
 \author Sébastien Angibaud
*/

/*! --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param parent Le parent.
*/
texte_edition_dialog::texte_edition_dialog(QWidget *parent, const old_texte& source)
    : QDialog(parent)
{
    creer_widgets();
    utils::charger_edittext(source, texte_edition);

    setWindowTitle("Edition de texte");
    setFixedSize( 800,600 );
    texte_edition->setFocus();
}

/*! --------------------------------------------------------------------------------------
 \brief Destructeur.
*/
texte_edition_dialog::~texte_edition_dialog()
{
    delete bouton_sauvegarder;
    delete bouton_charger;
    delete bouton_valider;
    delete bouton_annuler;
    delete texte_edition;
}

/*! --------------------------------------------------------------------------------------
 \brief Retourne le texte.
*/
const old_texte texte_edition_dialog::get_texte() const
{
    return m_texte;
}

/*! --------------------------------------------------------------------------------------
 \brief Valide le dialogue.
*/
void texte_edition_dialog::valider()
{
    set_texte();
    accept();
}

/*! --------------------------------------------------------------------------------------
 \brief Annule le dialogue.
*/
void texte_edition_dialog::annuler()
{
    reject();
}

/*! --------------------------------------------------------------------------------------
 \brief Initialise le texte à partir de l'edit texte.
*/
void texte_edition_dialog::set_texte()
{
    utils::charger_texte( m_texte, texte_edition );
}

/*! --------------------------------------------------------------------------------------
 \brief Crée les widgets.
*/
void texte_edition_dialog::creer_widgets()
{
    bouton_charger = new QPushButton();
    bouton_sauvegarder = new QPushButton();
    bouton_valider = new QPushButton();
    bouton_annuler = new QPushButton();
    texte_edition = new QTextEdit();

    QStyle* style = QApplication::style();
    bouton_annuler->setIcon( style->standardIcon( QStyle::SP_DialogCancelButton ) );
    bouton_valider->setIcon( style->standardIcon( QStyle::SP_DialogApplyButton ) );
    bouton_charger->setIcon( style->standardIcon( QStyle::SP_DialogOpenButton ) );
    bouton_sauvegarder->setIcon( style->standardIcon( QStyle::SP_DialogSaveButton ) );

    texte_edition->setMaximumHeight(1000);
    texte_edition->setMaximumWidth(1000);
    bouton_charger->setMaximumHeight(1000);
    bouton_sauvegarder->setMaximumHeight(1000);
    bouton_valider->setMaximumHeight(1000);
    bouton_annuler->setMaximumHeight(1000);

    connect(bouton_valider, SIGNAL(clicked()),this, SLOT(valider()));
    connect(bouton_annuler, SIGNAL(clicked()),this, SLOT(annuler()));

    QHBoxLayout *topLayout = new QHBoxLayout;
    topLayout->addWidget(bouton_charger);
    topLayout->addWidget(bouton_sauvegarder);

    QHBoxLayout *bottomLayout = new QHBoxLayout;
    bottomLayout->addWidget(bouton_valider);
    bottomLayout->addWidget(bouton_annuler);

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(topLayout,1);
    mainLayout->addWidget(texte_edition,10);
    mainLayout->addLayout(bottomLayout,1);
    setLayout(mainLayout);
}
