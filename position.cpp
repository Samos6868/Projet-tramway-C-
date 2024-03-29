#include "position.h"

position::position(int x, int y) : d_x{x}, d_y{y}
{
    //ctor
}

position::~position()
{
    //dtor

}



//renvoie le x
double position::X()const { return d_x ; }

//renvoie le Y
double position::Y()const { return d_y ; }

//change la valeur du X
void position::changeX( double val ) { d_x = val ; }

//change le valeur du Y
void position::changeY( double val ) { d_y = val ; }

//changement de position avec ceux passé en parametre
void position::changePosition( double val1, double val2) { d_x = val1 ; d_y = val2 ; }

//calcul de distance
double position::calculeDistance(const position& p)const
{
    return fabs( sqrt(((d_x-p.d_x)*(d_x-p.d_x))+((d_y-p.d_y)*(d_y-p.d_y))) );
}


//test pour afficher
void position::affiche(ostream& ost) const
{
    ost<<'('<<d_x<<','<<d_y<<')'<<endl;
}
