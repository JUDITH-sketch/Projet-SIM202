#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;


const double pi=4*atan(1.);
typedef vector<double> vecteur; 

// classe point héritant de vector<double>
class Point : public vector<double>
{  protected: 

   public:
   int dim;
   vector<double> coord;
   Point()=default;
   Point(double x) : vector<double>{x}              //constructeur point 1D
   {
      dim=1;
      coord = vector(dim);
      coord[1]=x;
   }
   Point(double x, double y) : vector<double>{x,y}  //constructeur point 2D
   {
      dim=2;
      coord = vector(dim);
      coord[0]=x;
      coord[1]=y;
   }
};
Point operator+(const Point& P1, const Point& P2)     // P1+P2
{
   if (P1.dim != P2.dim){ cout<<"erreur dimension"; exit(-1);}
   Point P = Point(0,0 );
   for(int k=0;k<P1.dim;k++){
      P.coord[k]=P1.coord[k]+P2.coord[k];
   }
   return P;
}

Point operator-(const Point& P1, const Point& P2)     // P1-P2
{
   if (P1.dim != P2.dim){ cout<<"erreur dimension"; exit(-1);}
   Point P = Point(0,0 );
   for(int k=0;k<P1.dim;k++){
      P.coord[k]=P1.coord[k]-P2.coord[k];
   }
   return P;
}
Point operator*(const double a ,const Point& P2){
   if(a==0){cout<<"multiplie par 0";exit(-1);}
   Point P = Point(0,0 );
   for(int k=0;k<P2.dim;k++){
      P.coord[k]=P2.coord[k]*a;
   }
   return P;
}
double norme(const Point& P)                          // |P|
{
   double S=0;
   for(int k=0;k<P.dim;k++){
      S+= P.coord[k]*P.coord[k];
   }
   return sqrt(S);
}
ostream& operator<<(ostream& o, const Point& P)     // affichage (x1,x2,...)
{
   o<<"(";
  for(int k=0; k<P.dim;k++){
    o<<P.coord[k]<<",";
  }
  o<<")";
  return o;
}

//classe Arc parent de Segment, ArcEllipse, ArcParametre
class Arc
{  public:
   string type="test";
   vector<Point> points;                                // extremites de l'arc


   virtual double longueur() const = 0;                 // longueur de l'arc
   virtual Arc& retourne() = 0;                         // retourne l'arc
   // virtual void exporte(ostream& out, int n) const = 0; // export de l'arc

   
};

ostream& operator<<(ostream& o, const Arc& A){       //type : point de départ point d’arrivée
   o<<A.type<<":"<<A.points[0]<<","<<A.points[1];
   return o;
}


//classe Segment héritant de Arc

class Segment : public Arc
{
   public:
   

   Segment(Point A,Point B)
   {  
   points =vector<Point>(2);
   points[0]= A;
   points[1]=B;
   type ="Segment";
   }


   double longueur()const                               // longueur de l'arc
   {return norme(points[0]-points[1]);}                       

   Segment& retourne()                                     // retourne l'arc
   {
      Point x = points[0];
      points[0]= points[1];
      points[1]=x;
      return *this;
   }
   
   Point direction(){
      Point A =points[1]-points[0];
      return A;
   }

   Point normal(){
      Point D = (*this).direction();
      Point N(D.coord[1],-D.coord[0]);
      return N;
   }

   bool is_intersect(Segment S){
      Point X1=points[0]; Point X2 = points[1];
      Point X3=S.points[0]; Point X4 = S.points[1];
         cout<<'\n'<<"start (is_intersect)"<<'\n';
         double a,b,c,d;
         double k1,k2;
         
         a = X2.coord[0] - X1.coord[0]; b = X3.coord[0] - X4.coord[0];
         c = X2.coord[1] - X1.coord[1]; d = X3.coord[1] - X4.coord[1];
         k1 = X3.coord[0] - X1.coord[0]; k2 =  X3.coord[1] - X1.coord[1];

         cout<<a<<b<<c<<d;
         double det = a*d-b*c;
         if(det !=0){
             cout<<"d!=0"<<'\n';
             double xk,yk; xk =1/det *(k1*d-k2*b); yk = 1/det *(k2*a-c*k1);
              
             cout<<"("<<xk<<","<<yk<<")";
             if(0<=xk && xk<=1){
                 cout<<"x bien paramétré"<<'\n';
                 if(0<=yk && yk<=1){
                     cout<<"y bien paramétré"<<'\n';
                     cout<<"TRUE";
                     return true;
                    }
                }
            }
        return false;
    }
};
