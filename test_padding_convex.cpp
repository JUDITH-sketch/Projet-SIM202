
#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"

using namespace std;

int main() {

    
    Sommet e1(1,0), e2(0,1);
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

    O3.slide(0.5*e2);
    O3.inversion();

    A=A*3;
    B=B*3;
    O1.grow(3);
    O2.grow(3);
    O3.grow(3);
    
    cout << "\n===== Construction du Padding =====\n";
    Obstacle PO1 = O1.Paddington(3,0.2);
    Obstacle PO2 = O2.Paddington(3,0.2);
    Obstacle PO3 = O3.Paddington(3,0.2);
    cout << "\n===== Fin du Padding =====\n";
    Gobstacle G01(PO1, 1);
    Gobstacle G02(PO2, 2);
    Gobstacle G03(PO3, 3);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, B, {G01,G02,G03});
    cout << "====== Graphe terminé ======\n\n";

    // Extract the graph, nodes, and references
    Graph& G = graphData.G;
    vector<Sommet>& list_sommet = graphData.list_sommet;
    vector<int>& list_indice = graphData.list_indice;
    vector<int>& list_ref = graphData.list_ref;

    // // ========== Affichage des Sommets ==========
    // cout << "Liste des Sommets :\n";
    // for (size_t i = 0; i < list_sommet.size(); i++) {
    //     cout << "Sommet " << list_indice[i] << " : (" 
    //          << list_sommet[i].x << ", " << list_sommet[i].y 
    //          << "), Réf: " << list_ref[i] << "\n";
    // }
    // cout << "\n";

    // ========== Exécution de Dijkstra ==========
    // cout << "====== Test de Dijkstra ======\n";
    // cout << "Début du test...\n";
    
    // auto [l, p] = dijkstra(G, 0);
    // cout<<"Dijkstra complete \n";
    // ========== Affichage des trois listes ==========
    afficher_listes(graphData);

    // ========== Exportation du Graphe ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);
  
    cout << "Test terminé !\n\n";

    // // ========== Affichage des Distances Minimales ==========
    // cout << "Distances minimales (l) :\n";
    // for (size_t i = 0; i < G.nombreSommets; i++) {
    //     cout << "   l[" << i << "] = " << l[i] << "\n";
    // }

    // // ========== Affichage des Prédécesseurs ==========
    // cout << "\nPrédécesseurs (p) :\n";
    // for (size_t i = 0; i < G.nombreSommets; i++) {
    //     cout << "   p[" << i << "] = " << p[i] << "\n";
    // }

    cout << "\nFin du programme\n";

    return 0;
}
