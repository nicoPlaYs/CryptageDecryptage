#include "include/cnoeud.h"



// Getter
template<class T>
T CNoeud<T>::getObjet() const
{
    return objet;
}
template<class T>
T* CNoeud<T>::getObjetPt()
{
    return &objet;
}
template<class T>
CNoeud<T>* CNoeud<T>::getSuivant() const
{
    return suivant;
}

// Setter
template<class T>
void CNoeud<T>::setObjet(T nouvObjet)
{
    objet = nouvObjet;
}
template<class T>
void CNoeud<T>::setSuivant(CNoeud<T>* nouvSuivant)
{
    suivant = nouvSuivant;
}



// Constructeur
template<class T>
CNoeud<T>::CNoeud(T objet, CNoeud<T>* suivant)
{
    this->objet = objet;
    this->suivant = suivant;
}

// Destructeur
template<class T>
CNoeud<T>::~CNoeud()
{

}
