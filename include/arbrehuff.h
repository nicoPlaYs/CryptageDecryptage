#ifndef ARBREHUFF_H
#define ARBREHUFF_H



// Interface graphique

    // Conteneurs
    #include <QGraphicsWidget> // Widget contenu dans une scène graphique
    #include <QWidget> // Widget de base

    // Interactions avec l'utilisateur
    #include <QGraphicsSceneMouseEvent> // Evenement de souris dans une scène graphique
    #include <QGraphicsSceneDragDropEvent> // Evenement de glisser/déposer
    #include <QDrag> // Utiliser lors d'un glisser/déposer
    #include <QActionGroup> // Regroupe plusieurs actions ensembles

    // Dessin & Scène Graphique
    #include <QGraphicsView> // Affiche une scène graphique
    #include <QPainter> // Outils de dessins

// Structures Qt
#include <QColor> // Contient une couleur
#include <QLinearGradient> // Contient un dégradé linéaire
#include <QMimeData> // Stockage d'information lors du glisser déposer
#include <QPixmap> // Surface de pixels
#include <QCursor> // Définit les curseurs de souris


class ArbreHuff;
#include "occurences.h" // Stocke un caractère et son nombre d'occurences
#include "dialogmodifnoeud.h" // Fenêtre de dialogue de modification de feuille



// Arbre binaire d'Huffman
class ArbreHuff : public QGraphicsWidget
{
    Q_OBJECT

    // Attributs
    private :
        // Attributs algorithmiques
            // Etiquette de l'arbre qui est un couple (caractère, nombre d'occurences du caractère)
            Occurences etiquette;
            // Fils gauche
            ArbreHuff* fils0;
            // Fils droit
            ArbreHuff* fils1;
            // Père
            ArbreHuff* pere;

        // Atributs visuels
            // Couleur de fond du noeud
            QLinearGradient coulFond;
            // Couleur du texte du noeud
            QColor coulTexte;
            // Barre d'outils pour modifier l'arbre (commune à tous les éléments de la classe arbre)
            static QActionGroup* actionsOutils;


    // Getters
    public :
        Occurences getEtiquette() const;
        ArbreHuff* getFils0() const;
        ArbreHuff* getFils1() const;
        ArbreHuff* getPere() const;
        QActionGroup* getActionsOutils() const;

    // Setters
    public :
        void setEtiquette(Occurences nouvEtiquette);
        void setFils0(ArbreHuff* nouvFils0);
        void setFils1(ArbreHuff* nouvFils1);
        void setPere(ArbreHuff* nouvPere);
        void setActionsArbre(QActionGroup* nouvActionsOutils);

    // Constructeurs
    public :
        ArbreHuff(QGraphicsItem* parent = 0);
        ArbreHuff(Occurences etiquette, ArbreHuff* fils0 = 0, ArbreHuff* fils1 = 0, ArbreHuff* pere = 0, QGraphicsItem* parent = 0);

    // Destructeurs
    public :
        ~ArbreHuff();

    // Méthodes
    public :
        // Méthodes algorithmiques
            // Retourne vrai si l'arbre est vide, sinon faux.
            bool estVide();
            // Retourne vrai si l'arbre est une feuille, sinon faux.
            bool estFeuille();
            // Retourne vrai si on se situe à la racine de l'arbre, sinon faux.
            bool estRacine();
            // Retourne vrai si le noeud est l'ancêtre de celui en argument, sinon faux.
            bool estAncetreDe(ArbreHuff* noeud);
            // Retourne la profondeur de l'arbre (-1 si l'arbre est vide)
            int calculProf();
            // Retourne le nombre de feuilles contenues dans l'arbre
            int calculFeuille();
            // Répercute le changement de poids d'une feuille ou d'un noeud sur le reste de l'arbre
            void modifOcc(int changement);

        // Méthodes visuelles
            // Initialisation des couleurs du noeud
            void initCoul();
            // Réinitialisation les couleurs du noeud et de ses descendants après avoir été survolé par l'outil de suppresion
            void initCoulEchangeSupprSousArbre();
            // Couleur du noeud lorsqu'il est survolé par les outils d'édition ou d'ajouts
            void hoverCoulEditerAjout();
            // Couleur du noeud lorsqu'il est survolé par l'outil d'échange
            void hoverCoulEchangerSrc();
            // Couleur du noeud lorsqu'il est survolé par l'outil d'échange lors d'un glisser/déposer
            void hoverCoulEchangerDest();
            // Couleur du noeud lorsqu'il est survolé par l'outil de suppresion de noeud/feuille
            void hoverCoulSupprFeuilleNoeud();
            // Couleur du noeud lorsqu'il est survolé par l'outil de suppresion de sous-arbre
            void hoverCoulSupprSousArbre();
            // Retourne le point centrale du noeud
            QPointF sceneCentre() const;
            // Retourne le rectangle correspondant à la zone délimitant le noeud
            virtual QRectF boundingRect() const;
            // Retourne la taille de la zone délimitant le noeud
            virtual QSizeF sizeHint(Qt::SizeHint which, const QSizeF &constraint) const;
            // Dessine le noeud
            virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
            /* Lorsqu'on rentre dans la zone du noeud en le survolant à la souris
             * -> changement de la couleur du/des noeud(s) et du curseur */
            virtual void hoverEnterEvent(QGraphicsSceneHoverEvent* event);
            /* Lorsqu'on sort de la zone du noeud en le survolant à la souris
             * -> réinitialisation de la couleur du/des noeud(s) et du curseur */
            virtual void hoverLeaveEvent(QGraphicsSceneHoverEvent* event);
            /* Lorsqu'on déplace le noeud (presser + déplacer la souris)
             * -> le gisser du glisser/déposer */
            virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
            /* Lorsqu'on clic sur le noeud
             * -> opération différentes suivant l'outil sélectionné */
            virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
            /* Lorsqu'on relâche le clic sur le noeud
             * -> réinitilisation du curseur pour l'outil glisser/déposer */
            virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
            /* Lorsqu'on rentre quelque chose dans la zone de glisser/déposer
             * -> changement de la couleur des noeuds */
            virtual void dragEnterEvent(QGraphicsSceneDragDropEvent *event);
            /* Lorsqu'on sort quelque chose de la zone de glisser/déposer
             * -> réinitialisation de la couleur des noeuds */
            virtual void dragLeaveEvent(QGraphicsSceneDragDropEvent *event);
            /* Lorsqu'on lache quelque chose dans la zone de glisser/déposer
             * -> le déposer du glisser/déposer */
            virtual void dropEvent(QGraphicsSceneDragDropEvent *event);

    // Signals Qt
    signals :
        // Lorsque un noeud / une feuille est ajouté(e) / supprimé(e) et qu'il faut donc redessiner tout l'arbre du programme
        void arbreModifie();


    // Surcharge d'opérateur
    public :
        // Deux arbres sont égaux s'ils possèdent les mêmes fils et la même étiquette
        bool operator==(ArbreHuff& secondArbreHuff);
        // On réutilise l'opérateur == pour définir le !=
        bool operator!=(ArbreHuff& secondArbreHuff);
        /* Un arbre est inférieur à l'autre si le nombre d'occurences contenu dans son étiquette
         * est inférieur à celui de l'autre arbre */
        bool operator<(ArbreHuff& secondArbreHuff);
};



#endif // ARBREHUFF_H
