#include <iostream>
#include "arc-graph.hpp"
#include "dijkstra.hpp"

int main() {
    // Définition du graphe
    Graph g = {
        {1, 2, 15}, {1, 5, 4}, {3, 2, 3}, {3, 4, 2}, {4, 1, 10},
        {4, 2, 3}, {5, 3, 7}, {5, 4, 5}
    };

    // Exécuter Dijkstra à partir du sommet 1
    auto [l, p] = dijkstra(g, 1);

    // Affichage des distances minimales
    std::cout << "Distances minimales (l) :\n";
    for (size_t i = 1; i <= g.nombreSommets; i++) {
        std::cout << "l[" << i << "] = " << l[i] << "\n";
    }

    // Affichage des prédécesseurs
    std::cout << "\nPrédécesseurs (p) :\n";
    for (size_t i = 1; i <= g.nombreSommets; i++) {
        std::cout << "p[" << i << "] = " << p[i] << "\n";
    }

    return 0;
}
