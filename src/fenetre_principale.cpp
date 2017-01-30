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
    m_ui->menuBar->hide();
    m_style = QApplication::style();

    creer_toolbar();
    creer_widgets();
    init_widgets();

    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/emgine.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon1);
    resize(QSize(1200,900));

    init_test();
}

/** --------------------------------------------------------------------------------------
 \brief Destructeur.
*/
fenetre_principale::~fenetre_principale()
{
    deconnecter();
    for ( projets_iterateur it = s_projets.begin(); it != s_projets.end(); ++it )
        delete *it;
    s_projets.clear();

    delete s_compilateur;
    s_compilateur = NULL;
    delete m_ui;
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
    m_toolbar_bouton_executer = new QPushButton();

    m_toolbar_bouton_nouveau_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet_sous->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ouvrir_projet->setObjectName("ButtonToolBar");

    m_toolbar_bouton_ajout_fonction_source->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_conversion->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_sortie->setObjectName("ButtonToolBar");

    m_toolbar_bouton_executer->setObjectName("ButtonToolBar");

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

    /*
    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ui->mainToolBar->addWidget(spacer);
    */

    //m_ui->mainToolBar->addSeparator();
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_executer);
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

    connect( s_explorateur, SIGNAL(signal_e_demande_ajout_fonction(fonctions_conteneur *, objet_selectionnable*, base_fonction::type_fonction)),
             this, SLOT(on_externe_e_demande_ajout_fonction(fonctions_conteneur *, objet_selectionnable*, base_fonction::type_fonction)));
    connect( s_explorateur, SIGNAL(signal_e_objet_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable *)));
    connect( s_explorateur, SIGNAL(signal_e_objet_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable *)));
    connect( s_explorateur, SIGNAL(signal_e_enregistrer_projet(projet *)),
             this, SLOT(enregistrer_projet(projet *)));
    connect( s_explorateur, SIGNAL(signal_e_enregistrer_projet_sous(projet *)),
             this, SLOT(enregistrer_projet_sous(projet *)));
    connect( s_explorateur, SIGNAL(signal_e_dupliquer_projet(projet *)),
             this, SLOT(on_externe_dupliquer_projet(projet *)));
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
    m_toolbar_bouton_ajout_fonction_source->setShortcut( QKeySequence("Alt+A") );

    QIcon icone_conversion;
    icone_conversion.addFile(QString::fromUtf8("icons/ajout_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_conversion->setIcon(icone_conversion);
    m_toolbar_bouton_ajout_fonction_conversion->setText("Conversion");
    m_toolbar_bouton_ajout_fonction_conversion->setShortcut( QKeySequence("Alt+Z") );

    QIcon icone_sortie;
    icone_sortie.addFile(QString::fromUtf8("icons/ajout_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_sortie->setIcon(icone_sortie);
    m_toolbar_bouton_ajout_fonction_sortie->setText("Résultat");
    m_toolbar_bouton_ajout_fonction_sortie->setShortcut( QKeySequence("Alt+E") );

    QIcon icone_nouveau_projet;
    icone_nouveau_projet.addFile(QString::fromUtf8("icons/nouveau_projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_nouveau_projet->setIcon(icone_nouveau_projet);
    m_toolbar_bouton_nouveau_projet->setText("Nouveau projet");

    QIcon icone_projet;
    icone_projet.addFile(QString::fromUtf8("icons/projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ouvrir_projet->setIcon(icone_projet);
    m_toolbar_bouton_ouvrir_projet->setText("Ouvrir un projet");

    m_toolbar_bouton_sauvegarder_projet->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet->setText("Enregistrer");
    m_toolbar_bouton_sauvegarder_projet->setShortcut( QKeySequence("Ctrl+S") );
    m_toolbar_bouton_sauvegarder_projet_sous->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet_sous->setText("Enregistrer sous");

    connect( m_toolbar_bouton_ajout_fonction_source, SIGNAL(released()), this, SLOT(on_ajouter_fonction_source_click()));
    connect( m_toolbar_bouton_ajout_fonction_conversion, SIGNAL(released()), this, SLOT(on_ajouter_fonction_conversion_click()));
    connect( m_toolbar_bouton_ajout_fonction_sortie, SIGNAL(released()), this, SLOT(on_ajouter_fonction_sortie_click()));
    connect( m_toolbar_bouton_nouveau_projet, SIGNAL(released()), this, SLOT(on_nouveau_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet, SIGNAL(released()), this, SLOT(on_enregistrer_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet_sous, SIGNAL(released()), this, SLOT(on_enregistrer_projet_sous_click()));
    connect( m_toolbar_bouton_ouvrir_projet, SIGNAL(released()), this, SLOT(on_ouvrir_projet_click()));
    connect( m_toolbar_bouton_executer, SIGNAL(released()), this, SLOT(on_executer_click()));

    QWidget * top_widget = new QWidget(this);
    QHBoxLayout * hor_lay = new QHBoxLayout();
    hor_lay->setMargin(0);
    hor_lay->setSpacing(0);
    hor_lay->addWidget(s_explorateur,1);
    hor_lay->addWidget(s_vue_fonctions,3);
    top_widget->setLayout(hor_lay);

    m_ui->centralLayout->setMargin(0);
    m_ui->centralLayout->setSpacing(0);

    m_ui->centralLayout->addWidget(top_widget,5);
    m_ui->centralLayout->addWidget(s_vue_logs, 1);

    QIcon icon_compile;
    icon_compile.addFile(QString::fromUtf8("icons/grand_compile.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_executer->setIcon(icon_compile);
    m_toolbar_bouton_executer->setText("Exécuter");
    m_toolbar_bouton_executer->setShortcut( QKeySequence("Ctrl+R") );
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une source au projet courant.
*/
void fenetre_principale::ajouter_source()
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(), base_fonction::fonction_source);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction de conversion au projet courant.
*/
void fenetre_principale::ajouter_conversion( )
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(), base_fonction::fonction_conversion);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une sortie au projet courant.
*/
void fenetre_principale::ajouter_sortie( )
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(), base_fonction::fonction_sortie);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, base_fonction::type_fonction type )
{
    if ( conteneur != NULL )
    {
        selecteur_fonction_dialog * dlg = new selecteur_fonction_dialog(type, m_ui->centralWidget);

        int r = dlg->exec();

        if ( r == QDialog::Accepted )
        {
            base_fonction * f = dlg->get_fonction();
            f->set_conteneur(conteneur);

            if ( f != NULL )
                ajouter_fonction(conteneur, obj_ref, f, true, true);
        }
    }
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, base_fonction* f, bool init_defaut, bool afficher_vue )
{
    if ( init_defaut )
        f->initialisation_par_defaut();

    conteneur->ajouter_fonction(f,obj_ref);
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

    ajouter_fonction( p, NULL, new fonction_source_texte(p, "UNHBH TM SDRS !\nunhbh tm sdrs !"), true, true );
    ajouter_fonction( p, NULL, new fonction_cesar(p), true, true );
    ajouter_fonction( p, NULL, new fonction_sortie_texte(p), true, true );

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

    connecter_projet(p);
    p->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet.
*/
bool fenetre_principale::enregistrer_projet(projet* p)
{
    if ( p != NULL )
    {
        if ( p->est_nouveau() )
            return enregistrer_projet_sous( p );
        else
            return enregistrer_projet( p->get_nom_fichier(), p );
    }

    return false;
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet sous.
*/
bool fenetre_principale::enregistrer_projet_sous(projet * p)
{
    QFileDialog d(this);
    d.setDefaultSuffix("emg");
    QString dir;
    if( p->get_nom_fichier().isEmpty() )
        dir = "mes_projets";
    else
        dir = p->get_dossier();

    QString nom_fichier = d.getSaveFileName( this, tr("Sauvegarder le projet"), dir,
                                             tr("projet Decode (*.emg);;"));

    if (nom_fichier.isEmpty())
        return false;
    else
    {
        if (!nom_fichier.endsWith(".emg"))
            nom_fichier += ".emg";

        enregistrer_projet(nom_fichier, p);
        return true;
    }
}

/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet.
*/
bool fenetre_principale::enregistrer_projet(const QString & nom_fichier, projet * p)
{
    QFile file(nom_fichier);
    if (!file.open(QIODevice::WriteOnly)) {
        QMessageBox::information(this, tr("Impossible d'ouvrir le fichier."),
                                 file.errorString());
        return false;
    }

    p->set_nom_fichier(nom_fichier);

    QXmlStreamWriter stream(&file);
    stream.setAutoFormatting(true);
    stream.writeStartDocument();
    p->sauvegarder( stream );
    stream.writeEndDocument();

    return true;
}

/** --------------------------------------------------------------------------------------
 \brief Ouvrir un projet.
*/
void fenetre_principale::ouvrir_projet()
{
    QString nom_fichier =
            QFileDialog::getOpenFileName( this, tr("Ouvrir un projet Decode"),
                                          "mes_projets", tr("projet Decode (*.emg);;"));

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

        QXmlStreamReader xml(&file);
        creer_projet(xml, nom_fichier);
    }
}

/** --------------------------------------------------------------------------------------
 \brief Crée un projet à partir d'un xml.
*/
void fenetre_principale::creer_projet(QXmlStreamReader & xml, const QString & nom)
{
    projet * p = new projet();
    xml.readNextStartElement();

    if( xml.name() == "projet" )
    {
        p->charger(xml);
        p->set_nom_fichier(nom);
    }
    else
        xml.skipCurrentElement();

    ajouter_projet(p);
}

/** --------------------------------------------------------------------------------------
 \brief Executer le projet.
*/
void fenetre_principale::executer(projet* p)
{
    if ( p != NULL )
    {
        m_toolbar_bouton_executer->setEnabled( false );
        s_compilateur->compiler( p );
        p->selectionner();
        s_vue_fonctions->scrollToBottom();
    }
}

void fenetre_principale::update_boutons_projet( projet * p )
{
    if ( p != NULL )
    {
        m_toolbar_bouton_sauvegarder_projet->setEnabled( p->est_enregistrable());
        m_toolbar_bouton_sauvegarder_projet_sous->setEnabled( true );
    }
    else
    {
        m_toolbar_bouton_sauvegarder_projet->setEnabled( false );
        m_toolbar_bouton_sauvegarder_projet_sous->setEnabled( false );
    }
}

void fenetre_principale::update_bouton_execution( projet * p )
{
    if ( p != NULL )
    {
        m_toolbar_bouton_executer->setEnabled( p->est_executable() );
    }
    else
    {
        m_toolbar_bouton_executer->setEnabled( false );
    }
}

void fenetre_principale::update_boutons_fonctions( objet_selectionnable * obj, bool etat )
{
    if ( obj != NULL )
    {
        if ( obj->est_conteneur() && obj->est_verrouille_avec_parent() )
            etat = false;

        if ( obj->est_fonction() && obj->parents_verrouilles() )
            etat = false;
    }

    m_toolbar_bouton_ajout_fonction_source->setEnabled( etat );
    m_toolbar_bouton_ajout_fonction_conversion->setEnabled( etat );
    m_toolbar_bouton_ajout_fonction_sortie->setEnabled( etat );
}

void fenetre_principale::connecter_projet(projet *p)
{
    connect( p, SIGNAL(signal_p_projet_etat_modification_change(projet *, bool)),
             this, SLOT(on_externe_projet_etat_modification_change(projet *, bool)));

    connect( p, SIGNAL(signal_p_projet_executable_change(projet *)),
             this, SLOT(on_externe_projet_executable_change(projet *)));

    connect( p, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
             this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

    connect( p, SIGNAL(signal_p_fermeture_projet(projet *)),
             this, SLOT(on_externe_fermeture_projet(projet *)));
}

void fenetre_principale::deconnecter_projet(projet *p)
{
    disconnect( p, SIGNAL(signal_p_projet_etat_modification_change(projet *, bool)),
                this, SLOT(on_externe_projet_etat_modification_change(projet *, bool)));

    disconnect( p, SIGNAL(signal_p_projet_executable_change(projet *)),
                this, SLOT(on_externe_projet_executable_change(projet *)));

    disconnect( s_explorateur, SIGNAL(signal_e_enregistrer_projet(projet *)),
                this, SLOT(enregistrer_projet(projet *)));

    disconnect( s_explorateur, SIGNAL(signal_e_enregistrer_projet_sous(projet *)),
                this, SLOT(enregistrer_projet_sous(projet *)));
}

void fenetre_principale::deconnecter_projets()
{
    for ( projets_iterateur it = s_projets.begin(); it != s_projets.end(); ++it )
        deconnecter_projet( *it );
}

void fenetre_principale::deconnecter()
{
    deconnecter_projets();
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
void fenetre_principale::on_enregistrer_projet_click()
{
    if ( objet_selectionnable::existe_selection() )
        enregistrer_projet( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton sauvegarder_projet_sous est activé.
*/
void fenetre_principale::on_enregistrer_projet_sous_click()
{
    if ( objet_selectionnable::existe_selection() )
        enregistrer_projet_sous( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ouvrir_projet est activé.
*/
void fenetre_principale::on_ouvrir_projet_click()
{
    ouvrir_projet();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton executer est activé.
*/
void fenetre_principale::on_executer_click()
{
    if ( objet_selectionnable::existe_selection() )
        executer( objet_selectionnable::get_projet_courant() );
}

void fenetre_principale::on_externe_e_demande_ajout_fonction
(fonctions_conteneur *conteneur, objet_selectionnable* obj_ref, base_fonction::type_fonction type)
{
    ajouter_fonction(conteneur, obj_ref, type);
}


void fenetre_principale::on_externe_verrouillage_change(objet_selectionnable *obj)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_selection() == obj )
            update_boutons_fonctions( objet_selectionnable::get_selection(), true);
}


void fenetre_principale::on_externe_projet_etat_modification_change(projet *p, bool etat)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_projet_courant() == p )
        {
            update_boutons_projet( p );
            update_boutons_fonctions( objet_selectionnable::get_selection(), true);
        }
}

void fenetre_principale::on_externe_projet_executable_change(projet *p)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_projet_courant() == p )
            update_bouton_execution( p );
}

void fenetre_principale::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    update_boutons_fonctions(obj, true);
    update_boutons_projet(obj->get_projet());
    update_bouton_execution(obj->get_projet());
}

void fenetre_principale::on_externe_objet_deselectionne(objet_selectionnable *obj)
{
    update_boutons_fonctions(obj, false);
    update_boutons_projet(NULL);
}

void fenetre_principale::on_externe_fermeture_projet(projet *p)
{
    if ( s_projets.contains(p) )
    {
        bool fermer = true;

        if ( p->est_enregistrable() || p->est_nouveau() )
        {
            fermer = false;

            QMessageBox msgBox;
            msgBox.setText("Le projet n'est pas enregistré.");
            msgBox.setInformativeText("Souhaitez-vous enregistrer les changements ?");
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();

            switch (ret) {
              case QMessageBox::Save:
                    fermer = enregistrer_projet(p);
                  break;
              case QMessageBox::Discard:
                    fermer = true;
                  break;
              case QMessageBox::Cancel:
                  fermer = false;
                  break;
            }
        }

        if ( fermer )
        {
            objet_selectionnable::forcer_deselection();

            int i = s_projets.indexOf(p);
            delete s_projets.at(i);
            s_projets.removeOne(p);
        }
    }
}

void fenetre_principale::on_externe_dupliquer_projet(projet *p)
{
    // ON fait la copie
    QString copie;
    QXmlStreamWriter XmlWriter(&copie);
    XmlWriter.setAutoFormatting(true);
    XmlWriter.writeStartDocument();
    p->sauvegarder(XmlWriter, false);
    XmlWriter.writeEndDocument();

    QXmlStreamReader xmlReader(copie);
    QString nom = p->get_nom() + "[copie]";
    creer_projet(xmlReader, nom );
}
