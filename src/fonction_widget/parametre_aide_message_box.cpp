#include "entete/fonction_widget/parametre_aide_message_box.h"

#include "entete/projet/base_parametre.h"
#include "entete/projet/base_fonction.h"
#include <QVBoxLayout>
#include <QListWidget>
#include <QLabel>

parametre_aide_message_box::parametre_aide_message_box(QWidget *parent, const base_parametre* parametre)
    : QDialog(parent), m_parametre( parametre )
{
    init();
}

void parametre_aide_message_box::init()
{
    setWindowTitle("Fonction " + m_parametre->get_fonction_parent()->get_nom());

    QVBoxLayout * central_layout = new QVBoxLayout();
    central_layout->setMargin(5);
    central_layout->setSpacing(0);

    QLabel * item_nom = new QLabel("Paramètre " + m_parametre->get_nom());
    item_nom->setObjectName( "AideNomParametre" );
    central_layout->addWidget( item_nom );

    QLabel * item_aide = new QLabel(m_parametre->get_aide());
    item_aide->setObjectName( "AideParametre" );
    central_layout->addWidget( item_aide );

    QLabel * item_algo = new QLabel("Algorithme : " + m_parametre->get_aide_algorithme());
    item_algo->setObjectName( "AideAlgoParametre" );
    central_layout->addWidget( item_algo );

    setLayout( central_layout );
    resize(QSize(800,200));
}
