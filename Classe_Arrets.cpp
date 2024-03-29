#include "Classe_Arrets.h"
#include <string>
#include <fstream>



 // ---------------- CHAINONTRAM -------------------------
//constructeur

ChainonArret::ChainonArret():d_prec{nullptr},d_suiv{nullptr},is_arret_double{false},estPlein{false}
{
    tab.resize(0);

}

//constructeur par recopie
ChainonArret::ChainonArret( ChainonArret * &a):
     d_prec{nullptr},d_suiv{nullptr},d_pos{a->d_pos},d_nom{a->d_nom},duree_min{a->duree_min},d_num{a->d_num},is_arret_double{a->is_arret_double},estPlein{a->estPlein}

{
    d_tab.resize(a->d_tab.size());
    for(int i = 0; i<d_tab.size();i++)
    {
        d_tab[i]=a->d_tab[i];
    }


}


// renvoie la position x de l'arrêt
double ChainonArret::X() const
{
    return d_pos.X();
}



// renvoie la position y de l'arrêt
double ChainonArret::Y() const
{

    return d_pos.Y();
}

// renvoie le numero  de l'arrêt
double ChainonArret::num() const
{
    return d_num;
}


// renvoie la position de l'arrêt
position ChainonArret::pos() const
{
    return d_pos;
}


// renvoie le chainon suivant
ChainonArret* ChainonArret::suiv() const
{
    return d_suiv;
}


//renvoie le chainon precedent
ChainonArret* ChainonArret::prec() const
{
    return d_prec;
}


 // ---------------- LCA -------------------------


//constructeur
LCA::LCA():d_tete{nullptr}, d_nLignes{0}{}


//destructeur
LCA::~LCA()
{
    while(d_tete)
    {
        ChainonArret *tmp=d_tete->d_suiv;
        delete d_tete;
        d_tete=tmp;
    }
}


//lecture des arrets depuis un fichier  et creation de la liste chainée de tram
void LCA::lire(const std::string & fichier)
{

    std::ifstream f(fichier);
    std::string tmp;
    int nb;//nb d'arrets
    int n;//numero de l'arret
    std::string nom; //nom de l'arret
    double x,y;//la position de l'arret
    double dmin;//duree min d'arret dans cette station
    int nbligne;//nombre de lignes sur les quelles l'arret apparait
    int numLigne;//num de ligne correspondant
    int nLignestot;//nombre de lignes au total
    if(f)
    {
        f>>tmp>>nb;

        for(int i=0;i<nb;i++)
        {
            f>>n>>nom>>x>>y>>dmin>>nbligne;
            ChainonArret * a= new ChainonArret();

            a->d_num=n;
            a->d_nom=nom;
            a->d_pos.changeX(x);
            a->d_pos.changeY(y);
            a->duree_min=dmin;
            a->d_tab.resize(nbligne);
            cout<<"l'arret nommee "<<a->d_nom<<" apparait sur la (ou les) ligne(s) : ";//test d'affichage

            for ( int j = 0 ; j< nbligne ; j++) //on remplit le tableau
            {
                f>>numLigne;
                a->d_tab[j]=numLigne;
                cout<<a->d_tab[j]<<" ";//test d'affichage
            }
            cout<<endl;//test d'affichage
            ajouterArret(a);
        }
        f>>tmp>>nLignestot;
        d_nLignes=nLignestot;
    }
    cout << endl<<" -------------------------------------- " <<endl<<endl;//test d'affichage
}



//fonction qui ajoute un arret à la liste chainée
void LCA::ajouterArret(ChainonArret* &a)
{

    ChainonArret *nc= new ChainonArret(a);
    //si la liste chainée est vide
    if(!d_tete)
    {
        d_tete=nc;
        return;
    }
    else
    {
         ChainonArret *c=d_tete, *pc=nullptr;
        while( c != nullptr)
        {
            pc=c;
            c=c->d_suiv;
        }
        pc->d_suiv = nc;
        nc->d_prec = pc;
        nc -> d_suiv = nullptr;

    }


}







 // ---------------- TESTS -------------------------


//test qui affiche la taille du tableau
void LCA::affichetest()
{
    cout<<d_tete->d_tab.size();
}

//test qui affiche si l'arret est double
void LCA::test()
{
    ChainonArret *a=d_tete;
    while(a!=nullptr)
    {



    cout << "l'arret "<< a->d_num << "est-il double " << a->is_arret_double << endl;

    if(a->is_arret_double)
    {
        for(int i = 0; i<a->tab.size();i++)
        {
            cout << " l'Arret " << a << " a un Pointeur vers l'arret  " << a->tab[i] << endl;
        }
    }
        a=a->d_suiv;

    }
}
