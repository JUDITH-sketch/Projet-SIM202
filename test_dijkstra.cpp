#include <iostream>
#include "arc_graph.hpp"
#include "dijkstra.hpp"

int main() {
    // Définition du graphe
    Graph g = {
        {1, 2, 15}, {1, 5, 4}, {3, 2, 3}, {3, 4, 2}, {4, 1, 10},
        {4, 2, 3}, {5, 3, 7}, {5, 4, 5}
    };

    Graph g1 = {
        {1, 5, 0.7}, {5, 1 , 0.7}, {1, 4, 1.58}, {4, 1, 1.58}, {1, 2, 1.58},
        {2, 1, 1.58}, {5, 4, 1}, {4, 5, 1}, {4, 3, 1}, {3, 4, 1}, {3, 2, 1}, {2, 3, 1}, {5, 2, 1}, {2, 5, 1}, {4, 6, 0.7}, {6, 4, 0.7}, {3, 6 ,0.7}, {6, 3, 0.7}
    };

    // Exécuter Dijkstra à partir du sommet 1
    auto [l, p] = dijkstra(g1, 1);

    // Affichage des distances minimales
    std::cout << "Distances minimales (l) :\n";
    for (size_t i = 1; i <= g1.nombreSommets; i++) {
        std::cout << "l[" << i << "] = " << l[i] << "\n";
    }

    // Affichage des prédécesseurs
    std::cout << "\nPrédécesseurs (p) :\n";
    for (size_t i = 1; i <= g1.nombreSommets; i++) {
        std::cout << "p[" << i << "] = " << p[i] << "\n";
    }

    return 0;
}
