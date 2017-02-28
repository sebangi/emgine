/********************************************************************************
** Form generated from reading UI file 'fenetre_principale.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/
#ifndef UI_FENETRE_PRINCIPALE_H
#define UI_FENETRE_PRINCIPALE_H

/** 
 * \file entete/ui_fenetre_principale.h
 * \brief Fichier de déclaration de la classe Ui_fenetre_principale.
 * \author Sébastien Angibaud
 */

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

/**
  * \class Ui_fenetre_principale
  * \brief Classe représentant la fenètre principale du projet Emgine.
  * \author Sébastien Angibaud
 */
class Ui_fenetre_principale
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *centralLayout;
    QMenuBar *menuBar;
    QMenu *menuFichier;
    QMenu *menuAide;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *fenetre_principale)
    {
        if (fenetre_principale->objectName().isEmpty())
            fenetre_principale->setObjectName(QStringLiteral("fenetre_principale"));
        fenetre_principale->resize(650, 419);
        centralWidget = new QWidget(fenetre_principale);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        centralLayout = new QVBoxLayout();
        centralLayout->setSpacing(0);
        centralLayout->setObjectName(QStringLiteral("centralLayout"));

        verticalLayout_2->addLayout(centralLayout);

        fenetre_principale->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(fenetre_principale);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 25));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QStringLiteral("menuFichier"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QStringLiteral("menuAide"));
        fenetre_principale->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fenetre_principale);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setMovable(false);
        mainToolBar->setOrientation(Qt::Vertical);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setFloatable(true);
        fenetre_principale->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(fenetre_principale);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fenetre_principale->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuAide->menuAction());

        retranslateUi(fenetre_principale);

        QMetaObject::connectSlotsByName(fenetre_principale);
    } // setupUi

    void retranslateUi(QMainWindow *fenetre_principale)
    {
        fenetre_principale->setWindowTitle(QApplication::translate("fenetre_principale", "Mon d\303\251codeur", 0));
        menuFichier->setTitle(QApplication::translate("fenetre_principale", "Fichier", 0));
        menuAide->setTitle(QApplication::translate("fenetre_principale", "Aide", 0));
    } // retranslateUi

};

namespace Ui {
    class fenetre_principale: public Ui_fenetre_principale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRE_PRINCIPALE_H
