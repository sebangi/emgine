#include "entete/fonction_widget/base_parametre_widget.h"
#include <QHBoxLayout>
#include <QLabel>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QMessageBox>
#include "entete/projet/base_parametre.h"
#include "entete/projet/base_fonction.h"
#include "entete/fenetre_principale.h"
#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/noeud_parametre.h"
#include <iostream>
#include <math.h>

base_parametre_widget::base_parametre_widget(base_parametre* param, QWidget* parent)
    : QWidget(parent), m_parametre(param)
{
    init();
}

base_parametre_widget::~base_parametre_widget()
{
}

void base_parametre_widget::paintEvent(QPaintEvent *)
 {
     QStyleOption opt;
     opt.init(this);
     QPainter p(this);
     style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

void base_parametre_widget::init()
{
    QStyle* style = QApplication::style();

    QHBoxLayout * main_layout = new QHBoxLayout();
    main_layout->setMargin(5);
    main_layout->setSpacing(5);

    QLabel * nom = new QLabel( m_parametre->get_nom() + " : " );
    nom->setObjectName("NomParametre");
    nom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    nom->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    main_layout->addWidget(nom,5);

    QLabel * valeur = new QLabel( calcul_valeur_courte() );
    valeur->setObjectName("valeur_courte");
    valeur->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    valeur->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    main_layout->addWidget(valeur,5);

    m_aide_bouton = new QPushButton();
    m_aide_bouton->setObjectName("BoutonParametreWidget");
    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_aide_bouton->setIcon( icon1 );
    m_aide_bouton->setFixedSize(30,30);
    connect(m_aide_bouton, SIGNAL(released()), this, SLOT(on_aide()));
    main_layout->addWidget(m_aide_bouton,1);

    setLayout(main_layout);
    update_object_name();
}

/** --------------------------------------------------------------------------------------
 \brief Mise à jour du nom de l'objet.
*/
void base_parametre_widget::update_object_name()
{
    setObjectName("base_parametre_widget");

    style()->unpolish(this);
    style()->polish(this);
}

void base_parametre_widget::aide()
{
    QMessageBox msgBox(this);
    msgBox.setWindowTitle(m_parametre->get_fonction_parent()->get_nom());
    msgBox.setText("Paramètre " + m_parametre->get_nom() + " : \n" + m_parametre->get_aide());
    msgBox.exec();
}

QString base_parametre_widget::calcul_valeur_courte() const
{
    QString s = m_parametre->get_valeur_courte();

    s.replace ( "\n", "|" );
    if ( s.size() > 20 )
    {
        s = s.mid(0,20);
        s += "...";
    }

    return s;
}

bool base_parametre_widget::event(QEvent* e)
{
    bool action = true;

    if (e->type() == QEvent::Enter)
        setObjectName("base_parametre_widget_hovered");
    else if (e->type()==QEvent::Leave)
        setObjectName("base_parametre_widget");
    else
        action = false;

    if ( action )
    {
        style()->unpolish(this);
        style()->polish(this);
    }

    return QWidget::event(e); // Or whatever parent class you have.
}

void base_parametre_widget::on_aide()
{
    aide();
}

void base_parametre_widget::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
        m_parametre->selectionner();
}

