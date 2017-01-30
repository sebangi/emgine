#include "entete/fonction_widget/parametre_aide_message_box.h"

#include "entete/projet/base_parametre.h"
#include "entete/projet/base_fonction.h"
#include <QVBoxLayout>
#include <QListWidget>

parametre_aide_message_box::parametre_aide_message_box(QWidget *parent, const base_parametre* parametre)
    : QDialog(parent), m_parametre( parametre )
{
    init();
}

void parametre_aide_message_box::init()
{
    setWindowTitle("Menu d'aide d'un paramètre");

    QVBoxLayout * central_layout = new QVBoxLayout();
    central_layout->setMargin(5);
    central_layout->setSpacing(0);

    QListWidget * liste = new QListWidget;
    central_layout->addWidget(liste);
    liste->addItem( new QListWidgetItem(m_parametre->get_nom()) );

    setLayout( central_layout );

    //setText(m_parametre->get_fonction_parent()->get_nom());


    //setText("Paramètre " + m_parametre->get_nom() + " : \n" + m_parametre->get_aide());
}
