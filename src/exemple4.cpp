#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"  // Assure-toi d'avoir un fichier d'en-tête pour cette fonction

using namespace std;

int main() {
    // ========== Initialisation des Sommets ==========
    Sommet A(-1.5, 1.5);
    Sommet B(1.5, 1.5);

    // ========== Définition de l'Obstacle ==========
    Sommet S1(-0.5, 2.5), S2(-0.5, -1), S3(0.5, 1), S4(0.5, 2.5), S5(0.32,2.71), S6(0.1, 2.8), S7(-0.14, 2.8), S8(-0.28, 2.7), S9(-0.42, 2.54);
    Obstacle O1({S1, S2, S3, S4, S5, S6, S7, S8, S9});
    Gobstacle G01(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G01});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des trois listes ==========
    afficher_listes(graphData);

    // ========== Exportation du Graphe ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}
