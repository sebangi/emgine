/**
 * \file fonction_source_entier_widget.cpp
 * \brief Fichier d'implémentation de la classe fonction_source_entier_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/fonction_source_widget/fonction_source_entier_widget.h"

#include "entete/fonction/fonction_source/fonction_source_entier.h"

#include <QHBoxLayout>
#include <QLabel>
#include <limits>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe fonction_source_entier_widget.
 * \param fonction Un pointeur sur la fonction associée.
 * \param parent Un pointeur sur le widget parent.
 */
fonction_source_entier_widget::fonction_source_entier_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void fonction_source_entier_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();

    QLabel* label1 = new QLabel( "valeur" );
    label1->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label1->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    lay->addWidget(label1, 1, Qt::AlignRight);

    m_spin_box = new QSpinBox();
    m_spin_box->setRange( std::numeric_limits<int>::min(), std::numeric_limits<int>::max() );
    m_spin_box->setObjectName("SpinBoxParametreWidget");
    m_spin_box->setValue(((fonction_source_entier*)m_fonction)->get_valeur());
    lay->addWidget(m_spin_box, 2, Qt::AlignLeft);
    connect(m_spin_box, SIGNAL(valueChanged(int)), this, SLOT(on_entier_changed(int)));

    m_specialisation_layout->addLayout(lay);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque la valeur de l'entier est modifié.
 */
void fonction_source_entier_widget::on_entier_changed( int valeur )
{
    ((fonction_source_entier*)m_fonction)->set_valeur( valeur );
    m_fonction->modifier();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsque l'état de verrouillage de la fonction associée change.
 */
void fonction_source_entier_widget::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
        m_spin_box->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
    else
        m_spin_box->setEnabled( false );
}

