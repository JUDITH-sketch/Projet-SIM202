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
}*/


};
#endif // OBSTACLE_HPP
