#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"

using namespace std;

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(2, 8);  // Point de départ à droite
    Sommet B(8, 2);  // Point d'arrivée en haut à gauche

    // ========== Définition des Obstacles (Non Chevauchants) ==========
    

    // Premier obstacle (pentagone au milieu, oblige à un contournement)
    Sommet S1(4, 5), S2(5, 6), S3(6, 5.5), S4(6, 4), S5(4.5, 4); // ne fonctionne pas pour s4(5.5,4)
    Obstacle O1({S1, S2, S3, S4, S5});

    //Second obstacle
    Sommet S6(7, 3), S7(8, 3), S8(8, 4), S9(7, 4);
    Obstacle O2({S6, S7, S8, S9});


    // Création des Gobstacles
    Gobstacle G1(O1, 1);
    Gobstacle G2(O2, 2);


    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G1, G2});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}
