#include "include/cliste.h"



// Getter
template<class T>
int CListe<T>::getTaille() const
{
    return taille;
}
template<class T>
CNoeud<T>* CListe<T>::getTete() const
{
    return tete;
}



// Setter
template<class T>
void CListe<T>::setTaille(int nouvTaille)
{
    taille = nouvTaille;
}
template<class T>
void CListe<T>::setTete(CNoeud<T>* nouvTete)
{
    tete = nouvTete;
}



// Constructeurs
template<class T>
CListe<T>::CListe()
{
    taille = 0;
    tete = 0;
}
template<class T>
CListe<T>::CListe(const CListe<T>& clone)
{
    taille = clone.taille;
    tete = clone.tete;
}



// Destructeur
template<class T>
CListe<T>::~CListe()
{
    // Tant que la liste n'est pas vide, on supprime le premier noeud de la liste
    CNoeud<T>* ptrDelete = 0;
    while(!estVide())
    {
        ptrDelete = tete;
        tete = tete->getSuivant();
        delete ptrDelete;
        taille--;
    }
}



// Méthodes

// Retourne vrai si la liste est vide
template<class T>
bool CListe<T>::estVide()
{
    // Si la tête est vide, c'est que la liste est vide
    if(tete == 0)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Ajout un élément en début de liste
template<class T>
void CListe<T>::ajoutDebut(T objet)
{
    // On crée un nouveau noeud
    CNoeud<T>* nouvNoeud = new CNoeud<T>(objet);

    // On définit le suivant de ce nouveau noeud
    nouvNoeud->setSuivant(tete);
    // Il devient la nouvelle tete de la liste
    tete = nouvNoeud;

    // On incrémente la taille de la liste
    taille++;
}

// Ajout un élément en fin de liste
template<class T>
void CListe<T>::ajoutFin(T objet)
{
    // On crée un nouveau noeud
    CNoeud<T>* nouvNoeud = new CNoeud<T>(objet);

    // Si la liste est vide...
    if(estVide())
    {
        // ... la tete devient ce nouveau noeud
        tete = nouvNoeud;
    }
    // Si la liste n'est pas vide
    else
    {
        /* On parcours toute la liste jusqu'a trouvé le dernier noeud
         * (celui qui n'a pas de noeud suivant) */
        CNoeud<T>* ptrParcourir = tete;
        while(ptrParcourir->getSuivant() != 0)
        {
            ptrParcourir = ptrParcourir->getSuivant();
        }

        // Le noeud suivant de ce dernier noeud, devient alors le nouveau noeud
        ptrParcourir->setSuivant(nouvNoeud);
    }

    // On incrémente la taille de la liste
    taille++;
}

// Supresion de l'objet en argument dans la liste
template<class T>
void CListe<T>::suppression(T objet)
{
    // On vérifie tout d'abord si la liste est vide
    if(!estVide())
    {
        CNoeud<T>* ptrParcourir = tete;
        CNoeud<T>* ptrTemp = 0;

        // Si l'objet que l'on cherche est à la tete de notre liste
        if(tete->getObjet() == objet)
        {
            // On garde de côté le pointeur sur la tete que l'on souhaite supprimer
            ptrTemp = tete;
            // La nouvelle tete est alors le noeud qui suit le noeud que l'on veut supprimer
            tete = tete->getSuivant();
            // On supprime l'ancienne tete
            delete ptrTemp;

            // La taille de la liste est décrémenté
            taille--;
        }
        // S'il n'est pas a la tête de notre liste
        else
        {
            /* Tant que l'on a pas atteint la fin de la liste
             * et que l'on est pas arriver sur l'objet que l'on souhaite supprimer... */
            while(ptrParcourir->getSuivant() != 0 && ptrParcourir->getSuivant()->getObjet() != objet)
            {
                // ...on avance dans la liste
                ptrParcourir = ptrParcourir->getSuivant();
            }

            // Si on sait arrêté de parcourir la liste car on a rencontré notre objet...
            if(ptrParcourir != 0)
            {
                // On garde de côté le pointeur sur le noeud que l'on souhaite supprimer
                ptrTemp = ptrParcourir->getSuivant();
                /* Le noeud qui suit celui où on s'est arrêté
                 * devient le noeud qui suit celui que l'on souhaite supprimer */
                ptrParcourir->setSuivant(ptrParcourir->getSuivant()->getSuivant());

                // On supprime le noeud contenu l'objet que l'on souhaitais supprimer
                delete ptrTemp;

                // La taille de la liste est décrémenté
                taille--;
            }
        }
    }
}

// Recherche un objet dans la liste et retourne le noeud qui le contient
template<class T>
CNoeud<T>* CListe<T>::rechercheNoeud(T objet)
{
    /* On parcours la liste tant que l'on a pas atteint sa fin
     * et que l'on est pas tombé sur l'objet que l'on recherche */
    CNoeud<T>* ptrParcourir = tete;
    while(ptrParcourir != 0 && ptrParcourir->getObjet() != objet)
    {
        ptrParcourir = ptrParcourir->getSuivant();
    }

    // Si on s'est arrêté car on est arrivé en fin de liste
    if(ptrParcourir == 0)
    {
        return 0;
    }
    // Sinon...
    else
    {
        // ...on retourne le pointeur vers le noeud content l'objet que l'on cherche
        return ptrParcourir;
    }
}

// Recherche un objet dans la liste et retourne sa valeur
template<class T>
T CListe<T>::rechercheObj(T objet)
{
    // On cherche le noeud qui contient notre objet
    CNoeud<T>* noeud = rechercheNoeud(objet);

    // Si on a bien trouvé notre objet dans la liste, on retourne sa valeur
    if(noeud != 0)
    {
        return noeud->getObjet();
    }
    else
    {
        return 0;
    }
}


// Rercherche un objet dans la liste et retourne son adresse
template<class T>
T* CListe<T>::rechercheObjPtr(T objet)
{
    // On cherche le noeud qui contient notre objet
    CNoeud<T>* noeud = rechercheNoeud(objet);
    // Si on a bien trouvé notre objet dans la liste, on retourne son adresse
    if(noeud != 0)
    {
        return noeud->getObjetPt();
    }
    else
    {
        return 0;
    }
}

// Recherche l'objet de valeur minimale dans la liste où le type T est un pointeur
template<class T>
T CListe<T>::recherchePtrMin()
{
    T objMin = 0;
    // On vérifie que la liste possède au moins un noeud
    if(taille > 0)
    {
        // Le premier objet de la liste devient l'objet le plus petit
        objMin = tete->getObjet();

        // Si il y'a plus d'1 objet, il va falloir chercher plus loin...
        if(taille > 1)
        {
            // Tant qu'on est pas a la fin de la liste
            CNoeud<T>* ptrParcourir = tete->getSuivant();
            while(ptrParcourir != 0)
            {
                // Si l'objet du noeud courant est plus petit que l'objet minimum temporaire...
                if(*(ptrParcourir->getObjet()) < *objMin)
                {
                    // ... l'objet minimum temporaire devient l'objet du noeud courant
                    objMin = ptrParcourir->getObjet();
                }
                // Et on avance !
                ptrParcourir = ptrParcourir->getSuivant();
            }
        }
    }
    // On retourne l'objet de valeur minimale
    return objMin;
}
