#include "include/dialogmodifnoeud.h"

DialogModifFeuille::DialogModifFeuille(ArbreHuff* feuille, QWidget* parent) : QDialog(parent)
{
    // On définit le titre de la fênetre de dialogue
    this->setWindowTitle("Modifier la feuille");
    /* On la définit comme étant modal (la fenêtre de dialogue
     * doit etre fermé avant de pouvoir réaccéder à la fenêtre principale du programme) */
    this->setModal(true);
    // On enlève le "?" placé par défaut en haut à droite de la fenêtre
    this->setWindowFlags(windowFlags() & ~Qt::WindowContextHelpButtonHint);

    // On récupère la feuille sur laquelle on va travailler avec la fenêtre de dialogue
    this->feuille = feuille;

    // Layout principale de la fenêtre qui est une grille
    layoutPrincipal = new QGridLayout(this);
    layoutPrincipal->setContentsMargins(10,10,10,10);

        // On crée un champ de ligne de texte
        lineEditCarac = new QLineEdit("Caractère :", this);
        // On peut y mettre au maximium un caractère
        lineEditCarac->setMaxLength(1);
        // On y écrit le caractère d'origine de la feuille sur laquelle on travaille
        lineEditCarac->setText(QString(feuille->getEtiquette().getCarac()));

    // On ajoute ce dernier widget au layout principal
    layoutPrincipal->addWidget(lineEditCarac, 0, 0, 1, 2);

        // On crée un label contenu du texte, qui servira à illustrer le spinBox du nombre d'occurences
        labelNbOcc = new QLabel("Nombre d'occurences :", this);

    // On ajoute ce dernier widget au layout principal
    layoutPrincipal->addWidget(labelNbOcc, 1, 0, 1, 1);

        // On crée un champ contenu uniquement des chiffres
        spinBoxNbOcc = new QSpinBox(this);
        // On définit le minimum / maximum que l'on peut y rentrer
        spinBoxNbOcc->setRange(0, 2147483647); // Le maximum étant la taille maximum d'un int
        // On y place le nombre d'occurence d'origine de la feuille sur laquelle on travaille
        spinBoxNbOcc->setValue(feuille->getEtiquette().getNbOcc());

    // On ajoute ce dernier widget au layout principal
    layoutPrincipal->addWidget(spinBoxNbOcc, 1, 1, 1, 1);

        // On crée un nouveau boutton qui sera celui de validation
        boutonValider = new QPushButton("Valider", this);
        // C'est le bouton par défaut de la fenêtre de dialogue
        boutonValider->setDefault(true);
        // Lorsqu'il sera cliqué, la fonction modifFeuille de cette classe sera appelé
        QObject::connect(boutonValider, SIGNAL(clicked(bool)), this, SLOT(modifFeuille()));

    // On ajoute ce dernier widget au layout principal
    layoutPrincipal->addWidget(boutonValider, 2, 0, 1, 1);

        // On crée un nouveau boutton qui sera celui d'annulation
        boutonAnnuler = new QPushButton("Annuler", this);
        // Lorsqu'il sera cliqué, la fenêtre de dialogue se fermera
        QObject::connect(boutonAnnuler, SIGNAL(clicked()), this, SLOT(close()));

    // On ajoute ce dernier widget au layout principal
    layoutPrincipal->addWidget(boutonAnnuler, 2, 1, 1, 1);
}

// Modifie la feuille avec laquelle la fenêtre de dialogue a été ouverte
void DialogModifFeuille::modifFeuille()
{
    // On garde de côté son nombre d'occurence précédent
    int precNbOcc = feuille->getEtiquette().getNbOcc();

    /* On modifie son nombre d'occurence
     * suivant ce que l'utilisateur a rentré dans la fenetre de dialogue */
    feuille->setEtiquette(Occurences(lineEditCarac->text()[0].unicode(), spinBoxNbOcc->value()));

    // On modifie en conséquence l'occurence de ses ancetres à commencer par son père
    feuille->getPere()->modifOcc(feuille->getEtiquette().getNbOcc() - precNbOcc);

    // On ferme la fenêtre de dialogue
    this->close();
}
