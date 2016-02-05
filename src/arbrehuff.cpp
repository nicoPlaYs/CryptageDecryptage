#include "include/arbrehuff.h"



/* Initialisation de la variable static contenant un pointeur vers
 * la barre d'outils de modification de l'arbre */
QActionGroup* ArbreHuff::actionsOutils = 0;



// Getters
Occurences ArbreHuff::getEtiquette() const
{
    return etiquette;
}
ArbreHuff* ArbreHuff::getFils0() const
{
    return fils0;
}
ArbreHuff* ArbreHuff::getFils1() const
{
    return fils1;
}
ArbreHuff* ArbreHuff::getPere() const
{
    return pere;
}
QActionGroup* ArbreHuff::getActionsOutils() const
{
    return actionsOutils;
}



// Setters
void ArbreHuff::setEtiquette(Occurences nouvEtiquette)
{
    etiquette = nouvEtiquette;
}
void ArbreHuff::setFils0(ArbreHuff *nouvFils0)
{
    fils0 = nouvFils0;
}
void ArbreHuff::setFils1(ArbreHuff *nouvFils1)
{
    fils1 = nouvFils1;
}
void ArbreHuff::setPere(ArbreHuff *nouvPere)
{
    pere = nouvPere;
}
void ArbreHuff::setActionsArbre(QActionGroup *nouvActionsOutils)
{
    actionsOutils = nouvActionsOutils;
}



// Constructeurs
ArbreHuff::ArbreHuff(QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    // Initialisation des attributs d'algorithmes
        this->etiquette = Occurences();
        this->fils0 = 0;
        this->fils1 = 0;
        this->pere = 0;

    // Initialisation des attributs visuels
        // Autorise les clics gauches et droits pour interargir avec l'arbre
        this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
        // Autorise les évènements de survol
        this->setAcceptHoverEvents(true);
        // Autorise les glisser/déposer
        this->setAcceptDrops(true);
        // Initialise les couleurs de l'arbre
        this->initCoul();
}
ArbreHuff::ArbreHuff(Occurences etiquette, ArbreHuff* fils0, ArbreHuff* fils1, ArbreHuff* pere, QGraphicsItem* parent) : QGraphicsWidget(parent)
{
    // Initialisation des attributs d'algorithmes
        this->etiquette = etiquette;
        this->fils0 = fils0;
        this->fils1 = fils1;
        this->pere = pere;
        // Si le fils 0 n'est pas vide on définit son père
        if(!this->fils0->estVide())
        {
            this->fils0->pere = this;
        }
        // Si le fils 1 n'est pas vide on définit son père
        if(!this->fils1->estVide())
        {
            this->fils1->pere = this;
        }

    // Initialisation des attributs visuels
        // Autorise les clics gauches et droits pour interargir avec l'arbre
        this->setAcceptedMouseButtons(Qt::LeftButton | Qt::RightButton);
        // Autorise les évènements de survol
        this->setAcceptHoverEvents(true);
        // Autorise les glisser/déposer
        this->setAcceptDrops(true);
        // Initiliase les couleurs de l'arbre
        this->initCoul();
}



// Destructeur
ArbreHuff::~ArbreHuff()
{
    // S'il a un fils 0, on le supprime
    if(!fils0->estVide())
    {
        delete fils0;
    }
    // S'il a un fils 1, on le supprime
    if(!fils1->estVide())
    {
        delete fils1;
    }
    // S'il n'est pas la racine de l'arbre, on l'enlève des fils de son père
    if(!estRacine())
    {
        if(pere->getFils0() == this)
        {
            pere->setFils0(0);
        }
        else if(pere->getFils1() == this)
        {
            pere->setFils1(0);
        }
    }
}



// Méthodes



// Méthodes algorithmiques

// Retourne vrai si l'arbre est vide, sinon faux.
bool ArbreHuff::estVide()
{
    if(this == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Retourne vrai si l'arbre est une feuille, sinon faux.
bool ArbreHuff::estFeuille()
{
    // C'est une feuille, si ses deux fils sont vides
    if(fils0->estVide() && fils1->estVide())
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Retourne vrai si on se situe à la racine de l'arbre, sinon faux.
bool ArbreHuff::estRacine()
{
    // C'est la racine s'il ne possède pas de père...
    if(pere->estVide())
    {
        return true;
    }
    // ... Sinon, c'est un noeud !
    else
    {
        return false;
    }
}

// Retourne vrai si le noeud est l'ancêtre de celui en argument, sinon faux.
bool ArbreHuff::estAncetreDe(ArbreHuff* noeud)
{
    // Si le noeud n'est pas vide (c'est à dire que l'on ne se trouve pas à la fin d'une branche)
    if(!this->estVide())
    {
        // On renvoie vrai si on a trouvé le noeud qu'on cherche
        if(this == noeud)
        {
            return true;
        }
        // Sinon on remonte un peu plus dans l'arbre
        else
        {
            return this->getFils0()->estAncetreDe(noeud) || this->getFils1()->estAncetreDe(noeud);
        }
    }
    // Sinon on renvoie faux (on est arrivé a la fin d'une branche)
    else
    {
        return false;
    }
}

// Retourne la profondeur de l'arbre (et retourne -1 si l'arbre est vide)
int ArbreHuff::calculProf()
{
    // Si le noeud n'est pas vide (c'est à dire que l'on ne se trouve pas à la fin d'une branche de l'arbre)
    if(!estVide())
    {
        // On fait l'appel récursif sur les fils du noeud actuel
        int profFils0 = fils0->calculProf();
        int profFils1 = fils1->calculProf();

        // On retourne la plus grande profondeur des deux + 1
        if(profFils0 > profFils1)
        {
            return 1 + profFils0;
        }
        else
        {
            return 1 + profFils1;
        }
    }
    // Si on est arrivé au bout d'une branche de l'arbre on retourne 0
    else
    {
        return 0;
    }
}

// Retourne le nombre de feuilles contenues dans l'arbre
int ArbreHuff::calculFeuille()
{
    // Si le noeud n'est pas vide (que l'on est pas à la fin d'une branche de l'arbre)
    if(!estVide())
    {
        // Si c'est une feuille, alors on retourne 1
        if(estFeuille())
        {
            return 1;
        }
        // Sinon on additionne les deux appels récursifs sur les deux fils du noeud
        else
        {
            return fils0->calculFeuille() + fils1->calculFeuille();
        }
    }
    // Si on est arrivé au bout d'une branche on retourne 0
    else
    {
        return 0;
    }
}

// Répercute le changement de poid d'une feuille ou d'un noeud sur le reste de l'arbre
void ArbreHuff::modifOcc(int changement)
{
    // Si le noeud n'est pas vide (que l'on est pas encore arrivé au sommet de l'arbre)
    if(!this->estVide())
    {
        // On récupère l'ancien couple (caractère, nombre d'occurences)
        Occurences nouvOcc = this->getEtiquette();
        // On ajoute le changement du nombre d'occurences à cette variable
        nouvOcc.setNbOcc(nouvOcc.getNbOcc() + changement);
        // Et on la définit comme la nouvelle étiquette du noeud
        this->setEtiquette(nouvOcc);

        // On réalise l'appel récursif sur son père pour remonter dans l'arbre
        this->getPere()->modifOcc(changement);
    }
}



// Méthodes visuelles

// Initialisation des couleurs du noeud
void ArbreHuff::initCoul()
{
    // Définit les positions de départ et de fin du dégradé
    coulFond.setStart(this->boundingRect().x(),this->boundingRect().y());
    coulFond.setFinalStop(coulFond.start().x() + this->boundingRect().width(),
                          coulFond.start().y() + this->boundingRect().height());

    // Dégradé gris s'il s'agit d'un noeud et texte blanc
    if(this->getEtiquette().getCarac() == '\0')
    {
        coulTexte.setNamedColor("#000000");
        coulFond.setColorAt(0, QColor("#FFFFFF"));
        coulFond.setColorAt(1, QColor("#969696"));
    }
    // Dégradé noir s'il s'agit d'une feuille et texte noir
    else
    {
        coulTexte.setNamedColor("#FFFFFF");

        coulFond.setColorAt(0, QColor("#646464"));
        coulFond.setColorAt(1, QColor("#000000"));
    }

    // Mise à jour de l'affichage du noeud/feuille
    update();
}

/* Réinitialisation les couleurs du noeud et de ses descendants
 * après avoir été survolé par l'outil d'échange ou de suppresion */
void ArbreHuff::initCoulEchangeSupprSousArbre()
{
    // Si le noeud n'est pas vide (si on est pas encore arrivé à la fin d'une branche de l'arbre)
    if(!this->estVide())
    {
        // On réinitialise sa couleur
        this->initCoul();

        // Appels récursifs sur ses fils
        this->getFils0()->initCoulEchangeSupprSousArbre();
        this->getFils1()->initCoulEchangeSupprSousArbre();
    }
}

// Couleur du noeud lorsqu'il est survolé par les outils d'édition ou d'ajouts
void ArbreHuff::hoverCoulEditerAjout()
{
    // Texte en noir
    coulTexte.setNamedColor("#FFFFFF");

    // Dégradé vert
    coulFond.setColorAt(0, QColor("#61c244"));
    coulFond.setColorAt(1, QColor("#274f1b"));

    // Mise à jour de l'affichage du noeud/feuille
    update();
}

// Couleur du noeud lorsqu'il est survolé par l'outil d'échange
void ArbreHuff::hoverCoulEchangerSrc()
{
    // Si le noeud n'est pas vide (si on est pas encore arrivé à la fin d'une branche de l'arbre)
    if(!this->estVide())
    {
        // Texte en blanc
        coulTexte.setNamedColor("#FFFFFF");

        // Dégradé bleu
        coulFond.setColorAt(0, QColor("#3fb2ec"));
        coulFond.setColorAt(1, QColor("#0d5f88"));

        // Mise à jour de l'affichage du noeud/feuille
        update();

        // Appels récursifs sur les fils
        this->getFils0()->hoverCoulEchangerSrc();
        this->getFils1()->hoverCoulEchangerSrc();
    }
}

// Couleur du noeud lorsqu'il est survolé par l'outil d'échange lors d'un glisser/déposer
void ArbreHuff::hoverCoulEchangerDest()
{
    // Si le noeud n'est pas vide (si on est pas encore arrivé à la fin d'une branche de l'arbre)
    if(!this->estVide())
    {
        // Texte en blanc
        coulTexte.setNamedColor("#FFFFFF");

        // Dégradé jaune
        coulFond.setColorAt(0, QColor("#ecde3f"));
        coulFond.setColorAt(1, QColor("#887e0d"));

        // Mise à jour de l'affichage du noeud/feuille
        update();

        // Appels récursifs sur les fils
        this->getFils0()->hoverCoulEchangerDest();
        this->getFils1()->hoverCoulEchangerDest();
    }
}

// Couleur du noeud lorsqu'il est survolé par l'outil de suppresion de noeud/feuille
void ArbreHuff::hoverCoulSupprFeuilleNoeud()
{
    // Texte en blanc
    coulTexte.setNamedColor("#FFFFFF");

    // Dégradé rouge
    coulFond.setColorAt(0, QColor("#ea2d2d"));
    coulFond.setColorAt(1, QColor("#5b0808"));

    // Mise à jour de l'affichage du noeud/feuille
    update();
}

// Couleur du noeud lorsqu'il est survolé par l'outil de suppresion de sous-arbre
void ArbreHuff::hoverCoulSupprSousArbre()
{
    // Si le noeud n'est pas vide (si on est pas encore arrivé à la fin d'une branche de l'arbre)
    if(!this->estVide())
    {
        // Texte en blanc
        coulTexte.setNamedColor("#FFFFFF");

        // Dégradé rouge
        coulFond.setColorAt(0, QColor("#ea2d2d"));
        coulFond.setColorAt(1, QColor("#5b0808"));

        // Mise à jour de l'affichage du noeud/feuille
        update();

        // Appels récursifs sur les fils
        this->getFils0()->hoverCoulSupprSousArbre();
        this->getFils1()->hoverCoulSupprSousArbre();
    }
}

// Retourne le point centrale du noeud
QPointF ArbreHuff::sceneCentre() const
{
    QPointF centre;
    centre.setX(this->scenePos().x() + this->boundingRect().width() / 2);
    centre.setY(this->scenePos().y() + this->boundingRect().height() / 2);

    return centre;
}

// Retourne le rectangle correspondant à la zone délimitant le noeud
QRectF ArbreHuff::boundingRect() const
{
    // Si il s'agit d'un noeud
    if(this->getEtiquette().getCarac() == '\0')
    {
        return QRectF(0,0,25,20);
    }
    // Sinon il s'agit d'une feuille
    else
    {
        return QRectF(0,0,25,40);
    }
}

// Retourne la taille de la zone délimitant le noeud
QSizeF ArbreHuff::sizeHint(Qt::SizeHint which, const QSizeF &constraint) const
{
    Q_UNUSED(which);
    Q_UNUSED(constraint);

    // S'il s'agit d'un noeud
    if(this->getEtiquette().getCarac() == '\0')
    {
        return QSizeF(25,20);
    }
    // Sinon il s'agit d'une feuille
    else
    {
        return QSizeF(25,40);
    }
}

// Dessine le noeud
void ArbreHuff::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);

    // On vérifie que le noeud n'est pas vide
    if(!estVide())
    {
        // On définit le rectangle qui représentera le noeud
        QRectF noeudRect;
        if(this->getEtiquette().getCarac() == '\0')
        {
            noeudRect = QRectF(0,0,25, 20);
        }
        else
        {
            noeudRect = QRectF(0,0,25, 40);
        }
        // On dessine le rectangle plein
        painter->setBrush(QBrush(coulFond));
        painter->drawRoundedRect(noeudRect, 10,10);
        // On dessine un contour noir pour ce rectangle
        painter->setPen(QPen(Qt::black, 1.5));
        painter->drawRoundedRect(noeudRect, 10,10);

        // On s'occupe maintenant du texte
        painter->setPen(QPen(coulTexte));
        QFont police = QFont();
            police.setPixelSize(16);
            police.setFamily("Arial");

        // On calcule la taille du texte suivant l'espace disponible et les caracètres à afficher
        painter->setFont(police);
        float factor = boundingRect().width() / painter->fontMetrics().width(QString::number(this->getEtiquette().getNbOcc()));
        if(factor < 1)
        {
            police.setPixelSize(((double) police.pixelSize() * factor) - 0.25);
            painter->setFont(police);
        }

        // S'il s'agit d'un noeud, il y'a juste le nombre d'occurences à indiquer
        if(this->getEtiquette().getCarac() == '\0')
        {
            // Le nombre d'occurences
            painter->drawText(noeudRect, QString::number(this->getEtiquette().getNbOcc()), QTextOption(Qt::AlignCenter));
        }
        // Sinon il y'a également le caracètre à afficher au dessus du nombre d'occurences
        else
        {
            // Le caractère
            noeudRect.setY(noeudRect.y() + ((40 - (QFontMetrics(police).height() * 2)) / 2));
            painter->drawText(noeudRect, QString("'%1'").arg(this->getEtiquette().getCarac()), QTextOption(Qt::AlignHCenter));

            // Le nombre d'occurences
            noeudRect.setY(noeudRect.y() + QFontMetrics(police).height());
            painter->drawText(noeudRect, QString::number(this->getEtiquette().getNbOcc()), QTextOption(Qt::AlignHCenter));
        }
    }
}

/* Lorsqu'on rentre dans la zone du noeud en le survolant à la souris
 * -> changement de la couleur du/des noeud(s) et du curseur */
void ArbreHuff::hoverEnterEvent(QGraphicsSceneHoverEvent *event)
{
    /* Si l'outil actif est soit "editer", soit "ajouterfeuille" soit "ajouterNoeud"
     * et que leur conditions d'utilisation respective sont respectées */
    if((actionsOutils->checkedAction()->objectName() == "editer" && this->getEtiquette().getCarac() != '\0')
            || (actionsOutils->checkedAction()->objectName() == "ajouterFeuille" && (this->getEtiquette().getCarac() == '\0') && (this->getFils0()->estVide() || this->getFils1()->estVide()))
            || (actionsOutils->checkedAction()->objectName() == "ajouterNoeud" && this->getEtiquette().getCarac() == '\0'))
    {
        // On accepte l'évènement
        event->accept();

        // On définit le curseur à avoir lors du survol
        setCursor(Qt::PointingHandCursor);

        // On modifie la couleur du noeud
        this->hoverCoulEditerAjout();
    }
    /* Si l'outil actif est "echanger"
     * et que sa condition d'utilisation est respecté */
    else if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On définit le curseur à avoir lors du survol
        setCursor(Qt::OpenHandCursor);

        // On modifie la couleur du noeud
        this->hoverCoulEchangerSrc();
    }
    /* Si l'outil actif est "supprimerFeuilleNoeud"
     * et que ses conditions d'utilisation sont respectées  */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerFeuilleNoeud" && !this->estRacine()
            && (this->getFils0()->estVide() || this->getFils1()->estVide() || this->getPere()->getFils0()->estVide() || this->getPere()->getFils1()->estVide()))
    {
        // On accepte l'évènement
        event->accept();

        // On définit le curseur à avoir lors du survol
        setCursor(Qt::PointingHandCursor);

        // On modifie la couleur du noeud
        this->hoverCoulSupprFeuilleNoeud();
    }
    /* Si l'outil actif est "supprimerSousArbre"
     * et que ses conditions d'utilisation sont respectées */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerSousArbre" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On définit le curseur à avoir lors du survol
        setCursor(Qt::PointingHandCursor);

        // On modifie la couleur du noeud
        this->hoverCoulSupprSousArbre();
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on sort de la zone du noeud en le survolant à la souris
 * -> réinitialisation de la couleur du/des noeud(s) et du curseur */
void ArbreHuff::hoverLeaveEvent(QGraphicsSceneHoverEvent *event)
{
    /* Si l'outil actif est soit "editer", soit "ajouterfeuille" soit "ajouterNoeud"
     * et que leur conditions d'utilisation respective sont respectées */
    if((actionsOutils->checkedAction()->objectName() == "editer" && this->getEtiquette().getCarac() != '\0')
            || (actionsOutils->checkedAction()->objectName() == "ajouterFeuille" && (this->getEtiquette().getCarac() == '\0') && (this->getFils0()->estVide() || this->getFils1()->estVide()))
            || (actionsOutils->checkedAction()->objectName() == "ajouterNoeud" && this->getEtiquette().getCarac() == '\0'))
    {
        // On accepte l'évènement
        event->accept();

        // On réinitialise le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur du noeud
        this->initCoul();
    }
    /* Si l'outil actif est "echanger"
     * et que sa condition d'utilisation est respecté */
    else if (actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On réinitialise le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur des noeuds
        this->initCoulEchangeSupprSousArbre();
    }
    /* Si l'outil actif est "supprimerFeuilleNoeud"
     * et que ses conditions d'utilisation sont respectées  */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerFeuilleNoeud" && !this->estRacine()
            && (this->getFils0()->estVide() || this->getFils1()->estVide() || this->getPere()->getFils0()->estVide() || this->getPere()->getFils1()->estVide()))
    {
        // On accepte l'évènement
        event->accept();

        // On réinitialise le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur des noeuds
        this->initCoul();
    }
    /* Si l'outil actif est "supprimerSousArbre"
     * et que ses conditions d'utilisation sont respectées */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerSousArbre" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On réinitialise le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur des noeuds
        this->initCoulEchangeSupprSousArbre();
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on déplace le noeud (presser + déplacer la souris)
 * -> le gisser du glisser/déposer */
void ArbreHuff::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    /* Si l'outil actif est "echanger"
     * et que sa condition d'utilisation est respecté */
    if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // Création d'un objet de "glissement" et d'un MIME dans lequel on copie le pointeur de l'arbre
        QDrag *drag = new QDrag(event->widget());
        QMimeData *mime = new QMimeData;
        QByteArray copieArbreByteArray;
        QDataStream copieArbreStream(&copieArbreByteArray, QIODevice::WriteOnly);
        copieArbreStream << (qint64) this;
        mime->setData("ArbreBinHuff", copieArbreByteArray);
        drag->setMimeData(mime);

        // Création d'une surface transparente d'une taille légèrement suppérieur à celle du noeud
        QPixmap pixmap(this->boundingRect().width() + 2,this->boundingRect().height() + 2);
        pixmap.fill(Qt::transparent);

        // On dessine le noeud sur cette nouvelle surface
        QPainter painter(&pixmap);
        painter.translate(1, 1);
        painter.setRenderHint(QPainter::Antialiasing);
        paint(&painter, 0, 0);
        painter.end();

        // On applique ce dessin sur l'action de glissement
        drag->setPixmap(pixmap);

        // On définit ou se situe la pointe du curseur lors du glissement
        drag->setHotSpot(QPoint(0,0));

        // On éxécute le glissement
        drag->exec();

        // Après le glissement, on réinitialise la couleur des noeuds
        this->initCoulEchangeSupprSousArbre();
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on clic sur le noeud
 * -> opération différentes suivant l'outil sélectionné */
void ArbreHuff::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    /* Si l'outil actif est "editer"
     * et que ses conditions d'utilisation sont respectées */
    if(actionsOutils->checkedAction()->objectName() == "editer" && this->getEtiquette().getCarac() != '\0')
    {
        // On accepte l'évènement
        event->accept();

        // On ouvre la fenêtre de dialogue de modification de feuille
        DialogModifFeuille* modifFeuille = new DialogModifFeuille(this);
        modifFeuille->setAttribute(Qt::WA_DeleteOnClose);
        modifFeuille->show();
    }
    /* Si l'outil actif est "echanger"
     * et que sa condition d'utilisation est respectée */
    else if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On modifie le curseur
        setCursor(Qt::ClosedHandCursor);
    }
    /* Si l'outil actif est "ajouterFeuille"
     * et que ses conditions d'utilisation sont respectées */
    else if(actionsOutils->checkedAction()->objectName() == "ajouterFeuille" && (this->getEtiquette().getCarac() == '\0') && (this->getFils0()->estVide() || this->getFils1()->estVide()))
    {
        // On accepte l'évènement
        event->accept();

        ArbreHuff* nouvFeuille;
        // Si le clic gauche a été pressé et que le fils gauche est libre...
        if(event->button() == Qt::LeftButton && this->getFils0()->estVide())
        {
            // ...on crée une nouvelle feuille qui se placera à gauche du noeud cliqué
            nouvFeuille = new ArbreHuff(Occurences('A', 0), 0, 0, this);
            this->setFils0(nouvFeuille);
        }
        // Sinon si le clic droit a été pressé et que le fils droit est libre...
        else if(event->button() == Qt::RightButton && this->getFils1()->estVide())
        {
            // ...on crée une nouvelle feuille qui se placera à droite du noeud cliqué
            nouvFeuille = new ArbreHuff(Occurences('A', 0), 0, 0, this);
            this->setFils1(nouvFeuille);
        }

        // On change le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur du noeud
        this->initCoul();

        // On indique à la fenetre principale qu'il faut réafficher entièrement l'arbre
        emit this->arbreModifie();
    }
    /* Si l'outil actif est "ajouterNoeud"
     * et que ses conditions d'utilisation sont respectées */
    else if(actionsOutils->checkedAction()->objectName() == "ajouterNoeud" && (this->getEtiquette().getCarac() == '\0'))
    {
        // On accepte l'évènement
        event->accept();

        ArbreHuff* nouvNoeud;
        // Si le clic gauche a été pressé...
        if(event->button() == Qt::LeftButton)
        {
            // ... on crée un nouveau noeud à gauche
            nouvNoeud = new ArbreHuff(Occurences('\0', 0), this->getFils0(), 0, this);
            if(!nouvNoeud->getFils0()->estVide())
            {
                nouvNoeud->setEtiquette(Occurences('\0', this->getFils0()->getEtiquette().getNbOcc()));
                nouvNoeud->getFils0()->setPere(nouvNoeud);
            }
            this->setFils0(nouvNoeud);
        }
        // Sinon si le clic droit a été pressé...
        else if(event->button() == Qt::RightButton)
        {
            // ... on crée un nouveau noeud à droite
            nouvNoeud = new ArbreHuff(Occurences('\0', 0), 0, this->getFils1(), this);
            if(!nouvNoeud->getFils1()->estVide())
            {
                nouvNoeud->setEtiquette(Occurences('\0', this->getFils1()->getEtiquette().getNbOcc()));
                nouvNoeud->getFils1()->setPere(nouvNoeud);
            }
            this->setFils1(nouvNoeud);
        }

        // On modifie le curseur
        setCursor(Qt::ArrowCursor);

        // On réinitialise la couleur du noeud
        this->initCoul();

        // On indique à la fenetre principale qu'il faut réafficher entièrement l'arbre
        emit this->arbreModifie();
    }
    /* Si l'outil actif est "supprimerFeuilleNoeud"
     * et que ses conditions d'utilisation sont respectées */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerFeuilleNoeud" && !this->estRacine()
            && (this->getFils0()->estVide() || this->getFils1()->estVide() || this->getPere()->getFils0()->estVide() || this->getPere()->getFils1()->estVide()))
    {
        // Si il s'agit d'une feuille...
        if(this->estFeuille())
        {
            if(this->getPere()->getFils0() == this)
            {
                this->getPere()->setFils0(0);
            }
            else if(this->getPere()->getFils1() == this)
            {
                this->getPere()->setFils1(0);
            }

            if(this->getEtiquette().getCarac() != '\0')
            {
                int changement = - this->getEtiquette().getNbOcc();
                pere->modifOcc(changement);
            }
        }
        // Sinon, si les deux fils du noeud sont vides
        else if(!this->getFils0()->estVide() && !this->getFils1()->estVide())
        {
            this->getPere()->setFils0(this->getFils0());
            this->getFils0()->setPere(this->getPere());
            this->getPere()->setFils1(this->getFils1());
            this->getFils1()->setPere(this->getPere());
        }
        // Sinon, si seulement le fils gauche est vide
        else if(!this->getFils0()->estVide())
        {
            if(this->getPere()->getFils0() == this)
            {
                this->getPere()->setFils0(this->getFils0());
                this->getFils0()->setPere(this->getPere());
            }
            else if(this->getPere()->getFils1() == this)
            {
                this->getPere()->setFils1(this->getFils0());
                this->getFils0()->setPere(this->getPere());
            }
        }
        // Sinon, si seulement le fils droit est vide
        else if(!this->getFils1()->estVide())
        {
            if(this->getPere()->getFils0() == this)
            {
                this->getPere()->setFils0(this->getFils1());
                this->getFils1()->setPere(this->getPere());
            }
            else if(this->getPere()->getFils1() == this)
            {
                this->getPere()->setFils1(this->getFils1());
                this->getFils1()->setPere(this->getPere());
            }
        }

        // On récupère le pere de la feuille/noeud à supprimer
        ArbreHuff* pereThis = this->getPere();

        /* On supprime le noeud/feuille en faisant bien attention à ne pas supprimer
         * ses anciens descendants */
        this->setFils0(0);
        this->setFils1(0);
        this->setPere(0);
        delete this;

        // On indique à la fenetre principale qu'il faut réafficher entièrement l'arbre
        emit pereThis->arbreModifie();
    }
    /* Si l'outil actif est "supprimerSousArbre"
     * et que sa condition d'utilisation est respectée */
    else if(actionsOutils->checkedAction()->objectName() == "supprimerSousArbre" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // Stocke le changement à répercuter au niveau du nombre d'occurences
        int changement = -this->getEtiquette().getNbOcc();

        // On sauvegarde un pointeur vers le père avant de supprimer le sous-arbre
        ArbreHuff* pereThis = this->getPere();
        delete this;

        // On met à jour les occurences dans l'arbre
        pereThis->modifOcc(changement);

        // On indique à la fenetre principale qu'il faut réafficher entièrement l'arbre
        emit pereThis->arbreModifie();
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on relâche le clic sur le noeud
 * -> Affiche le curseur de main ouverte */
void ArbreHuff::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    /* Si l'outil actif est "echanger"
     * et que sa condition d'utilisation est respectée */
    if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine())
    {
        // On accepte l'évènement
        event->accept();

        // On modifie le curseur
        setCursor(Qt::OpenHandCursor);
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on rentre quelque chose dans sa zone de glisser/déposer
 * -> Changement de couleur du noeud */
void ArbreHuff::dragEnterEvent(QGraphicsSceneDragDropEvent *event)
{
    /* On vérifie que ce qui est déposé contient bien un arbre binaire d'huffman
     * et que l'outil actif est bien celui de glisser/déposer */
    if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine()
            && event->mimeData()->hasFormat("ArbreBinHuff"))
    {
        // On récupère le pointeur de l'arbre contenu dans les informations de glissement
        QByteArray copieArbreByteArray = event->mimeData()->data("ArbreBinHuff");
        QDataStream copieArbreStream(&copieArbreByteArray, QIODevice::ReadOnly);
        qint64 dropArbrePtr;
        copieArbreStream >> dropArbrePtr;
        ArbreHuff* dropArbre = (ArbreHuff*) dropArbrePtr;

        // On vérifie que l'arbre n'a pas été glissé sur un de ses ancêtres et inversement
        if(!this->estAncetreDe(dropArbre) && !dropArbre->estAncetreDe(this))
        {
            // On accepte l'évènement
            event->accept();

            // On modifie la couleur des noeuds
            this->hoverCoulEchangerDest();
        }
        else if(this == dropArbre)
        {
            // On ignore l'évènement
            event->ignore();

            // On modifie la couleur des noeuds
            this->hoverCoulEchangerSrc();
        }
        // Sinon on ignore l'évènement
        else
        {
            event->ignore();
        }

    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on sort quelque chose de sa zone de glisser/déposer
 * -> Couleur du noeud qui revient à la normale */
void ArbreHuff::dragLeaveEvent(QGraphicsSceneDragDropEvent *event)
{
    /* On vérifie que ce qui est déposé contient bien un arbre binaire d'huffman
     * et que l'outil actif est bien celui de glisser/déposer */
    if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine()
            && event->mimeData()->hasFormat("ArbreBinHuff"))
    {
        // On récupère le pointeur de l'arbre contenu dans les informations de glissement
        QByteArray copieArbreByteArray = event->mimeData()->data("ArbreBinHuff");
        QDataStream copieArbreStream(&copieArbreByteArray, QIODevice::ReadOnly);
        qint64 dropArbrePtr;
        copieArbreStream >> dropArbrePtr;
        ArbreHuff* dropArbre = (ArbreHuff*) dropArbrePtr;

        // On vérifie que l'arbre n'a pas été glissé sur un de ses ancêtres et inversement
        if(!this->estAncetreDe(dropArbre) && !dropArbre->estAncetreDe(this))
        {
            // On accepte l'évènement
            event->accept();

            // On modifie la couleur des noeuds
            this->initCoulEchangeSupprSousArbre();
        }
        // Sinon on ignore l'évènement
        else
        {
            event->ignore();
        }
    }
    // Sinon on ignore l'évènement
    else
    {
        event->ignore();
    }
}

/* Lorsqu'on lache quelque chose dans sa zone de glisser/déposer
 * -> Echange de position entre les deux noeuds */
void ArbreHuff::dropEvent(QGraphicsSceneDragDropEvent *event)
{
    /* On vérifie que ce qui est déposé contient bien un arbre binaire d'huffman
     * et que l'outil actif est bien celui de glisser/déposer */
    if(actionsOutils->checkedAction()->objectName() == "echanger" && !this->estRacine() &&
            event->mimeData()->hasFormat("ArbreBinHuff"))
    {
        // On récupère le pointeur de l'arbre contenu dans les informations de glissement
        QByteArray copieArbreByteArray = event->mimeData()->data("ArbreBinHuff");
        QDataStream copieArbreStream(&copieArbreByteArray, QIODevice::ReadOnly);
        qint64 dropArbrePtr;
        copieArbreStream >> dropArbrePtr;
        ArbreHuff* dropArbre = (ArbreHuff*) dropArbrePtr;

        // On vérifie que l'arbre n'a pas été glissé sur un de ses ancêtres et inversement
        if(!this->estAncetreDe(dropArbre) && !dropArbre->estAncetreDe(this))
        {
            // On accepte l'évènement
            event->accept();

            // On garde le pointeur vers le père d'origine du noeud/feuille
            ArbreHuff* pereThis = this->getPere();

            // Si l'arbre glisser se trouve dans le fils 0 de son père
            if(dropArbre->getPere()->getFils0() == dropArbre)
            {
                // Si l'arbre ou l'on drop se trouve dans le fils 0 de son père
                if(this->getPere()->getFils0() == this)
                {
                    // On indique les nouveaux fils des 2 pères
                    this->getPere()->setFils0(dropArbre);
                    dropArbre->getPere()->setFils0(this);

                    // On indique leurs nouveaux père s
                    this->setPere(dropArbre->getPere());
                    dropArbre->setPere(pereThis);
                }
                // Si l'arbre ou l'on drop se trouve dans le fils 1 de son père
                else if(this->getPere()->getFils1() == this)
                {
                    // On indique les nouveaux fils des 2 pères
                    this->getPere()->setFils1(dropArbre);
                    dropArbre->getPere()->setFils0(this);

                    // On indique leurs nouveaux pères
                    this->setPere(dropArbre->getPere());
                    dropArbre->setPere(pereThis);
                }
            }
            // Si l'arbre glisser se trouve dans le fils 1 de son père
            else if(dropArbre->getPere()->getFils1() == dropArbre)
            {
                // Si l'arbre ou l'on drop se trouve dans le fils 0 de son père
                if(this->getPere()->getFils0() == this)
                {
                    // On indique les nouveaux fils des 2 pères
                    this->getPere()->setFils0(dropArbre);
                    dropArbre->getPere()->setFils1(this);

                    // On indique leurs nouveaux pères
                    this->setPere(dropArbre->getPere());
                    dropArbre->setPere(pereThis);
                }
                // Si l'arbre ou l'on drop se trouve dans le fils 1 de son père
                else if(this->getPere()->getFils1() == this)
                {
                    // On indique les nouveaux fils des 2 pères
                    this->getPere()->setFils1(dropArbre);
                    dropArbre->getPere()->setFils1(this);

                    // On indique leurs nouveaux pères
                    this->setPere(dropArbre->getPere());
                    dropArbre->setPere(pereThis);
                }
            }

            // Modification du nombre d'occurences
            int prec = this->getEtiquette().getNbOcc();
            int changement = dropArbre->getEtiquette().getNbOcc() - prec;
            this->getPere()->modifOcc(-changement);
            dropArbre->getPere()->modifOcc(changement);

            // Réinitialisation de la couleur des noeuds
            this->initCoulEchangeSupprSousArbre();

            // On indique à la fenetre principale qu'il faut réafficher entièrement l'arbre
            emit this->arbreModifie();
        }
        // Sinon, on ignore l'évènement
        else
        {
            event->ignore();
        }
    }
    // Sinon, on ignore l'évènement
    else
    {
        event->ignore();
    }
}



// Surcharge d'opérateur

// Deux arbres sont égaux s'il possède les mêmes fils et la même étiquette
bool ArbreHuff::operator==(ArbreHuff& secondArbreHuff)
{
    if(this->fils0 == secondArbreHuff.fils0 && this->fils1 == secondArbreHuff.fils1 && this->etiquette == secondArbreHuff.etiquette)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// On réutilise l'opérateur == pour définir le !=
bool ArbreHuff::operator!=(ArbreHuff& secondArbreHuff)
{
    return (!(*this == secondArbreHuff));
}
/* Un arbre est inférieur à l'autre si le nombre d'occurences contenu dans son étiquette
 * est inférieur à celui de l'autre arbre */
bool ArbreHuff::operator<(ArbreHuff& secondArbreHuff)
{
    if(this->getEtiquette().getNbOcc() < secondArbreHuff.getEtiquette().getNbOcc())
    {
        return true;
    }
    else
    {
        return false;
    }
}
