#include "entete/fonction_widget/selecteur_fonction_dialog.h"
#include "entete/define.h"
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QApplication>
#include <QFontMetrics>
#include <QStyle>
#include <iostream>

selecteur_fonction_dialog::selecteur_fonction_dialog(base_fonction::type_fonction type, QWidget *parent)
    : QDialog(parent), m_fonction(NULL), m_nb_colonnes(1)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *recherche_layout = new QHBoxLayout;
    m_recherche = new QLineEdit();
    m_recherche->setClearButtonEnabled(true);
    connect(m_recherche, SIGNAL (returnPressed()),this, SLOT (chercher()));
    connect(m_recherche, SIGNAL (textChanged(const QString &)),this, SLOT (chercher(const QString &)));
    m_recherche->setFocusPolicy(Qt::StrongFocus);

    recherche_layout->addWidget(m_recherche);

    m_grid_layout = new QGridLayout;
    calcul_nb_colonnes(type);
    init_choix(type);

    mainLayout->addLayout(recherche_layout);
    mainLayout->addLayout(m_grid_layout);

    m_buttonBox = new QDialogButtonBox(QDialogButtonBox::Cancel);
    connect(m_buttonBox, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_buttonBox, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(m_buttonBox);
    setLayout(mainLayout);

    if ( type == base_fonction::fonction_source )
        setWindowTitle("Quelle source souhaitez-vous ?");
    else if ( type == base_fonction::fonction_conversion )
        setWindowTitle("Quelle fonction souhaitez-vous ?");
    else
        setWindowTitle("Quelle sortie souhaitez-vous ?");

    setMinimumWidth( std::max(m_nb_colonnes * 200,400) );

    QList<QPushButton *> buttonList = findChildren<QPushButton *>();
    foreach(QPushButton *pb, buttonList) {
        pb->setAutoDefault( false );
    }
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

    int ligne = m_boutons.size() / 2 ;
    int colonne = m_boutons.size() % 2 ;

    m_boutons.push_back( bouton );
    m_grid_layout->addWidget(bouton, ligne, colonne);
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
    for ( QList< bouton_choix_fonction * >::iterator it = m_boutons.begin(); it != m_boutons.end(); ++it )
        (*it)->mettre_a_jour_visibilite( m_recherche->text() );

    adjustSize();
    adjustSize();
}

void selecteur_fonction_dialog::chercher(const QString &)
{
    chercher();
}

void selecteur_fonction_dialog::calcul_nb_colonnes(base_fonction::type_fonction type)
{
    int nb_fonctions = 0;

    if ( type == base_fonction::fonction_source )
        nb_fonctions = fin_fonction_source - debut_fonction_source;
    else if ( type == base_fonction::fonction_conversion )
        nb_fonctions = fin_fonction_conversion - debut_fonction_conversion;
    else
        nb_fonctions = fin_fonction_sortie - debut_fonction_sortie;

    m_nb_colonnes = nb_fonctions / 5 + 1;
    m_nb_colonnes = std::min( m_nb_colonnes, 4);

}
