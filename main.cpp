#include <iostream>
#include "class_tram.h"
#include "LCL.h"
#include "position.h"
#include "graphics.h"
using namespace std;


int main()
{

    LCA A;
    A.lire("Ligne1V3.txt");



// ----------------- CREATION DES LISTES CHAINEES TRAM ------------------------
     LCT tram1;
     tram1.lire("Ligne1V3.txt",1);

     LCT tram2;
     tram2.lire("Ligne1V3.txt",2);

     LCT tram3;
     tram3.lire("Ligne1V3.txt",3);

     LCT tram4;
     tram4.lire("Ligne1V3.txt",4);
// -------------------------------------------------------------------------------------------





// ----------------- CREATION LIGNE INITIALISATION --------------------
    LCL L1;
    L1.creation(A,tram1,1);

    LCL L2;
    L2.creation(A,tram2,2);

    LCL L3;
    L3.creation(A,tram3,3);

    LCL L4;
    L4.creation(A,tram4,4);

// --------------------------------------------------------------------------


    L1.search_arret_double(L2); // search arret en commun
    L1.search_arret_double(L3);
    L2.search_arret_double(L3);



 // ---------------- INITIALISATION ARRET SUIVANT -------------------------

    L1.init_refresh_arret_suiv(tram1);

    L2.init_refresh_arret_suiv(tram2);

    L3.init_refresh_arret_suiv(tram3);

    L4.init_refresh_arret_suiv(tram4);

// ------------------------------------------------------------------------------








// ----------------------------AFFICHAGE GRAPHIQUE -----------------------

     opengraphsize(850,500);
     setbkcolor(LIGHTGRAY);


       for(int i=0;i<2000;i++)
       {
           L1.init_affichage(tram1);
           L2.init_affichage(tram2);
           L3.init_affichage(tram3);
           L4.init_affichage(tram4);
           delay(20);



           cleardevice();

           L1.circulation(tram1,A);
           L2.circulation(tram2,A);
           L3.circulation(tram3,A);
           L4.circulation(tram4,A);

           L1.init_affichage(tram1);
           L2.init_affichage(tram2);
           L3.init_affichage(tram3);
           L4.init_affichage(tram4);

           delay(20);
           cleardevice();



       }



     getch();
     cleardevice();

// ---------------------------------------------------------------------------------


}

