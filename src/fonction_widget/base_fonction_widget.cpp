/**
 * \file base_fonction_widget.cpp
 * \brief Fichier d'implémentation de la classe base_fonction_widget.
 * \author Sébastien Angibaud
 */

#include "entete/fonction_widget/base_fonction_widget.h"

#include "entete/fenetre_principale.h"
#include "entete/fonction_widget/base_parametre_widget.h"
#include "entete/projet/base_fonction.h"

#include <QApplication>
#include <QLabel>
#include <QMessageBox>
#include <QPainter>
#include <QSpacerItem>
#include <QStyle>
#include <QStyleOption>
#include <QVBoxLayout>

/** --------------------------------------------------------------------------------------
 * \brief Constructeur de la classe base_fonction_widget.
 * \param fonction Un pointeur sur la fonction associée au composant.
 * \param parent Un pointeur sur le widget parent.
 */
base_fonction_widget::base_fonction_widget(base_fonction* fonction, QWidget* parent)
    : QWidget(parent), m_fonction(fonction)
{
    init();
    connecter_fonction();
}

/** --------------------------------------------------------------------------------------
 * \brief Destructeur de la classe base_fonction_widget.
 */
base_fonction_widget::~base_fonction_widget()
{
}

/** --------------------------------------------------------------------------------------
 * \brief Surcharge de la fonction paintEvent.
 * \param e L'événement survenu.
 */
void base_fonction_widget::paintEvent(QPaintEvent * e)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}

/** --------------------------------------------------------------------------------------
 * \brief Accesseur de la fonction associée au widget.
 * \return Un pointeur sur la fonction associée au widget.
 */
base_fonction *base_fonction_widget::get_fonction()
{
    return m_fonction;
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le widget en fonction de l'état de verrouillage actuel.
 */
void base_fonction_widget::mettre_a_jour_verrouillage()
{
    update_verrouillage_bouton();
    update_actif_bouton();
    update_close_bouton();

    for ( type_liste_parametre_widgets::iterator it = m_parametre_widgets.begin();
          it != m_parametre_widgets.end(); ++it )
        (*it)->informer_verrouillage_change();

    informer_verrouillage_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le widget.
 */
void base_fonction_widget::init()
{
    QStyle* style = QApplication::style();

    QVBoxLayout * central_layout = new QVBoxLayout();
    central_layout->setMargin(5);
    central_layout->setSpacing(0);

    QToolBar * toolbar = new QToolBar();
    toolbar->setMovable(false);

    m_visibilite_bouton = new QPushButton();
    m_visibilite_bouton->setObjectName("BoutonFonctionWidget");
    m_visibilite_bouton->setIconSize(QSize(24,24));
    m_visibilite_bouton->setFixedHeight(32);
    connect(m_visibilite_bouton, SIGNAL(released()), this, SLOT(on_visibilite_change()));
    toolbar->addWidget(m_visibilite_bouton);

    m_actif_bouton = new QPushButton();
    m_actif_bouton->setObjectName("BoutonFonctionWidget");
    m_actif_bouton->setIconSize(QSize(24,24));
    m_actif_bouton->setFixedHeight(32);
    connect(m_actif_bouton, SIGNAL(released()), this, SLOT(on_inverser_activation()));
    toolbar->addWidget(m_actif_bouton);

    m_verrouillage_bouton = new QPushButton();
    m_verrouillage_bouton->setObjectName("BoutonFonctionWidget");
    m_verrouillage_bouton->setIconSize(QSize(24,24));
    m_verrouillage_bouton->setFixedHeight(32);
    connect(m_verrouillage_bouton, SIGNAL(released()), this, SLOT(on_inverser_verrouillage()));
    toolbar->addWidget(m_verrouillage_bouton);

    m_aide_bouton = new QPushButton();
    m_aide_bouton->setObjectName("BoutonFonctionWidget");
    QIcon icon1;
    icon1.addFile(QString::fromUtf8(":/icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_aide_bouton->setIcon( icon1 );
    m_aide_bouton->setIconSize(QSize(24,24));
    m_aide_bouton->setFixedHeight(32);
    connect(m_aide_bouton, SIGNAL(released()), this, SLOT(on_aide()));
    toolbar->addWidget(m_aide_bouton);

    m_nom_label = new QLabel( QObject::tr( qUtf8Printable( get_nom() ) ) );
    m_nom_label->setObjectName("NomFonction");
    m_nom_label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_nom_label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    toolbar->addWidget(m_nom_label);

    m_fermer_bouton = new QPushButton();
    m_fermer_bouton->setObjectName("BoutonFonctionWidget");
    m_fermer_bouton->setIcon( style->standardIcon( QStyle::SP_DialogCloseButton ) );
    m_fermer_bouton->setIconSize(QSize(24,24));
    m_fermer_bouton->setFixedHeight(32);
    connect(m_fermer_bouton, SIGNAL(released()), this, SLOT(on_fermer()));
    toolbar->addWidget(m_fermer_bouton);

    central_layout->addWidget(toolbar);

    m_parametre_widget = new QWidget();
    m_parametre_layout = new QVBoxLayout();
    m_parametre_layout->setMargin(0);
    m_parametre_layout->setSpacing(0);
    m_parametre_widget->setLayout(m_parametre_layout);
    m_separation1 = new QFrame;
    m_separation1->setFrameStyle(QFrame::HLine | QFrame::Raised);
    m_parametre_layout->addWidget(m_separation1);

    m_specialisation_widget = new QWidget();
    m_specialisation_layout = new QVBoxLayout();
    m_specialisation_layout->setMargin(0);
    m_specialisation_layout->setSpacing(0);
    m_specialisation_widget->setLayout(m_specialisation_layout);
    m_separation2 = new QFrame;
    m_separation2->setFrameStyle(QFrame::HLine | QFrame::Raised);
    m_specialisation_layout->addWidget(m_separation2);

    if ( m_fonction != NULL )
    {
        base_fonction::parametres_const_iterateur it;
        for ( it = m_fonction->parametres_begin(); it != m_fonction->parametres_end(); ++it )
        {
            if ( it->second->editable() )
            {
                base_parametre_widget* w = new base_parametre_widget(it->second);
                m_parametre_layout->addWidget(w);
                m_parametre_widgets.push_back(w);
            }
        }
    }

    central_layout->addWidget( m_parametre_widget );
    central_layout->addWidget( m_specialisation_widget );
    setLayout(central_layout);
    update_actif_bouton();
    update_verrouillage_bouton();
    update_close_bouton();
    update_visibilite_bouton();
    update_object_name();
    update_visibilite();
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le bouton d'activation.
 */
void base_fonction_widget::update_actif_bouton()
{
    QIcon icon1;

    m_actif_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() );

    if ( m_fonction != NULL )
    {
        if ( m_fonction->est_active_avec_parent() )
        {
            m_actif_bouton->setToolTip("Cliquer pour ne pas exécuter la fonction");
            icon1.addFile(QString::fromUtf8(":/icons/compile.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        else
        {
            m_actif_bouton->setToolTip("Cliquer pour exécuter la fonction");
            icon1.addFile(QString::fromUtf8(":/icons/non_compile.png"), QSize(), QIcon::Normal, QIcon::Off);
            if ( ! m_fonction->parents_actifs() )
                m_actif_bouton->setEnabled(false);
        }
    }
    else
    {
        m_actif_bouton->setToolTip("Cliquer pour exécuter la fonction");
        icon1.addFile( QString::fromUtf8(":/icons/non_compile.png"), QSize(), QIcon::Normal, QIcon::Off );
        m_actif_bouton->setEnabled(false);
    }

    m_actif_bouton->setIcon( icon1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le bouton de fermeture.
 */
void base_fonction_widget::update_close_bouton()
{
    m_fermer_bouton->setEnabled( ! m_fonction->est_verrouille_avec_parent() );
}


/** --------------------------------------------------------------------------------------
 * \brief Met à jour le bouton de verrouillage.
 */
void base_fonction_widget::update_verrouillage_bouton()
{
    QIcon icon1;

    m_verrouillage_bouton->setEnabled( ! m_fonction->parents_verrouilles() );

    if ( m_fonction != NULL )
    {
        if ( m_fonction->est_verrouille_avec_parent() )
            icon1.addFile(QString::fromUtf8(":/icons/verrouille.png"), QSize(), QIcon::Normal, QIcon::Off);
        else
        {
            icon1.addFile(QString::fromUtf8(":/icons/deverrouille.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
    }
    else
    {
        icon1.addFile( QString::fromUtf8(":/icons/verrouille.png"), QSize(), QIcon::Normal, QIcon::Off );
        m_verrouillage_bouton->setEnabled(false);
    }

    m_verrouillage_bouton->setIcon( icon1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le bouton de visibilité.
 */
void base_fonction_widget::update_visibilite_bouton()
{
    QIcon icon1;

    if ( m_fonction != NULL )
    {
        if ( m_fonction->get_niveau_visibilite() >= 3 )
            icon1.addFile(QString::fromUtf8(":/icons/fleche_haut_double.png"), QSize(), QIcon::Normal, QIcon::Off);
        else if ( m_fonction->get_niveau_visibilite() >= 2 )
        {
            if ( m_fonction->get_max_niveau_visibilite() >= 3 )
                icon1.addFile(QString::fromUtf8(":/icons/fleche_haut_bas.png"), QSize(), QIcon::Normal, QIcon::Off);
            else
                icon1.addFile(QString::fromUtf8(":/icons/fleche_haut.png"), QSize(), QIcon::Normal, QIcon::Off);
        }
        else
            icon1.addFile(QString::fromUtf8(":/icons/fleche_bas.png"), QSize(), QIcon::Normal, QIcon::Off);
    }
    else
        icon1.addFile(QString::fromUtf8(":/icons/fleche_bas.png"), QSize(), QIcon::Normal, QIcon::Off);

    m_visibilite_bouton->setIcon( icon1 );
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour le widget en fonction du niveau de visibilité de la fonction associée.
 */
void base_fonction_widget::update_visibilite()
{
    QSize save_size = size();

    int niveau = m_fonction->get_niveau_visibilite();

    if ( m_fonction->a_parametre() )
    {
        m_specialisation_widget->setVisible( niveau >= 2 && m_fonction->get_max_niveau_visibilite() >= 3 );
        m_parametre_widget->setVisible( niveau >= m_fonction->get_max_niveau_visibilite() );
    }
    else
    {
        m_specialisation_widget->setVisible( niveau >= 2 );
        m_parametre_widget->setVisible( false );
    }

    adjustSize();
    save_size.setHeight( size().height() );
    resize(save_size);
}

/** --------------------------------------------------------------------------------------
 * \brief Met à jour les noms des objets.
 */
void base_fonction_widget::update_object_name()
{
    if ( m_fonction != NULL )
    {
        if ( ! m_fonction->est_active_avec_parent() )
            setObjectName("FonctionInactiveWidget");
        else if ( m_fonction->get_type() == type_fonction::fonction_source )
            setObjectName("FonctionSourceWidget");
        else if ( m_fonction->get_type() == type_fonction::fonction_conversion )
            setObjectName("FonctionConversionWidget");
        else if ( m_fonction->get_type() == type_fonction::fonction_sortie )
            setObjectName("FonctionSortieWidget");

        style()->unpolish(this);
        style()->polish(this);

        if ( ! m_fonction->est_active_avec_parent() )
        {
            m_separation1->setObjectName("separation_inactive");
            m_separation2->setObjectName("separation_inactive");
        }
        else if (  m_fonction->get_type() == type_fonction::fonction_source  )
        {
            m_separation1->setObjectName("separation_source");
            m_separation2->setObjectName("separation_source");
        }
        else if (  m_fonction->get_type() == type_fonction::fonction_conversion  )
        {
            m_separation1->setObjectName("separation_conversion");
            m_separation2->setObjectName("separation_conversion");
        }
        else if (  m_fonction->get_type() == type_fonction::fonction_sortie  )
        {
            m_separation1->setObjectName("separation_sortie");
            m_separation2->setObjectName("separation_sortie");
        }

        style()->unpolish(m_separation1);
        style()->polish(m_separation1);

        style()->unpolish(m_separation2);
        style()->polish(m_separation2);
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Affiche l'aide de la fonction associée.
 */
void base_fonction_widget::aide()
{
    if ( m_fonction != NULL )
    {
        QMessageBox msgBox(this);
        msgBox.setWindowTitle(m_fonction->get_nom());
        msgBox.setText(m_fonction->get_info_bulle());
        msgBox.exec();
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'inversion d'activation.
 */
void base_fonction_widget::on_inverser_activation()
{
    if ( m_fonction != NULL )
        m_fonction->inverser_activation();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'inversion de verrouillage.
 */
void base_fonction_widget::on_inverser_verrouillage()
{
    if ( m_fonction != NULL )
        m_fonction->inverser_verrouillage();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un changement d'activation de la fonction associée.
 * \param f Un pointeur sur la fonction associée.
 */
void base_fonction_widget::on_externe_activation_fonction_change(base_fonction * f)
{
    update_actif_bouton();
    update_object_name();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un changement de verrouillage de l'objet associé.
 * \param obj Un pointeur sur l'objet associé.
 */
void base_fonction_widget::on_externe_verrouillage_change(objet_selectionnable * obj)
{
    mettre_a_jour_verrouillage();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un changement de niveau de visibilité de la fonction associée.
 * \param f Un pointeur sur la fonction associée.
 */
void base_fonction_widget::on_externe_niveau_visibilite_change(base_fonction* f)
{
    update_visibilite_bouton();
    update_visibilite();
    emit signal_bfw_size_change();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de fermeture de la fonction.
 */
void base_fonction_widget::on_fermer()
{
    if ( m_fonction != NULL )
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Fonction " + m_fonction->get_nom());
        msgBox.setText("Voulez-vous vraiment supprimer la fonction " + m_fonction->get_nom() + " ?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
        msgBox.setDefaultButton(QMessageBox::Yes);
        msgBox.setButtonText(QMessageBox::Yes,tr("Oui"));
        msgBox.setButtonText(QMessageBox::Cancel,tr("Non"));
        int ret = msgBox.exec();

        switch (ret)
        {
            case QMessageBox::Yes:
                if ( m_fonction != NULL )
                {
                    deconnecter_fonction();

                    delete m_fonction;
                }
                break;
        }
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande de changement de niveau de visibilité.
 */
void base_fonction_widget::on_visibilite_change()
{
    if ( m_fonction != NULL )
        m_fonction->change_niveau_visibilite();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'une demande d'affichage de l'aide.
 */
void base_fonction_widget::on_aide()
{
    aide();
}

/** --------------------------------------------------------------------------------------
 * \brief Ajoute les connections pour la fonction associée.
 */
void base_fonction_widget::connecter_fonction()
{
    if ( m_fonction != NULL )
    {
        connect( m_fonction, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                 this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

        connect( m_fonction, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
                 this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

        connect( m_fonction, SIGNAL(signal_niveau_visibilite_change(base_fonction *)),
                 this, SLOT(on_externe_niveau_visibilite_change(base_fonction *)));
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Retire les connections de la fonction associée.
*/
void base_fonction_widget::deconnecter_fonction()
{
    if ( m_fonction != NULL )
    {
        disconnect( m_fonction, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                    this, SLOT(on_externe_activation_fonction_change(base_fonction *)));

        disconnect( m_fonction, SIGNAL(signal_verrouillage_change(objet_selectionnable *)),
                    this, SLOT(on_externe_verrouillage_change(objet_selectionnable *)));

        disconnect( m_fonction, SIGNAL(signal_niveau_visibilite_change(base_fonction *)),
                    this, SLOT(on_externe_niveau_visibilite_change(base_fonction *)));
    }
}

/** --------------------------------------------------------------------------------------
 * \brief Initialise le nom du widget.
*/
void base_fonction_widget::init_nom()
{
    m_nom_label->setText( get_nom() );
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction retournant le nom de la fonction à afficher.
 */
QString base_fonction_widget::get_nom() const
{
    return m_fonction->get_nom();
}

/** --------------------------------------------------------------------------------------
 * \brief Fonction appelée lors d'un changement de verrouillage.
 */
void base_fonction_widget::informer_verrouillage_change()
{
}

