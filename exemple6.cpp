#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"
#include <iostream>
#include <cstdlib>  // Pour rand() et srand()
#include <ctime>    // Pour time()
#include <vector>
#include <algorithm> // Pour sort
#include <cmath>    // Pour atan2

using namespace std;

// Fonction pour calculer l'angle polaire
// Adaptation en fonction de la structure de votre classe Sommet
double angle_polaire(const Sommet& point, const Sommet& centre) {
    // Supposons que Sommet a des membres publics x et y
    return atan2(point.y - centre.y, point.x - centre.x);
}

// Fonction pour générer un polygone convexe
vector<Sommet> generer_polygone_convexe(int n, double centre_x, double centre_y, double rayon_min, double rayon_max) {
    vector<Sommet> points;
    vector<double> angles;
    
    // Générer n points aléatoires autour du centre
    for (int i = 0; i < n; i++) {
        double angle = (double)rand() / RAND_MAX * 2 * M_PI;
        double rayon = rayon_min + (double)rand() / RAND_MAX * (rayon_max - rayon_min);
        double x = centre_x + rayon * cos(angle);
        double y = centre_y + rayon * sin(angle);
        points.push_back(Sommet(x, y));
        angles.push_back(angle);
    }
    
    // Trier les points par angle polaire
    Sommet centre(centre_x, centre_y);
    sort(points.begin(), points.end(), [centre](const Sommet& a, const Sommet& b) {
        return angle_polaire(a, centre) < angle_polaire(b, centre);
    });
    
    return points;
}

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(0, 0);  // Point de départ à droite
    Sommet B(100, 100);  // Point d'arrivée en haut à gauche

    // ========== Définition des Obstacles (Non Chevauchants) ==========
    
    // Définition du nombre de sommets
    srand(time(0)); // Initialisation du générateur de nombres aléatoires

    int min = 3;
    int max = 49; // Maximum number less than 50
    int nombre = min + rand() % (max - min + 1);
    
    // Génération d'un polygone convexe
    double centre_x = 50; // Centre du polygone
    double centre_y = 50;
    double rayon_min = 10; // Distance minimale du centre
    double rayon_max = 40; // Distance maximale du centre
    
    vector<Sommet> sommets_polygone = generer_polygone_convexe(nombre, centre_x, centre_y, rayon_min, rayon_max);
    
    // Création de l'obstacle avec les sommets générés
    Obstacle obstacle(sommets_polygone);
    
    std::cout << "Nombre de sommets >= " << min << " : " << nombre << std::endl;

    // Définition du vecteur de sommets S
    vector<Sommet> S;
    for(int i = 0; i < nombre; i++){
        int coord_x = min + rand() % (max - min+1);
        int coord_y = min + rand() % (max - min+1);
        S.push_back(Sommet(coord_x, coord_y));
    }

    // Premier obstacle (angle droit, oblige à un contournement)
    Obstacle O1(sommets_polygone); // Utiliser le polygone convexe généré


    // Création des Gobstacles
    Gobstacle G1(O1, 1);
    

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, B, {G1});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}