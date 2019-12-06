/** \file base_parametre_widget.cpp
 * \brief Fichier d'implémentation de la classe base_parametre_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_parametre_widget.h"

#include "entete/explorateur/explorateur.h"
#include "entete/explorateur/noeud_parametre.h"
#include "entete/fenetre_principale.h"
#include "entete/fonction_widget/parametre_aide_message_box.h"
#include "entete/projet/base_fonction.h"
#include "entete/projet/base_parametre.h"

#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QStyle>
#include <QStyleOption>

#include <math.h>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_parametre_widget.
 * \param param Un pointeur sur le paramètre à afficher.
 * \param parent Un pointeur sur le widget parent.
 */
base_parametre_widget::base_parametre_widget(base_parametre* param, QWidget* parent)
    : QWidget(parent), m_parametre(param)
{
    init();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe base_parametre_widget.
 */
base_parametre_widget::~base_parametre_widget()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'événement paintEvent.
 * \param e Un pointeur sur l'événement.
 */
void base_parametre_widget::paintEvent(QPaintEvent * e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelé lorsque le verrouillage du paramètre change.
 */
void base_parametre_widget::informer_verrouillage_change()
{
    mettre_a_jour_configuration();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void base_parametre_widget::init()
{
    QHBoxLayout * main_layout = new QHBoxLayout();
    main_layout->setMargin(5);
    main_layout->setSpacing(5);

    QString s( m_parametre->get_nom() );
    QLabel * nom = new QLabel( s + " : " );
    nom->setObjectName("NomParametre");
    nom->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    nom->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    main_layout->addWidget(nom,3);

    QLabel * valeur = new QLabel( calcul_valeur_courte() );
    valeur->setObjectName("ValeurCourte");
    valeur->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    valeur->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    main_layout->addWidget(valeur,7);

    m_configuration_bouton = new QPushButton();
    m_configuration_bouton->setObjectName("BoutonParametreWidget");
    m_configuration_bouton->setFixedSize(30,30);
    connect(m_configuration_bouton, SIGNAL(released()), this, SLOT(on_inverser_configuration()));
    main_layout->addWidget(m_configuration_bouton,1);
    mettre_a_jour_configuration();

    m_aide_bouton = new QPushButton();
    m_aide_bouton->setObjectName("BoutonParametreWidget");
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_aide_bouton->setIcon( icon1 );
    m_aide_bouton->setFixedSize(30,30);
    connect(m_aide_bouton, SIGNAL(released()), this, SLOT(on_aide()));
    main_layout->addWidget(m_aide_bouton,1);

    setLayout(main_layout);
    update_object_name();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour la visualisation de la configuration.
*/
void base_parametre_widget::mettre_a_jour_configuration()
{
    QIcon icon1;
    if ( m_parametre->configuration_visible() )
        icon1.addFile(QString::fromUtf8(":/icons/log.png"), QSize(), QIcon::Normal, QIcon::Off);
    else
        icon1.addFile(QString::fromUtf8(":/icons/no_log.png"), QSize(), QIcon::Normal, QIcon::Off);

    m_configuration_bouton->setIcon( icon1 );
    m_configuration_bouton->setEnabled( ! m_parametre->est_verrouille_avec_parent() );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour du nom de l'objet.
*/
void base_parametre_widget::update_object_name()
{
    setObjectName("base_parametre_widget");

    style()->unpolish(this);
    style()->polish(this);
}

/** --------------------------------------------------------------------------------------
 * \brief Affiche l'aide du paramètre associé.
 */
void base_parametre_widget::aide()
{
    parametre_aide_message_box msgBox(this, m_parametre);

    msgBox.exec();
}

/** --------------------------------------------------------------------------------------
 * \brief Calcule et retourne la valeur du paramètre associé au format raccourci.
 * \return La valeur courte du paramètre associé.
 */
QString base_parametre_widget::calcul_valeur_courte() const
{
    QString s = m_parametre->get_valeur_courte();

    s.replace ( "\n", "|" );
    if ( s.size() > 40 )
    {
        s = s.mid(0,40);
        s += "...";
    }

    return s;
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'événement event.
 * \param e Un pointeur sur l'événement.
 * \return Un booléen indiquant sur l'événement a été traité.
 */
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

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'affichage de l'aide.
 */
void base_parametre_widget::on_aide()
{
    aide();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'inversion de configuration.
 */
void base_parametre_widget::on_inverser_configuration()
{
    m_parametre->inverser_configuration_visibilite();
    mettre_a_jour_configuration();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'événement mouseDoubleClickEvent.
 * \param e Un pointeur sur l'événement.
 */
void base_parametre_widget::mouseDoubleClickEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
        m_parametre->selectionner();
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de l'événement mouseReleaseEvent.
 * \param e Un pointeur sur l'événement.
 */
void base_parametre_widget::mouseReleaseEvent( QMouseEvent * e )
{
    if ( e->button() == Qt::LeftButton )
        m_parametre->selectionner();
}

