/**
 * \file fonction_source_choix_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_choix_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h"

#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/parametre/parametre_choix.h"

#include <QHBoxLayout>
#include <QListWidgetItem>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_choix_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_source_choix_widget::fonction_source_choix_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent), m_verrou_boucle_signaux(false)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le composant.
 */
void fonction_source_choix_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();
    lay->setSizeConstraint(QLayout::SetMaximumSize);

    m_liste = new QListWidget();
    m_liste->setMinimumHeight(20);
    m_liste->setMaximumHeight(400);
    m_liste->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    construire_liste();
    lay->addWidget(m_liste);
    m_specialisation_layout->addLayout(lay);

    connect(m_liste, SIGNAL(itemChanged(QListWidgetItem *)), this, SLOT(on_itemChanged(QListWidgetItem *)));

    informer_verrouillage_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Construit la liste de choix.
 */
void fonction_source_choix_widget::construire_liste()
{
    m_liste->clear();

    if ( m_fonction != NULL )
    {
        QStringList choix = ((fonction_source_choix *)m_fonction)->get_choix();

        for ( QStringList::const_iterator it = choix.constBegin(); it != choix.constEnd(); ++it )
        {
            QListWidgetItem* item = new QListWidgetItem(*it, m_liste);
            item->setFlags(item->flags() | Qt::ItemIsUserCheckable);
            item->setCheckState(Qt::Unchecked);
        }

        QStringList selection = ((fonction_source_choix *)m_fonction)->get_selection();

        for ( QStringList::iterator it = selection.begin(); it != selection.end(); ++it )
        {
            QList<QListWidgetItem*> l = m_liste->findItems(*it, Qt::MatchExactly);
            for( QList<QListWidgetItem*>::iterator it_l = l.begin(); it_l != l.end(); it_l++ )
                (*it_l)->setCheckState(Qt::Checked);
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de verrouillage de la focntion associée change.
 */
void fonction_source_choix_widget::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
        m_liste->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    else
        m_liste->setEnabled(false);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la choix sélectionné change.
 * \param item Un pointeur sur l'item sélectionné.
 */
void fonction_source_choix_widget::on_itemChanged(QListWidgetItem *item)
{
    if ( ! m_verrou_boucle_signaux )
    {
        m_verrou_boucle_signaux = true;

        QStringList l;

        if ( ! ((fonction_source_choix *)m_fonction)->get_multiple_selection() )
        {
            // on décoche tout
            for ( int i = 0; i != m_liste->count(); ++i )
                m_liste->item(i)->setCheckState( Qt::Unchecked );

            // on recoche le sélectionné
            item->setCheckState(Qt::Checked);
        }

        for ( int i = 0; i != m_liste->count(); ++i )
            if ( m_liste->item(i)->checkState() == Qt::Checked )
                l.push_back( m_liste->item(i)->text() );

        ((fonction_source_choix*)m_fonction)->set_selection( l );

        m_fonction->modifier();

        m_verrou_boucle_signaux = false;
    }
}
