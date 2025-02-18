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
    Sommet S1(-0.5, 0), S2(0.5, 0), S3(0.5, 3), S4(-0.5, 3);
    Obstacle O1({S1, S2, S3, S4});
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
