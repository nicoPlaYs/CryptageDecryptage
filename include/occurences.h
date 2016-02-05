#ifndef OCCURENCES_H
#define OCCURENCES_H



// Stocke un caractère et son nombre d'occurences
class Occurences
{
    // Attributs
    private :
        // Un caractère...
        char carac;
        // ... le nombre d'occurences de ce caractère
        int nbOcc;

    // Getter
    public :
        char getCarac() const;
        int getNbOcc() const;

    // Setter
    public :
        void setCarac(char nouvCarac);
        void setNbOcc(int nouvNbOcc);

    // Constructeur
    public :
        Occurences();
        Occurences(const Occurences& clone);
        Occurences(char carac, int nbOcc = 0);

    // Destructeur
    public :
        ~Occurences();

    // Surcharge d'opérateur
    public :
        // Recopie toutes les informations d'une 'Occurences' dans une autre
        Occurences& operator=(const Occurences& clone);
        // Incrémente l'attribut nbOcc de 1
        Occurences& operator++(int);
        // Deux 'Occurences' sont égaux lorsque le caracètre qu'elles décrivent sont identiques
        bool operator==(Occurences& secondeOcc);
        // Réutilisation de l'opérateur ==
        bool operator!=(Occurences& secondeOcc);
};



#endif // OCCURENCES_H
