#include "include/occurences.h"



// Getters
char Occurences::getCarac() const
{
    return carac;
}
int Occurences::getNbOcc() const
{
    return nbOcc;
}

// Setters
void Occurences::setCarac(char nouvCarac)
{
    carac = nouvCarac;
}
void Occurences::setNbOcc(int nouvNbOcc)
{
    nbOcc = nouvNbOcc;
}



// Constructeurs
Occurences::Occurences()
{
    this->carac = '\0';
    this->nbOcc = 0;
}
Occurences::Occurences(const Occurences &clone)
{
    this->carac = clone.carac;
    this->nbOcc = clone.nbOcc;
}

Occurences::Occurences(char carac, int nbOcc)
{
    this->carac = carac;
    this->nbOcc = nbOcc;
}

// Destructeur
Occurences::~Occurences()
{

}


// Surcharge d'opérateur

// Recopie toutes les informations d'une 'Occurences' dans une autre
Occurences& Occurences::operator=(const Occurences& clone)
{
    this->carac = clone.carac;
    this->nbOcc = clone.nbOcc;

    return *this;
}
// Incrémente l'attribut nbOcc de 1
Occurences& Occurences::operator++(int)
{
    nbOcc++;
    return *this;
}
// Deux 'Occurences' sont égales lorsque le caracètre qu'elles décrivent sont identiques
bool Occurences::operator==(Occurences& secondeOcc)
{
    if(this->carac == secondeOcc.carac)
    {
        return true;
    }
    else
    {
        return false;
    }
}
// Réutilisation de l'opérateur ==
bool Occurences::operator!=(Occurences& secondeOcc)
{
    return !(*this == secondeOcc);
}
