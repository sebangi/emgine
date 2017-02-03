#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"
#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"

#include <iostream>
#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QStyle>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

fonction_sortie_texte_widget::fonction_sortie_texte_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_textes( ((fonction_sortie_texte*)fonction)->get_textes())
{
    init();
}

void fonction_sortie_texte_widget::on_externe_fst_textes_modifie()
{
    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();

    creer_liste_texte();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();
}

void fonction_sortie_texte_widget::creer_liste_texte()
{
    m_liste_texte->clear();

    int i = 1;
    for ( textes::iterator it = m_textes.begin(); it != m_textes.end(); ++it )
    {
        texte_widget_item* item = new texte_widget_item(*it, i);
        m_liste_texte->addItem( item );
        ++i;
    }
}

void fonction_sortie_texte_widget::init()
{
    QVBoxLayout* layout = new QVBoxLayout();
    layout->setSizeConstraint(QLayout::SetFixedSize);
    layout->setMargin(0);
    layout->setSpacing(0);

    m_liste_texte = new liste_texte_widget();

    layout->addWidget(m_liste_texte);
    connect( m_liste_texte, SIGNAL(itemDoubleClicked(QListWidgetItem*)),
             this, SLOT(onTexteDoubleClicked(QListWidgetItem*)));
    connect(m_liste_texte, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));

    m_textes = ((fonction_sortie_texte*)m_fonction)->get_textes();
    creer_liste_texte();

    m_specialisation_layout->addLayout(layout);

    connect((fonction_sortie_texte*)m_fonction, SIGNAL(signal_fst_textes_modifie()), this, SLOT(on_externe_fst_textes_modifie()));
}

void fonction_sortie_texte_widget::onTexteDoubleClicked(QListWidgetItem* item)
{
    ((texte_widget_item*)item)->get_texte().inverser_configuration_visibilite();
    ((texte_widget_item*)item)->update();

    m_liste_texte->updateGeometry();
    signal_bfw_size_change();

    // Attention si on utilise la fonction get_configuration() si la fonction a été détruite depuis
    // std::cout << ((texte_widget_item*)item)->get_texte().get_string_configuration().toStdString() << std::endl;
}

void fonction_sortie_texte_widget::showContextMenu(const QPoint& pos)
{
    QStyle* style = QApplication::style();
    QPoint globalPos = mapToGlobal(pos);
    QMenu menu;

    QIcon icon_nouveau_projet;
    icon_nouveau_projet.addFile(QString::fromUtf8("icons/nouveau_projet.png"), QSize(), QIcon::Normal, QIcon::Off);
    QAction *newAct_nouveau_projet = new QAction(icon_nouveau_projet, tr("Créer un projet avec ce texte en source"), this);
    newAct_nouveau_projet->setStatusTip(tr("Créer un projet avec ce texte en source"));
    connect(newAct_nouveau_projet, SIGNAL(triggered()), this, SLOT(creer_projet()));
    menu.addAction(newAct_nouveau_projet);

    QAction *newAct_sauvegarder_texte = new QAction(style->standardIcon( QStyle::SP_DialogSaveButton ), tr("Sauvegarder ce texte"), this);
    newAct_sauvegarder_texte->setStatusTip(tr("Sauvegarder ce texte"));
    connect(newAct_sauvegarder_texte, SIGNAL(triggered()), this, SLOT(sauvegarder_texte()));
    menu.addAction(newAct_sauvegarder_texte);

    // Show context menu at handling position
    menu.exec(globalPos);
}

void fonction_sortie_texte_widget::creer_projet()
{
    texte_widget_item *item = (texte_widget_item *)m_liste_texte->takeItem(m_liste_texte->currentRow());

    emit signal_bfw_demande_creation_projet( item->get_texte() );
}

void fonction_sortie_texte_widget::sauvegarder_texte()
{
    QString nom_fichier = QFileDialog::getSaveFileName( this, "Sauvegarder le fichier", "mes_projets", "*.txt" );

    if ( nom_fichier.isEmpty() )
        return;
    else
    {
        if (! nom_fichier.endsWith(".txt"))
            nom_fichier += ".txt";

        QFile file(nom_fichier);

        if (! file.open(QIODevice::WriteOnly  | QIODevice::Text)) {
            QMessageBox::information(this, tr("Impossible d'ouvrir le fichier"),
                                     file.errorString());
            return;
        }

        texte_widget_item *item = (texte_widget_item *)m_liste_texte->takeItem(m_liste_texte->currentRow());

        QTextStream out(&file);
        out << item->get_texte().to_string_lisible();

        file.close();
    }
}
