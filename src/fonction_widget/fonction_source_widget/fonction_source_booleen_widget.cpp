/**
 * \file fonction_source_booleen_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_booleen_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_source_widget/fonction_source_booleen_widget.h"

#include "entete/fonction/fonction_source/fonction_source_booleen.h"

#include <QHBoxLayout>
#include <QLabel>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_booleen_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_source_booleen_widget::fonction_source_booleen_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void fonction_source_booleen_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();

    QLabel* label1 = new QLabel( "oui" );
    label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(label1, 1, Qt::AlignRight);

    m_check_oui = new QCheckBox();
    m_check_oui->setObjectName("CheckBoxParametreWidget");
    m_check_oui->setChecked(((fonction_source_booleen*)m_fonction)->get_valeur());
    lay->addWidget(m_check_oui, 1, Qt::AlignLeft);
    connect(m_check_oui, SIGNAL(stateChanged(int)), this, SLOT(on_oui_stateChanged(int)));

    QLabel* label2 = new QLabel( "non" );
    label2->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label2->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(label2, 1, Qt::AlignRight);

    m_check_non = new QCheckBox();
    m_check_non->setObjectName("CheckBoxParametreWidget");
    m_check_non->setChecked(! ((fonction_source_booleen*)m_fonction)->get_valeur());
    lay->addWidget(m_check_non, 1, Qt::AlignLeft);
    connect(m_check_non, SIGNAL(stateChanged(int)), this, SLOT(on_non_stateChanged(int)));

    m_specialisation_layout->addLayout(lay);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état du bouton à cocher OUI est modifié.
 * \param checkState L'état du bouton.
 */
void fonction_source_booleen_widget::on_oui_stateChanged(int checkState)
{
    ((fonction_source_booleen*)m_fonction)->set_valeur( checkState );
    m_check_non->setChecked( ! m_check_oui->isChecked() );
    m_fonction->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état du bouton à cocher NON est modifié.
 * \param checkState L'état du bouton.
 */
void fonction_source_booleen_widget::on_non_stateChanged(int checkState)
{
    ((fonction_source_booleen*)m_fonction)->set_valeur( ! checkState );
    m_check_oui->setChecked( ! m_check_non->isChecked() );
    m_fonction->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de verrouillage de la fonction associée change.
 */
void fonction_source_booleen_widget::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
    {
        m_check_non->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
        m_check_oui->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    }
    else
    {
        m_check_non->setEnabled( false );
        m_check_oui->setEnabled( false );
    }
}

