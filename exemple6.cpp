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
#include <random>   // Pour distribution normale

using namespace std;

// Fonction pour limiter une valeur dans un intervalle
double clip(double value, double lower, double upper) {
    return min(upper, max(value, lower));
}

// Génère les angles de division d'une circonférence de façon aléatoire
vector<double> random_angle_steps(int steps, double irregularity) {
    vector<double> angles;
    double lower = (2 * M_PI / steps) - irregularity;
    double upper = (2 * M_PI / steps) + irregularity;
    double cumsum = 0;
    
    for (int i = 0; i < steps; i++) {
        double angle = lower + (upper - lower) * ((double)rand() / RAND_MAX);
        angles.push_back(angle);
        cumsum += angle;
    }
    
    // Normaliser les pas pour que le point 0 et le point n+1 soient identiques
    cumsum /= (2 * M_PI);
    for (int i = 0; i < steps; i++) {
        angles[i] /= cumsum;
    }
    
    return angles;
}

// Fonction pour générer un polygone avec irrégularités contrôlées
vector<Sommet> generer_polygone(double centre_x, double centre_y, double rayon_moyen, 
                             double irregularite, double pointes, int nb_sommets) {
    // Vérification des paramètres
    irregularite = clip(irregularite, 0.0, 1.0);
    pointes = clip(pointes, 0.0, 1.0);
    
    // Calcul des paramètres dérivés
    irregularite *= 2 * M_PI / nb_sommets;
    pointes *= rayon_moyen;
    
    // Générer les pas angulaires
    vector<double> angle_steps = random_angle_steps(nb_sommets, irregularite);
    
    // Générer les points
    vector<Sommet> points;
    double angle = ((double)rand() / RAND_MAX) * 2 * M_PI;
    
    random_device rd;
    mt19937 gen(rd());
    normal_distribution<> dist(rayon_moyen, pointes);
    
    for (int i = 0; i < nb_sommets; i++) {
        double radius = clip(dist(gen), 0.0, 2 * rayon_moyen);
        double x = centre_x + radius * cos(angle);
        double y = centre_y + radius * sin(angle);
        points.push_back(Sommet(x, y));
        angle += angle_steps[i];
    }
    
    return points;
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(0));
    
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(0, 0);  // Point de départ
    Sommet B(100, 100);  // Point d'arrivée
    
    // ========== Définition des Obstacles (Non Chevauchants) ==========
    
    // Paramètres pour la génération du polygone
    double centre_x = 50;
    double centre_y = 50;
    double rayon_moyen = 30;
    double irregularite = 0.4; // Entre 0 et 1
    double pointes = 0.2; // Entre 0 et 1
    
    // Définition du nombre de sommets
    int min = 3;
    int max = 49; // Maximum inférieur à 50
    int nombre = min + rand() % (max - min + 1);
    
    // Générer le polygone
    vector<Sommet> sommets_polygone = generer_polygone(centre_x, centre_y, rayon_moyen, irregularite, pointes, nombre);
    
    // Création de l'obstacle avec les sommets générés
    Obstacle O1(sommets_polygone);
    
    std::cout << "Nombre de sommets: " << nombre << std::endl;
    
    // Création du Gobstacle
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