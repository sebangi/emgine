/********************************************************************************
** Form generated from reading UI file 'fenetre_principale.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRE_PRINCIPALE_H
#define UI_FENETRE_PRINCIPALE_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fenetre_principale
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *centralLayout;
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
        mainToolBar = new QToolBar(fenetre_principale);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy);
        mainToolBar->setLayoutDirection(Qt::LeftToRight);
        mainToolBar->setMovable(false);
        mainToolBar->setOrientation(Qt::Horizontal);
        mainToolBar->setIconSize(QSize(32, 32));
        mainToolBar->setFloatable(true);
        fenetre_principale->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(fenetre_principale);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        fenetre_principale->setStatusBar(statusBar);

        retranslateUi(fenetre_principale);

        QMetaObject::connectSlotsByName(fenetre_principale);
    } // setupUi

    void retranslateUi(QMainWindow *fenetre_principale)
    {
        fenetre_principale->setWindowTitle(QApplication::translate("fenetre_principale", "Mon d\303\251codeur", 0));
    } // retranslateUi

};

namespace Ui {
    class fenetre_principale: public Ui_fenetre_principale {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRE_PRINCIPALE_H
