//===============================================================
//                    obstacle carré
//                  alignement 3 points
//===============================================================

#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"  // Assure-toi d'avoir un fichier d'en-tête pour cette fonction

using namespace std;

int main() {
    // ========== Initialisation des Sommets ==========
    Sommet A(2, 4);
    Sommet B(6, 0);

    // ========== Définition de l'Obstacle ==========
    Sommet S11(3, 1), S12(5, 1), S13(5, 3), S14(3, 3);
    Obstacle O1({S11, S12, S13, S14});
    Gobstacle G01(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, B, {G01});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des trois listes ==========
    afficher_listes(graphData);

    // ========== Exportation du Graphe ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}
