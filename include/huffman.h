#ifndef HUFFMAN_H
#define HUFFMAN_H



// Structure Qt
#include <QString> // Chaîne de caractère


class Huffman;
#include "cliste.h" // Liste chaînée
#include "src/cliste.cpp" // Liste chaînée
#include "occurences.h" // Stocke un caractère et son nombre d'occurences
#include "arbrehuff.h" // Arbre binaire d'Huffman
#include "codage.h" // Associe à un caractère, une suite de 0 et de 1



// Algorithme d'Huffman
class Huffman
{
    // Attributs
    private :
        // Liste d'occurences de caractères
        CListe<Occurences>* listeOcc;
        // Arbre binaire généré par la méthode de codage d'Huffman
        ArbreHuff* arbreHuff;
        // Liste de correspondance caractère<->codage binaire
        CListe<Codage>* codageHuff;

    // Getter
    public :
        CListe<Occurences>* getListeOcc() const;
        ArbreHuff* getArbreHuff() const;
        CListe<Codage>* getCodageHuff() const;

    // Setter
    public :
        void setListeOcc(CListe<Occurences>* nouvListeOcc);
        void setArbreHuff(ArbreHuff* nouvArbreHuff);
        void setCodageHuff(CListe<Codage>* nouvCodageHuff);

    // Constructeur
    public :
        Huffman();
        Huffman(QString texte);

    // Destructeur
    public :
        ~Huffman();

    // Méthodes
    public :
        // Initialisation d'outils du codage de huffman
            // Calcule l'occurence de chaque caractère dans un texte donné
            void calculOcc(QString texte);
            // Génère l'arbre d'Huffman à l'aide d'une liste d'occurences de caractères
            void genererArbreHuff();
            // Calcul le codage binaire de chaque caractère d'après un arbre d'huffman
            void calculCodage(ArbreHuff* arbreHuffCodage, QString codeBin = '\0');

        // Utilisation des outils du codage de huffman
            // Crypte un texte
            QString crypter(QString texteNonCrypte);
            // Décrypte un texte
            QString decrypter(QString texteCrypte);
};



#endif // HUFFMAN_H
