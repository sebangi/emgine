#include "entete/fonction_widget/fonction_source_widget/fonction_source_fichier_texte_widget.h"

#include "entete/fonction/fonction_source/fonction_source_fichier_texte.h"
#include "entete/projet/projet.h"
#include <iostream>
#include <QHBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QStyle>
#include <QApplication>

fonction_source_fichier_texte_widget::fonction_source_fichier_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

void fonction_source_fichier_texte_widget::init()
{
    QStyle* style = QApplication::style();
    QHBoxLayout * lay = new QHBoxLayout();
    lay->setSpacing(0);
    lay->setSizeConstraint(QLayout::SetFixedSize);

    m_nom_fichier_label = new QLabel();
    m_nom_fichier_label->setObjectName("NomFichier");
    m_nom_fichier_label->setText( ((fonction_source_fichier_texte*)m_fonction)->get_nom_fichier() );

    m_choix_bouton = new QPushButton();
    m_choix_bouton->setObjectName("ChoixOuvertureFichier");
    m_choix_bouton->setIcon(style->standardIcon( QStyle::SP_FileDialogDetailedView ));
    m_choix_bouton->setMaximumWidth(50);
    m_choix_bouton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_choix_bouton);
    lay->addWidget(m_nom_fichier_label);

    connect( m_choix_bouton, SIGNAL(released()), this, SLOT(on_choisir_click()));
    m_specialisation_layout->addLayout(lay);
    informer_verrouillage_change();
}

void fonction_source_fichier_texte_widget::on_choisir_click()
{
    choisir_nom_fichier();
}

void fonction_source_fichier_texte_widget::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
        m_choix_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    else
        m_choix_bouton->setEnabled( false );
}

void fonction_source_fichier_texte_widget::choisir_nom_fichier()
{
    QString dir = "mes_projets";
    if ( ! m_fonction->get_projet()->est_nouveau() )
        dir = m_fonction->get_projet()->get_dossier();

    QString nom_fichier =
            QFileDialog::getOpenFileName( this, tr("Ouvrir un projet Decode"),
                                          dir, tr("Texte (*.txt);;Autres fichiers (*))"));

    if ( nom_fichier.isEmpty() || nom_fichier.compare( m_nom_fichier_label->text() ) == 0 )
        return;

    QFile file(nom_fichier);

    if (! file.open(QIODevice::ReadOnly))
        return;

    m_nom_fichier_label->setText( nom_fichier );
    ((fonction_source_fichier_texte*)m_fonction)->set_nom_fichier( nom_fichier );
    m_fonction->modifier();
}

