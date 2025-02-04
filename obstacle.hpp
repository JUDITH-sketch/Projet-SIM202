#include "segment-sommet.hpp"
#include <list>


ostream& operator<<(ostream& o, const vector<Point> V){
    int n = V.size();
    cout<<n;
    for(int k=0;k<n;k++){
        o<<V[k];
    }
    return o;
}



class obstacle
{
    public:
    int n;                  //nombre de sommets de l'obstacle
    vector<Point> Coord;    //coordonée des sommets
    vector<Point> normal;   //normale de l'obstacle

    obstacle(){n=0;}
    obstacle(const initializer_list<Point> cord){
        n = cord.size();
        Coord.resize(n);
        int k=0;
        for(auto e:cord){
            Coord[k]=e;
            k=k+1;
        }
        for(int k=0; k<n-1;k++){
            Segment Sk(Coord[k],Coord[k+1]);
            Point N = Sk.normal();
            normal.emplace_back(N);
        }
        Segment Sk(Coord[n-1],Coord[0]);
        Point N = Sk.normal();
        
        normal.emplace_back(N);
    }
    //================fonctions obstacles================


    bool is_intersect(Segment S){
        bool T=false;
        cout<<S<<'\n';
        for(int k=0;k<=n-2;k++){
            cout<<'\n'<<"============="<<k<<"=========="<<'\n';
            Segment Sk(Coord[k],Coord[k+1]);
            cout<<Sk<<'\n';
            if(S.is_intersect(Sk)){T=true;return T;}
        }
        cout<<"============="<<n-1<<"=========="<<'\n';
        Segment Sk(Coord[n-1],Coord[0]);
        if(S.is_intersect(Sk)){T=true;return T;}
        return T;
    }
};

























//  bool is_intersect(Segment S){
//         Point P = S.direction();
//         double a,b;
//         a = P.coord[0]; b=P.coord[1];
//         double c = S.points[0].coord[0]*a +S.points[0].coord[1]*b;
//         cout<<"======================"<<endl;
//         int k=0;
//         for(auto& e : normal){
//             cout<<k<<endl;
//             double ae,be;
//             ae =e.coord[0];be=e.coord[1];

//             if(a*be-ae*b == 0){1+1;}
//             else{
//                 double ce = Coord[k].coord[0]*ae +Coord[k].coord[1]*be;
//                 double xs = (c*be-ce*b)/(a*be-ae*b);
//                 double ys = (a*ce-ae*c)/(a*be-ae*b);
//                 cout<<"SOL"<<'('<<xs<<','<<ys<<')'<<endl;

//                 bool t1=false,t2=false,r1=false,r2=false;
//                 cout<<"1er "<< S.points[0].coord[0]<<","<< S.points[1].coord[0]<<"\n";
//                 if(((S.points[0].coord[0] <= xs) && (xs <= S.points[1].coord[0])) ||((S.points[0].coord[0] >= xs) &&(xs >= S.points[1].coord[0])))
//                 {t1 =true;cout<<"T1 \n";}
//                 cout<<"2e "<< S.points[0].coord[1]<<","<< S.points[1].coord[1]<<"\n";
//                 if(((S.points[0].coord[1] <= ys) &&(ys <= S.points[1].coord[1])) || ((S.points[0].coord[1] >= ys) &&(ys >= S.points[1].coord[1])))
//                 {t2 =true;cout<<"T2 \n";}

//                 if(k!=n){
//                     cout<<"3e "<<Coord[k].coord[0]<<','<<Coord[k+1].coord[0]<<'\n';
//                     if(((Coord[k].coord[0]<= xs) && (xs <=Coord[k+1].coord[0])) || ((Coord[k].coord[0] >= xs) && (xs >=Coord[k+1].coord[0])))
//                     {r1 =true;
//                     cout<<"R1 \n";}
//                     cout<<"4e "<<Coord[k].coord[1]<<','<<Coord[k+1].coord[1]<<'\n';
//                     if(((Coord[k].coord[1]<= ys) && (ys <=Coord[k+1].coord[1])) || ((Coord[k].coord[1] >= ys) && (ys >=Coord[k+1].coord[1])))
//                     {r2 =true;
//                     cout<<"R2 \n";}}

//                 else{
//                     cout<<"3e "<<Coord[n].coord[0]<<','<<Coord[0].coord[0]<<'\n';
//                     if(((Coord[n].coord[0]<= xs) && (xs <=Coord[0].coord[0])) || ((Coord[n].coord[0] >= xs) && (xs >=Coord[0].coord[0])))
//                     {r1 =true;
//                     cout<<"R1 \n";}
//                     cout<<"4e "<<Coord[n].coord[1]<<','<<Coord[0].coord[1]<<'\n';
//                     if(((Coord[n].coord[1]<= ys) && (ys <=Coord[0].coord[1])) || ((Coord[n].coord[1] >= ys) && (ys >=Coord[0].coord[1])))
//                     {r2 =true;
//                     cout<<"R2 \n";}}
                
//                 cout<<t1<<","<<t2<<","<<r1<<","<<r2<<endl;
//                 if( ((t1 && t2) && r1) && r2){cout<<" TRUE "<<"("<<xs<<","<<ys<<")";return true;}                
//             }
//             k =k+1;
//             cout<<"=========================="<<endl;
//         }
//         return false;
//     }