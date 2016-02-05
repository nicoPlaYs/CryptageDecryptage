#include "include/fenetreprincipale.h"




// Constructeur
FenetrePrincipale::FenetrePrincipale() : QMainWindow()
{
    // On définit la taille minimale de la fenêtre
    this->setMinimumSize(600,300);
    // On définit sa taille à son ouverture
    this->resize(800,500);

    // Initialisation de la variable d'Huffman
    huffman = new Huffman();
    // L'arbre contient uniquement une racine au début du programme
    huffman->setArbreHuff(new ArbreHuff(Occurences('\0')));
    // Zoom à 100%
    zoomArbreReset = 1.000000;



    // Menu "Fichier"
    menuFichier = menuBar()->addMenu("Fichier");
        // Sous-menu "Charger un texte non crypté"
        actionChargerNonCrypte = new QAction(QIcon(":/images/menu/fichier/charger.ico"),"&Charger un texte non crypté", this);
        QObject::connect(actionChargerNonCrypte, SIGNAL(triggered()), this, SLOT(chargerNonCrypte()));

    menuFichier->addAction(actionChargerNonCrypte);

        // Sous-menu "Charger un texte crypté"
        actionChargerCrypte = new QAction(QIcon(":/images/menu/fichier/charger.ico"),"&Charger un texte crypté", this);
        QObject::connect(actionChargerCrypte, SIGNAL(triggered()), this, SLOT(chargerCrypte()));

    menuFichier->addAction(actionChargerCrypte);
    menuFichier->addSeparator();

        // Sous-menu "Enregistrer le texte non crypté sous..."
        actionEnregistrerNonCrypte = new QAction(QIcon(":/images/menu/fichier/enregistrer.ico"),"&Enregistrer le texte non crypté sous...", this);
        QObject::connect(actionEnregistrerNonCrypte, SIGNAL(triggered()), this, SLOT(enregistrerNonCrypte()));

    menuFichier->addAction(actionEnregistrerNonCrypte);

        // Sous-menu "Enregistrer le fichier texte crypté sous..."
        actionEnregistrerCrypte = new QAction(QIcon(":/images/menu/fichier/enregistrer.ico"),"&Enregistrer le fichier texte crypté sous...", this);
        QObject::connect(actionEnregistrerCrypte, SIGNAL(triggered()), this, SLOT(enregistrerCrypte()));

    menuFichier->addAction(actionEnregistrerCrypte);
    menuFichier->addSeparator();

        // Sous-menu "Quitter"
        actionQuitter = new QAction(QIcon(":/images/menu/fichier/quitter.ico") ,"&Quitter", this);
        QObject::connect(actionQuitter, SIGNAL(triggered()), qApp, SLOT(quit()));
        menuFichier->addAction(actionQuitter);

    // Menu "Aide"
    menuAide = menuBar()->addMenu("Aide");
        actionAPropos = new QAction(QIcon(":/images/menu/aide/apropos.ico"), "À propos...", this);
        QObject::connect(actionAPropos, SIGNAL(triggered(bool)), this, SLOT(aPropos()));

    menuAide->addAction(actionAPropos);



    // Widget centrale de la fenêtre principale
    widgetCentral = new QWidget(this);
    setCentralWidget(widgetCentral);

        // Layout du widget centrale
        layoutCentral = new QVBoxLayout(widgetCentral);
        layoutCentral->setContentsMargins(10,10,10,10);

            // Widget à onglet
            widgetOnglet = new QTabWidget(widgetCentral);

        layoutCentral->addWidget(widgetOnglet);

                // Onglet "Texte"
                ongletTexte = new QWidget(widgetOnglet);

            widgetOnglet->addTab(ongletTexte, QIcon(":/images/texte/texte.ico"), "Texte");

                    // Layout vertical pour l'onglet de texte
                    layoutTexte= new QVBoxLayout(ongletTexte);
                    layoutTexte->setContentsMargins(10,10,10,10);

                        // Création d'un splitter contenant les deux zones de texte
                        splitterTexte = new QSplitter(ongletTexte);

                    layoutTexte->addWidget(splitterTexte);

                            // Widget de la zone non cryptée
                            widgetNonCrypte = new QWidget(splitterTexte);

                        splitterTexte->addWidget(widgetNonCrypte);

                                // Layout en grille pour le widget de la zone non cryptée
                                layoutNonCrypte = new QGridLayout(widgetNonCrypte);
                                layoutNonCrypte->setContentsMargins(0,0,5,0);

                                    // Champ de texte en bloc contenant le texte non cryptée
                                    zoneTexteNonCrypte =  new QTextEdit(widgetNonCrypte);
                                    zoneTexteNonCrypte->setAcceptRichText(false);
                                    zoneTexteNonCrypte->setAlignment(Qt::AlignJustify);

                                layoutNonCrypte->addWidget(zoneTexteNonCrypte, 0, 0, 1, 2);

                                    // Bouton pour crypter le texte qui se trouve au dessus de lui
                                    boutonCrypter = new QPushButton(QIcon(":/images/texte/crypter.ico"), "Crypter", widgetNonCrypte);
                                    QObject::connect(boutonCrypter, SIGNAL(clicked()), this, SLOT(crypter()));

                                layoutNonCrypte->addWidget(boutonCrypter, 1, 0, 1, 2, Qt::AlignTop);

                                    // Bloc d'option de cryptage
                                    optionCryptage = new QWidget(widgetNonCrypte);
                                    optionCryptage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

                                layoutNonCrypte->addWidget(optionCryptage, 3, 0, 1, 2);

                                        // Layout pour le bloc d'option de cryptage
                                        optionCryptageLayout = new QStackedLayout(optionCryptage);

                                            // Widget de la page d'option de cryptage à partir d'un fichier texte
                                            optionCryptTexte = new QWidget(optionCryptage);

                                                // Layout en grille pour le widget contenant les options de cryptage à partir d'un fichier
                                                optionCryptTexteLayout = new QGridLayout(optionCryptTexte);
                                                optionCryptTexteLayout->setContentsMargins(20,0,20,0);

                                                    // Chemin du texte utilisé pour le cryptage
                                                    cheminCrypterSrcTexte = new QLineEdit(optionCryptTexte);
                                                    QObject::connect(cheminCrypterSrcTexte, SIGNAL(textChanged(QString)), this, SLOT(coulInitSrcCheminCrypter()));

                                                optionCryptTexteLayout->addWidget(cheminCrypterSrcTexte, 0, 0, 1, 1);

                                                    // Bouton pour parcourir ses fichiers à la recherche d'un texte de source de cryptage
                                                    parcourirCrypterSrcTexte = new QPushButton("...", optionCryptTexte);
                                                    parcourirCrypterSrcTexte->setFixedWidth(40);
                                                    QObject::connect(parcourirCrypterSrcTexte, SIGNAL(clicked()), this, SLOT(ouvrirSrcTexteCrypter()));

                                                optionCryptTexteLayout->addWidget(parcourirCrypterSrcTexte, 0, 1, 1, 1);

                                                    // Case à cocher permettant d'ignorer la casse
                                                    optCryptTexteCasse = new QCheckBox("Ignorer la casse");

                                                optionCryptTexteLayout->addWidget(optCryptTexteCasse, 1, 0, 1, 2, Qt::AlignCenter);

                                        optionCryptageLayout->addWidget(optionCryptTexte);

                                            // Widget de la page d'option de cryptage à partir de l'arbre du second onglet
                                            optionCryptArbre = new QWidget(optionCryptage);

                                        optionCryptageLayout->addWidget(optionCryptArbre);

                                            // Widget de la page d'option de cryptage à partir du texte à crypté
                                            optionCryptLuiMeme = new QWidget(optionCryptage);

                                                // Layout pour le widget de la page d'option de cryptage à partir du texte à crypté lui même
                                                optionCryptLuiMemeLayout = new QVBoxLayout(optionCryptLuiMeme);

                                                    // Case à cocher permettant d'ignorer la casse
                                                    optCryptLuiMemeCasse = new QCheckBox("Ignorer la casse");

                                                optionCryptLuiMemeLayout->addWidget(optCryptLuiMemeCasse, 0, Qt::AlignCenter);

                                        optionCryptageLayout->addWidget(optionCryptLuiMeme);

                                    // Texte placer à gauche de la liste déroulante permettant de sélectionner la source de cryptage
                                    labelChoixCryptage = new QLabel("Source du cryptage :", widgetNonCrypte);
                                    labelChoixCryptage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

                                layoutNonCrypte->addWidget(labelChoixCryptage, 2, 0, 1, 1);

                                    // Liste déroulante permettant de sélectionner la source de cryptage
                                    choixCryptage = new QComboBox(widgetNonCrypte);
                                    choixCryptage->addItem("Fichier texte");
                                    choixCryptage->addItem("Arbre du second onglet");
                                    choixCryptage->addItem("Le texte lui-même");
                                    QObject::connect(choixCryptage, SIGNAL(activated(int)), optionCryptageLayout, SLOT(setCurrentIndex(int)));

                                layoutNonCrypte->addWidget(choixCryptage, 2, 1, 1, 1);


                            // Widget de la zone cryptée
                            widgetCrypte = new QWidget(splitterTexte);

                        splitterTexte->addWidget(widgetCrypte);

                                // Layout de la zone cryptée
                                layoutCrypte = new QGridLayout(widgetCrypte);
                                layoutCrypte->setContentsMargins(5,0,0,0);

                                    // Champ de texte en bloc contenant le texte crypté
                                    zoneTexteCrypte = new QTextEdit(widgetCrypte);
                                    zoneTexteCrypte->setAcceptRichText(false);
                                    zoneTexteCrypte->setAlignment(Qt::AlignJustify);

                                layoutCrypte->addWidget(zoneTexteCrypte, 0, 0, 1, 2);

                                    // Bouton permettant de décrypter le texte au dessus de lui
                                    boutonDecrypter = new QPushButton(QIcon(":/images/texte/decrypter.ico"), "Décrypter", widgetCrypte);
                                    QObject::connect(boutonDecrypter, SIGNAL(clicked(bool)), this, SLOT(decrypter()));

                                layoutCrypte->addWidget(boutonDecrypter, 1, 0, 1 , 2, Qt::AlignTop);

                                    // Bloc d'option de décryptage
                                    optionDecryptage = new QWidget(widgetCrypte);
                                    optionDecryptage->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

                                layoutCrypte->addWidget(optionDecryptage, 3, 0, 1, 2);

                                        // Layout pour le bloc d'option de décryptage
                                        optionDecryptageLayout = new QStackedLayout(optionDecryptage);

                                            // Widget de la page d'option de décryptage à partir d'un fichier texte
                                            optionDecryptTexte = new QWidget(optionDecryptage);

                                                // Layout en grille pour le widget contenant les options de décryptage à partir d'un fichier
                                                optionDecryptTexteLayout = new QGridLayout(optionDecryptTexte);
                                                optionDecryptTexteLayout->setContentsMargins(20,0,20,0);

                                                    // Chemin du texte utilisé pour le décryptage
                                                    cheminDecrypterSrcTexte = new QLineEdit(optionDecryptTexte);
                                                    QObject::connect(cheminDecrypterSrcTexte, SIGNAL(textChanged(QString)), this, SLOT(coulInitSrcCheminCrypter()));

                                                optionDecryptTexteLayout->addWidget(cheminDecrypterSrcTexte, 0, 0, 1, 1);

                                                    // Bouton pour parcourir ses fichiers à la recherche d'un texte de source de décryptage
                                                    parcourirDecrypterSrcTexte = new QPushButton("...", optionCryptTexte);
                                                    parcourirDecrypterSrcTexte->setFixedWidth(40);
                                                    QObject::connect(parcourirDecrypterSrcTexte, SIGNAL(clicked()), this, SLOT(ouvrirSrcTexteDecrypter()));

                                                optionDecryptTexteLayout->addWidget(parcourirDecrypterSrcTexte, 0, 1, 1, 1);

                                                    // Case à cocher permettant d'ignorer la casse
                                                    optDecryptTexteCasse = new QCheckBox("Ignorer la casse");

                                                optionDecryptTexteLayout->addWidget(optDecryptTexteCasse, 1, 0, 1, 2, Qt::AlignCenter);

                                        optionDecryptageLayout->addWidget(optionDecryptTexte);

                                            // Widget de la page d'option de décryptage à partir de l'arbre du second onglet
                                            optionDecryptArbre = new QWidget(optionDecryptage);

                                        optionDecryptageLayout->addWidget(optionDecryptArbre);

                                    // Texte placer à gauche de la liste déroulante permettant de sélectionner la source de cryptage
                                    labelChoixDecryptage = new QLabel("Source du décryptage :", widgetCrypte);
                                    labelChoixDecryptage->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);

                                layoutCrypte->addWidget(labelChoixDecryptage, 2, 0, 1, 1);

                                    // Liste déroulante permettant de sélectionner la source de cryptage
                                    choixDecryptage = new QComboBox(widgetCrypte);
                                    choixDecryptage->addItem("Fichier texte");
                                    choixDecryptage->addItem("Arbre du second onglet");
                                    QObject::connect(choixDecryptage, SIGNAL(activated(int)), optionDecryptageLayout, SLOT(setCurrentIndex(int)));

                                layoutCrypte->addWidget(choixDecryptage, 2, 1, 1, 1);


                            // Rajoute une barre entre les deux zones du splitter
                            QSplitterHandle *handleSplitterTexte = splitterTexte->handle(1);
                            QHBoxLayout *layoutHandleSplitterTexte = new QHBoxLayout(handleSplitterTexte);
                            layoutHandleSplitterTexte->setContentsMargins(QMargins(0,5,0,5));
                            QFrame *lineHandleSplitterTexte = new QFrame(splitterTexte);
                            lineHandleSplitterTexte->setFrameShape(QFrame::VLine);
                            lineHandleSplitterTexte->setFrameShadow(QFrame::Raised);
                            layoutHandleSplitterTexte->addWidget(lineHandleSplitterTexte);


                // Onglet contenant l'arbre
                ongletArbre = new QWidget(widgetOnglet);

            widgetOnglet->addTab(ongletArbre, QIcon(":/images/arbre/arbre.ico"), "Arbre");

                    // Layout de l'onglet contenant l'arbre
                    layoutArbre = new QVBoxLayout(ongletArbre);
                    layoutArbre->setContentsMargins(10,10,10,10);

                        // Barre d'outil de modification de l'arbre
                        outilsArbre = new QToolBar(ongletArbre);

                            // Groupe d'action de la barre d'outils de modification de l'arbre
                            actionsArbre = new QActionGroup(ongletArbre);

                                // Outil d'édition de feuille de l'arbre
                                editerArbre = actionsArbre->addAction(QIcon(":/images/arbre/editer.ico"), "Modifie les valeurs d'une feuille");
                                editerArbre->setObjectName("editer");
                                editerArbre->setCheckable(true);
                                editerArbre->setChecked(true);

                                // Outil d'echange de sous-arbre
                                echangerArbre = actionsArbre->addAction(QIcon(":/images/arbre/echanger.ico"), "Intervertie deux sous-arbres");
                                echangerArbre->setObjectName("echanger");
                                echangerArbre->setCheckable(true);

                                // Outil d'ajout de feuille
                                ajouterFeuilleArbre = actionsArbre->addAction(QIcon(":/images/arbre/ajouterfeuille.ico"), "Insère une feuille à gauche ou à droite suivant le clic");
                                ajouterFeuilleArbre->setObjectName("ajouterFeuille");
                                ajouterFeuilleArbre->setCheckable(true);

                                // Outil d'ajout de noeud
                                ajouterNoeudArbre = actionsArbre->addAction(QIcon(":/images/arbre/ajouternoeud.ico"), "Insère un noeud à gauche ou à droite suivant le clic");
                                ajouterNoeudArbre->setObjectName("ajouterNoeud");
                                ajouterNoeudArbre->setCheckable(true);

                                // Outil de suppresion de noeud/feuille
                                supprimerFeuilleNoeud = actionsArbre->addAction(QIcon(":/images/arbre/supprimerFeuilleNoeud.ico"), "Supprime une feuille ou un noeud inutile (qui ne possède qu'un seule fils)");
                                supprimerFeuilleNoeud->setObjectName("supprimerFeuilleNoeud");
                                supprimerFeuilleNoeud->setCheckable(true);

                                // Outil de suppression de sous-arbre
                                supprimerSousArbre = actionsArbre->addAction(QIcon(":/images/arbre/supprimerSousArbre.ico"), "Supprime un sous-arbre");
                                supprimerSousArbre->setObjectName("supprimerSousArbre");
                                supprimerSousArbre->setCheckable(true);

                        outilsArbre->addActions(actionsArbre->actions());

                        outilsArbre->addSeparator();

                            // Bouton de Zoom
                            zoomPlusAction = outilsArbre->addAction(QIcon(":/images/arbre/zoom+.ico"), "Zoom");
                            QObject::connect(zoomPlusAction, SIGNAL(triggered(bool)), this, SLOT(zoomPlus()));

                            // Bouton de Dézoom
                            zoomMoinsAction = outilsArbre->addAction(QIcon(":/images/arbre/zoom-.ico"), "Dézoom");
                            QObject::connect(zoomMoinsAction, SIGNAL(triggered(bool)), this, SLOT(zoomMoins()));

                            // Bouton de réinitialisation de zoom
                            zoomResetAction = outilsArbre->addAction(QIcon(":/images/arbre/zoomReset.ico"), "Réinitialiser le zoom");
                            QObject::connect(zoomResetAction, SIGNAL(triggered(bool)), this, SLOT(zoomReset()));

                    layoutArbre->addWidget(outilsArbre);

                        // Scène graphique de l'arbre binaire de Huffman
                        arbreGraphicsScene = new QGraphicsScene(ongletArbre);

                        // Afficheur de la scène graphique de l'arbre binaire de Huffman
                        arbreGraphicsView = new QGraphicsView(arbreGraphicsScene, widgetOnglet);
                        arbreGraphicsView->setDragMode(QGraphicsView::ScrollHandDrag);
                        arbreGraphicsView->setRenderHint(QPainter::Antialiasing);
                        arbreGraphicsView->show();

                    layoutArbre->addWidget(arbreGraphicsView);




    // On dessine l'arbre de début de programme
    dessinerArbre();
}



// Destructeur
FenetrePrincipale::~FenetrePrincipale()
{
    delete huffman;

    /* Qt libère lui même en cascade la mémoire de tout les widgets dont la fenêtre est le parent à sa fermeture :
     * il n'est donc pas nécessaire d'ajouter des "delete" pour supprimer tous ses widgets
     */
}



// Méthodes

// Ouvre la fenêtre d'ouverture de fichier et retourne le chemin du fichier sélectionné
QString FenetrePrincipale::ouvrirFichierChemin()
{
    return QFileDialog::getOpenFileName(widgetCentral, "Choississez votre fichier texte", QDir::homePath(), "Texte (*.txt);;All(*.*)");
}

/* Ouvre la fenêtre d'ouverture de fichier si le chemin en argument est vide
 * et retourne le texte du fichier sélectionné */
QString FenetrePrincipale::ouvrirFichierTexte(QString chemin)
{
    if(chemin.isEmpty())
    {
        // On demande à l'utilisateur le fichier qu'il souhaite charger
        chemin = ouvrirFichierChemin();
    }

    QString texte;
    // On vérifie que le chemin du fichier n'est pas vide
    if(!chemin.isEmpty())
    {
        QFile fichier(chemin);

        // Ouverture du fichier en lecture seule en tant que texte
        if(fichier.open(QIODevice::ReadOnly | QIODevice::Text))
        {
            QTextStream fluxFichier(&fichier);

            // On vérifie le codec du texte
            QTextCodec::ConverterState state;
            QTextCodec *codec = QTextCodec::codecForName("UTF-8");
            codec->toUnicode(fichier.readAll(), fichier.size(), &state);

            // On revient au début du fichier texte
            fichier.seek(0);

            // Texte en UTF 8
            if (state.invalidChars <= 0)
            {
                // On récupère le texte du fichier
                texte = fichier.readAll();
            }
            // Autre type de texte (ANSI etc...)
            else
            {
                // On récupère le texte du fichier
                texte = fluxFichier.readAll();
            }

            // Fermeture du fichier
            fichier.close();
        }
        // Si le fichier n'a pas pu s'ouvrir
        else
        {
            // On affiche une fenêtre de dialogue d'erreur
            QMessageBox::critical(this, "Erreur d'ouverture de fichier", "Impossible d'ouvrir ce fichier !");
        }
    }

    // On retourne le texte
    return texte;
}




// Slots Qt


// Interaction dans le menu principal

// Chargement d'un fichier texte non crypté
void FenetrePrincipale::chargerNonCrypte()
{
    // On demande à l'utilisateur son fichier et on récupère le texte de celui-ci
    QString texteNonCrypte = ouvrirFichierTexte();

    // Si le fichier n'est pas vide
    if(!texteNonCrypte.isEmpty())
    {
        // On place le texte dans la zone de texte non cryptée
        zoneTexteNonCrypte->setText(texteNonCrypte);

        // Alignement du texte en justifié
        zoneTexteNonCrypte->setAlignment(Qt::AlignJustify);
    }
}

// Chargement d'un fichier texte crypté
void FenetrePrincipale::chargerCrypte()
{
    // On demande à l'utilisateur son fichier et on récupère le texte de celui-ci
    QString texteCrypte = ouvrirFichierTexte();

    // Si le fichier n'est pas vide
    if(!texteCrypte.isEmpty())
    {
        // On place le texte dans la zone de texte cryptée
        zoneTexteCrypte->setText(texteCrypte);

        // Alignement du texte en justifié
        zoneTexteCrypte->setAlignment(Qt::AlignJustify);
    }
}

// Enregistrement du fichier texte non crypté
void FenetrePrincipale::enregistrerNonCrypte()
{
    // Demande à l'utilisateur où enregister son texte
    QString chemin(QFileDialog::getSaveFileName(widgetCentral, "Enregistrer votre fichier texte", QDir::homePath(), "Texte (*.txt);;All(*.*)"));

    // On vérifie que le chemin indiqué n'est pas vide
    if(!chemin.isEmpty())
    {
        QFile fichier(chemin);

        // Ouverture du fichier en lecture/écriture en tant que texte
        if(fichier.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // On écrit dans le fichier tout ce qui est contenu dans la zone de texte de gauche
            QTextStream fluxFichier(&fichier);
            fluxFichier << zoneTexteNonCrypte->toPlainText();

            // On ferme le fichier
            fichier.close();
        }
        // Si le fichier à écrire n'a pas pu s'ouvrir
        else
        {
            // On affiche une fenêtre de dialogue d'erreur
            QMessageBox::critical(this, "Erreur d'enregistrement du texte", "Impossible d'enregistrer le texte !");
        }
    }
}

// Enregistrement du fichier texte crypté
void FenetrePrincipale::enregistrerCrypte()
{
    // Demande à l'utilisateur où enregister son texte
    QString chemin(QFileDialog::getSaveFileName(widgetCentral, "Enregistrer votre fichier texte", QDir::homePath(), "Texte (*.txt);;All(*.*)"));

    // On vérifie que le chemin indiqué n'est pas vide
    if(!chemin.isEmpty())
    {
        QFile fichier(chemin);

        // Ouverture du fichier en lecture/écriture en tant que texte
        if(fichier.open(QIODevice::ReadWrite | QIODevice::Text))
        {
            // On écrit dans le fichier tout ce qui est contenu dans la zone de texte de droite
            QTextStream fluxFichier(&fichier);
            fluxFichier << zoneTexteCrypte->toPlainText();

            // On ferme le fichier
            fichier.close();
        }
        // Si le fichier à écrire n'a pas pu s'ouvrir
        else
        {
            // On affiche une fenêtre de dialogue d'erreur
            QMessageBox::critical(this, "Erreur d'enregistrement du texte", "Impossible d'enregistrer le texte !");
        }
    }
}

// Fenêtre de dialogue affichant les crédits
void FenetrePrincipale::aPropos()
{
    QMessageBox::about(this, "À propos...", "<p><b>Cryptage & Décryptage</b><br/>"
                                            "<b>Version :</b> 1.0<br/>"
                                            "<b>Développé par :</b> Maximilien Breton & Nicolas Fostier<br/>"
                                            "<b>Librairie utilisée :</b> Qt 5.5.1<br/>"
                                            "<b>Logo : </b> Nicolas Fostier<br/>"
                                            "<b>Icônes :</b> <a href='http://www.customicondesign.com/'>Custom Icon Design</a></p>"
                                            "<p>Codé dans le cadre d'un projet étudiant à l'<a href='http://uvsq.fr'>UVSQ</a></p>"
                                            "<p><a href='http://uvsq.fr'><img style='display: block; margin: auto; width 100%;' src=':/images/menu/aide/uvsq.png'/></a></p>");
}

// Crypte le texte de la zone de gauche
void FenetrePrincipale::crypter()
{    
    QString srcCryptageTexte;
    QString texteACrypter = zoneTexteNonCrypte->toPlainText();

    // Si on a choisit "Fichier texte" comme source de cryptage
    if(choixCryptage->currentText() == "Fichier texte")
    {
        // On vérifie si le chemin vers la texte permettant de crypter n'est pas vide
        if(cheminCrypterSrcTexte->text().isEmpty())
        {
            // Si c'est le cas, on affiche une fenetre de dialogue d'erreur
            QMessageBox::warning(this, "Indiquez un fichier texte !", "Indiquez le chemin d'un fichier texte pour pouvoir crypter votre texte !");
            // Et on change la couleur de la ligne de texte contenant le chemin
            coulErreurSrcCheminCrypter();
        }
        else
        {
            // On récupère le texte du fichier indiqué dans la source de cryptage
            QString srcCryptageTexte = ouvrirFichierTexte(cheminCrypterSrcTexte->text());

            // Si on a bien un texte non vide comme source de cryptage...
            if(!srcCryptageTexte.isEmpty())
            {
                // Si la case pour ignorer la casse est cochée...
                if(optCryptTexteCasse->isChecked())
                {
                    // On passe le texte a crypté et le dictionnaire en minuscule
                    texteACrypter = texteACrypter.toLower();
                    srcCryptageTexte = srcCryptageTexte.toLower();
                }

                // On réinitialise Huffman
                if(huffman != 0)
                {
                    delete huffman;
                }
                huffman = new Huffman(srcCryptageTexte);

                // On dessine l'arbre de Huffman
                dessinerArbre();

                try
                {
                    // On essaie de crypter le texte
                    zoneTexteCrypte->setText(huffman->crypter(texteACrypter));
                }
                catch(const QString msgErreur)
                {
                    // S'il y'a une exception de lancé, on l'affiche dans une fenêtre de dialogue
                    QMessageBox::critical(this, "Erreur de cryptage !", msgErreur);
                }
            }
        }
    }
    // Sinon si on a choisit "Arbre du second onglet" comme source de cryptage
    else if(choixCryptage->currentText() == "Arbre du second onglet")
    {
        // Si l'arbre d'huffman du second onglet est vide...
        if(huffman->getArbreHuff()->estVide())
        {
            // ...on affiche une fenetre de dialogue d'erreur
            QMessageBox::warning(this, "Arbre vide !", "L'arbre du second onglet est vide !");
        }
        // Sinon s'il n'est pas vide
        else
        {
            // On recalcule le codage à partir de notre arbre
            huffman->calculCodage(huffman->getArbreHuff());
            try
            {
                // On essaie de crypter le texte
                zoneTexteCrypte->setText(huffman->crypter(texteACrypter));
            }
            catch(const QString msgErreur)
            {
                // S'il y'a une exception de lancé, on affiche une fenêtre de dialogue d'erreur
                QMessageBox::critical(this, "Erreur de cryptage !", msgErreur);
            }
        }
    }
    // Sinon si on a choisit "Le texte lui-même" comme source de cryptage
    else if(choixCryptage->currentText() == "Le texte lui-même")
    {
        //On récupère le texte dans la zone non crypte
        srcCryptageTexte = zoneTexteNonCrypte->toPlainText();

        // Si la case pour ignorer la casse est cochée...
        if(optCryptLuiMemeCasse->isChecked())
        {
            // On passe le texte a crypté et la source de cryptage en minuscule
            texteACrypter = texteACrypter.toLower();
            srcCryptageTexte = srcCryptageTexte.toLower();
        }

        // On réinitialise Huffman
        if(huffman != 0)
        {
            delete huffman;
        }
        huffman = new Huffman(srcCryptageTexte);

        // On dessine l'arbre de Huffman
        dessinerArbre();

        try
        {
            // On essaie de crypter le texte
            zoneTexteCrypte->setText(huffman->crypter(texteACrypter));
        }
        catch(const QString msgErreur)
        {
            // S'il y'a une exception de lancé, on affiche une fenêtre de dialogue d'erreur
            QMessageBox::critical(this, "Erreur de cryptage !", msgErreur);
        }
    }
}

// Décrypte le texte de la zone de droite
void FenetrePrincipale::decrypter()
{
    // Si on a choisit "Fichier texte" comme source de décryptage
    if(choixDecryptage->currentText() == "Fichier texte")
    {
        // On vérifie si le chemin vers la texte permettant de décrypter n'est pas vide
        if(cheminDecrypterSrcTexte->text().isEmpty())
        {
            // Si c'est le cas, on affiche une fenetre de dialogue d'erreur
            QMessageBox::warning(this, "Pas de dictionnaire !", "Il est impossible de décrypter sans dictionnaire !");
            // Et on change la couleur de la ligne de texte contenant le chemin
            coulErreurSrcCheminDecrypter();
        }
        else
        {
            // On récupère le texte du fichier indiqué dans la source de décryptage
            QString srcDecryptageTexte = ouvrirFichierTexte(cheminDecrypterSrcTexte->text());

            // Si on a bien un texte non vide comme source de décryptage...
            if(!srcDecryptageTexte.isEmpty())
            {
                // Si la case pour ignorer la casse est cochée...
                if(optDecryptTexteCasse->isChecked())
                {
                    // On passe le texte a crypté et la source de décryptage en minuscule
                    srcDecryptageTexte = srcDecryptageTexte.toLower();
                }

                // On réinitialise Huffman
                if(huffman != 0)
                {
                    delete huffman;
                }
                huffman = new Huffman(srcDecryptageTexte);

                // On dessine l'arbre de Huffman
                dessinerArbre();

                try
                {
                    // On essaie de décrypter le texte
                    zoneTexteNonCrypte->setText(huffman->decrypter(zoneTexteCrypte->toPlainText()));
                }
                catch(QString msgErreur)
                {
                    // S'il y'a une exception de lancé, on l'affiche dans une fenêtre de dialogue
                    QMessageBox::critical(this, "Erreur de décryptage !", msgErreur);
                }
            }
        }
    }
    // Sinon si on a choisit "Arbre du second onglet" comme source de décryptage
    else if(choixDecryptage->currentText() == "Arbre du second onglet")
    {
        // Si l'arbre d'huffman du second onglet est vide...
        if(huffman->getArbreHuff()->estVide())
        {
            // ...on affiche une fenetre de dialogue d'erreur
            QMessageBox::warning(this, "Arbre vide !", "L'arbre du second onglet est vide !");
        }
        // Sinon s'il n'est pas vide
        else
        {
            // On recalcule le codage à partir de notre arbre
            huffman->calculCodage(huffman->getArbreHuff());
            try
            {
                // On essaie de décrypter le texte
                zoneTexteNonCrypte->setText(huffman->decrypter(zoneTexteCrypte->toPlainText()));
            }
            catch(QString msgErreur)
            {
                QMessageBox::critical(this, "Erreur de décryptage !", msgErreur);
            }
        }
    }
}



// Interaction dans l'onglet "Texte"

// Sélectionne le dictionnaire utilisé pour crypter
void FenetrePrincipale::ouvrirSrcTexteCrypter()
{
    cheminCrypterSrcTexte->setText(ouvrirFichierChemin());
}

// Sélectionne le dictionnaire utilisé pour décrypter
void FenetrePrincipale::ouvrirSrcTexteDecrypter()
{
    cheminDecrypterSrcTexte->setText(ouvrirFichierChemin());
}



// Changement de couleur dù à des erreurs dans l'onglet "Texte"

// Colorie en rouge le chemin indiquant le texte pour crypter
void FenetrePrincipale::coulErreurSrcCheminCrypter()
{
    cheminCrypterSrcTexte->setStyleSheet("border : 1px solid red; padding: 1px;");
}

// Colorie en rouge le chemin indiquant le texte pour décrypter
void FenetrePrincipale::coulErreurSrcCheminDecrypter()
{
    cheminDecrypterSrcTexte->setStyleSheet("border : 1px solid red; padding: 1px;");
}

// Rétablit la couleur d'origine du chemin indiquant le texte pour crypter
void FenetrePrincipale::coulInitSrcCheminCrypter()
{
    cheminCrypterSrcTexte->setStyleSheet("");
}

// Rétablit la couleur d'origine du chemin indiquant le texte pour décrypter
void FenetrePrincipale::coulInitSrcCheminDecrypter()
{
    cheminDecrypterSrcTexte->setStyleSheet("");
}



// Interaction dans l'onglet "Arbre"

// Zoom sur l'arbre
void FenetrePrincipale::zoomPlus()
{
    zoomArbreReset *= 0.8;
    arbreGraphicsView->scale(1.25, 1.25);
}

// Dézoom sur l'arbre
void FenetrePrincipale::zoomMoins()
{
    zoomArbreReset *= 1.25;
    arbreGraphicsView->scale(0.8, 0.8);
}

// Réinitialise le zoom sur l'arbre
void FenetrePrincipale::zoomReset()
{
    arbreGraphicsView->scale(zoomArbreReset, zoomArbreReset);
    zoomArbreReset = 1.000000;
}



// Affichage de l'arbre dans l'onglet "Arbre"

// Dessine l'arbre dans l'onglet qui lui est destiné
void FenetrePrincipale::dessinerArbre()
{
    // Supprime l'ancienne scène tout en faisant attention à ne pas delete l'arbre binaire

    // On récupère tout les items de la scène dans une liste
    QList<QGraphicsItem*> ancienNoeuds = arbreGraphicsScene->items();
    // Tant qu'il reste des items dans la liste, on enlève des items de la scène
    while(!ancienNoeuds.empty())
    {
        arbreGraphicsScene->removeItem(ancienNoeuds.first());
        ancienNoeuds.removeFirst();
    }

    // On récupère l'arbre
    ArbreHuff* arbreHuff = huffman->getArbreHuff();

    // On calcule sa profondeur
    int profArbre = arbreHuff->calculProf();

    // On indique à notre arbre la barre d'outil permettant de le modifier
    arbreHuff->setActionsArbre(actionsArbre);

    // On initialise la variable qui va nous permettre d'afficher correctement l'arbre
    int colDecalage[profArbre+1] = {0};

    // On dessine les noeuds/feuilles
    dessinerArbreNoeud(arbreHuff, 0, colDecalage);
    // On dessine les lignes entre les noeuds/feuilles
    dessinerArbreLigne(arbreHuff);

    // On corrige la taille de la scene suivant ce qu'elle contient
    arbreGraphicsScene->setSceneRect(arbreGraphicsScene->itemsBoundingRect());
}

// Dessine les noeuds de l'arbre
void FenetrePrincipale::dessinerArbreNoeud(ArbreHuff* arbreHuff, int row, int colDecalage[])
{
    // Si le noeud n'est pas vide (si on est pas encore arrivé à la fin d'une branche)
    if(!arbreHuff->estVide())
    {
        // On ajoute le noeud à la scène
        arbreGraphicsScene->addItem(arbreHuff);

        // On lui relie le signal de modification d'arbre avec le slot pour dessiner l'arbre
        // (on le disconnect avant au cas ou c'était déjà fait)
        QObject::disconnect(arbreHuff, SIGNAL(arbreModifie()), this, SLOT(dessinerArbre()));
        QObject::connect(arbreHuff, SIGNAL(arbreModifie()), this, SLOT(dessinerArbre()));

        // On calcule le nombre de feuille contenue dans sont sous arbre
        int nbFeuille = arbreHuff->calculFeuille();

        // On lui donne sa position x,y dans la scène
        arbreHuff->setPos((colDecalage[row] *  (arbreHuff->boundingRect().width() + 4)
                          + (((arbreHuff->boundingRect().width() + 4) * nbFeuille) / 2)), row * 40);

        // On fait l'appel récursif sur ses deux fils en modifiant de manière adequat les variables
        colDecalage[row+1] = colDecalage[row];
        dessinerArbreNoeud(arbreHuff->getFils0(), row+1, colDecalage);
        dessinerArbreNoeud(arbreHuff->getFils1(), row+1, colDecalage);
        colDecalage[row] += nbFeuille;
    }
}

// Dessiner les traits reliants les différents noeuds de l'arbre
void FenetrePrincipale::dessinerArbreLigne(ArbreHuff* arbreHuff)
{
    // Si l'arbre n'est pas vide (si on est pas arrivé a la fin d'une branche)
    if(!arbreHuff->estVide())
    {
        QGraphicsLineItem* arete;
        QGraphicsTextItem* etiquetteArete;
        QFont etiquetteAreteFont = QFont("Arial");
        etiquetteAreteFont.setWeight(50);
        etiquetteAreteFont.setPixelSize(14);

        // Si le fils 0 n'est pas vide
        if(!arbreHuff->getFils0()->estVide())
        {
            // On crée une nouvelle ligne
            arete = new QGraphicsLineItem(QLineF(arbreHuff->sceneCentre(), arbreHuff->getFils0()->sceneCentre()));
            arete->setZValue(-1);
            arete->setPen(QPen(Qt::black, 1.5));
            // On l'ajoute a la scène
            arbreGraphicsScene->addItem(arete);

            // On crée un nouveau texte qui etiquitera cette arête
            etiquetteArete = new QGraphicsTextItem("0");
            etiquetteArete->setDefaultTextColor(QColor("#969696"));
            etiquetteArete->setFont(etiquetteAreteFont);
            // On lui donne sa position x,y dans la scène
            etiquetteArete->setPos((arbreHuff->sceneCentre().x() + arbreHuff->getFils0()->sceneCentre().x()) / 2 - QFontMetrics(etiquetteAreteFont).width("0") - 4,
                                   (arbreHuff->sceneCentre().y() + arbreHuff->getFils0()->sceneCentre().y()) / 2 - arbreHuff->boundingRect().height() + 3);
            // On l'ajoute a la scène
            arbreGraphicsScene->addItem(etiquetteArete);

            // Appel récursif sur son fils 0
            dessinerArbreLigne(arbreHuff->getFils0());
        }

        // Si le fils 1 n'est pas vide
        if(!arbreHuff->getFils1()->estVide())
        {
            // On crée une nouvelle ligne
            arete = new QGraphicsLineItem(QLineF(arbreHuff->sceneCentre(), arbreHuff->getFils1()->sceneCentre()));
            arete->setZValue(-1);
            arete->setPen(QPen(Qt::black, 1.5));
            // On l'ajoute à la scène
            arbreGraphicsScene->addItem(arete);

            // On crée un nouveau texte qui étiquitera cette arête
            etiquetteArete = new QGraphicsTextItem("1");
            etiquetteArete->setDefaultTextColor(QColor("#969696"));
            etiquetteArete->setFont(etiquetteAreteFont);
            // On lui donne sa position x,y
            etiquetteArete->setPos((arbreHuff->sceneCentre().x() + arbreHuff->getFils1()->sceneCentre().x()) / 2 - QFontMetrics(etiquetteAreteFont).width("1") + 4,
                                   (arbreHuff->sceneCentre().y() + arbreHuff->getFils1()->sceneCentre().y()) / 2 - arbreHuff->boundingRect().height() + 3);
            // On l'ajoute à la scène
            arbreGraphicsScene->addItem(etiquetteArete);

            // Appel récursf sur son fils 1
            dessinerArbreLigne(arbreHuff->getFils1());
        }
    }
}
