#ifndef DIALOGMODIFFEUILLE_H
#define DIALOGMODIFFEUILLE_H



// Interface graphique
    // Conteneur
    #include <QDialog> // Fenêtre de dialogue

    // Layout
    #include <QGridLayout> // Layout en grille

    // Interaction
    #include <QLineEdit> // Champ de texte (ligne)
    #include <QSpinBox> // Champ pour chiffre
    #include <QPushButton> // Boutton à presser

    // Décoration
    #include <QLabel> // Texte ou Image sous forme de widget


class DialogModifFeuille;
#include "arbrehuff.h" // Arbre binaire d'Huffman



// Fenêtre de dialogue de modification de feuille
class DialogModifFeuille : public QDialog
{
    Q_OBJECT

    // Attributs
    private :
        // Interface graphique
        QGridLayout* layoutPrincipal;
            QLineEdit* lineEditCarac;
            QLabel* labelNbOcc;
            QSpinBox* spinBoxNbOcc;
            QPushButton* boutonValider;
            QPushButton* boutonAnnuler;

        // Algorithme
        ArbreHuff* feuille;

    // Constructeurs
    public:
        DialogModifFeuille(ArbreHuff* feuille, QWidget* parent = 0);

    // Qt Slots
    public slots :
        // Modifie la feuille avec laquelle la fenêtre de dialogue a été ouverte
        void modifFeuille();
};



#endif // DIALOGMODIFFEUILLE_H
