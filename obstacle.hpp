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

bool intersection(const Segment& s) const {
    for (size_t i = 0; i < sommets.size(); i++) {
        Segment edge(sommets[i], sommets[(i + 1) % sommets.size()]);
        if (s == edge) {
            continue; 
        }
        if (edge.intersection(s)) {
            return true;
        }
    }
    return false;
}
    
/*
// tester pour des intersections fermée.
bool intersection(const Segment& s) const {
    bool isPartOfObstacle = false;
    bool hasIntersection = false;
    for (size_t i = 0; i < sommets.size(); i++) {
        Segment edge(sommets[i], sommets[(i + 1) % sommets.size()]);
        
        if (s == edge) {
            isPartOfObstacle = true; 
        }

        if (edge.intersection(s)) {
            hasIntersection = true;
        }
    }
    return isPartOfObstacle ? false : hasIntersection;
}
*/
/*
    // Détermine si un point est strictement à l'intérieur du polygone (ray-casting)
    bool point_est_interieur(const Sommet& p) const {
        int count = 0;
        int n = sommets.size();

        for (int i = 0; i < n; i++) {
            Sommet A = sommets[i];
            Sommet B = sommets[(i + 1) % n];

            // Vérifier si le point est sur une arête
            if ((B.x - A.x) * (p.y - A.y) == (B.y - A.y) * (p.x - A.x) &&
                p.x >= min(A.x, B.x) && p.x <= max(A.x, B.x) &&
                p.y >= min(A.y, B.y) && p.y <= max(A.y, B.y)) {
                return false; // Considéré comme extérieur
            }

            // Algorithme de l'angle balayé
            if ((A.y > p.y) != (B.y > p.y)) {
                double x_intersect = (B.x - A.x) * (p.y - A.y) / (B.y - A.y) + A.x;
                if (p.x < x_intersect) count++;
            }
        }
        return (count % 2) == 1;  // Retourne vrai si le point est strictement à l'intérieur
    }

    // Vérifie si un segment traverse strictement l'obstacle
    bool segmentTraverseStrictement(const Segment& s) const {
        bool p1Inside = point_est_interieur(s.A);
        bool p2Inside = point_est_interieur(s.B);

        // Si une extrémité est strictement à l'intérieur, il y a pénétration
        if (p1Inside || p2Inside) {
            return true;
        }

        // Vérifier si une partie du segment passe strictement à l'intérieur
        int n = sommets.size();
        for (int i = 0; i < n; i++) {
            Sommet A = sommets[i];
            Sommet B = sommets[(i + 1) % n];

            // Vérifier si le segment traverse une arête du polygone
            double cross1 = (B.x - A.x) * (s.A.y - A.y) - (B.y - A.y) * (s.A.x - A.x);
            double cross2 = (B.x - A.x) * (s.B.y - A.y) - (B.y - A.y) * (s.B.x - A.x);

            if ((cross1 > 0 && cross2 < 0) || (cross1 < 0 && cross2 > 0)) {
                return true; // Traversée stricte du polygone
            }
        }
        return false;
    }
        */
};
#endif // OBSTACLE_HPP
