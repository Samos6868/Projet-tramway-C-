#ifndef CLASSE_ARRETS_H
#define CLASSE_ARRETS_H
#include <string>
#include <vector>
#include "position.h"


class ChainonArret
{
    friend class LCL;
    friend class LCA;
public:

    double X() const; // renvoie la position x de l'arr�t
    double Y() const;// renvoie la position y de l'arr�t
    double num() const;// renvoie le numero  de l'arr�t
    position pos() const;// renvoie la position de l'arr�t
    ChainonArret* suiv() const;// renvoie le chainon suivant
    ChainonArret* prec() const;//renvoie le chainon precedent

private:
    ChainonArret();//constructeur
    ChainonArret(ChainonArret* &a);//constructeur par recopie
    ChainonArret *d_prec,*d_suiv;// pointeurs cers le precedent et le suivant

    position d_pos; // Sa position
    std::string d_nom;// nom de l'arret
    double duree_min; // La dur�e minimale pendant laquelle le tramway doit rester � l�arr�t
    int d_num;//numero de l'arret
    bool is_arret_double;//Renvoie Vrai si l'arret est present sur plusieures lignes
    bool estPlein;//renvoie vrai si l'arret est plein

    std::vector<int>d_tab;//tableau qui va stocker le numero des lignes dans lesquelles cet arret apparait
    std::vector<ChainonArret*>tab; // tableau de pointeur (g�re les arrets en commmuns sur plusieurs ligne;
};

class LCA
{
    public:
        friend class LCL;
        LCA();//constructeur
        ~LCA();//destructeur
        void lire(const std::string & fichier);//lecture des arrets depuis un fichier  et creation de la liste chain�e de tous les arrets
        void ajouterArret(ChainonArret * &a);//fonction qui ajoute un arret � la liste chain�e



        //Tests
        void affichetest();//test qui affiche la taille du tableau d_tab
        void test();//test qui affiche si l'arret est double et s'il l'est sur quel arr�t il pointe

    private:
        ChainonArret *d_tete;
        int d_nLignes;//nombre de lignes dans le reseau
};




#endif // CLASSE_ARRETS_H
