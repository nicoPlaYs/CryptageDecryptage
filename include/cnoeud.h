#ifndef CNOEUD_H
#define CNOEUD_H



// Noeud de liste chaînée
template<class T>
class CNoeud
{
    // Attributs
    private :
        // Objet stocké dans le noeud
        T objet;
        // Noeud suivant dans la liste
        CNoeud<T>* suivant;

    // Getter
    public :
        T getObjet() const;
        T* getObjetPt();
        CNoeud<T>* getSuivant() const;

    // Setter
    public :
        void setObjet(T nouvObjet);
        void setSuivant(CNoeud<T>* nouvSuivant);

    // Constructeurs
    public :
        CNoeud(T objet, CNoeud<T>* suivant = 0);

    // Destructeurs
    public :
        ~CNoeud();
};



#endif // CNOEUD_H
