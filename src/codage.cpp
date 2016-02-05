#include "include/codage.h"



// Getter
char Codage::getCarac() const
{
    return carac;
}
QString Codage::getCodeBin() const
{
    return codeBin;
}



// Setter
void Codage::setCarac(char nouvCarac)
{
    this->carac = nouvCarac;
}
void Codage::setCodeBin(QString nouvCodeBin)
{
    this->codeBin = nouvCodeBin;
}



// Constructeurs
Codage::Codage()
{
    this->carac = '\0';
    this->codeBin = QString();
}
Codage::Codage(const Codage& clone)
{
    this->carac = clone.carac;
    this->codeBin = clone.codeBin;
}
Codage::Codage(char carac, QString codeBin)
{
    this->carac = carac;
    this->codeBin = codeBin;
}

// Destructeur
Codage::~Codage()
{

}



// Surcharge d'opérateur

// Deux codages sont égaux lorsque le caractère qu'ils décrivent sont identiques
bool Codage::operator==(Codage& secondCodage)
{
    if(this->carac == secondCodage.carac)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Réutilisation de l'opérateur ==
bool Codage::operator!=(Codage& secondCodage)
{
    return (!(*this == secondCodage));
}
