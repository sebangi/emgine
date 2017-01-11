#include "entete/fonction_widget/base_fonction_widget.h"
#include <QVBoxLayout>
#include <QSpacerItem>
#include <QLabel>
#include <QStyle>
#include <QStyleOption>
#include <QPainter>
#include <QApplication>
#include <QMessageBox>
#include "entete/projet/base_fonction.h"
#include "entete/fonction_widget/base_parametre_widget.h"
#include "entete/fenetre_principale.h"
#include <iostream>

base_fonction_widget::base_fonction_widget(base_fonction* fonction, QWidget* parent)
    : QWidget(parent), m_fonction(fonction), m_separation(NULL)
{
    init();
    init_connect();
}

base_fonction_widget::~base_fonction_widget()
{
    if ( m_fonction != NULL )
    {
        disconnect( m_fonction, SIGNAL(signal_activation_fonction_change(base_fonction *)),
                      this, SLOT(on_externe_activation_fonction_change(base_fonction *)));
    }
}

void base_fonction_widget::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


base_fonction *base_fonction_widget::get_fonction()
{
    return m_fonction;
}

void base_fonction_widget::init()
{
    QStyle* style = QApplication::style();

    QVBoxLayout * central_layout = new QVBoxLayout();
    central_layout->setMargin(5);
    central_layout->setSpacing(5);

    QToolBar * toolbar = new QToolBar();
    toolbar->setMovable(false);

    m_parametre_bouton = new QPushButton();
    m_parametre_bouton->setObjectName("BoutonFonctionWidget");
    m_parametre_bouton->setIconSize(QSize(24,24));
    m_parametre_bouton->setFixedHeight(32);
    connect(m_parametre_bouton, SIGNAL(released()), this, SLOT(on_parametre_switch()));
    toolbar->addWidget(m_parametre_bouton);

    m_actif_bouton = new QPushButton();
    m_actif_bouton->setObjectName("BoutonFonctionWidget");
    m_actif_bouton->setIconSize(QSize(24,24));
    m_actif_bouton->setFixedHeight(32);
    connect(m_actif_bouton, SIGNAL(released()), this, SLOT(on_inverser_activation()));
    toolbar->addWidget(m_actif_bouton);

    m_aide_bouton = new QPushButton();
    m_aide_bouton->setObjectName("BoutonFonctionWidget");
    QIcon icon1;
    icon1.addFile(QString::fromUtf8("icons/info.png"), QSize(), QIcon::Normal, QIcon::Off);
    m_aide_bouton->setIcon( icon1 );
    m_aide_bouton->setIconSize(QSize(24,24));
    m_aide_bouton->setFixedHeight(32);
    connect(m_aide_bouton, SIGNAL(released()), this, SLOT(on_aide()));
    toolbar->addWidget(m_aide_bouton);

    QLabel * label = new QLabel( m_fonction->get_nom() );
    label->setObjectName("NomFonction");
    label->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    label->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    toolbar->addWidget(label);

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

    m_separation = new QFrame;
    m_separation->setFrameStyle(QFrame::HLine | QFrame::Raised);
    m_parametre_layout->addWidget(m_separation);

    if ( m_fonction != NULL )
    {
        base_fonction::parametres_const_iterateur it;
        for ( it = m_fonction->parametres_begin(); it != m_fonction->parametres_end(); ++it )
        {
            base_parametre_widget* w = new base_parametre_widget(it->second);
            m_parametre_layout->addWidget(w);
        }
    }

    if ( m_fonction != NULL )
        m_parametre_widget->setVisible( m_fonction->get_parametre_visible() );

    central_layout->addWidget( m_parametre_widget );
    setLayout(central_layout);
    update_actif_bouton();
    update_parametre_bouton();
    update_object_name();
}

/** --------------------------------------------------------------------------------------
 \brief Mise à jour du bouton d'activation.
*/
void base_fonction_widget::update_actif_bouton()
{
    QStyle* style = QApplication::style();
    if ( m_fonction != NULL )
    {
        if ( m_fonction->est_active() )
            m_actif_bouton->setIcon( style->standardIcon( QStyle::SP_MediaPause ) );
        else
            m_actif_bouton->setIcon( style->standardIcon( QStyle::SP_MediaPlay ) );
    }
    else
        m_actif_bouton->setIcon( style->standardIcon( QStyle::SP_MediaPlay ) );
}


/** --------------------------------------------------------------------------------------
 \brief Mise à jour du bouton d'activation.
*/
void base_fonction_widget::update_parametre_bouton()
{
    QStyle* style = QApplication::style();

    if ( m_fonction != NULL )
    {
        if ( m_fonction->get_parametre_visible() )
            m_parametre_bouton->setIcon( style->standardIcon( QStyle::SP_TitleBarShadeButton ) );
        else
            m_parametre_bouton->setIcon( style->standardIcon( QStyle::SP_TitleBarUnshadeButton ) );
    }
    else
        m_parametre_bouton->setIcon( style->standardIcon( QStyle::SP_TitleBarUnshadeButton ) );
}

/** --------------------------------------------------------------------------------------
 \brief Mise à jour du nom de l'objet.
*/
void base_fonction_widget::update_object_name()
{
    if ( m_fonction != NULL )
    {
        if ( ! m_fonction->est_active() )
            setObjectName("FonctionInactiveWidget");
        else if ( m_fonction->get_type() == base_fonction::fonction_source )
            setObjectName("FonctionSourceWidget");
        else if ( m_fonction->get_type() == base_fonction::fonction_conversion )
            setObjectName("FonctionConversionWidget");
        else if ( m_fonction->get_type() == base_fonction::fonction_sortie )
            setObjectName("FonctionSortieWidget");

        style()->unpolish(this);
        style()->polish(this);

        if ( m_separation != NULL )
        {
            if ( ! m_fonction->est_active() )
                m_separation->setObjectName("separation_inactive");
            else if (  m_fonction->get_type() == base_fonction::fonction_source  )
                m_separation->setObjectName("separation_source");
            else if (  m_fonction->get_type() == base_fonction::fonction_conversion  )
                m_separation->setObjectName("separation_conversion");
            else if (  m_fonction->get_type() == base_fonction::fonction_sortie  )
                m_separation->setObjectName("separation_sortie");

            style()->unpolish(m_separation);
            style()->polish(m_separation);
        }
    }
}

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
 \brief Le bouton d'inversion d'activation est activé.
*/
void base_fonction_widget::on_inverser_activation()
{
    if ( m_fonction != NULL )
    {
        m_fonction->inverser_activation();
    }
}

/** --------------------------------------------------------------------------------------
 \brief L'activation de la fonction est modifié.
*/
void base_fonction_widget::on_externe_activation_fonction_change(base_fonction * f)
{
    update_actif_bouton();
    update_object_name();
}

/** --------------------------------------------------------------------------------------
 \brief Le bouton fermer est activé.
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
                delete m_fonction;
                break;
        }
    }
}

void base_fonction_widget::on_parametre_switch()
{
    if ( m_fonction != NULL )
    {
        m_fonction->set_parametre_visible( ! m_fonction->get_parametre_visible() );

        update_parametre_bouton();
        QSize save_size = size();
        m_fonction->get_parametre_visible();
        m_parametre_widget->setVisible( m_fonction->get_parametre_visible() );
        adjustSize();
        save_size.setHeight( size().height() );
        resize(save_size);
        fenetre_principale::adjust_size_vue_fonction();
    }
}

void base_fonction_widget::on_aide()
{
    aide();
}

void base_fonction_widget::init_connect()
{
    if ( m_fonction != NULL )
    {
        connect( m_fonction, SIGNAL(signal_activation_fonction_change(base_fonction *)),
             this, SLOT(on_externe_activation_fonction_change(base_fonction *)));
    }
}


