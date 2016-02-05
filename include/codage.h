#ifndef CODAGE_H
#define CODAGE_H



// Structure Qt
#include <QString> // Chaîne de caractère


class Codage;
#include "cliste.h" // Liste chaînée



// Associe à un caractère, une suite de 0 et de 1
class Codage
{
    // Attributs
    private :
        // Un caractère...
        char carac;
        // ... et le codage binaire qui lui est associé
        QString codeBin;

    // Getter
    public :
        char getCarac() const;
        QString getCodeBin() const;

    // Setter
    public :
        void setCarac(char nouvCarac);
        void setCodeBin(QString nouvCodeBin);

    // Constructeurs
    public :
        Codage();
        Codage(const Codage& clone);
        Codage(char carac, QString codeBin = QString());

    // Destructeur
    public :
        ~Codage();

    // Surcharge d'opérateur
    public :
        // Deux codages sont égaux lorsque le caractère qu'ils décrivent sont identiques
        bool operator==(Codage& secondCodage);
        // Réutilisation de l'opérateur ==
        bool operator!=(Codage& secondCodage);
};



#endif // CODAGE_H
