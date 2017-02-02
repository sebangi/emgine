#include "entete/fonction_widget/selecteur_fonction_dialog.h"
#include "entete/define.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QStyle>
#include <iostream>

selecteur_fonction_dialog::selecteur_fonction_dialog(base_fonction::type_fonction type, QWidget *parent)
    : QDialog(parent), m_fonction(NULL)
{
    QStyle* style = QApplication::style();

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *recherche_layout = new QHBoxLayout;
    m_recherche = new line_edit();
    connect(m_recherche, SIGNAL (returnPressed()),this, SLOT (chercher()));
    connect(m_recherche, SIGNAL (focussed(bool)),this, SLOT (rechercheFocussed(bool)));

    recherche_layout->addWidget(m_recherche);
    m_bouton_recherche = new QPushButton();
    m_bouton_recherche->setIcon(style->standardIcon( QStyle::SP_FileDialogContentsView ));
    recherche_layout->addWidget(m_bouton_recherche);

    m_grid_layout = new QGridLayout;
    init_choix(type);

    mainLayout->addLayout(recherche_layout);
    mainLayout->addLayout(m_grid_layout);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);

    if ( type == base_fonction::fonction_source )
        setWindowTitle("Quelle source souhaitez-vous ?");
    else if ( type == base_fonction::fonction_conversion )
        setWindowTitle("Quelle fonction souhaitez-vous ?");
    else
        setWindowTitle("Quelle sortie souhaitez-vous ?");

    m_bouton_recherche->setFocus();
}

base_fonction *selecteur_fonction_dialog::get_fonction() const
{
    return m_fonction;
}

void selecteur_fonction_dialog::init_choix(base_fonction::type_fonction type)
{
    int debut = debut_fonction_conversion;
    int fin = fin_fonction_conversion;

    if ( type == base_fonction::fonction_source )
    {
        debut = debut_fonction_source;
        fin = fin_fonction_source;
    }
    else if ( type == base_fonction::fonction_sortie )
    {
        debut = debut_fonction_sortie;
        fin = fin_fonction_sortie;
    }

    for ( int nom = debut; nom != fin; ++nom)
        ajouter_choix((type_id_fonction)nom);
}

void selecteur_fonction_dialog::ajouter_choix(type_id_fonction nom)
{
    bouton_choix_fonction * bouton = new bouton_choix_fonction(nom);
    connect(bouton, SIGNAL (released()),this, SLOT (choisir()));

    m_boutons.push_back( bouton );

    m_grid_layout->addWidget(bouton);
}

void selecteur_fonction_dialog::choisir()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    int indexOfButton = m_grid_layout->indexOf(buttonWidget);
    int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton, columnSpanOfLabel;

    m_grid_layout->getItemPosition(indexOfButton, &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfLabel);

    QLayoutItem *item = m_grid_layout->itemAtPosition(rowOfButton, columnOfButton);
    bouton_choix_fonction *clickedButton = (bouton_choix_fonction*)(item->widget());
    if (!clickedButton)
        return;

    m_fonction = clickedButton->get_fonction();
    m_fonction->set_id( clickedButton->get_id_fonction() );

    done( QDialog::Accepted );
}

void selecteur_fonction_dialog::chercher()
{
    std::cout << "Chercher" << std::endl;
}

void selecteur_fonction_dialog::rechercheFocussed(bool hasFocus)
{
    if ( hasFocus)
        m_bouton_recherche->setFocus();
}


