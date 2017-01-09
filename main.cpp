#include "fenetre_principale.h"

#include <QApplication>
#include <QTextCodec>
#include <QFile>

/*! --------------------------------------------------------------------------------------
 \brief Fonction principale du projet.
 \author Sébastien Angibaud
*/
int main(int argc, char *argv[])
{
    // Accents en français
#ifdef __linux__
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#elif _WIN32
    // windows code goes here
#else

#endif

    QFile File("stylesheet.qss");
    File.open(QFile::ReadOnly);
    QString StyleSheet = QLatin1String(File.readAll());

    QApplication a(argc, argv);
    a.setStyleSheet(StyleSheet);

    fenetre_principale w;
    w.show();
    
    return a.exec();
}
