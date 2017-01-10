#include "compilation/compilateur.h"
#include "compilation/logs_compilation_widget.h"
#include "explorateur/explorateur.h"
#include "explorateur/noeud_fonction.h"
#include "explorateur/noeud_parametre.h"
#include "explorateur/noeud_projet.h"
#include "explorateur/base_noeud.h"
#include "fenetre_principale.h"
#include "fonction/fonction_conversion/fonction_cesar.h"
#include "fonction/fonction_source/fonction_source_texte.h"
#include "fonction/fonction_sortie/fonction_sortie_texte.h"
#include "fonction_widget/base_fonction_widget.h"
#include "vue_fonction/vue_fonctions.h"
#include "old_texte.h"
#include "projet.h"
#include "selecteur_fonction_dialog.h"
#include "ui_fenetre_principale.h"

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
    resize(QSize(1000,700));

    init_test();

    s_compilateur = new compilateur();
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
    m_toolbar_bouton_ajout_fonction_source->setObjectName("ButtonToolBarSource");
    m_toolbar_bouton_ajout_fonction_conversion->setObjectName("ButtonToolBarConversion");
    m_toolbar_bouton_ajout_fonction_sortie->setObjectName("ButtonToolBarSortie");
    m_toolbar_bouton_compiler->setObjectName("ButtonToolBar");

    m_ui->mainToolBar->addWidget(m_toolbar_bouton_nouveau_projet);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_sauvegarder_projet);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_sauvegarder_projet_sous);
    m_ui->mainToolBar->addWidget(m_toolbar_bouton_ouvrir_projet);
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
    s_explorateur = new explorateur(this, this);

    connect( s_explorateur,
             SIGNAL(noeud_courant_change(base_noeud*)),
             SLOT(on_externe_noeud_courant_change(base_noeud*))
           );

    s_vue_fonctions = new vue_fonctions(this);
    s_vue_fonctions->verticalHeader()->hide();
    s_vue_fonctions->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    s_vue_fonctions->setSelectionMode(QAbstractItemView::SingleSelection);
    s_vue_fonctions->setSelectionBehavior(QAbstractItemView::SelectRows);
    s_vue_fonctions->setColumnCount(3);
    s_vue_fonctions->setColumnHidden(2,true);
    s_vue_fonctions->setColumnWidth(0,50);
    s_vue_fonctions->horizontalHeader()->setStretchLastSection(true);
    s_vue_fonctions->setHorizontalHeaderItem(0, new QTableWidgetItem());
    s_vue_fonctions->horizontalHeaderItem(0)->setText("");
    s_vue_fonctions->setHorizontalHeaderItem(1, new QTableWidgetItem());
    s_vue_fonctions->horizontalHeaderItem(1)->setText("");
    s_vue_fonctions->setShowGrid(false);

    connect( s_vue_fonctions->selectionModel(),
             SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
             SLOT(on_vue_fonction_selectionChanged(const QItemSelection &, const QItemSelection &))
           );
    connect( s_vue_fonctions, SIGNAL(signal_vf_parametre_selectionne(base_parametre*)),
             this, SLOT(on_externe_parametre_selectionne(base_parametre*)));

    s_vue_logs = new logs_compilation_widget(this);
}

/** --------------------------------------------------------------------------------------
 \brief Initialise les différents widgets.
*/
void fenetre_principale::init_widgets()
{
    QStyle* style = QApplication::style();
    setWindowTitle("Emgine");

    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/add.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_ajout_fonction_source->setIcon(icon1);
    m_toolbar_bouton_ajout_fonction_source->setText("Source");
    m_toolbar_bouton_ajout_fonction_conversion->setIcon(icon1);
    m_toolbar_bouton_ajout_fonction_conversion->setText("Conversion");
    m_toolbar_bouton_ajout_fonction_sortie->setIcon(icon1);
    m_toolbar_bouton_ajout_fonction_sortie->setText("Sortie");

    m_toolbar_bouton_nouveau_projet->setIcon(style->standardIcon( QStyle::SP_FileDialogNewFolder ));
    m_toolbar_bouton_nouveau_projet->setText("Projet");

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

    m_ui->centralLayout->addWidget(top_widget,3);
    m_ui->centralLayout->addWidget(s_vue_logs, 1);

    QIcon icon2;
    icon2.addFile(QString::fromUtf8("icons/compile.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_toolbar_bouton_compiler->setIcon(icon2);
    m_toolbar_bouton_compiler->setText("Exécuter");
}

/** --------------------------------------------------------------------------------------
 \brief Selectionner le nouveau noeud courant.
*/
void fenetre_principale::set_noeud_courant( base_noeud * p )
{
    s_explorateur->set_noeud_courant(p);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une source au projet courant.
*/
void fenetre_principale::ajouter_source( base_noeud * n )
{
    ajouter_fonction( n, base_fonction::fonction_source);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction de conversion au projet courant.
*/
void fenetre_principale::ajouter_conversion( base_noeud * n )
{
    ajouter_fonction( n, base_fonction::fonction_conversion);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une sortie au projet courant.
*/
void fenetre_principale::ajouter_sortie( base_noeud * n )
{
    ajouter_fonction( n, base_fonction::fonction_sortie);
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( base_noeud * n, base_fonction::type_fonction type )
{
    if ( n != NULL )
    {
        selecteur_fonction_dialog * dlg = new selecteur_fonction_dialog(type, m_ui->centralWidget);

        int r = dlg->exec();

        if ( r == QDialog::Accepted )
        {
            // TODO : gérer la ligne suivante
            // set_noeud_courant(p);

            base_fonction * f = dlg->get_fonction();

            if ( f != NULL )
                ajouter_fonction(n, f, true, true);
        }
    }
}

/** --------------------------------------------------------------------------------------
 \brief Ajoute une fonction à un noeud.
*/
void fenetre_principale::ajouter_fonction( base_noeud * n, base_fonction* f, bool init_defaut, bool afficher_vue )
{
    bool ajout = true;

    // Ajout dans le projet
    if ( n->type() == base_noeud::type_projet )
        ((noeud_projet*)n)->get_projet()->ajouter_fonction(f);
    else if ( n->type() == base_noeud::type_parametre )
            ((noeud_parametre*)n)->get_parametre()->ajouter_fonction(f);
    else
        ajout = false;

    if ( init_defaut )
        f->initialisation_par_defaut();

    if ( ajout )
        s_explorateur->ajouter_noeud_fonction(n, f);

    if ( afficher_vue )
        s_vue_fonctions->ajouter_vue_fonction(f);

    s_vue_fonctions->update_selection( s_explorateur->get_noeud_courant() );
}

void fenetre_principale::informe_supression_projet(projet * p)
{
    for ( projet::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        informe_supression_fonction( *it );

    s_vue_logs->informe_supression_projet(p);
}

void fenetre_principale::informe_supression_fonction(base_fonction * f)
{
    for ( base_fonction::parametres_iterateur it = f->parametres_begin(); it != f->parametres_end(); ++it )
        informe_supression_parametre( it->second );

    s_vue_logs->informe_supression_fonction(f);
}

void fenetre_principale::informe_supression_parametre(base_parametre * p)
{
    for ( base_parametre::fonctions_iterateur it = p->fonctions_begin(); it != p->fonctions_end(); ++it )
        informe_supression_fonction( *it );

    s_vue_logs->informe_supression_parametre(p);
}



/** --------------------------------------------------------------------------------------
 \brief Jeu de test.
*/
void fenetre_principale::init_test()
{
    creer_projet();

    noeud_projet * n =  s_explorateur->get_projet_courant();

    if ( n  != NULL )
    {
        ajouter_fonction( n, new fonction_source_texte(n->get_projet(), "UNHBH TM SDRS !"), true, true );
        ajouter_fonction( n, new fonction_cesar(n->get_projet()), true, true );
        ajouter_fonction( n, new fonction_sortie_texte(n->get_projet()), true, true );
    }
}


/** --------------------------------------------------------------------------------------
 \brief Ajoute un nouveau projet.
*/
void fenetre_principale::creer_projet()
{
    projet * p = new projet();

    s_projets.push_back( p );
    s_explorateur->ajouter_noeud_projet(p);

    set_projet_courant(p);
}

/** --------------------------------------------------------------------------------------
 \brief Sélectionne un projet.
*/
void fenetre_principale::set_projet_courant( projet * p )
{
    if ( p != NULL )
    {
        s_explorateur->set_projet_courant(p);
        // TODO : a retirer
        // s_vue_fonctions->update_vue_fonction( s_explorateur->get_noeud_courant() );
    }
}


/** --------------------------------------------------------------------------------------
 \brief Sauvegarder le projet.
*/
void fenetre_principale::sauvegarder_projet(projet* p)
{
    if ( p != NULL )
    {
        std::cout << "sauvegarder_projet 1" << std::endl;
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
    std::cout << "sauvegarder_projet_sous" << std::endl;
    QFileDialog d(this);
    d.setDefaultSuffix("dec");
    QString nom_fichier = d.getSaveFileName( this,
                                            tr("Sauvegarder le projet"), "projets",
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
    std::cout << "sauvegarder_projet" << nom_fichier.toStdString() << std::endl;
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
void fenetre_principale::ouvrir_projet(projet * p)
{
    QString nom_fichier = QFileDialog::getOpenFileName( this,
                                                        tr("Ouvrir un projet Decode"),
                                                        "projets",
                                                        tr("projet Decode (*.dec);;"));

    if (nom_fichier.isEmpty())
        return;

    base_noeud* n = NULL;
    n = s_explorateur->get_projet_selon_nom_fichier(nom_fichier);

    if ( n != NULL )
    {
        set_noeud_courant(n);
    }
    else
    {
        QFile file(nom_fichier);

        if (!file.open(QIODevice::ReadOnly))
        {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier."),
                                     file.errorString());
            return;
        }

        QXmlStreamReader xml(&file);

        xml.readNextStartElement();

        if( xml.name() == "projet" )
        {
            std::cout << "projet " << xml.name().toString().toStdString() << std::endl;
            p->set_nom_fichier(nom_fichier);
            p->charger(xml);
            s_vue_fonctions->update_vue_fonction( s_explorateur->get_noeud_courant() );
        }
        else
            xml.skipCurrentElement();
    }
}


/** --------------------------------------------------------------------------------------
 \brief Ouvrir un projet.
*/
void fenetre_principale::ouvrir_projet()
{
    // TODO : A REVOIR
    creer_projet();

    noeud_projet * n = s_explorateur->get_projet_courant();

    if ( n != NULL )
    {
        ouvrir_projet( n->get_projet() );
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
        set_projet_courant(p);
    }
}

void fenetre_principale::adjust_size_vue_fonction()
{
    for ( int i = 0; i < s_vue_fonctions->rowCount(); ++i )
        s_vue_fonctions->setRowHeight(i, s_vue_fonctions->cellWidget(i,1)->size().height());
}


/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_source est activé.
*/
void fenetre_principale::on_ajouter_fonction_source_click()
{
    base_noeud* courant = s_explorateur->get_noeud_courant();

    if ( courant != NULL )
    {
        ajouter_source( courant );
        fenetre_principale::s_vue_fonctions->scrollToBottom();
    }
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_conversion est activé.
*/
void fenetre_principale::on_ajouter_fonction_conversion_click()
{
    base_noeud* courant = s_explorateur->get_noeud_courant();

    if ( courant != NULL )
    {
        ajouter_conversion( courant );
        fenetre_principale::s_vue_fonctions->scrollToBottom();
    }
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_fonction_sortie est activé.
*/
void fenetre_principale::on_ajouter_fonction_sortie_click()
{
    base_noeud* courant = s_explorateur->get_noeud_courant();

    if ( courant != NULL )
    {
        ajouter_sortie( courant );
        fenetre_principale::s_vue_fonctions->scrollToBottom();
    }
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton ajouter_nouveau_projet est activé.
*/
void fenetre_principale::on_nouveau_projet_click()
{
    creer_projet();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton sauvegarder_projet est activé.
*/
void fenetre_principale::on_sauvegarder_projet_click()
{
    noeud_projet * n = s_explorateur->get_projet_courant();

    if ( n != NULL )
        sauvegarder_projet( n->get_projet() );
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton sauvegarder_projet_sous est activé.
*/
void fenetre_principale::on_sauvegarder_projet_sous_click()
{
    noeud_projet * n = s_explorateur->get_projet_courant();

    if ( n != NULL )
        sauvegarder_projet_sous( n->get_projet() );
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
    noeud_projet * n = s_explorateur->get_projet_courant();

    if ( n != NULL )
        compiler( n->get_projet() );
}

/** --------------------------------------------------------------------------------------
 \brief La sélection de la vue_fonction change.
*/
void fenetre_principale::on_vue_fonction_selectionChanged(const QItemSelection &last_index, const QItemSelection & new_index)
{
    int row = s_vue_fonctions->currentRow();

    if ( row >= 0 )
    {
        // TODO
//        base_noeud * n =
//                ((base_fonction_widget*)(s_vue_fonctions->cellWidget(row,1)))->get_fonction()->get_noeud();
//        s_explorateur->clearSelection();
//        s_explorateur->setItemSelected((QTreeWidgetItem*)n, true);
//        update_selection();
    }
}

void fenetre_principale::on_externe_noeud_courant_change(base_noeud *noeud_courant)
{
    s_vue_fonctions->update_vue_fonction( noeud_courant );
}

void fenetre_principale::on_externe_parametre_selectionne(base_parametre* p)
{
    s_explorateur->set_parametre_courant( p );
}



