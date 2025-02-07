#ifndef ARC_GRAPH_HPP
#define ARC_GRAPH_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <set>

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
    Graph(initializer_list<Arc> L) : listeArcs(L) {
    set<int> sommets_uniques;
    for (const auto& arc : L) {
        sommets_uniques.insert(arc.S1);
        sommets_uniques.insert(arc.S2);
    }
    nombreSommets = sommets_uniques.size();  // Nombre réel de sommets
}

// Ajoute un arc au graph
    void add(Arc A){
        listeArcs.emplace_back(A);
        set<int> sommets_uniques;
        for (const auto& arc : listeArcs){
        sommets_uniques.insert(arc.S1);
        sommets_uniques.insert(arc.S2);
    }
    nombreSommets = sommets_uniques.size(); 
    }
};

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

// ============== Operateur de sortie ==============

// sortie graph
ostream& operator<<(ostream& o, const Graph& G){
    o<<"le graph comporte les arcs suivants : "<<'\n';
    for(auto& arc : G.listeArcs){
        o<<arc<<'\n';
    }
    return o;
}

// sortie Arc
ostream& operator<<(ostream& os, const Arc& A) {
    os << "[" << A.S1 << " -> " << A.S2 << "]" <<'('<<A.Poids<<')';
    return os;
}


#endif // ARC_GRAPH_HPP

/*   

    std::vector<Sommet> sommetsGraph;     // Liste des sommets du graphe
    std::unordered_map<int, int> sommetToObstacle; // Associe chaque sommet à un obstacle (-1 = libre)
    std::vector<Obstacle> obstacles;      // Liste des obstacles du graphe

// Ajoute un sommet et retourne son index
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

    // Renvoie les coordonnées d'un sommet
    Sommet getCoordonnees(int index) const {
        return sommetsGraph.at(index);
    }

    // Vérifie si un sommet appartient à un obstacle
    bool estSommetObstacle(int index) const {
        return sommetToObstacle.find(index) != sommetToObstacle.end();
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
