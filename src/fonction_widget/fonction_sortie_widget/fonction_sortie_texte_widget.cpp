/** \file fonction_sortie_texte_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_sortie_texte_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_sortie_widget/fonction_sortie_texte_widget.h"

#include "entete/fonction/fonction_sortie/fonction_sortie_texte.h"
#include "entete/fonction_widget/fonction_sortie_widget/liste_texte_widget.h"
#include "entete/fonction_widget/fonction_sortie_widget/texte_widget_item.h"
#include "entete/projet/projet.h"

#include <QHBoxLayout>
#include <QMenu>
#include <QApplication>
#include <QStyle>
#include <QFileDialog>
#include <QTextStream>
#include <QMessageBox>

#include <iostream>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_sortie_texte_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_sortie_texte_widget::fonction_sortie_texte_widget(base_fonction *fonction, QWidget *parent)
    : fonction_base_sortie_widget(fonction, parent)
{
    connect(m_liste_texte, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'ouverture de menu.
 * \param pos La position cliqué.
 */
void fonction_sortie_texte_widget::showContextMenu(const QPoint& pos)
{
    QStyle* style = QApplication::style();
    QPoint globalPos = mapToGlobal(pos);
    QMenu menu;

    QIcon icon_nouveau_projet;
    icon_nouveau_projet.addFile(QString::fromUtf8(":/icons/nouveau_projet.png"), QSize(), QIcon::Normal, QIcon::Off);
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

/** --------------------------------------------------------------------------------------
 * \brief Crée un projet avec pour texte source le texte actuellement sélectionné.
 */
void fonction_sortie_texte_widget::creer_projet()
{
    texte_widget_item *item = (texte_widget_item *)m_liste_texte->takeItem(m_liste_texte->currentRow());

    emit signal_bfw_demande_creation_projet( item->get_texte() );
}

/** --------------------------------------------------------------------------------------
 * \brief Sauvegarde le texte actuellement sélectionné dans un fichier.
 */
void fonction_sortie_texte_widget::sauvegarder_texte()
{
    QString dir = "mes_projets";
    if ( ! m_fonction->get_projet()->est_nouveau() )
        dir = m_fonction->get_projet()->get_dossier();

    QString nom_fichier = QFileDialog::getSaveFileName( this, "Sauvegarder le fichier", dir, "*.txt" );

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

        QPoint p(m_liste_texte->currentRow(), 0);
        texte_widget_item *item = (texte_widget_item *)m_liste_texte->itemAt(p);

        QTextStream out(&file);
        out << item->get_texte().to_string_lisible();

        file.close();
    }
}
