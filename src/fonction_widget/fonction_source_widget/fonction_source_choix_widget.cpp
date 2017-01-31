#include "entete/fonction_widget/fonction_source_widget/fonction_source_choix_widget.h"
#include "entete/fonction/fonction_source/fonction_source_choix.h"
#include "entete/parametre/parametre_choix.h"
#include <iostream>
#include <QHBoxLayout>

fonction_source_choix_widget::fonction_source_choix_widget(base_fonction *fonction, QWidget *parent)
    : base_fonction_widget(fonction, parent)
{
    init();
}

void fonction_source_choix_widget::init()
{
    QHBoxLayout * lay = new QHBoxLayout();
    lay->setSizeConstraint(QLayout::SetMaximumSize);

    m_liste = new QListWidget();
    m_liste->setMinimumHeight(20);
    m_liste->setMaximumHeight(400);
    m_liste->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Maximum);

    if ( m_fonction != NULL )
        if ( m_fonction->get_conteneur() != NULL )
            if ( m_fonction->get_conteneur()->est_parametre() )
                if ( ((base_parametre *)m_fonction->get_conteneur())->get_type() == TYPE_PARAM_CHOIX )
                {
                    QStringList choix = ((parametre_choix *)m_fonction->get_conteneur())->get_choix();

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

    lay->addWidget(m_liste);

    /*
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
*/

    m_specialisation_layout->addLayout(lay);
}

/*
void fonction_source_choix_widget::on_oui_stateChanged(int checkState)
{
    ((fonction_source_booleen*)m_fonction)->set_valeur( checkState );
    m_check_non->setChecked( ! m_check_oui->isChecked() );
    m_fonction->modifier();
}

void fonction_source_choix_widget::on_non_stateChanged(int checkState)
{
    ((fonction_source_booleen*)m_fonction)->set_valeur( ! checkState );
    m_check_oui->setChecked( ! m_check_non->isChecked() );
    m_fonction->modifier();
}
*/

void fonction_source_choix_widget::informer_verrouillage_change()
{
    if ( m_fonction != NULL )
    {
        //   m_check_non->setEnabled( m_fonction->est_verrouille_avec_parent() );
        //   m_check_oui->setEnabled( m_fonction->est_verrouille_avec_parent() );
    }
    else
    {
        //  m_check_non->setEnabled( false );
        //  m_check_oui->setEnabled( false );
    }
}

