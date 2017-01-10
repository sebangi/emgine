#include "entete/selecteur_fonction_dialog.h"
#include "entete/define.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <iostream>

selecteur_fonction_dialog::selecteur_fonction_dialog(base_fonction::type_fonction type, QWidget *parent)
    : QDialog(parent), m_fonction(NULL)
{
    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);

    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    m_grid_layout = new QGridLayout;
    init_choix(type);

    mainLayout->addLayout(m_grid_layout);
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);

    if ( type == base_fonction::fonction_source )
        setWindowTitle("Quelle source souhaitez-vous ?");
    else if ( type == base_fonction::fonction_conversion )
        setWindowTitle("Quelle fonction souhaitez-vous ?");
    else
        setWindowTitle("Quelle sortie souhaitez-vous ?");
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
    bouton_choix_fonction * button = new bouton_choix_fonction(nom);
    connect(button, SIGNAL (released()),this, SLOT (choisir()));

    m_grid_layout->addWidget(button);
}

void selecteur_fonction_dialog::choisir()
{
    QWidget *buttonWidget = qobject_cast<QWidget*>(sender());
    if (!buttonWidget)
        return;

    int indexOfButton = m_grid_layout->indexOf(buttonWidget);
    int rowOfButton, columnOfButton, rowSpanOfButton, columnSpanOfButton, columnSpanOfLabel;

    m_grid_layout->getItemPosition(indexOfButton,
                                   &rowOfButton, &columnOfButton, &rowSpanOfButton, &columnSpanOfLabel);

    QLayoutItem *item = m_grid_layout->itemAtPosition(rowOfButton, columnOfButton);
    bouton_choix_fonction *clickedButton = (bouton_choix_fonction*)(item->widget());
    if (!clickedButton)
        return;

    m_fonction = clickedButton->get_fonction();
    m_fonction->set_id( clickedButton->get_id_fonction() );

    done( QDialog::Accepted );
}





