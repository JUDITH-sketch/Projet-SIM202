#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"
#include <iostream>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()




using namespace std;

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(0, 0);  // Point de départ à droite
    Sommet B(100, 100);  // Point d'arrivée en haut à gauche

    // ========== Définition des Obstacles (Non Chevauchants) ==========
    
    // Définition du nombre de sommets
    srand(time(0)); // Initialisation du générateur de nombres aléatoires

    int min = 3;
    int nombre = min + rand(); // Génère un nombre aléatoire supérieur ou égal à min

    std::cout << "Nombre de sommets >= " << min << " : " << nombre << std::endl;

    // Définition du vecteur de sommets S
    vector<Sommet> S;
    for(int i = 0; i < nombre; i++){
        S.push_back(Sommet(rand(), rand()));
    };


    // Premier obstacle (angle droit, oblige à un contournement)

    Obstacle O1({S});




    // Création des Gobstacles
    Gobstacle G1(O1, 1);
    

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G1});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}