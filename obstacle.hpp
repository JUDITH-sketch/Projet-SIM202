#ifndef OBSTACLE_HPP
#define OBSTACLE_HPP

#include <vector>
#include <iostream>
#include "segment-sommet.hpp"

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
/*
    // Vérifie si un segment coupe l'obstacle
    bool intersection(const Segment& S) const {
        int n = sommets.size();
        for (int i = 0; i < n; i++) {
            Segment seg(sommets[i], sommets[(i + 1) % n]);
            if (S.intersection(seg)) {
                return true;
            }
        }
        return false;
    }
    */
bool intersection(const Segment& s) const {
    for (size_t i = 0; i < sommets.size(); i++) {
        Segment edge(sommets[i], sommets[(i + 1) % sommets.size()]);
        
        // Allow obstacle's own edges but block true intersections
        if (s == edge) {
            cout << " ✅ Segment " << s << " is an OBSTACLE EDGE and is ALLOWED" << endl;
            continue;  // Skip if the segment is an actual edge of the obstacle
        }

        if (edge.intersection(s)) {
            cout << " ❌ Segment " << s << " STRICTLY INTERSECTS obstacle edge " << edge << endl;
            return true;
        }
    }
    return false;
}


};

#endif // OBSTACLE_HPP
