#include <iostream>
#include "sommet_graph_v2.hpp"
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "dijkstra.hpp"

using namespace std;

int main() {
    // ========== Initialisation des Sommets ==========
    Sommet A(1, 4);
    Sommet B(7, 2);

    Node An(A, 0);
    Node Bn(B, 1);

    // ========== Définition de l'Obstacle ==========
    Sommet S11(3, 0), S12(6, 0), S13(6, 3), S14(3, 3);
    Obstacle O1({S11, S12, S13, S14});
    Gobstacle G01(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    Graph G = to_graph_Naive_2(A, B, {G01});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Voisins ==========
    cout << "Voisins du point de départ (0) :\n";
    cout << "   " << G.voisins(0) << "\n\n";

    cout << "Voisins du point d'arrivée (" << G.nombreSommets - 1 << ") :\n";
    cout << "   " << G.voisins(G.nombreSommets - 1) << "\n\n";

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
