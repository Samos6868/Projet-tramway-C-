#ifndef LCL_H_INCLUDED
#define LCL_H_INCLUDED
#include"Classe_Arrets.h"
#include"class_tram.h"

class LCL
{
public:
    friend class LCA;
    friend class LCT;

    LCL();// Constructeur
    ~LCL();// Destructeur

    //Methodes

    void ajouterArretListe(ChainonArret * &a);//ajout d'un arret dans la liste chainé
    void ajouterTramListe(ChainonTram* &a);//ajout d'un tram dans la liste chainé
    void creation(const LCA &a,const LCT &t, int x);//creation de la liste chainée de ligne en copiant les arrets et les trams selon le numero de ligne

    void search_arret_double(LCL &l);//recherche les arrets sur plusieur lignes
    void rendre_arret_plein(ChainonArret *a);//modifie le bool 'estPlein' en vrai
    void rendre_arret_vide(ChainonArret *a);//modifie le bool 'estPlein' en faux

    void init_affichage(LCT &a); // initialisation de l'affichage pour les trams et arrets
    void init_refresh_arret_suiv(LCT &a);// rafraichissement
    void refresh_arret_suiv(LCT &a);//

    void circulation(LCT &a, LCA &lca);//


    // tests
    void testt();//affiche quels arrets pointent sur quels autres arrets
    void affiche() const; // test affiche ligne sur CONSOLE
    std::string getArret(const int& nb) const;//affiche le nom de l'arret numéro nb

private:
    friend class ChainonArret;
    ChainonArret *d_t;// tete arret
    ChainonTram *d_tete; // tete tram

    int d_numLigne;//numero de la ligne
    vector<int>couleur;//

};

#endif // LCL_H_INCLUDED
