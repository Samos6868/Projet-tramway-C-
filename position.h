#ifndef POSITION_H
#define POSITION_H
#include<cmath>
#include<iostream>
using namespace std;


class position
{
    public:
        position(int x=0,int y=0);
        ~position();

        double X()const;//renvoie le x
        double Y()const;//renvoie le y

        void changeX(double val);//change le x
        void changeY(double val);//change le y
        void changePosition(double val1 ,double val2);//change la position



        double calculeDistance(const position& p)const;



        //test
        void affiche ( ostream &ost ) const ;
    protected:

    private:
        double d_x;
        double d_y;
};


#endif // POSITION_H
