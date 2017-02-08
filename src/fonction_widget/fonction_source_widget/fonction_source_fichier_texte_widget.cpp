#include "entete/fonction_widget/fonction_source_widget/fonction_source_fichier_texte_widget.h"

#include "entete/fonction/fonction_source/fonction_source_fichier_texte.h"
#include "entete/projet/projet.h"
#include <iostream>
#include <QHBoxLayout>
#include <QFile>
#include <QFileDialog>
#include <QTextStream>
#include <QStyle>
#include <QApplication>
#include <QMessageBox>

fonction_source_fichier_texte_widget::fonction_source_fichier_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget_avec_text_edit(fonction, parent), m_modifie(false), m_choisi(false), m_charge(false)
{
    init();
}

void fonction_source_fichier_texte_widget::init()
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
    m_nom_fichier_label->setText( ((fonction_source_fichier_texte*)m_fonction)->get_nom_fichier() );
    lay->addWidget(m_nom_fichier_label);

    m_charger_bouton = new QPushButton();
    m_charger_bouton->setObjectName("BoutonSourceFichier");
    m_charger_bouton->setIcon(style->standardIcon( QStyle::SP_BrowserReload ));
    m_charger_bouton->setFixedSize(QSize(30,30));
    m_charger_bouton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_charger_bouton);

    m_sauvegarder_bouton = new QPushButton();
    m_sauvegarder_bouton->setObjectName("BoutonSourceFichier");
    m_sauvegarder_bouton->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_sauvegarder_bouton->setFixedSize(QSize(30,30));
    m_sauvegarder_bouton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    lay->addWidget(m_sauvegarder_bouton);

    connect( m_choix_bouton, SIGNAL(released()), this, SLOT(on_choisir_click()));
    connect( m_charger_bouton, SIGNAL(released()), this, SLOT(on_charger_click()));
    connect( m_sauvegarder_bouton, SIGNAL(released()), this, SLOT(on_sauvegarder_click()));
    m_specialisation_layout->addLayout(lay);

    m_choisi = ! m_nom_fichier_label->text().isEmpty();

    super::init();

    m_text_edit->setVisible(false);
}

void fonction_source_fichier_texte_widget::update_boutons()
{
    if ( m_fonction != NULL )
    {
        m_choix_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
        m_charger_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() && m_choisi );
        m_sauvegarder_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() && m_modifie );
        m_text_edit->setEnabled( ! m_fonction->est_verrouille_avec_parent() && m_charge );
    }
    else
    {
        m_choix_bouton->setEnabled( false );
        m_charger_bouton->setEnabled( false );
        m_sauvegarder_bouton->setEnabled( false );
        m_text_edit->setEnabled( false );
    }

    if ( m_modifie )
        m_sauvegarder_bouton->setObjectName("BoutonSourceFichierSauvegarderModifie");
    else if ( ! m_modifie && m_charge )
        m_sauvegarder_bouton->setObjectName("BoutonSourceFichierSauvegarderOk");
    else
        m_sauvegarder_bouton->setObjectName("BoutonSourceFichier");

    style()->unpolish(m_sauvegarder_bouton);
    style()->polish(m_sauvegarder_bouton);
}

void fonction_source_fichier_texte_widget::informer_verrouillage_change()
{
    update_boutons();
}

void fonction_source_fichier_texte_widget::choisir_nom_fichier()
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

    m_choisi = true;
    m_nom_fichier_label->setText( nom_fichier );
    ((fonction_source_fichier_texte*)m_fonction)->set_nom_fichier( nom_fichier );
    update_boutons();
    m_fonction->modifier();
}

void fonction_source_fichier_texte_widget::charger_fichier()
{
    QFile file(((fonction_source_fichier_texte*)m_fonction)->get_nom_fichier());
    if (! file.open(QIODevice::ReadOnly))
        return;

    QTextStream in(&file);
    m_text_edit->setVisible(true);
    m_text_edit->setPlainText( in.readAll() );
    m_modifie = false;
    file.close();

    m_charge = true;
    update_boutons();
}

void fonction_source_fichier_texte_widget::sauvegarder_fichier()
{
    QFile file(((fonction_source_fichier_texte*)m_fonction)->get_nom_fichier());

    if (! file.open(QIODevice::WriteOnly  | QIODevice::Text)) {
        QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                                 file.errorString());
        return;
    }

    QTextStream out(&file);
    out << m_text_edit->toPlainText();
    file.close();

    m_modifie = false;
    update_boutons();
}

void fonction_source_fichier_texte_widget::on_nouveau_texte()
{
    m_modifie = true;
    update_boutons();
}

QString fonction_source_fichier_texte_widget::chercher_valeur() const
{
    // return ((fonction_source_fichier_texte*)m_fonction)->get_valeur();
    return QString();
}

void fonction_source_fichier_texte_widget::on_choisir_click()
{
    choisir_nom_fichier();
}

void fonction_source_fichier_texte_widget::on_charger_click()
{
    charger_fichier();
}

void fonction_source_fichier_texte_widget::on_sauvegarder_click()
{
    sauvegarder_fichier();
}

