/********************************************************************************
** Form generated from reading UI file 'fenetre_principale.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRE_PRINCIPALE_H
#define UI_FENETRE_PRINCIPALE_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

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
            fenetre_principale->setObjectName(QString::fromUtf8("fenetre_principale"));
        fenetre_principale->resize(650, 419);
        centralWidget = new QWidget(fenetre_principale);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setAutoFillBackground(true);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        centralLayout = new QVBoxLayout();
        centralLayout->setSpacing(0);
        centralLayout->setObjectName(QString::fromUtf8("centralLayout"));

        verticalLayout_2->addLayout(centralLayout);

        fenetre_principale->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(fenetre_principale);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 650, 25));
        menuFichier = new QMenu(menuBar);
        menuFichier->setObjectName(QString::fromUtf8("menuFichier"));
        menuAide = new QMenu(menuBar);
        menuAide->setObjectName(QString::fromUtf8("menuAide"));
        fenetre_principale->setMenuBar(menuBar);
        mainToolBar = new QToolBar(fenetre_principale);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
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
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        fenetre_principale->setStatusBar(statusBar);

        menuBar->addAction(menuFichier->menuAction());
        menuBar->addAction(menuAide->menuAction());

        retranslateUi(fenetre_principale);

        QMetaObject::connectSlotsByName(fenetre_principale);
    } // setupUi

    void retranslateUi(QMainWindow *fenetre_principale)
    {
        fenetre_principale->setWindowTitle(QApplication::translate("fenetre_principale", "Mon d\303\251codeur", 0, QApplication::UnicodeUTF8));
        menuFichier->setTitle(QApplication::translate("fenetre_principale", "Fichier", 0, QApplication::UnicodeUTF8));
        menuAide->setTitle(QApplication::translate("fenetre_principale", "Aide", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class fenetre_principale: public Ui_fenetre_principale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRE_PRINCIPALE_H
