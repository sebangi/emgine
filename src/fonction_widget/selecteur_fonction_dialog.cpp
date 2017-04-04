/** \file selecteur_fonction_dialog.cpp
 * \brief Fichier d'implémentation de la classe selecteur_fonction_dialog.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/selecteur_fonction_dialog.h"

#include "entete/define.h"

#include <QApplication>
#include <QDialogButtonBox>
#include <QFontMetrics>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QStyle>
#include <QVBoxLayout>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe selecteur_fonction_dialog.
 * \param type Le type de fonction à créer.
 * \param conteneur Un pointeur sur le conteneur dans lequel il faut ajouter la fonction.
 * \param parent Un pointeur sur le widget parent.
 */
selecteur_fonction_dialog::selecteur_fonction_dialog(type_fonction type, fonctions_conteneur * conteneur, QWidget *parent)
    : QDialog(parent), m_fonction(NULL), m_nb_colonnes(1)
{
    QVBoxLayout *mainLayout = new QVBoxLayout;

    QHBoxLayout *recherche_layout = new QHBoxLayout;
    m_recherche = new QLineEdit();
    m_recherche->setClearButtonEnabled(true);
    connect(m_recherche, SIGNAL (textChanged(const QString &)),this, SLOT (on_chercher(const QString &)));
    m_recherche->setFocusPolicy(Qt::StrongFocus);

    recherche_layout->addWidget(m_recherche);

    m_grid_layout = new QGridLayout;
    calcul_nb_colonnes(type);
    init_choix(type, conteneur);

    mainLayout->addLayout(recherche_layout);
    mainLayout->addLayout(m_grid_layout);

    m_cancel_button = new QDialogButtonBox(QDialogButtonBox::Cancel);
    connect(m_cancel_button, SIGNAL(accepted()), this, SLOT(accept()));
    connect(m_cancel_button, SIGNAL(rejected()), this, SLOT(reject()));
    mainLayout->addWidget(m_cancel_button);
    setLayout(mainLayout);

    if ( type == type_fonction::fonction_source )
        setWindowTitle("Quelle source souhaitez-vous ?");
    else if ( type == type_fonction::fonction_conversion )
        setWindowTitle("Quelle fonction souhaitez-vous ?");
    else
        setWindowTitle("Quelle sortie souhaitez-vous ?");

    setMinimumWidth( std::max(m_nb_colonnes * 200,400) );

    QList<QPushButton *> buttonList = findChildren<QPushButton *>();
    foreach(QPushButton *pb, buttonList) {
        pb->setAutoDefault( false );
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Accessur de la fonction créée.
 * \return Un pointeur sur la fonction créée.
 */
base_fonction *selecteur_fonction_dialog::get_fonction() const
{
    return m_fonction;
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise les choix.
 * \param type Le type de fonction à créer.
 * \param conteneur Un pointeur sur le conteneur dans lequel il faut ajouter la fonction.
 */
void selecteur_fonction_dialog::init_choix(type_fonction type, fonctions_conteneur * conteneur)
{
    int debut = debut_fonction_conversion;
    int fin = fin_fonction_conversion;

    bool type_choix = false;

    if ( conteneur != NULL )
        if ( conteneur->est_parametre() )
            type_choix = ((base_parametre *)conteneur)->get_type() == TYPE_PARAM_CHOIX;

    if ( type_choix )
    {
        debut = debut_fonction_source_choix;
        fin = fin_fonction_source_choix;
    }
    else if ( type == type_fonction::fonction_source )
    {
        debut = debut_fonction_source;
        fin = fin_fonction_source;
    }
    else if ( type == type_fonction::fonction_sortie )
    {
        debut = debut_fonction_sortie;
        fin = fin_fonction_sortie;
    }

    for ( int nom = debut; nom != fin; ++nom)
        ajouter_choix((type_id_fonction)nom);
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute un choix.
 * \param id L'identifiant de la fonction à ajouter dans les choix.
 */
void selecteur_fonction_dialog::ajouter_choix(type_id_fonction id)
{
    bouton_choix_fonction * bouton = new bouton_choix_fonction(id);
    connect(bouton, SIGNAL (released()),this, SLOT (on_choix()));

    int ligne = m_boutons.size() / 2 ;
    int colonne = m_boutons.size() % 2 ;

    m_boutons.push_back( bouton );
    m_grid_layout->addWidget(bouton, ligne, colonne);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lorsqu'un choix est effectué.
 */
void selecteur_fonction_dialog::on_choix()
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

/** --------------------------------------------------------------------------------------
 * \brief Rend visible uniquement les fonctions de le recherche.
 */
void selecteur_fonction_dialog::chercher()
{
    for ( QList< bouton_choix_fonction * >::iterator it = m_boutons.begin(); it != m_boutons.end(); ++it )
        (*it)->mettre_a_jour_visibilite( m_recherche->text() );

    adjustSize();
    adjustSize();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de recherche.
 */
void selecteur_fonction_dialog::on_chercher(const QString &)
{
    chercher();
}

/** --------------------------------------------------------------------------------------
 * \brief Calcule le nombre de colonnes de choix en fonction de leur nombre.
 * \param type Le type de fonction à créer.
 */
void selecteur_fonction_dialog::calcul_nb_colonnes(type_fonction type)
{
    int nb_fonctions = 0;

    if ( type == type_fonction::fonction_source )
        nb_fonctions = fin_fonction_source - debut_fonction_source;
    else if ( type == type_fonction::fonction_conversion )
        nb_fonctions = fin_fonction_conversion - debut_fonction_conversion;
    else
        nb_fonctions = fin_fonction_sortie - debut_fonction_sortie;

    m_nb_colonnes = nb_fonctions / 5 + 1;
    m_nb_colonnes = std::min( m_nb_colonnes, 4);

}
