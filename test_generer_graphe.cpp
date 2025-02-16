#include <iostream>
#include "generer_graphe.hpp"
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "dijkstra.hpp"

using namespace std;

int main() {
    // ========== Initialisation des Sommets ==========
    Sommet A(1, 4);
    Sommet B(7, 2);

    // ========== Définition de l'Obstacle ==========
    Sommet S11(3, 0), S12(6, 0), S13(6, 3), S14(3, 3);
    Obstacle O1({S11, S12, S13, S14});
    Gobstacle G01(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G01});
    cout << "====== Graphe terminé ======\n\n";

    // Extract the graph, nodes, and references
    Graph& G = graphData.G;
    vector<Sommet>& list_sommet = graphData.list_sommet;
    vector<int>& list_indice = graphData.list_indice;
    vector<int>& list_ref = graphData.list_ref;

    // ========== Affichage des Sommets ==========
    cout << "Liste des Sommets :\n";
    for (size_t i = 0; i < list_sommet.size(); i++) {
        cout << "Sommet " << list_indice[i] << " : (" 
             << list_sommet[i].x << ", " << list_sommet[i].y 
             << "), Réf: " << list_ref[i] << "\n";
    }
    cout << "\n";

    // ========== Affichage des Voisins ==========
    cout << "Voisins du point de départ (0) :\n";
    cout << "   " << G.voisins(0) << "\n\n";

    cout << "Voisins du point d'arrivée (" << list_indice.back() << ") :\n";
    cout << "   " << G.voisins(list_indice.back()) << "\n\n";

    cout << "Voisins d'un point obstacle (2) :\n";
    cout << "   " << G.voisins(2) << "\n\n";

    cout << "Voisins d'un point obstacle (1) :\n";
    cout << "   " << G.voisins(1) << "\n\n";

    cout << "====== Affichage du Graphe ======\n";
    cout << G << "\n\n";

    // ========== Exécution de Dijkstra ==========
    cout << "====== Test de Dijkstra ======\n";
    cout << "Début du test...\n";
    
    auto [l, p] = dijkstra(G, 0);
    
    cout << "Test terminé !\n\n";

    // ========== Affichage des Distances Minimales ==========
    cout << "Distances minimales (l) :\n";
    for (size_t i = 0; i < G.nombreSommets; i++) {
        cout << "   l[" << i << "] = " << l[i] << "\n";
    }

    // ========== Affichage des Prédécesseurs ==========
    cout << "\nPrédécesseurs (p) :\n";
    for (size_t i = 0; i < G.nombreSommets; i++) {
        cout << "   p[" << i << "] = " << p[i] << "\n";
    }

    cout << "\nFin du programme\n";

    return 0;
}
