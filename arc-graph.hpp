#ifndef ARC_GRAPH_HPP
#define ARC_GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>

using namespace std;

// Classe représentant un arc dans le graphe
class Arc {
public:
    int S1; // Sommet de départ
    int S2; // Sommet d'arrivée
    double Poids;
    
    // Constructeur avec poids par défaut
    Arc(int s1, int s2) : S1(s1), S2(s2), Poids(1) {}
    
    // Constructeur avec poids spécifié
    Arc(int s1, int s2, double val) : S1(s1), S2(s2), Poids(val) {}

    // Renvoie le sommet de départ de l'arc
    int pred() const { return S1; }
    
    // Renvoie le sommet d'arrivée de l'arc
    int succ() const { return S2; }
    
    // Renvoie la valeur (poids) de l'arc
    double poids() const { return Poids; }
};

// Classe représentant un graphe sous forme de liste d'arcs
class Graph {
public:
    int nombreSommets; // Nombre total de sommets dans le graphe
    vector<Arc> listeArcs; // Liste des arcs du graphe

    // Constructeur par défaut
    Graph() : nombreSommets(0) {}
    
    // Constructeur à partir d'une liste d'arcs
    Graph(initializer_list<Arc> L) : nombreSommets(L.size()), listeArcs(L) {}

    // Renvoie la liste des voisins en aval d'un sommet donné (successeurs)
    vector<int> successeurs(int sommet) const {
        vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.pred()) {
                voisins.emplace_back(arc.succ());
            }
        }
        return voisins;
    }

    // Renvoie la liste des voisins en amont d'un sommet donné (prédécesseurs)
    vector<int> predecesseurs(int sommet) const {
        vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.succ()) {
                voisins.emplace_back(arc.pred());
            }
        }
        return voisins;
    }

    // Renvoie la liste de tous les voisins (entrants et sortants) d'un sommet donné
    vector<int> voisins(int sommet) const {
        vector<int> voisins;
        for (const auto &arc : listeArcs) {
            if (sommet == arc.succ()) {
                voisins.emplace_back(arc.pred());
            }
            if (sommet == arc.pred()) {
                voisins.emplace_back(arc.succ());
            }
        }
        return voisins;
    }
};

// Surcharge de l'opérateur d'affichage pour afficher une liste de voisins
ostream& operator<<(ostream& o, const vector<int>& voisins) {
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