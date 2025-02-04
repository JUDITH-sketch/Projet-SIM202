#include "obstacle.hpp"

int main(int argc, char *argv[]){

    //base
    Point e1(0,1); Point e2(1,0);
    //l'ordre des points est importants
    Point S1(0,0);    Point S2(0,2);    Point S3(2,2);    Point S4(2,0);

    obstacle O({S1,S2,S3,S4}); //carré de longueur 2 

    Segment S(e1-e2,3*e2+e1); //segment (1,-1)->(1,3)
    cout<<O.is_intersect(S)<<'\n'; //true  (1,0) et (1,2)

    Segment A(S1,2*e1); //segment (0,0)->(2,0)
    // A.retourne();
    cout<<A<<S<<'\n';
    cout<<A.is_intersect(S)<<'\n'; //true (1,0)

}