#include "class_tram.h"
#include <fstream>
#include <iostream>




 // ---------------- CHAINONARRET -------------------------

//constructeur
ChainonTram::ChainonTram():
     d_suiv{nullptr},vmax{1},distanceMin{100},cpt{0},a{0},b{0},arret_suiv{nullptr}
{
    //ctor
}


//constructeur par recopie
ChainonTram::ChainonTram( ChainonTram * &t):
     d_suiv{nullptr},d_pos{t->d_pos},ntram{t->ntram},vmax{t->vmax},distanceMin{t->distanceMin},sens{t->sens},cpt{t->cpt},a{t->a},b{t->b},arret_suiv(t->arret_suiv)
{
    //ctor
}


//Renvoie si le tram est sur la même position de l'arrêt
bool ChainonTram::estsurArret() const
{

    if(arret_suiv->X() < d_pos.X())
{

     return (  (d_pos.X() <= arret_suiv->X()+vmax)  );
}
else
{

     return (  (d_pos.X() >= arret_suiv->X()-vmax)  );
}



}

//procedure qui fait avancer le tram
void ChainonTram::avancer()
{


    int pente=0;




arret_suiv->pos().X();

   // double a = ( arret_suiv->pos().Y()  -  d_pos.Y()    ) / ( arret_suiv->pos().X() - d_pos.X()     );

   // double b = d_pos.Y() - a * d_pos.X();

   // cout << ntram << " -> " << arret_suiv->num() << " y = " << a << " x + " << b << endl;

if(arret_suiv->pos().X() < d_pos.X())
{
    pente=-1;
}
else
{
    pente=1;
}

    if(d_pos.X()== arret_suiv->pos().X())
    {
       d_pos.changeY( d_pos.Y()+vmax    );
    }

    else
    {
        d_pos.changeX( d_pos.X() + vmax*pente      );
        d_pos.changeY( a*d_pos.X() + b     );



    }


}


// actualise l'arret vers le quel le tram doit avancer
void ChainonTram::refresh_arret_suiv()
{
//cout << " mon arret suivant actuel est " << arret_suiv->num() << endl;

        if(sens==0 && arret_suiv->suiv() !=nullptr)
        {
            // cout << " mon sens = " << sens <<" cas 1 " << endl;

            arret_suiv=arret_suiv->suiv();

        }
        else if(sens==1 && arret_suiv->prec()!=nullptr )
        {

         //   cout << " mon sens = " << sens << " cas 2  " << endl;
            arret_suiv=arret_suiv->prec();

        }
        else if(arret_suiv->suiv()==nullptr )
        {
          //  cout << "mon sens = " << sens << " cas 3 " << endl;
            arret_suiv=arret_suiv->prec();
            sens=1;

        }
        else if(arret_suiv->prec()==nullptr)
        {
        //    cout << " mon sens = "  << sens << "cas 4 " << endl;
            arret_suiv=arret_suiv->suiv();
            sens=0;

        }




  a = ( arret_suiv->pos().Y()  -  d_pos.Y()    ) / ( arret_suiv->pos().X() - d_pos.X()     );

  b = d_pos.Y() - a * d_pos.X();



}

//renvoie la distance entre le tram et l'arret suivant
double ChainonTram::distante_restante() const
{
    return d_pos.calculeDistance(arret_suiv->pos());
}


//renvoie vrai si la distance minimale avec le tram suivant (dans le meme sens) n'est pas respecté
bool ChainonTram::distanceMinimum() const
{
if(d_suiv == nullptr)
{
    return false;
}

    return (d_suiv->sens == sens) &&  (d_pos.calculeDistance(d_suiv->d_pos) <= distanceMin);


}

 // ---------------- LCT -------------------------

 //constructeur
LCT::LCT ():
    d_tete{nullptr}
{

}

//destructeur
LCT::~LCT()
{
    while(d_tete)
    {
        ChainonTram *tmp=d_tete->d_suiv;
        delete d_tete;
        d_tete=tmp;
    }
}



// methode qui lit et ajoute des trams à une liste chainée depuis un fichier selon la ligne 'a'
void LCT::lire(const std::string & fichier, const int& a)
{

    std::ifstream f(fichier);
    std::string tmp;
    int nligne;
    int nb;//nb de trams
    int n;//numero du tram
    double x,y;//la position
    bool s;//le sens du tram
    double vitess; // vitesse
    if(f)
    {

        while(tmp!="Trams"){f>>tmp;}//on parcours le fichier jusqu'à la partie des trams
        f>>nb;
        int i=0;
        while(i<nb)
        {
            f>>n>>x>>y>>s>> vitess >> nligne;

            if(nligne==a)
             {
                cout<<"Pour la ligne "<<nligne<<" on a le(s) tram(s) : ";
                ChainonTram * t= new ChainonTram();
                t->d_Ligne=nligne;
                t->ntram=n;
                t->d_pos.changeX(x);
                t->d_pos.changeY(y);
                t->sens=s;
                t->vmax=vitess;
                ajouter(t);
                cout<<t->ntram<<" qui  est a la position "<<t->d_pos.X()<<" "<< t->d_pos.Y() << " sa vitesse est " << t->vmax << endl;//testaffichage
             }
             i++;


        }

    }
    cout << " ---------------" << endl;
}

//ajout des trams à liste chainée
void LCT::ajouter( ChainonTram  *  & t)
{
   ChainonTram * nc= new ChainonTram(t);
    //si la lsite chainée est vide
    if(!d_tete)
    {
        d_tete=nc;
        return;
    }
    else
    {
         ChainonTram *c=d_tete, *pc=nullptr;
        while( c != nullptr)
        {
            pc=c;
            c=c->d_suiv;
        }
        pc->d_suiv = nc;
        nc -> d_suiv = nullptr;

    }
}




//renvoie la distance entre un tram passé en parametre et un tram numero 'x'
double LCT::distance(ChainonTram  *  &t,int x)
{
    int i=0;
    ChainonTram * tmp=d_tete;
    while(tmp && i<x)
    {
        i++;
        tmp=tmp->d_suiv;
    }
    position p(t->d_pos.X(),t->d_pos.Y());
    return tmp->d_pos.calculeDistance(p);
}














 // ---------------- TESTS-------------------------


//test qui renvoie le sens du tram
void LCT::test_arretsuiv()
{
  ChainonTram *t=d_tete;
  while(t!=nullptr)
  {
       // cout << " le tram numero " << t->ntram << " a pour arret suivant" << t->arret_suiv->num()<< endl;
      // cout << " le tram numero " << t->ntram << " a pour distance restante " << t->distante_restante() << " avec l'arret " << t->arret_suiv->num() << endl;
      // cout << " le tram numero " << t->ntram << " est sur un arret ? 0 non, 1 oui : " << t->estsurArret() << endl;
      cout << " le tram numero " << t->ntram << " a pour sens " << t->sens << endl;
      if(t->d_suiv!=nullptr)
      {
  // cout << " le tram numero " << t->ntram << " est dans la distance minimum " << t->distanceMinimum() << endl;
    //cout << t->distanceMinimum() << endl;
      }
    //  t->avancer();

      t=t->d_suiv;

  }
}


//Methode qui affiche les trams de la liste et leur position
void LCT::affiche_liste()
{
    ChainonTram *tr=d_tete;

    while(tr)
    {
        cout << " tram numero "<< tr->ntram << " a la position " << tr->d_pos.X() << " : " << tr->d_pos.Y() << " . " << endl;
      //  cout << " son arret suivant est l'arret numero " << tr->arret_suiv->num() << endl;
        tr=tr->d_suiv;
    }
}


// renvoie la position X du tram numero 'x' passé en parametre
double LCT :: numerontram(int x)
{
    int i=1;
    ChainonTram * tmp=d_tete;
    while(tmp && i<x)
    {
        i++;
        tmp=tmp->d_suiv;
    }
    return tmp->d_pos.X();
}
