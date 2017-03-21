/** \file fonction_source_dictionnaire_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_dictionnaire_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_source_widget/fonction_source_dictionnaire_widget.h"

#include "entete/fonction/fonction_source/fonction_source_dictionnaire.h"
#include "entete/projet/projet.h"

#include <QApplication>
#include <QFile>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QStyle>
#include <QTextStream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_dictionnaire_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_source_dictionnaire_widget::fonction_source_dictionnaire_widget(base_fonction *fonction, QWidget *parent)
    : super(fonction, parent)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le composant.
 */
void fonction_source_dictionnaire_widget::init()
{
    QStyle* style = QApplication::style();
    QHBoxLayout * lay = new QHBoxLayout();
    lay->setSpacing(0);
    lay->setSizeConstraint(QLayout::SetFixedSize);

    m_choix_bouton = new QPushButton();
    m_choix_bouton->setObjectName("ChoixOuvertureFichier");
    m_choix_bouton->setIcon(style->standardIcon( QStyle::SP_FileLinkIcon ));
    m_choix_bouton->setFixedSize(QSize(30,30));
    m_choix_bouton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_choix_bouton);

    m_nom_fichier_label = new QLabel();
    m_nom_fichier_label->setObjectName("NomFichier");
    m_nom_fichier_label->setText( ((fonction_source_dictionnaire*)m_fonction)->get_chemin_relatif() );
    lay->addWidget(m_nom_fichier_label);

    connect( m_choix_bouton, SIGNAL(released()), this, SLOT(on_choisir_click()));
    m_specialisation_layout->addLayout(lay);
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour l'ensemble des boutons.
 */
void fonction_source_dictionnaire_widget::update_boutons()
{
    if ( m_fonction != NULL )
        m_choix_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    else
        m_choix_bouton->setEnabled( false );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de verrouillage de la fonction associée change.
 */
void fonction_source_dictionnaire_widget::informer_verrouillage_change()
{
    update_boutons();
}

/** --------------------------------------------------------------------------------------
 * \brief Choisi un nom de fichier.
 */
void fonction_source_dictionnaire_widget::choisir_nom_fichier()
{
    QString dir = "mes_projets";
    if ( ! m_fonction->get_projet()->est_nouveau() )
        dir = m_fonction->get_projet()->get_dossier();

    QString nom_fichier =
            QFileDialog::getOpenFileName( this, tr("Ouvrir un fichier textuel"),
                                          dir, tr("Texte (*.txt);;Autres fichiers (*))"));

    if ( nom_fichier.isEmpty() || nom_fichier.compare( m_nom_fichier_label->text() ) == 0 )
        return;

    QFile file(nom_fichier);

    if (! file.open(QIODevice::ReadOnly))
        return;

    ((fonction_source_dictionnaire*)m_fonction)->set_nom_fichier( nom_fichier );
    m_nom_fichier_label->setText( ((fonction_source_dictionnaire*)m_fonction)->get_chemin_relatif() );

    update_boutons();
    m_fonction->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de choix de nom de fichier.
 */
void fonction_source_dictionnaire_widget::on_choisir_click()
{
    choisir_nom_fichier();
}

