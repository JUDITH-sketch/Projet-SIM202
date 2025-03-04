#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <vector>
#include <iostream>
#include "segment_sommet.hpp"

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

    // Vérifie si un segment a au moins un point strictement à l'intérieur
    bool intersection(const Segment& seg, int samplePoints = 100) const {
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
};
#endif // OBSTACLE_HPP
