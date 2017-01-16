#include "entete/compilation/compilateur.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/explorateur/base_noeud.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/fonction_conversion/fonction_cesar.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/fonction_widget/vue_fonctions.h"
#include "entete/projet/projet.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/fonction_widget/selecteur_fonction_dialog.h"
#include "entete/ui_fenetre_principale.h"

#include <iostream>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QString>
#include <QtGui>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QFileDialog>
#include <QMessageBox>
#include <string>
#include <vector>

/** --------------------------------------------------------------------------------------
 \file Implémentation de la classe fenetre_principale.
 \author Sébastien Angibaud
*/
explorateur * fenetre_principale::s_explorateur = NULL;
vue_fonctions * fenetre_principale::s_vue_fonctions = NULL;
compilateur * fenetre_principale::s_compilateur = NULL;
logs_compilation_widget * fenetre_principale::s_vue_logs = NULL;
fenetre_principale::type_projets fenetre_principale::s_projets = fenetre_principale::type_projets();

/** --------------------------------------------------------------------------------------
 \brief Constructeur.
 \param parent Le widget parent.
*/
fenetre_principale::fenetre_principale(QWidget *parent) :
    QMainWindow(parent), m_ui(new Ui::fenetre_principale)
{
    m_ui->setupUi(this);
    m_style = QApplication::style();

    creer_toolbar();
    creer_widgets();
    init_widgets();
    resize(QSize(1000,900));

    init_test();
}

/** --------------------------------------------------------------------------------------
 \brief Destructeur.
*/
fenetre_principale::~fenetre_principale()
{
    for ( projets_iterateur it = s_projets.begin(); it != s_projets.end(); ++it )
        delete *it;
    s_projets.clear();

    delete m_ui;
    delete s_compilateur;
    s_compilateur = NULL;
}

/** --------------------------------------------------------------------------------------
 \brief Création de la barre d'outils.
*/
void fenetre_principale::creer_toolbar()
{
    addToolBar(Qt::LeftToolBarArea, m_ui->mainToolBar);

    m_toolbar_bouton_nouveau_projet = new QPushButton();
    m_toolbar_bouton_sauvegarder_projet = new QPushButton();
    m_toolbar_bouton_sauvegarder_projet_sous = new QPushButton();
    m_toolbar_bouton_ouvrir_projet = new QPushButton();
    m_toolbar_bouton_ajout_fonction_source = new QPushButton();
    m_toolbar_bouton_ajout_fonction_conversion = new QPushButton();
    m_toolbar_bouton_ajout_fonction_sortie = new QPushButton();
    m_toolbar_bouton_compiler = new QPushButton();

    m_toolbar_bouton_nouveau_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet_sous->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ouvrir_projet->setObjectName("ButtonToolBar");

    m_toolbar_bouton_ajout_fonction_source->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_conversion->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_sortie->setObjectName("ButtonToolBar");

    m_toolbar_bouton_compiler->setObjectName("ButtonToolBar");

    m_ui->mainToolBar->addWidget(m_toolbar_bouton_nouveau_projet);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_ouvrir_projet);
    m_ui->mainToolBar->addSeparator();
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_sauvegarder_projet);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_sauvegarder_projet_sous);
    m_ui->mainToolBar->addSeparator();
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_ajout_fonction_source);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_ajout_fonction_conversion);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_ajout_fonction_sortie);
    m_ui->mainToolBar->addSeparator();

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ui->mainToolBar->addWidget(spacer);

    m_ui->mainToolBar->addSeparator();
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_compiler);
}

/** --------------------------------------------------------------------------------------
 \brief Création des différents widgets.
*/
void fenetre_principale::creer_widgets()
{
    s_explorateur = new explorateur(this);
    s_vue_fonctions = new vue_fonctions(this);
    s_vue_logs = new logs_compilation_widget(this);
    s_compilateur = new compilateur(s_vue_logs);

    connect( s_explorateur, SIGNAL(signal_e_ajout_source(fonctions_conteneur *, base_fonction::type_fonction)),
             this, SLOT(on_externe_e_ajout_source(fonctions_conteneur *, base_fonction::type_fonction)));
    connect( s_explorateur, SIGNAL(signal_e_objet_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable *)));
    connect( s_explorateur, SIGNAL(signal_e_objet_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable *)));
}

/** --------------------------------------------------------------------------------------
 \brief Initialise les différents widgets.
*/
void fenetre_principale::init_widgets()
{
    QStyle* style = QApplication::style();
    setWindowTitle("Emgine");

    QIcon icone_source;
    icone_source.addFile(QString::fromUtf8("icons/ajout_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_source->setIcon(icone_source);
    m_toolbar_bouton_ajout_fonction_source->setText("Source");

    QIcon icone_conversion;
    icone_conversion.addFile(QString::fromUtf8("icons/ajout_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_conversion->setIcon(icone_conversion);
    m_toolbar_bouton_ajout_fonction_conversion->setText("Conversion");

    QIcon icone_sortie;
    icone_sortie.addFile(QString::fromUtf8("icons/ajout_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_sortie->setIcon(icone_sortie);
    m_toolbar_bouton_ajout_fonction_sortie->setText("Sortie");

    m_toolbar_bouton_nouveau_projet->setIcon(style->standardIcon( QStyle::SP_FileDialogNewFolder ));
    m_toolbar_bouton_nouveau_projet->setText("Nouveau projet");

    m_toolbar_bouton_ouvrir_projet->setIcon(style->standardIcon( QStyle::SP_DialogOpenButton ));
    m_toolbar_bouton_ouvrir_projet->setText("Ouvrir");

    m_toolbar_bouton_sauvegarder_projet->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet->setText("Enregistrer");
    m_toolbar_bouton_sauvegarder_projet_sous->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet_sous->setText("Enregistrer sous");

    connect( m_toolbar_bouton_ajout_fonction_source, SIGNAL(released()), this, SLOT(on_ajouter_fonction_source_click()));
    connect( m_toolbar_bouton_ajout_fonction_conversion, SIGNAL(released()), this, SLOT(on_ajouter_fonction_conversion_click()));
    connect( m_toolbar_bouton_ajout_fonction_sortie, SIGNAL(released()), this, SLOT(on_ajouter_fonction_sortie_click()));
    connect( m_toolbar_bouton_nouveau_projet, SIGNAL(released()), this, SLOT(on_nouveau_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet, SIGNAL(released()), this, SLOT(on_sauvegarder_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet_sous, SIGNAL(released()), this, SLOT(on_sauvegarder_projet_sous_click()));
    connect( m_toolbar_bouton_ouvrir_projet, SIGNAL(released()), this, SLOT(on_ouvrir_projet_click()));
    connect( m_toolbar_bouton_compiler, SIGNAL(released()), this, SLOT(on_compiler_click()));

    QWidget * top_widget = new QWidget(this);
    QHBoxLayout * hor_lay = new QHBoxLayout();
    hor_lay->setMargin(0);
    hor_lay->setSpacing(0);
    hor_lay->addWidget(s_explorateur,1);
    hor_lay->addWidget(s_vue_fonctions,2);
    top_widget->setLayout(hor_lay);

    m_ui->centralLayout->setMargin(0);
    m_ui->centralLayout->setSpacing(0);

    m_ui->centralLayout->addWidget(top_widget,5);
    m_ui->centralLayout->addWidget(s_vue_logs, 1);

    QIcon icon_compile;
    icon_compile.addFile(QString::fromUtf8("icons/grand_compile.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_compiler->setIcon(icon_compile);
    m_toolbar_bouton_compiler->setText("Exécuter");
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une source au projet courant.
*/
void fenetre_principale::ajouter_source()
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_conteneur_courant(), base_fonction::fonction_source);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction de conversion au projet courant.
*/
void fenetre_principale::ajouter_conversion( )
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_conteneur_courant(), base_fonction::fonction_conversion);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une sortie au projet courant.
*/
void fenetre_principale::ajouter_sortie( )
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_conteneur_courant(), base_fonction::fonction_sortie);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, base_fonction::type_fonction type )
{
    if ( conteneur != NULL )
    {
        selecteur_fonction_dialog * dlg = new selecteur_fonction_dialog(type, m_ui->centralWidget);

        int r = dlg->exec();

        if ( r == QDialog::Accepted )
        {
            base_fonction * f = dlg->get_fonction();

            if ( f != NULL )
                ajouter_fonction(conteneur, f, true, true);
        }
    }
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, base_fonction* f, bool init_defaut, bool afficher_vue )
{
    if ( init_defaut )
        f->initialisation_par_defaut();

    conteneur->ajouter_fonction(f);
    f->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Jeu de test.
*/
void fenetre_principale::init_test()
{
    projet * p  = new projet();
    p->set_nom("Exemple");
    ajouter_projet(p);

    ajouter_fonction( p, new fonction_source_texte(p, "UNHBH TM SDRS !"), true, true );
    ajouter_fonction( p, new fonction_cesar(p), true, true );
    ajouter_fonction( p, new fonction_sortie_texte(p), true, true );

    p->selectionner();
}


/** --------------------------------------------------------------------------------------
 \brief Ajoute un nouveau projet.
*/
void fenetre_principale::ajouter_projet( projet * p )
{
    s_projets.push_back( p );
    s_explorateur->ajouter_projet(p);
    s_vue_fonctions->ajouter_projet(p);

    p->selectionner();

    connect( p, SIGNAL(signal_p_projet_etat_modification_change(projet *, bool)),
             this, SLOT(on_externe_projet_etat_modification_change(projet *, bool)));
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet.
*/
void fenetre_principale::sauvegarder_projet(projet* p)
{
    if ( p != NULL )
    {
        if ( p->est_nouveau() )
            sauvegarder_projet_sous( p );
        else
            sauvegarder_projet( p->get_nom_fichier(), p );
    }
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet sous.
*/
void fenetre_principale::sauvegarder_projet_sous(projet * p)
{
    QFileDialog d(this);
    d.setDefaultSuffix("dec");
    QString nom_fichier = d.getSaveFileName( this,
                                             tr("Sauvegarder le projet"), "mes_projets",
                                             tr("projet Decode (*.dec);;"));

    if (nom_fichier.isEmpty())
        return;
    else
    {
        if (!nom_fichier.endsWith(".dec"))
            nom_fichier += ".dec";

        sauvegarder_projet(nom_fichier, p);
    }
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet.
*/
void fenetre_principale::sauvegarder_projet(const QString & nom_fichier, projet * p)
{
    QFile file(nom_fichier);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Impossible d'ouvrir le fichier."),
                                 file.errorString());
        return;
    }

    p->set_nom_fichier(nom_fichier);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    p->sauvegarder( stream );
    stream.writeEndDocument();
}

/** --------------------------------------------------------------------------------------
 \brief Ouvrir un projet.
*/
void fenetre_principale::ouvrir_projet()
{
    QString nom_fichier =
            QFileDialog::getOpenFileName( this, tr("Ouvrir un projet Decode"),
                                          "mes_projets", tr("projet Decode (*.dec);;"));

    if (nom_fichier.isEmpty())
        return;

    projet* existant = NULL;
    existant = s_explorateur->get_projet_selon_nom_fichier(nom_fichier);

    if ( existant != NULL )
        existant->selectionner();
    else
    {
        QFile file(nom_fichier);

        if (! file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier."), file.errorString());
            return;
        }

        projet * p = new projet();
        QXmlStreamReader xml(&file);
        xml.readNextStartElement();

        if( xml.name() == "projet" )
        {
            p->set_nom_fichier(nom_fichier);
            p->charger(xml);
        }
        else
            xml.skipCurrentElement();

        ajouter_projet(p);
    }
}

/** --------------------------------------------------------------------------------------
 \brief Compiler le projet.
*/
void fenetre_principale::compiler(projet* p)
{
    if ( p != NULL )
    {
        s_compilateur->compiler( p );
        p->selectionner();
        s_vue_fonctions->scrollToBottom();
    }
}

void fenetre_principale::update_boutons_projet( projet * p )
{
    if ( p != NULL )
    {
        m_toolbar_bouton_sauvegarder_projet->setEnabled( ! p->est_nouveau() && p->est_modifie() );
        m_toolbar_bouton_sauvegarder_projet_sous->setEnabled( true );
    }
    else
    {
        m_toolbar_bouton_sauvegarder_projet->setEnabled( false );
        m_toolbar_bouton_sauvegarder_projet_sous->setEnabled( false );
    }
}

void fenetre_principale::update_boutons_fonctions( objet_selectionnable * obj, bool etat )
{
    if ( obj != NULL )
        etat = etat && obj->est_conteneur();

    m_toolbar_bouton_ajout_fonction_source->setEnabled( etat );
    m_toolbar_bouton_ajout_fonction_conversion->setEnabled( etat );
    m_toolbar_bouton_ajout_fonction_sortie->setEnabled( etat );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_source est activé.
*/
void fenetre_principale::on_ajouter_fonction_source_click()
{
    ajouter_source();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_conversion est activé.
*/
void fenetre_principale::on_ajouter_fonction_conversion_click()
{
    ajouter_conversion();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_sortie est activé.
*/
void fenetre_principale::on_ajouter_fonction_sortie_click()
{
    ajouter_sortie();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_nouveau_projet est activé.
*/
void fenetre_principale::on_nouveau_projet_click()
{
    projet * p = new projet();
    ajouter_projet(p);
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton sauvegarder_projet est activé.
*/
void fenetre_principale::on_sauvegarder_projet_click()
{
    if ( objet_selectionnable::existe_selection() )
        sauvegarder_projet( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton sauvegarder_projet_sous est activé.
*/
void fenetre_principale::on_sauvegarder_projet_sous_click()
{
    if ( objet_selectionnable::existe_selection() )
        sauvegarder_projet_sous( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ouvrir_projet est activé.
*/
void fenetre_principale::on_ouvrir_projet_click()
{
    ouvrir_projet();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton compiler est activé.
*/
void fenetre_principale::on_compiler_click()
{
    if ( objet_selectionnable::existe_selection() )
        compiler( objet_selectionnable::get_projet_courant() );
}

void fenetre_principale::on_externe_e_ajout_source(fonctions_conteneur *conteneur, base_fonction::type_fonction type)
{
    ajouter_fonction(conteneur, type);
}

void fenetre_principale::on_externe_projet_etat_modification_change(projet *p, bool etat)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_projet_courant() == p )
            update_boutons_projet( p );
}


void fenetre_principale::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    update_boutons_fonctions(obj, true);
    update_boutons_projet(obj->get_projet());
}

void fenetre_principale::on_externe_objet_deselectionne(objet_selectionnable *obj)
{
    update_boutons_fonctions(obj, false);
}
