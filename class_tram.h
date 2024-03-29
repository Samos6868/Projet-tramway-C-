#ifndef CLASS_TRAM_H
#define CLASS_TRAM_H
#include <iostream>
#include <fstream>
#include "position.h"
#include "Classe_Arrets.h"



class ChainonTram
{
    friend class LCT;
    friend class LCL;
    friend class LCA;
public:
    bool estsurArret() const;//renvoie si le tram est sur la m�me position de l'arr�t
    void avancer();//procedure qui fait avancer le tram
    void refresh_arret_suiv();//actualise l'arr�t vers lequel le tram doit avancer
    double distante_restante() const ;//renvoie la distance entre le tram et l'arr�t  vers lequel il doit aller
    bool distanceMinimum() const;//renvoie vrai si la distance entre le tram et son tram suivant est inferieur � la distance minimale qu'on doit respecter

private:
    ChainonTram();//constructeur
    ChainonTram(ChainonTram * &t);//constructeur par recopie
    ChainonTram *d_suiv;//suivant
    position d_pos;// position
    int ntram;// numero du tram
    int d_Ligne;//ligne � la quelle il appartient
    double vmax; // vitesse maximum
    double distanceMin; // la distacne minimale avec le tram qui est devant lui
    bool sens; // sens de d�placement
    int cpt; // compteur qui gere le temps d'arret du tram sur un arret
    double a; // coefficient de sa droite
    double b;// coefficient de sa froite
    ChainonArret *arret_suiv;//variable qui stock l'arret vers le quel le tram va

};

class LCT
{
    friend class LCL;
    public:
        LCT();//constructeur
        ~LCT();//destructeur

        //Methodes
        void lire(const std::string & fichier, const int &a);//methode qui lit les trams d'une ligne 'a' depuis un fichier et creation de la liste chain�e
        void ajouter(ChainonTram * &t);//Methode qui ajoute un chainon � la liste chain�e

        double distance(ChainonTram  *  & t,int x);//calcule la distance entre deux trams



        //Test
        void affiche_liste();//Methode test qui affiche la liste de tram
        void test_arretsuiv();//test le sens du tram
        double numerontram(int x);//retourne le num�ro de tram

    private:
        ChainonTram *d_tete;
};

#endif // CLASS_TRAM_H
