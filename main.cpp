/**
 * \file main.cpp
 * \brief Fichier principal de l'application Emgine.
 * \author Sébastien Angibaud
 */

#include "entete/fenetre_principale.h"

#include <QApplication>
#include <QFile>
#include <QTextCodec>
#include <QTranslator>

/*! --------------------------------------------------------------------------------------
 \brief Fonction principale du projet.
 \param argc Le nombre d'argument de la fonction.
 \param argv Les arguments de la fonction.
 \return Le code d'erreur de la fonction.
*/
int main(int argc, char *argv[])
{    
    QFile File("stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    QApplication a(argc, argv);
    a.setStyleSheet(StyleSheet);

    QTranslator translator;
    translator.load("emgine_en");
    a.installTranslator(&translator);

    fenetre_principale w;
    w.show();
    
    return a.exec();
}
