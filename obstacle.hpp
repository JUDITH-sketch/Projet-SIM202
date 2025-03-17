#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <vector>
#include <iostream>
#include "segment_sommet.hpp"
#include <algorithm>

using namespace std;

class Obstacle {
public:
    std::vector<Sommet> sommets;  // Sommets définissant l'obstacle
    std::vector<Sommet> normales; // Normales aux segments de l'obstacle

    // Constructeur par défaut
    Obstacle() = default;

    // Constructeur prenant une liste de sommets
    Obstacle(const std::vector<Sommet>& sommets) : sommets(sommets) {
        calculer_normales();
    }

    // Fonction pour calculer les normales des segments de l'obstacle
    void calculer_normales() {
        int n = sommets.size();
        normales.clear();
        for (int i = 0; i < n; i++) {
            Segment seg(sommets[i], sommets[(i + 1) % n]);  // Connexion cyclique
            normales.push_back(seg.normale());
        }
    }

    // fait glisser un obstacle dans le sens du sommet
    void slide (Sommet s){
        std::vector<Sommet> S;
        for (auto& Som : sommets){
            S.push_back(Som +s);
        }
        sommets = S;
    }

    // fait grossir un obstacle par un scalaire
    void grow (double R){
        std::vector<Sommet> S;
        for (auto& Som : sommets){
            Som = Som*R;
            S.push_back(Som);
        }
        sommets = S;
    }


    // inverse l'ordre des sommets
    void inversion() {
        std::reverse(sommets.begin(), sommets.end());
    }

// bool intersection(const Segment& s) const {
//     for (size_t i = 0; i < sommets.size(); i++) {
//         Segment edge(sommets[i], sommets[(i + 1) % sommets.size()]);
//         if (s == edge) {
//             continue; 
//         }
//         if (edge.intersection(s)) {
//             return true;
//         }
//     }
//     return false;
// }
  

// // tester pour des intersections fermée.
// bool intersection(const Segment& s) const {
//     bool isPartOfObstacle = false;
//     bool hasIntersection = false;
//     for (size_t i = 0; i < sommets.size(); i++) {
//         Segment edge(sommets[i], sommets[(i + 1) % sommets.size()]);
        
//         if (s == edge) {
//             isPartOfObstacle = true; 
//         }

//         if (edge.intersection(s)) {
//             hasIntersection = true;
//         }
//     }
//     return isPartOfObstacle ? false : hasIntersection;
// }

    // Vérifie si un point est exactement sur une arête du polygone
    bool isOnBoundary(const Sommet& P) const {
        int n = sommets.size();
        for (int i = 0; i < n; i++) {
            Sommet A = sommets[i];
            Sommet B = sommets[(i + 1) % n];

            // Vérifier si P est sur le segment [A, B] en utilisant le produit vectoriel
            double crossProduct = (P.x - A.x) * (B.y - A.y) - (P.y - A.y) * (B.x - A.x);
            if (abs(crossProduct) < 1e-9) { // Si le produit est proche de zéro, P est colinéaire
                // Vérifier que P est bien entre A et B
                if (P.x >= min(A.x, B.x) && P.x <= max(A.x, B.x) &&
                    P.y >= min(A.y, B.y) && P.y <= max(A.y, B.y)) {
                    return true; // Le point est sur une arête
                }
            }
        }
        return false;
    }

    // Vérifie si un point est strictement à l'intérieur du polygone (Ray-Casting)
    bool isPointInside(const Sommet& P) const {
        if (isOnBoundary(P)) {
            return false; // Si le point est sur une arête, il n'est pas strictement à l'intérieur
        }

        int count = 0;
        int n = sommets.size();
        //double rayX = 1e9; // Un grand X pour aller loin à droite

        for (int i = 0; i < n; i++) {
            Sommet A = sommets[i];
            Sommet B = sommets[(i + 1) % n];

            // Vérifier si P est entre les y des deux sommets
            if ((P.y > min(A.y, B.y)) && (P.y <= max(A.y, B.y)) && (P.x < max(A.x, B.x))) {
                // Calculer l'intersection avec la demi-droite horizontale
                double xIntersect = A.x + (P.y - A.y) * (B.x - A.x) / (B.y - A.y);

                if (xIntersect > P.x) {
                    count++;
                }
            }
        }

        return (count % 2 == 1); // Impair = intérieur, Pair = extérieur
    }

    // //Vérifie si un segment a au moins un point strictement à l'intérieur
    bool intersection_RayTracing(const Segment& seg, int samplePoints = 100) const {
        for (int i = 1; i <= samplePoints; i++) {
            double t = (double)i / (samplePoints + 1);
            Sommet P(seg.A.x + t * (seg.B.x - seg.A.x),
                    seg.A.y + t * (seg.B.y - seg.A.y));

            if (isPointInside(P)) {
                return true; // Si un seul point est dedans, intersection confirmée
            }
        }
        return false;
    } 

    
    // Vérifie si un segment coupe l'obstacle
    bool intersection_ouvertferme(const Segment& S) const {
        int n = sommets.size();
        for (int i = 0; i < n; i++) {
            Segment seg(sommets[i], sommets[(i + 1) % n]);
            if (S.intersection(seg)) {return true;}
            if( isPointInside(S.midpoint())){return true;}
        }
        return false;
    }

// Méthode en uttilisant le principe des normales 
   bool intersection_normale_ouverte(const Segment& s) const {
    for (size_t i = 0; i < sommets.size(); i++) {
        Sommet A = sommets[i];
        Sommet B = sommets[(i + 1) % sommets.size()]; // Arête suivante (fermeture du polygone)
        
        Segment arrete(A, B);

        // Vérifier si le segment s croise l'arête actuelle de l'obstacle
        if (arrete.intersection(s)) {
            return true; // Intersection trouvée
        }

        // Calculer la normale perpendiculaire à l'arête
        double dx = B.x - A.x;
        double dy = B.y - A.y;
        double nx = -dy;
        double ny = dx;

        // Vérifier si les deux points du segment test sont de part et d'autre de la normale
        double proj1 = (s.A.x - A.x) * nx + (s.A.y - A.y) * ny;
        double proj2 = (s.B.x - A.x) * nx + (s.B.y - A.y) * ny;

        if (proj1 * proj2 < 0) { // Si les projections sont opposées, le segment traverse l'obstacle
            return true;
        }
    }

    return false;
    }
    bool intersection (const Segment& s, int methode=1) const {
        if (methode == 1){ return intersection_ouvertferme(s);}
        if (methode == 2){ return intersection_RayTracing(s);}
        if (methode == 3){ return intersection_normale_ouverte(s);}
        if (methode == 0 || methode >3) {cout<<"methode non defini"; exit(-1);}
        return 0;
    }
    

    // // Ces fonctions vont être utiles pour vérifier si deux obstacles se chevauchent pour l'exemple interactif (7)
    bool contient_point(const Sommet& s) const {
        int count = 0;
         size_t n = sommets.size();
    
        for (size_t i = 0; i < n; i++) {
            Sommet A = sommets[i];
            Sommet B = sommets[(i + 1) % n]; // Segment suivant (fermeture du polygone)
    
             // Vérifie si le point `s` est à gauche du segment (A,B) avec le produit vectoriel
            if (((A.y <= s.y && s.y < B.y) || (B.y <= s.y && s.y < A.y)) &&
                (s.x < (B.x - A.x) * (s.y - A.y) / (B.y - A.y) + A.x)) {
              count++;
            }
        }
    
    //     // Si le nombre d'intersections est impair, le point est à l'intérieur
       return count % 2 == 1;
     }

    // // Vérifie si deux obstacles se chevauchent
 static bool obstacles_se_chevauchent(const vector<pair<Obstacle, int>>& obstacles) {
    // // Parcours de tous les couples d'obstacles possibles
    for (size_t i = 0; i < obstacles.size(); i++) {
       for (size_t j = i + 1; j < obstacles.size(); j++) {
            
    //         // Vérifie si un sommet d'un obstacle est à l'intérieur de l'autre
           for (const auto& sommet : obstacles[i].first.sommets) { // Accès correct avec .first
               if (obstacles[j].first.contient_point(sommet)) { // Vérification d'inclusion
                   return true; // Il y a un chevauchement
              }
          }
            
           for (const auto& sommet : obstacles[j].first.sommets) {
               if (obstacles[i].first.contient_point(sommet)) {
                   return true;
               }
            }

    //         // Vérifie si les segments des deux obstacles s'intersectent
          for (size_t a = 0; a < obstacles[i].first.sommets.size(); a++) {
               Segment segA(obstacles[i].first.sommets[a], 
                            obstacles[i].first.sommets[(a + 1) % obstacles[i].first.sommets.size()]);

                for (size_t b = 0; b < obstacles[j].first.sommets.size(); b++) {
                    Segment segB(obstacles[j].first.sommets[b], 
                                 obstacles[j].first.sommets[(b + 1) % obstacles[j].first.sommets.size()]);

                   if (segA.intersection(segB)) { // Vérification d'intersection entre segments
                       return true; // Chevauchement détecté
                   }
               }
           }
       }
    }
     return false; // Aucun chevauchement détecté
     }

    

    
    
/// Le padding 
    // Padd un obstacle
    Obstacle Paddington(int Discret_cercle = 4, double Rayon=0.1 ) const{
        int n = sommets.size();
        vector<Sommet> padding;
        //double angle = 360./Discret_cercle;
        for(int k =0;k<n;k++){
            cout<<'\n'<<"================================="<<'\n';
            Sommet Sommet_topadd = sommets[k];
            cout<<"Sommet to padd : "<<Sommet_topadd<<'\n';

            Sommet X;Sommet Y;
            Segment pred(X,Y); Segment succ(X,Y);

            if(k!=n-1){   succ = Segment(sommets[k+1],Sommet_topadd);}
            else{       succ  = Segment(sommets[0],Sommet_topadd);}

            if(k!=0){   pred= Segment(sommets[k-1],Sommet_topadd);}
            else {      pred = Segment(sommets[n-1],Sommet_topadd);}

            Sommet e1 = -succ.normale() *(1/ (succ.longueur()));
            Sommet e2 = pred.normale()*(1/ (pred.longueur()));
            
            bool point_entrant = false;
            if(e1.x * e2.y - e1.y * e2.x<=0){point_entrant=true;}
            
            double angle = std::acos((e1.x*e2.x - e1.y*e2.y)/2); // angle entre e1 et e2
            double alpha_base = atan2(e1.y,e1.x) +angle ;

            Sommet u1(1,0) , u2(0,1);
            if(!point_entrant){
                angle /= Discret_cercle;

                for(int i=0;i<= Discret_cercle;i++){
                    cout<<'\n'<<"-----------"<<k<<"-"<<i<<"----------"<<'\n';
                    Sommet Sommet_test = Sommet_topadd + Rayon*(u2*sin(-i*angle+alpha_base) + u1*cos(-i*angle+alpha_base));
                    cout<<Sommet_test;
                    
                    // padding.push_back(Sommet_test);
                    if(!isPointInside(Sommet_test)){
                        cout<<"Point not inside"<<'\n';
                        double d1 = pred.distance(Sommet_test);
                        double d2 = succ.distance(Sommet_test);
                        cout<<"distance to obs = "<<d1<<" et "<<d2<<'\n';
                        if(d1>=Rayon-1e-9 && d2 >= Rayon-1e-9){
                            cout<<"Point hors range"<<'\n';
                            padding.push_back(Sommet_test);
                        }
                    }
                }
            }
            else{
                
                Sommet u1(1,0) , u2(0,1);
                Sommet Sommet_test = Sommet_topadd - Rayon/sin(angle/2)*(u2*sin(angle/2+alpha_base) + u1*cos(angle/2+alpha_base));
                cout<<Sommet_test;
                    
                padding.push_back(Sommet_test);
            }
        }
        Obstacle Obs_padded(padding);
        for(auto& somm : padding){
            cout<<somm<<'\n';
        }

        return Obs_padded;
    }
};
#endif // OBSTACLE_HPP
