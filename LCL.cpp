#include"LCL.h"
#include <fstream>
#include <cmath>
#include "graphics.h"



 // ---------------- LCL-------------------------

 //constructeur
LCL::LCL():d_t{nullptr}, d_tete{nullptr} {

couleur.resize(7);
    couleur[0] = 0;
    couleur[1] = 1;
    couleur[2] = 5;
    couleur[3] = 10;
    couleur[4] = 8;
    couleur[5] = 7;
    couleur[6] = 6;


}

//destructeur
LCL::~LCL()
{
    while(d_tete)
    {
        ChainonTram *tmp=d_tete->d_suiv;
        delete d_tete;
        d_tete=tmp;
    }
    while(d_t)
    {
        ChainonArret *tmp=d_t->d_suiv;
        delete d_t;
        d_t=tmp;
    }
}



//fonction qui ajoute un nouveau chainon. l'ordre des chainons  est croissant defini par la cordonné x(pas sur)
void LCL::ajouterArretListe(ChainonArret* &a)
{

    ChainonArret *nc= new ChainonArret(a);
    //si la liste chainée est vide
    if(!d_t)
    {
        d_t=nc;
        return;
    }
    else
    {

         ChainonArret *c=d_t, *pc=nullptr;
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


// fonction ajoute nouveau chainon tram
void LCL::ajouterTramListe(ChainonTram* &a)
{

   ChainonTram * nc= new ChainonTram(a);
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






//fonction qui va creer la liste chainée de ligne en copiant les arrets et les trams selon le 'x' en parametre qui represente la ligne
void LCL::creation(const LCA &a, const LCT &t, int x)
{
    //parcours liste arret

    ChainonArret *arret = a.d_tete;
    d_numLigne=x;


    while(arret)         //tant que on est dans la liste arret
    {
        int i = 0;
        int taille=arret->d_tab.size();
        //cout<<s;
        //parcours le tableau dans chaque chainon arret

        while(i< taille)  //tant que depasse pas le tableau ou trouve pas la ligne chercher
        {
            if(arret->d_tab[i]==x)  //si trouve la ligne cherche
            {

                ChainonArret *nc =arret;//cree chainon pareil que le chainon sur lequel on est

                if(taille>1) // tableau de pointeur pour les arrets double,triples..
                {
                   // cout << " j'ai rendu un arret double " <<  endl;
                    nc->is_arret_double=true;

                }
                ajouterArretListe(nc);


            }

            i++;

        }

        arret=arret->d_suiv;    //chainon suivant dans la liste arret


    }

    ChainonTram *tram= t.d_tete;

    while(tram)
    {

        ajouterTramListe(tram);
        tram=tram->d_suiv;


    }
cout << endl;
}





//recherche des arrets qui apparaissent plusieures fois sur differentes lignes, donc ajout dans le tableau des pointeurs
void LCL::search_arret_double(LCL &l)
{
ChainonArret *arret = d_t;

while(arret != nullptr)
    {
        ChainonArret *tmp = l.d_t;
            while(tmp != nullptr)
            {
                if(arret->d_num == tmp->d_num)
                {
                  //  cout << " l'arret en commun est l'arret numero " << arret->d_num << endl;
                    arret->tab.push_back(tmp);
                    tmp->tab.push_back(arret);
                }
             tmp = tmp->d_suiv;
            }
        arret=arret->d_suiv;

    }

}

//methode qui modifie le bool 'estPlein' dans le chainonArret, pour ce cas on indique que l'arret est plein
void LCL::rendre_arret_plein(ChainonArret *arret)
{
 //cout << " JE REND PLEIN MON ARRET " << endl;
    ChainonArret *tmp= d_t;

    while(tmp!=nullptr && tmp->d_num != arret-> d_num)
    {



        tmp=tmp->d_suiv;
    }

            tmp->estPlein=true;
            for(int i=0;i<tmp->tab.size();i++)
                        {
                            tmp->tab[i]->estPlein=true;
                        }


}


//methode qui modifie le bool 'estPlein' dans le chainonArret, pour ce cas on indique que l'arret est vide
void LCL::rendre_arret_vide(ChainonArret *arret)
{
 //cout << " JE REND VIDE MON ARRET " << endl;
    ChainonArret *tmp= d_t;

    while(tmp!=nullptr && tmp->d_num != arret-> d_num)
    {



        tmp=tmp->d_suiv;
    }

            tmp->estPlein=false;
            for(int i=0;i<tmp->tab.size();i++)
                        {
                            tmp->tab[i]->estPlein=false;
                        }


}
 // ---------------- Fonctions d'affichage-------------------------


 //initialisation de l'affichage des trams et des arrets
void LCL::init_affichage(LCT &a)
{


 // A METTRE DANS LE MAIN ! ->   lire("test.txt"); (initialise les tram avec le fichier txt)

//  -----------------------INIT AFFICHAGE TRAM---------------------------------------------
   ChainonTram *tram=a.d_tete;

   while(tram!=nullptr)
   {



    setcolor(couleur[d_numLigne]);
    rectangle(tram->d_pos.X(),tram->d_pos.Y(),tram->d_pos.X()+20,tram->d_pos.Y()+15);
        floodfill(tram->d_pos.X()+1,tram->d_pos.Y()+1,couleur[d_numLigne]);



       tram=tram->d_suiv;

   }






   // ----------------- INIT AFFICHAGE ARRET----------------------------------------
    ChainonArret *arret = d_t;
    while(arret !=nullptr)
    {
        setcolor(couleur[d_numLigne]);
        circle(arret->d_pos.X()+5,arret->d_pos.Y()+5,8);
        floodfill(arret->d_pos.X(),arret->d_pos.Y(),couleur[d_numLigne]);

    if(arret->d_suiv != nullptr)
        {
            setcolor(couleur[d_numLigne]);
            line(arret->d_pos.X()+5,arret->d_pos.Y()+5,arret->d_suiv->d_pos.X()+5,arret->d_suiv->d_pos.Y()+5);

        }

        arret = arret->d_suiv;

    }




}


//
void LCL::init_refresh_arret_suiv(LCT &a)
{
     ChainonTram *tram=a.d_tete;

   while(tram!=nullptr)
   {
        ChainonArret *arret=d_t;


        while( tram->d_pos.X() != arret->d_pos.X() || tram->d_pos.Y() != arret->d_pos.Y() ) // cherche sur quel arrêt il se trouve
            {

                arret = arret->d_suiv;

            }

   // cout << " mon tram " << tram->ntram << " est sur l'aret " << arret->num()<<endl;


        if(tram->sens==0 && arret->d_suiv !=nullptr)
        {
            tram->arret_suiv=arret->d_suiv;
      //     cout << " cas 1 pour le tram " << tram->ntram << endl;

        }
        else if(tram->sens==1 && arret->d_prec!=nullptr )
        {
            tram->arret_suiv=arret->d_prec;
          //  cout << " cas 2 pour le tram " << tram->ntram << endl;

        }
        else if(arret->d_suiv==nullptr )
        {
            // cout << " cas 3 pour le tram " << tram->ntram << endl;
             tram->sens=1;
            tram->arret_suiv=arret->d_prec;

        }
        else if(arret->d_prec==nullptr)
        {
          // cout << " cas 4 pour le tram " << tram->ntram << endl;
            tram->sens=0;
            tram->arret_suiv=arret->d_suiv;
        }

  //cout << " le tram numero " << tram->ntram << " a pour arret suivant l'arret " << tram->arret_suiv->d_pos.X() << endl;

   tram->a = ( tram->arret_suiv->pos().Y()  -  tram->d_pos.Y()    ) / ( tram->arret_suiv->pos().X() - tram->d_pos.X()     );

    tram->b = tram->d_pos.Y() -  tram->a*tram->d_pos.X();

      // double a = ( arret_suiv->pos().Y()  -  d_pos.Y()    ) / ( arret_suiv->pos().X() - d_pos.X()     );

   // double b = d_pos.Y() - a * d_pos.X();

        tram=tram->d_suiv;

   }


}


//
void LCL::circulation(LCT &a, LCA &lca)
{

ChainonTram *t = a.d_tete;
//cout << " ma tete est le tram " << t->ntram << endl;
    while(t!=nullptr)
    {

        if(t->estsurArret() && t->cpt < t->arret_suiv->duree_min)
        {
         //   cout << " rentre premier if " << endl;
             t->d_pos.changeX( t->arret_suiv->pos().X()  );

//--------- ------------ rendre plein ----------------------------------------------------------------
         //   cout << " mon tram numero " << t->ntram << "a pour arrret suiv un arret double ? " << t->arret_suiv->is_arret_double << endl;
            if(t->arret_suiv->is_arret_double == true )
            {
                rendre_arret_plein(t->arret_suiv  );
            }
 //*********************************************************** --------------------------



            (t->cpt)++;



                if(t->cpt == t->arret_suiv->duree_min)
                    {
//--------- ------------ rendre vide ----------------------------------------------------------------
                        if(t->arret_suiv->is_arret_double == true)
                        {
                            rendre_arret_vide(t->arret_suiv);
                        }
//*********************************************************** --------------------------
                        t->refresh_arret_suiv();


                     //  cout << " le tram " << t->ntram << " a maintenant pour arret suiv " << t->arret_suiv->num() << endl;


                    }

        }

        else
        {
         //   cout << " rentre deuxieme if " << endl;
        t->cpt=0;


            if(!t->distanceMinimum() && ( !t->arret_suiv->estPlein || t->d_pos.calculeDistance(t->arret_suiv->d_pos) > t->distanceMin  )   )
            {

//cout << " je fais savancer le tram numero " << t->ntram << endl;
                t->avancer();

            }

        }

t=t->d_suiv;

    }


}







 // ---------------- TESTS -------------------------


// test qui affiche quel arret pointe vers quels autres arrets
void LCL::testt()
{
    ChainonArret *arret = d_t;
    while(arret != nullptr)
    {
        cout << " mon arret numero " << arret->num() << " : " << arret;
        for(int i=0;i<arret->tab.size();i++)
        {
            cout << "Pointe vers " << arret->tab[i] << endl;
        }




        arret=arret->d_suiv;
    }
}


//test qui affiche le tableau qui contient les numeros de lignes

void LCL::affiche() const
{
    cout<<"test liste chainee Lignes :"<<endl;
    ChainonArret *c=d_t;
    ChainonTram  *tram=d_tete;
    while(c)
    {
        cout<<"l'arret numero "<<c->d_num<<"  de nom "<<c->d_nom<<" est dans la ligne "<<d_numLigne<<endl;
        c=c->d_suiv;
    }
    while(tram)
    {
        cout<<" le tram numero " << tram->ntram << " et sa position est " << tram->d_pos.X() << " : " << tram->d_pos.Y() << endl;
        tram=tram->d_suiv;
    }

}


//fonction qui return le nom de l'arret
std::string LCL::getArret(const int& nb) const
{
    int i =1;
    ChainonArret *c=d_t;
    while(i<nb && c)
    {
        i++;
        c=c->d_suiv;
    }

    if(c)
    {return c->d_nom;}
    //cas dans le quel la liste chainee s'arrete avant le nb
    else
        {
        std::string rep= "L'arret cherche n'existe pas";
        return rep;
        }
}


