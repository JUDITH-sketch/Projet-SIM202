//===============================================================
//                    error 404
//              itinerary not found
//===============================================================


#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"

using namespace std;

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(2, 2);  // Point de départ à droite
    Sommet N(4, 2);  // Point d'arrivée en haut à gauche

    // ========== Définition des Sommets ==========
    
    Sommet G(1,3),J(3,3),I(3,1),F(1,1);

    Obstacle O1({G,J,I,F});
    

    // Création des Gobstacles
    Gobstacle G1(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, N, {G1});
    cout << "====== Graphe terminé ======\n\n";
   
    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, N);

    return 0;
}