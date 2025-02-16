#ifndef DIJKSTRA_HPP
#define DIJKSTRA_HPP

#include <iostream>
#include <vector>
#include <limits>
#include <set>
#include "arc_graph.hpp"

using namespace std;

// Fonction de l'algorithme de Dijkstra basée sur la matrice de coût
pair<vector<double>, vector<int>> dijkstra(const Graph& graph, int start) {
    int n = graph.nombreSommets;
    const double INF = numeric_limits<double>::infinity();

    // Étape 1 : Construction de la matrice des coûts c[i][j]
    vector<vector<double>> c(n + 1, vector<double>(n + 1, INF));

    for (const auto& arc : graph.listeArcs) {
        c[arc.S1][arc.S2] = arc.Poids; // Stocke le poids de l'arc (i, j)
    }

    // Étape 2 : Initialisation des vecteurs l et p
    vector<double> l(n + 1, INF);  // Vecteur des distances, initialisé à ∞
    vector<int> p(n + 1, -1);      // Vecteur des prédécesseurs, initialisé à NIL (-1)

    l[start] = 0;  // La distance du sommet de départ à lui-même est 0
    p[start] = -1; // Le prédécesseur du sommet de départ est NIL

    for (int j = 1; j <= n; j++) {
        if (c[start][j] < INF) { 
            l[j] = c[start][j];  // Initialise l avec la première ligne de la matrice des coûts
            p[j] = start;
        }
    }

    // Étape 3 : Définition des ensembles S et T
    set<int> S = {start}; // S commence avec {1}
    set<int> T;           // T contient tous les sommets sauf le départ
    for (int j = 1; j <= n; j++) {
        if (j != start) {
            T.insert(j);
        }
    }

    // Étape 4 : Boucle principale
    while (!T.empty()) {
        // Choisir i dans T tel que l(i) est minimum
        int i = -1;
        double min_dist = INF;

        for (int j : T) {  // On regarde uniquement les sommets de T
            if (l[j] < min_dist) {
                min_dist = l[j];
                i = j;
            }
        }

        // Si aucun sommet valide n'est trouvé, on arrête
        if (i == -1) break;

        // Retirer i de T et l'ajouter à S
        T.erase(i);
        S.insert(i);

        // Étape 5 : Mise à jour des distances (relaxation)
        for (int j : T) {  // On met à jour seulement les voisins dans T
            if (c[i][j] < INF && l[j] > l[i] + c[i][j]) {
                l[j] = l[i] + c[i][j];
                p[j] = i;
            }
        }
    }

    return {l, p};
}

#endif // DIJKSTRA_HPP
