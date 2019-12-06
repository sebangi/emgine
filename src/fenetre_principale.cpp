/**
 * \file fenetre_principale.cpp
 * \brief Fichier d'implémentation de la classe fenetre_principale.
 * \author Sébastien Angibaud
 */

#include "entete/ui_fenetre_principale.h"

#include "entete/compilation/compilateur.h"
#include "entete/compilation/logs_compilation_widget.h"
#include "entete/explorateur/base_noeud.h"
#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/noeud_fonction.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/explorateur/noeud_projet.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction/fonction_conversion/fonction_cesar.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"
#include "entete/fonction/fonction_source/fonction_source_permutation.h"
#include "entete/fonction/fonction_source/fonction_source_texte.h"
#include "entete/fonction_widget/base_fonction_widget.h"
#include "entete/fonction_widget/selecteur_fonction_dialog.h"
#include "entete/fonction_widget/selecteur_fonction_dialog.h"
#include "entete/fonction_widget/vue_fonctions.h"
#include "entete/projet/fonctions_conteneur.h"
#include "entete/projet/projet.h"

#include <QCheckBox>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <QString>
#include <QtGui>
#include <QVBoxLayout>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

#include <iostream>
#include <string>
#include <vector>

// Initialisation des variables membres statiques
explorateur * fenetre_principale::s_explorateur = NULL;
vue_fonctions * fenetre_principale::s_vue_fonctions = NULL;
compilateur * fenetre_principale::s_compilateur = NULL;
logs_compilation_widget * fenetre_principale::s_vue_logs = NULL;
fenetre_principale::type_projets fenetre_principale::s_projets = fenetre_principale::type_projets();

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fenetre_principale.
 * \param parent Un pointeur sur le widget parent.
 */
fenetre_principale::fenetre_principale(QApplication * app, QWidget *parent) :
    m_application(app), QMainWindow(parent), m_ui(new Ui::fenetre_principale)
{
    m_ui->setupUi(this);
    m_ui->menuBar->hide();

    m_translator.load("emgine_fr");
    m_application->installTranslator(& m_translator);

    creer_toolbar();
    creer_widgets();
    init_widgets();

    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/emgine.png"), QSize(), QIcon::Normal, QIcon::Off);
    setWindowIcon(icon1);
    resize(QSize(1200,900));

    init_test();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe fenetre_principale.
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
    m_toolbar_bouton_francais = new QPushButton();
    m_toolbar_bouton_anglais = new QPushButton();

    m_toolbar_bouton_nouveau_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet->setObjectName("ButtonToolBar");
    m_toolbar_bouton_sauvegarder_projet_sous->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ouvrir_projet->setObjectName("ButtonToolBar");

    m_toolbar_bouton_ajout_fonction_source->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_conversion->setObjectName("ButtonToolBar");
    m_toolbar_bouton_ajout_fonction_sortie->setObjectName("ButtonToolBar");

    m_toolbar_bouton_executer->setObjectName("ButtonToolBar");

    m_toolbar_bouton_francais->setObjectName("BoutonLangueSelectionne");
    m_toolbar_bouton_anglais->setObjectName("BoutonLangueNonSelectionne");

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

    m_ui->mainToolBar->addWidget(m_toolbar_bouton_executer);

    QWidget* spacer = new QWidget();
    spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_ui->mainToolBar->addWidget(spacer);

    m_ui->mainToolBar->addWidget(m_toolbar_bouton_francais);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_anglais);
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

    // connect de l'explorateur
    connect( s_explorateur, SIGNAL(signal_e_demande_ajout_fonction(fonctions_conteneur *, objet_selectionnable*, type_fonction)),
             this, SLOT(on_externe_demande_ajout_fonction(fonctions_conteneur *, objet_selectionnable*, type_fonction)));
    connect( s_explorateur, SIGNAL(signal_e_objet_selectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_selectionne(objet_selectionnable *)));
    connect( s_explorateur, SIGNAL(signal_e_objet_deselectionne(objet_selectionnable*)),
             this, SLOT(on_externe_objet_deselectionne(objet_selectionnable *)));
    connect( s_explorateur, SIGNAL(signal_e_enregistrer_projet(projet *)),
             this, SLOT(on_enregistrer_projet(projet *)));
    connect( s_explorateur, SIGNAL(signal_e_enregistrer_projet_sous(projet *)),
             this, SLOT(on_enregistrer_projet_sous(projet *)));
    connect( s_explorateur, SIGNAL(signal_e_dupliquer_projet(projet *)),
             this, SLOT(on_externe_dupliquer_projet(projet *)));

    // connect de la vue des fonctions
    connect( s_vue_fonctions, SIGNAL(signal_vf_demande_creation_projet(const texte&)),
             this, SLOT(on_externe_demande_creation_projet(const texte &)));
}

/** --------------------------------------------------------------------------------------
 \brief Initialisation des différents widgets.
*/
void fenetre_principale::init_widgets()
{
    QStyle* style = QApplication::style();

    setWindowTitle( tr("Emgine") );

    QIcon icone_source;
    icone_source.addFile(QString::fromUtf8(":/icons/ajout_source.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_source->setIcon(icone_source);
    m_toolbar_bouton_ajout_fonction_source->setText(tr("Source"));
    m_toolbar_bouton_ajout_fonction_source->setShortcut( QKeySequence("Alt+A") );

    QIcon icone_conversion;
    icone_conversion.addFile(QString::fromUtf8(":/icons/ajout_conversion.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_conversion->setIcon(icone_conversion);
    m_toolbar_bouton_ajout_fonction_conversion->setText(tr("Conversion"));
    m_toolbar_bouton_ajout_fonction_conversion->setShortcut( QKeySequence("Alt+Z") );

    QIcon icone_sortie;
    icone_sortie.addFile(QString::fromUtf8(":/icons/ajout_sortie.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_sortie->setIcon(icone_sortie);
    m_toolbar_bouton_ajout_fonction_sortie->setText(tr("Résultat"));
    m_toolbar_bouton_ajout_fonction_sortie->setShortcut( QKeySequence("Alt+E") );

    QIcon icone_nouveau_projet;
    icone_nouveau_projet.addFile(QString::fromUtf8(":/icons/nouveau_projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_nouveau_projet->setIcon(icone_nouveau_projet);
    m_toolbar_bouton_nouveau_projet->setText(tr("Nouveau projet"));

    QIcon icone_projet;
    icone_projet.addFile(QString::fromUtf8(":/icons/projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ouvrir_projet->setIcon(icone_projet);
    m_toolbar_bouton_ouvrir_projet->setText(tr("Ouvrir un projet"));

    m_toolbar_bouton_sauvegarder_projet->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet->setText("Enregistrer");
    m_toolbar_bouton_sauvegarder_projet->setShortcut( QKeySequence("Ctrl+S") );
    m_toolbar_bouton_sauvegarder_projet_sous->setIcon(style->standardIcon( QStyle::SP_DialogSaveButton ));
    m_toolbar_bouton_sauvegarder_projet_sous->setText(tr("Enregistrer sous"));

    QIcon icone_drapeau_francais;
    icone_drapeau_francais.addFile(QString::fromUtf8(":/icons/drapeau/francais.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_francais->setIcon(icone_drapeau_francais);
    m_toolbar_bouton_francais->setText(tr("Français"));

    QIcon icone_drapeau_anglais;
    icone_drapeau_anglais.addFile(QString::fromUtf8(":/icons/drapeau/anglais.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_anglais->setIcon(icone_drapeau_anglais);
    m_toolbar_bouton_anglais->setText(tr("Anglais"));

    connect( m_toolbar_bouton_ajout_fonction_source, SIGNAL(released()), this, SLOT(on_ajouter_fonction_source_click()));
    connect( m_toolbar_bouton_ajout_fonction_conversion, SIGNAL(released()), this, SLOT(on_ajouter_fonction_conversion_click()));
    connect( m_toolbar_bouton_ajout_fonction_sortie, SIGNAL(released()), this, SLOT(on_ajouter_fonction_sortie_click()));
    connect( m_toolbar_bouton_nouveau_projet, SIGNAL(released()), this, SLOT(on_nouveau_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet, SIGNAL(released()), this, SLOT(on_enregistrer_projet_click()));
    connect( m_toolbar_bouton_sauvegarder_projet_sous, SIGNAL(released()), this, SLOT(on_enregistrer_projet_sous_click()));
    connect( m_toolbar_bouton_ouvrir_projet, SIGNAL(released()), this, SLOT(on_ouvrir_projet_click()));
    connect( m_toolbar_bouton_executer, SIGNAL(released()), this, SLOT(on_executer_click()));

    connect( m_toolbar_bouton_francais, SIGNAL(released()), this, SLOT(on_francais_click()));
    connect( m_toolbar_bouton_anglais, SIGNAL(released()), this, SLOT(on_anglais_click()));

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
    icon_compile.addFile(QString::fromUtf8(":/icons/grand_compile.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_executer->setIcon(icon_compile);
    m_toolbar_bouton_executer->setText(tr("Exécuter"));
    m_toolbar_bouton_executer->setShortcut( QKeySequence("Ctrl+R") );
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une source au projet courant.
*/
void fenetre_principale::ajouter_source()
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(),
                          type_fonction::fonction_source);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction de conversion au projet courant.
*/
void fenetre_principale::ajouter_conversion()
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(),
                          type_fonction::fonction_conversion);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une sortie au projet courant.
*/
void fenetre_principale::ajouter_sortie()
{
    if ( objet_selectionnable::existe_selection() )
        ajouter_fonction( objet_selectionnable::get_selection()->get_conteneur(), objet_selectionnable::get_selection(),
                          type_fonction::fonction_sortie);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une fonction dans un conteneur donné.
 * \param conteneur Un pointeur sur le conteneur dans lequel il faut ajouter la fonction.
 * \param obj_ref Un pointeur sur l'objet après lequel la fonction doit être ajoutée.
 * \param type Le type de fonction à ajouter.
 */
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, type_fonction type )
{
    if ( conteneur != NULL )
    {
        selecteur_fonction_dialog * dlg = new selecteur_fonction_dialog(type, conteneur, m_ui->centralWidget);

        int r = dlg->exec();

        if ( r == QDialog::Accepted )
        {
            base_fonction * f = dlg->get_fonction();
            f->set_conteneur(conteneur);

            if ( f != NULL )
                ajouter_fonction(conteneur, obj_ref, f, true);
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute une fonction dans un conteneur donné.
 * \param conteneur Un pointeur sur le conteneur dans lequel il faut ajouter la fonction.
 * \param obj_ref Un pointeru sur l'objet après lequel la fonction doit être ajoutée.
 * \param f Un pointeur sur la fonction à ajouter.
 * \param init_defaut Indique s'il faut initialiser par défaut la fonction.
 */
void fenetre_principale::ajouter_fonction( fonctions_conteneur * conteneur, objet_selectionnable * obj_ref, base_fonction* f, bool init_defaut )
{
    if ( init_defaut )
        f->initialisation_par_defaut();

    conteneur->ajouter_fonction(f,obj_ref);
    f->selectionner();
}

/** --------------------------------------------------------------------------------------
 \brief Fixe la largeur de la barre de menu.
*/
void fenetre_principale::fixer_largeur_menu()
{
     m_ui->mainToolBar->setFixedWidth(  m_ui->mainToolBar->width() );
}

/** --------------------------------------------------------------------------------------
 \brief Initialise par défaut un projet exemple.
*/
void fenetre_principale::init_test()
{
    projet * p  = new projet();
    p->set_nom(tr("Exemple"));
    ajouter_projet(p);

    ajouter_fonction( p, NULL, new fonction_source_texte(p, "UNHBH TM SDRS !\nunhbh tm sdrs !"), true );
    ajouter_fonction( p, NULL, new fonction_cesar(p), true );
    ajouter_fonction( p, NULL, new fonction_sortie_texte(p), true );

    p->selectionner();
}


/** --------------------------------------------------------------------------------------
 \brief Ajoute un nouveau projet donné.
 \param p Un pointeur sur le projet à ajouter.
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
 \brief Enregistre un projet donné.
 \param p Un pointeur sur le projet à enregistrer.
 \return \b True si le projet a bien été enregistré, \b False sinon.
*/
bool fenetre_principale::on_enregistrer_projet(projet* p)
{
    if ( p != NULL )
    {
        if ( p->est_nouveau() )
            return on_enregistrer_projet_sous( p );
        else
            return on_enregistrer_projet( p->get_chemin_absolu(), p );
    }

    return false;
}

/** --------------------------------------------------------------------------------------
 \brief Enregistre un projet donné sous.
 \param p Un pointeur sur le projet à enregistrer sous.
 \return \b True si le projet a bien été enregistré, \b False sinon.
*/
bool fenetre_principale::on_enregistrer_projet_sous(projet * p)
{
    QFileDialog d(this);
    d.setDefaultSuffix("emg");
    QString dir;
    if( p->get_chemin_relatif().isEmpty() )
        dir = "mes_projets/";
    else
        dir = p->get_dossier();

    QString nom_fichier = d.getSaveFileName( this, tr("Sauvegarder le projet"), dir,
                                             tr("projet Emgine") + " (*.emg);;");

    if (nom_fichier.isEmpty())
        return false;
    else
    {
        if (!nom_fichier.endsWith(".emg"))
            nom_fichier += ".emg";

        on_enregistrer_projet(nom_fichier, p);
        return true;
    }
}

/** --------------------------------------------------------------------------------------
 \brief Enregistre un projet donné avec un nom de fichier spécifié.
 \param nom_fichier Le nom du fichier à utiliser.
 \param p Un pointeur sur le projet à enregistrer.
 \return \b True si le projet a bien été enregistré, \b False sinon.
*/
bool fenetre_principale::on_enregistrer_projet(const QString & nom_fichier, projet * p)
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
 * \brief Retourne un projet d'un nom de fichier donné.
 * \param nom_fichier Le nom de fichier du projet à chercher.
 * \return Un pointeur sur le projet. Retourne la valeur \b NULL si aucun projet n'a ce nom de fichier.
 */
projet * fenetre_principale::get_projet_selon_nom_fichier(const QString &nom_fichier)
{
    projet * p = NULL;

    QFileInfo info(nom_fichier);
    QDir dir( QCoreApplication::applicationDirPath() );
    QString relative_path = dir.relativeFilePath( info.absoluteFilePath() );

    for ( type_projets::iterator it = s_projets.begin(); it != s_projets.end() && p == NULL; ++it )
        if ( (*it)->get_chemin_relatif() == relative_path )
            p = *it;

    return p;
}

/** --------------------------------------------------------------------------------------
 \brief Ouvre un projet.
*/
void fenetre_principale::ouvrir_projet()
{
    QString nom_fichier =
            QFileDialog::getOpenFileName( this, tr("Ouvrir un projet Emgine"),
                                          "mes_projets", tr("projet Emgine") +" (*.emg);;");

    if (nom_fichier.isEmpty())
        return;

    projet* existant = get_projet_selon_nom_fichier(nom_fichier);

    if ( existant != NULL )
    {
        QMessageBox::information(this, tr("Ouverture de projet"), tr("Le projet est déjà ouvert !") );
        existant->selectionner();
    }
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
 \brief Crée un projet à partir d'une source xml.
 \param xml La source xml à partir duquel créer le projet.
 \param nom_fichier Le nom du fichier du projet.
*/
void fenetre_principale::creer_projet(QXmlStreamReader & xml, const QString & nom_fichier)
{
    projet * p = new projet();
    xml.readNextStartElement();

    if( xml.name() == "projet" )
    {
        p->charger(xml);
        p->set_nom_fichier(nom_fichier);
    }
    else
        xml.skipCurrentElement();

    ajouter_projet(p);
}

/** --------------------------------------------------------------------------------------
 * \brief Crée un projet à partir d'un texte donné.
 * \param t Le texte source du projet à créer.
 */
void fenetre_principale::creer_projet(const texte &t)
{
    projet * p = new projet();

    p->set_nom(tr("Nouveau projet"));
    ajouter_projet(p);

    ajouter_fonction( p, NULL, new fonction_source_texte(p, t.to_string_lisible()), true );
}

/** --------------------------------------------------------------------------------------
 \brief Execute un projet donné.
 \param p Un pointeur sur le projet à exécuter.
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

/** --------------------------------------------------------------------------------------
 * \brief Met à jour les boutons de la fenêtre selon un projet donné.
 * \param p Un pointeur sur le projet à considérer.
 */
void fenetre_principale::mettre_a_jour_boutons_projet( projet * p )
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

/** --------------------------------------------------------------------------------------
 * \brief Met à jour les boutons d'exécution selon un projet donné.
 * \param p Un pointeur sur le projet à considérer.
 */
void fenetre_principale::mettre_a_jour_bouton_execution( projet * p )
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

/** --------------------------------------------------------------------------------------
 * \brief Met à jour les boutons d'ajout de fonctions selon un objet donné.
 * \param obj Un pointeur sur l'objet à considérer.
 * \param etat Booléen indiquant s'il faut activer les boutons.
 */
void fenetre_principale::mettre_a_jour_boutons_fonctions( objet_selectionnable * obj, bool etat )
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

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connections pour un projet donné.
 * \param p Un pointeur sur le projet à considérer.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections pour un projet donné.
 * \param p Un pointeur sur le projet à considérer.
 */
void fenetre_principale::deconnecter_projet(projet *p)
{
    disconnect( p, SIGNAL(signal_p_projet_etat_modification_change(projet *, bool)),
                this, SLOT(on_externe_projet_etat_modification_change(projet *, bool)));

    disconnect( p, SIGNAL(signal_p_projet_executable_change(projet *)),
                this, SLOT(on_externe_projet_executable_change(projet *)));

    disconnect( s_explorateur, SIGNAL(signal_e_enregistrer_projet(projet *)),
                this, SLOT(on_enregistrer_projet(projet *)));

    disconnect( s_explorateur, SIGNAL(signal_e_enregistrer_projet_sous(projet *)),
                this, SLOT(on_enregistrer_projet_sous(projet *)));
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections de tous les projets.
 */
void fenetre_principale::deconnecter_projets()
{
    for ( projets_iterateur it = s_projets.begin(); it != s_projets.end(); ++it )
        deconnecter_projet( *it );
}

/** --------------------------------------------------------------------------------------
 * \brief Retire toutes les connections.
 */
void fenetre_principale::deconnecter()
{
    deconnecter_projets();
}

/** --------------------------------------------------------------------------------------
 \brief Sélectionne une langue donnée.
 \param langue La langue voulue.
*/
void fenetre_principale::selectionner_langue(QString langue)
{
    m_application->removeTranslator(& m_translator );
    m_translator.load("emgine_" + langue );
    m_application->installTranslator(& m_translator);

    emit signal_fp_language_changed();
}

/** --------------------------------------------------------------------------------------
 \brief Met à jour les textes.
*/
void fenetre_principale::maj_textes()
{
    m_toolbar_bouton_nouveau_projet->setText(tr("Nouveau projet"));
    m_toolbar_bouton_ouvrir_projet->setText(tr("Ouvrir un projet"));
    m_toolbar_bouton_sauvegarder_projet->setText(tr("Enregistrer"));
    m_toolbar_bouton_sauvegarder_projet_sous->setText(tr("Enregistrer sous"));
    m_toolbar_bouton_ajout_fonction_source->setText(tr("Source"));
    m_toolbar_bouton_ajout_fonction_conversion->setText(tr("Conversion"));
    m_toolbar_bouton_ajout_fonction_sortie->setText(tr("Résultat"));
    m_toolbar_bouton_executer->setText(tr("Exécuter"));
    m_toolbar_bouton_francais->setText(tr("Français"));
    m_toolbar_bouton_anglais->setText(tr("Anglais"));
    setWindowTitle( tr("Emgine") );
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton ajouter_fonction_source est activé.
*/
void fenetre_principale::on_ajouter_fonction_source_click()
{
    ajouter_source();
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton ajouter_fonction_conversion est activé.
*/
void fenetre_principale::on_ajouter_fonction_conversion_click()
{
    ajouter_conversion();
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton ajouter_fonction_sortie est activé.
*/
void fenetre_principale::on_ajouter_fonction_sortie_click()
{
    ajouter_sortie();
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton ajouter_nouveau_projet est activé.
*/
void fenetre_principale::on_nouveau_projet_click()
{
    projet * p = new projet();
    ajouter_projet(p);
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton sauvegarder_projet est activé.
*/
void fenetre_principale::on_enregistrer_projet_click()
{
    if ( objet_selectionnable::existe_selection() )
        on_enregistrer_projet( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton sauvegarder_projet_sous est activé.
*/
void fenetre_principale::on_enregistrer_projet_sous_click()
{
    if ( objet_selectionnable::existe_selection() )
        on_enregistrer_projet_sous( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton ouvrir_projet est activé.
*/
void fenetre_principale::on_ouvrir_projet_click()
{
    ouvrir_projet();
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque le bouton executer est activé.
*/
void fenetre_principale::on_executer_click()
{
    if ( objet_selectionnable::existe_selection() )
        executer( objet_selectionnable::get_projet_courant() );
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque l'on choisit la langue française.
*/
void fenetre_principale::on_francais_click()
{
    selectionner_langue("fr");

    m_toolbar_bouton_francais->setObjectName("BoutonLangueSelectionne");
    m_toolbar_bouton_anglais->setObjectName("BoutonLangueNonSelectionne");

    m_toolbar_bouton_francais->style()->unpolish(m_toolbar_bouton_francais);
    m_toolbar_bouton_francais->style()->polish(m_toolbar_bouton_francais);
    m_toolbar_bouton_anglais->style()->unpolish(m_toolbar_bouton_anglais);
    m_toolbar_bouton_anglais->style()->polish(m_toolbar_bouton_anglais);
}

/** --------------------------------------------------------------------------------------
 \brief Fonction appelée lorsque l'on choisit la langue anglaise.
*/
void fenetre_principale::on_anglais_click()
{
    selectionner_langue("en");

    m_toolbar_bouton_francais->setObjectName("BoutonLangueNonSelectionne");
    m_toolbar_bouton_anglais->setObjectName("BoutonLangueSelectionne");

    m_toolbar_bouton_francais->style()->unpolish(m_toolbar_bouton_francais);
    m_toolbar_bouton_francais->style()->polish(m_toolbar_bouton_francais);
    m_toolbar_bouton_anglais->style()->unpolish(m_toolbar_bouton_anglais);
    m_toolbar_bouton_anglais->style()->polish(m_toolbar_bouton_anglais);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'il y a une demande externe d'ajout de fonction.
 * \param conteneur Un pointeur sur le conteneur dans lequel il faut ajouter la fonction.
 * \param obj_ref Un pointeur sur l'objet après lequel il faut ajouter la fonction.
 * \param type Le type de fonction à ajouter.
 */
void fenetre_principale::on_externe_demande_ajout_fonction
( fonctions_conteneur *conteneur, objet_selectionnable* obj_ref, type_fonction type)
{
    ajouter_fonction(conteneur, obj_ref, type);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'il y a un changement de verrouillage d'un objet.
 * \param obj Un pointeur sur l'objet ayant son vérouillage de modifié.
 */
void fenetre_principale::on_externe_verrouillage_change(objet_selectionnable *obj)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_selection() == obj )
            mettre_a_jour_boutons_fonctions( objet_selectionnable::get_selection(), true);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de modification d'un projet change.
 * \param p Un pointeur sur le projet à considérer.
 * \param etat Booléen indiquant si le projet est modifié.
 */
void fenetre_principale::on_externe_projet_etat_modification_change(projet *p, bool etat)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_projet_courant() == p )
        {
            mettre_a_jour_boutons_projet( p );
            mettre_a_jour_boutons_fonctions( objet_selectionnable::get_selection(), true);
        }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état d'exécutabitlité d'un projet change.
 * \param p Un pointeur sur le projet à considérer.
 */
void fenetre_principale::on_externe_projet_executable_change(projet *p)
{
    if ( objet_selectionnable::existe_selection() )
        if ( objet_selectionnable::get_projet_courant() == p )
            mettre_a_jour_bouton_execution( p );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet est sélectionné.
 * \param obj Un pointeur sur l'objet sélectionné.
 */
void fenetre_principale::on_externe_objet_selectionne(objet_selectionnable *obj)
{
    mettre_a_jour_boutons_fonctions(obj, true);
    mettre_a_jour_boutons_projet(obj->get_projet());
    mettre_a_jour_bouton_execution(obj->get_projet());
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un objet est déselectionné.
 * \param obj Un pointeur sur l'objet désélectionné.
 */
void fenetre_principale::on_externe_objet_deselectionne(objet_selectionnable *obj)
{
    mettre_a_jour_boutons_fonctions(obj, false);
    mettre_a_jour_boutons_projet(NULL);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'il y a une demande externe de fermeture d'un projet.
 * \param p Un pointeur sur le projet à fermer.
 */
void fenetre_principale::on_externe_fermeture_projet(projet *p)
{
    if ( s_projets.contains(p) )
    {
        bool fermer = true;

        if ( p->est_enregistrable() || p->est_nouveau() )
        {
            fermer = false;

            QMessageBox msgBox;
            msgBox.setText(tr("Le projet n'est pas enregistré."));
            msgBox.setInformativeText(tr("Souhaitez-vous enregistrer les changements ?"));
            msgBox.setStandardButtons(QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
            msgBox.setDefaultButton(QMessageBox::Save);
            int ret = msgBox.exec();

            switch (ret) {
                case QMessageBox::Save:
                    fermer = on_enregistrer_projet(p);
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'il y a une demande externe de duplication de projet.
 * \param p Un pointeur sur le projet à dupliquer.
 */
void fenetre_principale::on_externe_dupliquer_projet(projet *p)
{
    QString copie;
    QXmlStreamWriter XmlWriter(&copie);
    XmlWriter.setAutoFormatting(true);
    XmlWriter.writeStartDocument();
    p->sauvegarder(XmlWriter, false);
    XmlWriter.writeEndDocument();

    QXmlStreamReader xmlReader(copie);
    QString nom = p->get_nom() + "[" + tr("copie") + "]";
    creer_projet(xmlReader, nom );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'il y a une demande externe de création de projet avec un texte source.
 * \param t Le texte source ç ajouter au projet à créer.
 */
void fenetre_principale::on_externe_demande_creation_projet(const texte & t)
{
    creer_projet(t);
}
