#include "include/huffman.h"



// Getter
CListe<Occurences>* Huffman::getListeOcc() const
{
    return listeOcc;
}
ArbreHuff* Huffman::getArbreHuff() const
{
    return arbreHuff;
}
CListe<Codage>* Huffman::getCodageHuff() const
{
    return codageHuff;
}

// Setter
void Huffman::setListeOcc(CListe<Occurences>* nouvListeOcc)
{
    listeOcc = nouvListeOcc;
}
void Huffman::setArbreHuff(ArbreHuff *nouvArbreHuff)
{
    arbreHuff = nouvArbreHuff;
}
void Huffman::setCodageHuff(CListe<Codage> *nouvCodageHuff)
{
    codageHuff = nouvCodageHuff;
}



// Constructeurs
Huffman::Huffman()
{
    listeOcc = new CListe<Occurences>();
    arbreHuff = 0;
    codageHuff = new CListe<Codage>();
}
Huffman::Huffman(QString texte)
{
    listeOcc = new CListe<Occurences>();
    arbreHuff = 0;
    codageHuff = new CListe<Codage>();

    // On calcule le nombre d'occurence de chaque caractère dans le texte
    calculOcc(texte);
    // On génère l'arbre d'huffman qui découle de cette liste d'occurences
    genererArbreHuff();
    // On calcule le codage binaire de cette arbre d'huffman pour chacun des caractères
    calculCodage(arbreHuff);
}

// Destructeurs
Huffman::~Huffman()
{
    delete listeOcc;
    delete arbreHuff;
    delete codageHuff;
}



// Méthodes

// Calcule l'occurences de chaque caractères dans un texte donné
void Huffman::calculOcc(QString texte)
{
    char carac;
    Occurences* occCarac = 0;

    // On parcours le texte caractère par caractère
    for(int i = 0; i < texte.size(); i++)
    {
        // On convertie ce caractère en char
        carac = texte[i].unicode();
        // On cherche le noeud qui contient l'occurence de ce caractère
        occCarac = listeOcc->rechercheObjPtr(Occurences(carac));

        // Si il existe déjà un noeud pour ce caractère...
        if(occCarac != 0)
        {
            // ... On incrémente son nombre d'occurence
            (*occCarac)++;
        }
        // Si il n'existe pas encore de noeud dans la liste pour ce caractère...
        else
        {
            // ... on ajoute un nouveau noeud au début de la liste qui contient ce caractère
            listeOcc->ajoutDebut(Occurences(carac, 1));
        }
    }
}

// Génère l'arbre d'huffman à l'aide d'une liste d'occurences de caractère
void Huffman::genererArbreHuff()
{
    // On vérifie que la liste d'occurence de caractère n'est pas vide
    if(!listeOcc->estVide())
    {
        CNoeud<Occurences>* ptrParcourir = listeOcc->getTete();
        CListe<ArbreHuff*> listeArbreBin = CListe<ArbreHuff*>();
        ArbreHuff* min1 = 0;
        ArbreHuff* min2 = 0;
        int min1NbOcc = 0;
        int min2NbOcc = 0;

        // Tant que l'on est pas arrivé a la fin de la liste d'occurence...
        while(ptrParcourir != 0)
        {
            /* On ajoute au début de la liste d'arbre, un arbre qui contient uniquement
             * une racine étiqueté par l'occurence courante de la liste que l'on parcours */
            listeArbreBin.ajoutDebut(new ArbreHuff(ptrParcourir->getObjet()));

            // On avance dans la liste d'occurence
            ptrParcourir = ptrParcourir->getSuivant();
        }

        // Si il y'a uniquement qu'un seul caractère dans le texte utilisé pour crypter...
        if(listeArbreBin.getTaille() == 1)
        {
            // On récupère le seul arbre de la liste
            min1 = listeArbreBin.getTete()->getObjet();
            // On le supprime de la liste
            listeArbreBin.suppression(min1);

            // On récupère son nombre d'occurence
            min1NbOcc = min1->getEtiquette().getNbOcc();

            /* On ajoute à la liste d'arbre un nouvel arbre ayant comme fils gauche,
             *  le seul arbre qui était présent dans la liste */
            listeArbreBin.ajoutDebut(new ArbreHuff(Occurences('\0', min1NbOcc), min1, 0));
        }
        // S'il y'a plus d'un seul caractère...
        else
        {
            // Tant qu'il y'a plus d'un arbre dans la liste d'arbre...
            while(listeArbreBin.getTaille() > 1)
            {
                /* On récupère les deux plus petit arbre,
                 * et on les supprime de la liste d'arbre */
                min1 = listeArbreBin.recherchePtrMin();
                listeArbreBin.suppression(min1);
                min2 = listeArbreBin.recherchePtrMin();
                listeArbreBin.suppression(min2);

                // On récupère leur nombre d'occurences respectifs
                min1NbOcc = min1->getEtiquette().getNbOcc();
                min2NbOcc = min2->getEtiquette().getNbOcc();

                // On rajoute dans la liste d'arbre un nouvelle arbre ayant les deux arbres minimaux en fils
                listeArbreBin.ajoutDebut(new ArbreHuff(Occurences('\0', min1NbOcc + min2NbOcc), min1, min2));
            }
         }

        // L'arbre binaire de la variable de huffman, devient alors le seul arbre encore contenu dans la liste d'arbre
        arbreHuff = listeArbreBin.getTete()->getObjet();
    }
}

// Calcul le codage binaire de chaque caractère d'après un arbre d'huffman
void Huffman::calculCodage(ArbreHuff* arbreHuffCodage, QString codeBin)
{
    // Si le noeud ou l'on est n'est pas vide (que l'on est pas à la fin d'une branche)
    if(!(arbreHuffCodage->estVide()))
    {
        /* On supprime l'ancien codage si on est au début de la récursivité
         * et on en recrée un nouveau vide */
        if(arbreHuffCodage->estRacine())
        {
            delete codageHuff;
            codageHuff = new CListe<Codage>();
        }

        // Si on n'est au niveau d'une vrai feuille qui contient un caractère...
        if(arbreHuffCodage->estFeuille() && arbreHuffCodage->getEtiquette().getCarac() != '\0')
        {
            // ...on ajoute ce caractère à la liste de codage avec le code binaire que l'on a déterminé par récurrence
            codageHuff->ajoutDebut(Codage(arbreHuffCodage->getEtiquette().getCarac(), codeBin));
        }
        // Sinon...
        else
        {
            // Appels récursif sur les fils gauche et droite en rajoutant respectivement 0 et 1 à la fin du code binaire
            calculCodage(arbreHuffCodage->getFils0(), codeBin + '0');
            calculCodage(arbreHuffCodage->getFils1(), codeBin + '1');
        }
    }
}

// Crypte un texte
QString Huffman::crypter(QString texteNonCrypte)
{
    QString texteCrypte;
    Codage* codage;

    // On parcours tout le texte à crypter caractère par caractère
    for(int i = 0; i < texteNonCrypte.size(); i++)
    {
        /* On récupère le code binaire à ajouter a la fin de notre code crypté en recherchant notre
         * caractère dans la liste des code binaires */
        codage = codageHuff->rechercheObjPtr(Codage(texteNonCrypte[i].unicode()));

        // Si on ne trouve pas ce caractère dans la liste de code binaire
        if(codage == 0)
        {
            // On envoie une exception
            throw QString("Le caractère '" + texteNonCrypte[i] + "' n'est pas présent dans votre source de cryptage !");
        }
        // Sinon...
        else
        {
            // ...on ajoute ce code binaire à la fin du texte crypté
            texteCrypte.append(codage->getCodeBin());
        }
    }
    // On renvoit le texte crypté
    return texteCrypte;
}

// Décrypte un texte
QString Huffman::decrypter(QString texteCrypte)
{
    QString texteDecrypte;
    ArbreHuff* ptrArbre = arbreHuff;
    // On parcours tout le texte crypté caractère par caractère
    for(int i = 0; i < texteCrypte.size(); i++)
    {
        // Si le caractère courant est 0...
        if(texteCrypte[i] == '0')
        {
            // Si le fils 0, où l'on doit aller est vide...
            if(ptrArbre->getFils0()->estVide())
            {
                // ... on lance une exception
                throw QString("Le texte n'est pas compatible avec cette source :\n"
                              "le texte binaire nous dirige vers un fils qui n'existe pas dans l'arbre !");
            }
            // Sinon on avance dans ce fils 0
            else
            {
                ptrArbre = ptrArbre->getFils0();
            }
        }
        // Sinon s'il s'agit de 1...
        else if(texteCrypte[i] == '1')
        {
            // Si le fils 0, où l'on doit aller est vide...
            if(ptrArbre->getFils1()->estVide())
            {
                throw QString("Le texte n'est pas compatible avec cette source :\n"
                              "le texte binaire nous dirige vers un fils qui n'existe pas dans l'arbre !");
            }
            // Sinon on avance dans ce fils 0
            else
            {
                ptrArbre = ptrArbre->getFils1();
            }
        }
        // Si ce n'est ni 1 ni 0...
        else
        {
            // ... on lance une exception
            throw QString("Il n'y a pas que du binaire dans votre texte crypté !");
        }

        // Si on est au niveau d'une feuille qui contient bien un caractère...
        if(ptrArbre->estFeuille() && ptrArbre->getEtiquette().getCarac() != '\0')
        {
            // On rajoute ce caractère à la fin du texte décrypté
            texteDecrypte.append(ptrArbre->getEtiquette().getCarac());
            // Et on revient  à la racine de l'arbre
            ptrArbre = arbreHuff;
        }
        // Sinon, si on arrive à la fin du texte alors que l'on est donc pas tombé sur une feuille...
        else if(i == texteCrypte.size()-1)
        {
            // ... on lance une exception
            throw QString("Le texte n'est pas compatible avec cette source :\n"
                          "la fin du texte binaire ne correspond pas à une feuille de l'arbre");
        }
    }
    // On renvoit le texte décrypté
    return texteDecrypte;
}
