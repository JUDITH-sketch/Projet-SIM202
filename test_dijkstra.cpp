#include <iostream>
#include "arc_graph.hpp"
#include "dijkstra.hpp"

int main() {
    // Premier graphe (de l'énoncé), orienté
    Graph g = {
        {1, 2, 15}, {1, 5, 4}, {3, 2, 3}, {3, 4, 2}, {4, 1, 10},
        {4, 2, 3}, {5, 3, 7}, {5, 4, 5}
    };

    // Graphe de test "obstacle carré", non orienté
    Graph g1 = {
        {1, 5, 0.7}, {5, 1 , 0.7}, {1, 4, 1.58}, {4, 1, 1.58}, {1, 2, 1.58},
        {2, 1, 1.58}, {5, 4, 1}, {4, 5, 1}, {4, 3, 1}, {3, 4, 1}, {3, 2, 1}, {2, 3, 1}, 
        {5, 2, 1}, {2, 5, 1}, {4, 6, 0.7}, {6, 4, 0.7}, {3, 6 ,0.7}, {6, 3, 0.7}
    };

    // Graphe de la page Wikipedia, non orienté
    Graph g2 = {
        {1, 2, 7}, {2, 1, 7}, {1, 3, 9}, {3, 1, 9}, {1, 6, 14}, {6, 1, 14},
        {2, 3, 10}, {3, 2, 10}, {2, 4, 15}, {4, 2, 15}, {3, 4, 11}, {4, 3, 11},
        {3, 6, 2}, {6, 3, 2}, {4, 5, 6}, {5, 4, 6}, {5, 6, 9}, {6, 5, 9}
    };

    // Fonction pour exécuter Dijkstra et afficher les résultats
    auto run_dijkstra = [&](const Graph& graph, int start_node, const std::string& title) {
        std::cout << "===============================\n";
        std::cout << "Résultats de Dijkstra pour: " << title << "\n";
        std::cout << "===============================\n";

        int numNodes = graph.nombreSommets;  // Utilisation de la méthode `nombreSommets()`
        auto [l, p] = dijkstra(graph, start_node);

        std::cout << "Distances minimales (l) :\n";
        for (int i = 1; i <= numNodes; i++) {
            std::cout << "l[" << i << "] = " << l[i] << "\n";
        }

        std::cout << "\nPrédécesseurs (p) :\n";
        for (int i = 1; i <= numNodes; i++) {
            std::cout << "p[" << i << "] = " << p[i] << "\n";
        }

        std::cout << "\n";
    };

    // Exécution des tests
    run_dijkstra(g, 1, "Graphe de l'énoncé");
    run_dijkstra(g1, 1, "Graphe test 'obstacle carré'");
    run_dijkstra(g2, 1, "Graphe de la page Wikipedia");

    return 0;
}
