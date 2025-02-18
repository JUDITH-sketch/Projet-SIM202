#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"

using namespace std;

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(-1.71, 1.71);  // Point de départ à droite
    Sommet B(0.7, 0.9);  // Point d'arrivée en haut à gauche

    // ========== Définition des Obstacles (Non Chevauchants) ==========
    

    // Premier obstacle (angle droit, oblige à un contournement)
    Sommet S1(-1.5, 2), S2(-1, 2), S3(-1, 0.32), S4(0.99, 0.3), S5(0.99, -0.1), S6(-1.51, -0.09);
    Obstacle O1({S1, S2, S3, S4, S5, S6});

    //Second obstacle (losange)
    Sommet S7(-0.51, 0.81), S8(-0.31, 1.6), S9(0.5, 1.8), S10(0.3, 1);
    Obstacle O2({S7, S8, S9, S10});

    //Troisème obstacle (pentagone)
    Sommet S11(-0.2, 1.81), S12(0.2, 2.09), S13(0.05, 2.56), S14(-0.43, 2.56), S15(-0.59, 2.1);
    Obstacle O3({S11, S12, S13, S14, S15});


    // Création des Gobstacles
    Gobstacle G1(O1, 1);
    Gobstacle G2(O2, 2);
    Gobstacle G3(O3, 3);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G1, G2, G3});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}