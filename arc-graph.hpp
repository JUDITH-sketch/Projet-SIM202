#ifndef ARC_GRAPH_HPP
#define ARC_GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <set>
#include "segment-sommet.hpp"
#include "obstacle.hpp"

using namespace std;

// Classe représentant un arc dans le graphe
class Arc {
public:
    int S1;  // Sommet de départ
    int S2;  // Sommet d'arrivée
    double Poids;

    // Constructeurs
    Arc(int s1, int s2) : S1(s1), S2(s2), Poids(1) {}
    Arc(int s1, int s2, double val) : S1(s1), S2(s2), Poids(val) {}

    // Accesseurs
    int pred() const { return S1; }
    int succ() const { return S2; }
    double poids() const { return Poids; }
};

// Classe représentant un graphe sous forme de liste d'arcs
class Graph {
public:
    std::vector<Arc> listeArcs;           // Liste des arcs du graphe
    std::vector<Sommet> sommetsGraph;     // Liste des sommets du graphe
    std::unordered_map<int, int> sommetToObstacle; // Associe chaque sommet à un obstacle (-1 = libre)
    std::vector<Obstacle> obstacles;      // Liste des obstacles du graphe
    int nombreSommets;                    // Nombre total de sommets dans le graphe

    // Constructeur par défaut
    Graph() : nombreSommets(0) {}

    // Constructeur à partir d'une liste d'arcs (sans gestion d'obstacles)
    Graph(std::initializer_list<Arc> L) : listeArcs(L) {
        std::set<int> sommets_uniques;
        for (const auto& arc : L) {
            sommets_uniques.insert(arc.S1);
            sommets_uniques.insert(arc.S2);
        }
        nombreSommets = sommets_uniques.size();
        sommetsGraph.resize(nombreSommets);
    }

    // Renvoie la liste des successeurs d'un sommet
    std::vector<int> successeurs(int sommet) const {
        std::vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.pred()) {
                voisins.push_back(arc.succ());
            }
        }
        return voisins;
    }

    // Renvoie la liste des prédécesseurs d'un sommet
    std::vector<int> predecesseurs(int sommet) const {
        std::vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.succ()) {
                voisins.push_back(arc.pred());
            }
        }
        return voisins;
    }

    // Renvoie la liste de tous les voisins d'un sommet
    std::vector<int> voisins(int sommet) const {
        std::vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.succ()) {
                voisins.push_back(arc.pred());
            }
            if (sommet == arc.pred()) {
                voisins.push_back(arc.succ());
            }
        }
        return voisins;
    }

    // Renvoie les coordonnées d'un sommet
    Sommet getCoordonnees(int index) const {
        return sommetsGraph.at(index);
    }

    // Vérifie si un sommet appartient à un obstacle
    bool estSommetObstacle(int index) const {
        return sommetToObstacle.find(index) != sommetToObstacle.end();
    }
};

// Surcharge de l'opérateur d'affichage pour une liste de voisins
std::ostream& operator<<(std::ostream& o, const std::vector<int>& voisins) {
    o << "(";
    for (size_t k = 0; k < voisins.size(); ++k) {
        o << voisins[k];
        if (k < voisins.size() - 1) {
            o << ", ";
        }
    }
    o << ")";
    return o;
}

#endif // ARC_GRAPH_HPP

/*   // Ajoute un sommet et retourne son index
    int ajouterSommet(const Sommet& s, int obstacleID = -1) {
        int index = sommetsGraph.size();
        sommetsGraph.push_back(s);
        sommetToObstacle[index] = obstacleID;
        nombreSommets++;
        return index;
    }


void ajouterObstacle(const Obstacle& obstacle) {
    int obstacleID = obstacles.size();
    obstacles.push_back(obstacle);

    cout << "Adding obstacle " << obstacleID << " with " << obstacle.sommets.size() << " vertices" << endl;

    for (size_t i = 0; i < obstacle.sommets.size(); i++) {
        cout << "Obstacle vertex " << i << ": " << obstacle.sommets[i] << endl;
    }

    std::vector<int> indices;
    for (const auto& sommet : obstacle.sommets) {
        int index = ajouterSommet(sommet, obstacleID);
        indices.push_back(index);
    }
}

   bool arcEstValide(int s1, int s2) const {
    Segment seg(sommetsGraph[s1], sommetsGraph[s2]);
    cout << "Checking arc: " << s1 << " -> " << s2 << " (" << sommetsGraph[s1] << " -> " << sommetsGraph[s2] << ")" << endl;

    bool blocked = false;
    for (const auto& obstacle : obstacles) {
        if (obstacle.intersection(seg)) {
            cout << " ❌ Arc " << s1 << " -> " << s2 << " is INVALID (Blocked by obstacle)" << endl;
            blocked = true;
        }
    }

    if (!blocked) {
        cout << " ✅ Arc " << s1 << " -> " << s2 << " is VALID" << endl;
    }

    return !blocked;
}


void genererArcs() {
    listeArcs.clear();
    int n = sommetsGraph.size();
    cout << "Generating arcs for " << n << " vertices..." << endl;

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (arcEstValide(i, j)) {
                double poids = (sommetsGraph[i] - sommetsGraph[j]).norme();
                listeArcs.push_back(Arc(i, j, poids));
                cout << "✅ Arc added: " << i << " -> " << j << " (Weight: " << poids << ")" << endl;
            }
        }
    }

    cout << "Total arcs generated: " << listeArcs.size() << endl;
}*/