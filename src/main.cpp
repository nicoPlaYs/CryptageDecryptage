// Application Qt
#include <QApplication>

// Gestion de la langue de l'application Qt
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>


// Fenêtre principale du programme
#include "include/fenetreprincipale.h"



// Fonction principale
int main(int argc, char** argv)
{
    // Initialisation de l'application Qt
    QApplication app(argc, argv);
    app.setApplicationName("Cryptage & Décryptage");
    app.setWindowIcon(QIcon(":/images/app.ico"));

    // Configure l'application Qt pour qu'elle utilise la langue du système
    QString locale = QLocale::system().name().section('_', 0, 0);
    QTranslator translator;
    translator.load(QString("qt_") + locale, QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&translator);

    // Initialisation de la fenêtre principale
    FenetrePrincipale fMain;

    // Affichage de la fenêtre principale
    fMain.show();

    // Exécution de l'application Qt
    return app.exec();
}
