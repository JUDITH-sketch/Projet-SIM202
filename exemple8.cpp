//===============================================================
//                    trou de souris
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
    Sommet N(6, 2);  // Point d'arrivée en haut à gauche

    // ========== Définition des Sommets ==========
    
    Sommet B(0,1),C(4,1),D(4,0),E(0,0),F(1,1),G(1,4),H(0,4),I(3,1),J(3,4),K(4,4),L(0,5),M(4,5);

    Obstacle O1({B,C,D,E});
    Obstacle O2({H,G,F,B});
    Obstacle O3({J,K,C,I});
    Obstacle O4({L,M,K,H});
    

    // Création des Gobstacles
    Gobstacle G1(O1, 1);
    Gobstacle G2(O2, 2);
    Gobstacle G3(O3, 3);
    Gobstacle G4(O4, 4);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, N, {G1, G2, G3, G4});
    cout << "====== Graphe terminé ======\n\n";
   
    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, N);

    return 0;
}