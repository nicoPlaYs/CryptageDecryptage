#ifndef FENETREPRINCIPALE_H
#define FENETREPRINCIPALE_H



// Application Qt
#include <QApplication>


// Interface graphique

    // Conteneur
    #include <QMainWindow> // Fenêtre principale
    #include <QMenuBar> // // Menu de la fenêtre principale
        #include <QActionGroup> // Regoupe plusieurs actions dans une seule classe
    #include <QWidget> // Conteneur de base
    #include <QTabWidget> // Conteneur sous forme d'onglets
    #include <QSplitter> // Conteneur scindé à taille variable
    #include <QStackedLayout> // Conteneur de widget qui ne peut afficher qu'un seul des widgets qu'il contient à la fois
    #include <QToolBar> // Barre d'outils
    #include <QMessageBox> // Crée des fenêtres délivrant des messages d'informations

    // Layout
    #include <QVBoxLayout> // Layout vertical
    #include <QHBoxLayout> // Layout horizontal

    // Interaction avec l'utilisateur
    #include <QAction> // Actions Qt
    #include <QTextEdit> // Bloc de texte
    #include <QLineEdit> // Ligne de texte
    #include <QFileDialog> // Fenêtre d'ouverture / enregistrement de fichier
    #include <QPushButton> // Bouton à appuyer
    #include <QCheckBox> // Case à choix multiple à cocher/décocher
    #include <QComboBox> // Liste déroulante

    // Décoration
    #include <QLabel> // Affiche du texte ou des images
    #include <QFrame> // Permet de créer des bordures / lignes de séparation / etc pour les widgets

    // Dessin & Graphique
    #include <QGraphicsScene> // Stocke un ensemble d'objet graphique
    #include <QGraphicsView> // Affiche un QGraphicsScene


// Structure Qt
#include <QDir> // Gestion de dossier
#include <QFile> // Gestion de fichier
#include <QString> // Chaîne de caractère de Qt
#include <QTextStream> // Flux de texte
#include <QTextCodec> // Codec de texte


class FenetrePrincipale;
#include <qmath.h> // Classe mathématique de Qt
#include "huffman.h" // Algorithme d'Huffman
#include "arbrehuff.h" // Arbre binaire d'Huffman



// Fenêtre principale du programme
class FenetrePrincipale : public QMainWindow
{
    Q_OBJECT

    // Attributs
    private :
        // Variable de l'algorithme
        Huffman* huffman;

        // Menu de la fenêtre
        QMenu *menuFichier;
            QAction* actionChargerNonCrypte;
            QAction* actionChargerCrypte;
            QAction* actionEnregistrerNonCrypte;
            QAction* actionEnregistrerCrypte;
            QAction* actionQuitter;
        QMenu* menuAide;
            QAction* actionAPropos;
        // Widgets
        QWidget* widgetCentral;
            QVBoxLayout* layoutCentral;
                QTabWidget* widgetOnglet;
                    QWidget* ongletTexte;
                        QVBoxLayout* layoutTexte;
                            QSplitter* splitterTexte;
                                QWidget* widgetNonCrypte;
                                    QGridLayout* layoutNonCrypte;
                                        QTextEdit* zoneTexteNonCrypte;
                                        QPushButton* boutonCrypter;
                                        QLabel* labelChoixCryptage;
                                        QComboBox* choixCryptage;
                                        QWidget* optionCryptage;
                                            QStackedLayout* optionCryptageLayout;
                                                QWidget* optionCryptTexte;
                                                    QGridLayout* optionCryptTexteLayout;
                                                        QLineEdit* cheminCrypterSrcTexte;
                                                        QPushButton* parcourirCrypterSrcTexte;
                                                        QCheckBox* optCryptTexteCasse;
                                                QWidget* optionCryptArbre;
                                                QWidget* optionCryptLuiMeme;
                                                    QVBoxLayout* optionCryptLuiMemeLayout;
                                                        QCheckBox* optCryptLuiMemeCasse;

                                QWidget* widgetCrypte;
                                    QGridLayout* layoutCrypte;
                                        QTextEdit* zoneTexteCrypte;
                                        QPushButton* boutonDecrypter;
                                        QLabel* labelChoixDecryptage;
                                        QComboBox* choixDecryptage;
                                        QWidget* optionDecryptage;
                                            QStackedLayout* optionDecryptageLayout;
                                                QWidget* optionDecryptTexte;
                                                    QGridLayout* optionDecryptTexteLayout;
                                                        QLineEdit* cheminDecrypterSrcTexte;
                                                        QPushButton* parcourirDecrypterSrcTexte;
                                                        QCheckBox* optDecryptTexteCasse;
                                                QWidget* optionDecryptArbre;

                    QWidget* ongletArbre;
                        QVBoxLayout* layoutArbre;
                            QToolBar* outilsArbre;
                                QActionGroup* actionsArbre;
                                    QAction* editerArbre;
                                    QAction* echangerArbre;
                                    QAction* ajouterFeuilleArbre;
                                    QAction* ajouterNoeudArbre;
                                    QAction* supprimerFeuilleNoeud;
                                    QAction* supprimerSousArbre;
                                    QAction* zoomPlusAction;
                                    QAction* zoomMoinsAction;
                                    QAction* zoomResetAction;
                            QGraphicsScene* arbreGraphicsScene;
                            QGraphicsView* arbreGraphicsView;
                                qreal zoomArbreReset;

    // Constructeur
    public :
        FenetrePrincipale();

    // Destructeur
    public :
        ~FenetrePrincipale();

    // Méthodes
    public :
        // Ouvre la fenêtre d'ouverture de fichier et retourne le chemin du fichier sélectionné
        QString ouvrirFichierChemin();
        // Ouvre la fenêtre d'ouverture de fichier et retourne le texte du fichier sélectionné
        QString ouvrirFichierTexte(QString chemin = QString());

    // Slots Qt
    public slots :

        // Interaction dans le menu principal
            // Chargement d'un fichier texte non crypté
            void chargerNonCrypte();
            // Chargement d'un fichier texte crypté
            void chargerCrypte();
            // Enregistrement du fichier texte non crypté
            void enregistrerNonCrypte();
            // Enregistrement du fichier texte crypté
            void enregistrerCrypte();
            // Fenêtre de dialogue affichant les crédits
            void aPropos();


        // Interaction dans l'onglet "Texte"
            // Crypte le texte de la zone de gauche
            void crypter();
            // Décrypte le texte de la zone de droite
            void decrypter();
            // Sélectionne le texte utilisé pour crypter
            void ouvrirSrcTexteCrypter();
            // Sélectionne le texte utilisé pour décrypter
            void ouvrirSrcTexteDecrypter();

        // Changement de couleur dù à des erreurs dans les deux onglets
            // Colorie en rouge le chemin indiquant le texte pour crypter
            void coulErreurSrcCheminCrypter();
            // Colorie en rouge le chemin indiquant le texte pour décrypter
            void coulErreurSrcCheminDecrypter();
            // Rétablit la couleur d'origine du chemin indiquant le texte pour crypter
            void coulInitSrcCheminCrypter();
            // Rétablit la couleur d'origine du chemin indiquant le texte pour décrypter
            void coulInitSrcCheminDecrypter();


        // Interaction dans l'onglet "Arbre"
            // Zoom sur l'arbre
            void zoomPlus();
            // Dézoom sur l'arbre
            void zoomMoins();
            // Réinitialise le zoom sur l'arbre
            void zoomReset();

        // Affichage de l'arbre dans l'onglet "Arbre"
            // Dessine l'arbre dans l'onglet qui lui est destiné
            void dessinerArbre();
            // Dessine les noeuds de l'arbre
            void dessinerArbreNoeud(ArbreHuff* arbreHuff, int row, int colDecalage[]);
            // Dessiner les traits reliants les différents noeuds de l'arbre
            void dessinerArbreLigne(ArbreHuff* arbreHuff);
};



#endif // FENETREPRINCIPALE_H
