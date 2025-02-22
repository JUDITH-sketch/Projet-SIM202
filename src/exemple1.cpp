//=======================================================================
//                    un obstacle carré simple
//=======================================================================


#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"  // Assure-toi d'avoir un fichier d'en-tête pour cette fonction

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

    // ========== Affichage des trois listes ==========
    afficher_listes(graphData);

    // ========== Exportation du Graphe ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}
