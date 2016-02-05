#ifndef CLISTE_H
#define CLISTE_H



template<class T>
class CListe;
#include "cnoeud.h" // Noeud de liste chaînée
#include "src/cnoeud.cpp" // Noeud de liste chaînée



// Liste chaînée
template<class T>
class CListe
{
    // Attributs
    private :
        // Nombre de noeuds qui composent la liste
        int taille;
        // Premier noeud de la liste
        CNoeud<T>* tete;

    // Getters
    public :
        int getTaille() const;
        CNoeud<T>* getTete() const;

    // Setters
    public :
        void setTaille(int nouvTaille);
        void setTete(CNoeud<T>* nouvTete);

    // Constructeurs
    public :
        CListe();
        CListe(const CListe<T>& clone);

    // Destructeur
    public :
        ~CListe();

    // Méthodes
    public :
        // Méthodes de base
            // Retourne vrai si la liste est vide
            bool estVide();
            // Ajoute un élément en début de liste
            void ajoutDebut(T objet);
            // Ajoute un élément en fin de liste
            void ajoutFin(T objet);
            // Supprime l'objet en argument dans la liste
            void suppression(T objet);

        // Recherches
            // Recherche un objet dans la liste et retourne l'adresse du noeud qui le contient
            CNoeud<T>* rechercheNoeud(T objet);
            // Recherche un objet dans la liste et retourne sa valeur
            T rechercheObj(T objet);
            // Rercherche un objet dans la liste et retourne son adresse
            T* rechercheObjPtr(T objet);
            // Recherche l'objet de valeur minimale dans la liste où le type T est un pointeur
            T recherchePtrMin();
};



#endif // CLISTE_H
