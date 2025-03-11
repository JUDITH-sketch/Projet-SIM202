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

// Fonction pour vérifier si deux segments se croisent
bool segments_croisent(const Sommet& p1, const Sommet& q1, const Sommet& p2, const Sommet& q2) {
    // Orientation des triplets (p1, q1, p2) et (p1, q1, q2)
    auto orientation = [](const Sommet& p, const Sommet& q, const Sommet& r) {
        double val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
        if (fabs(val) < 1e-10) return 0;  // colinéaires
        return (val > 0) ? 1 : 2;  // 1 pour sens horaire, 2 pour sens antihoraire
    };
    
    // Vérifier si le point q est sur le segment pr
    auto sur_segment = [](const Sommet& p, const Sommet& q, const Sommet& r) {
        return q.x <= max(p.x, r.x) && q.x >= min(p.x, r.x) &&
               q.y <= max(p.y, r.y) && q.y >= min(p.y, r.y);
    };
    
    int o1 = orientation(p1, q1, p2);
    int o2 = orientation(p1, q1, q2);
    int o3 = orientation(p2, q2, p1);
    int o4 = orientation(p2, q2, q1);
    
    // Cas général d'intersection
    if (o1 != o2 && o3 != o4) return true;
    
    // Cas spéciaux
    if (o1 == 0 && sur_segment(p1, p2, q1)) return true;
    if (o2 == 0 && sur_segment(p1, q2, q1)) return true;
    if (o3 == 0 && sur_segment(p2, p1, q2)) return true;
    if (o4 == 0 && sur_segment(p2, q1, q2)) return true;
    
    return false;
}

// Fonction pour vérifier si deux polygones se chevauchent
bool polygones_se_chevauchent(const vector<Sommet>& poly1, const vector<Sommet>& poly2) {
    // Vérifier si un segment de poly1 croise un segment de poly2
    for (size_t i = 0; i < poly1.size(); i++) {
        size_t j = (i + 1) % poly1.size();
        
        for (size_t k = 0; k < poly2.size(); k++) {
            size_t l = (k + 1) % poly2.size();
            
            if (segments_croisent(poly1[i], poly1[j], poly2[k], poly2[l])) {
                return true;
            }
        }
    }
    
    // Vérifier si un polygone est à l'intérieur de l'autre
    auto point_dans_polygone = [](const Sommet& point, const vector<Sommet>& poly) {
        bool dedans = false;
        for (size_t i = 0, j = poly.size() - 1; i < poly.size(); j = i++) {
            if (((poly[i].y > point.y) != (poly[j].y > point.y)) &&
                (point.x < (poly[j].x - poly[i].x) * (point.y - poly[i].y) / 
                 (poly[j].y - poly[i].y) + poly[i].x)) {
                dedans = !dedans;
            }
        }
        return dedans;
    };
    
    // Vérifier si un point de poly1 est dans poly2
    for (const auto& point : poly1) {
        if (point_dans_polygone(point, poly2)) {
            return true;
        }
    }
    
    // Vérifier si un point de poly2 est dans poly1
    for (const auto& point : poly2) {
        if (point_dans_polygone(point, poly1)) {
            return true;
        }
    }
    
    return false;
}

int main() {
    // Initialisation du générateur de nombres aléatoires
    srand(time(0));
    
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    Sommet A(0, 0);  // Point de départ
    Sommet B(100, 100);  // Point d'arrivée
    
    // ========== Définition des Obstacles (Non Chevauchants) ==========
    
    // Nombre d'obstacles à générer
    int nb_obstacles = 5;
    
    // Paramètres de l'espace
    double largeur_espace = 100;
    double hauteur_espace = 100;
    
    // Paramètres pour les obstacles
    double rayon_moyen_min = 5;
    double rayon_moyen_max = 15;
    double irregularite = 0.4; // Entre 0 et 1
    double pointes = 0.2; // Entre 0 et 1
    
    // Vecteur pour stocker les obstacles
    vector<Obstacle> obstacles;
    vector<vector<Sommet>> polygones;
    
    // Générer nb_obstacles obstacles sans chevauchement
    int max_tentatives = 100;  // Nombre maximal d'essais pour placer un obstacle
    
    for (int i = 0; i < nb_obstacles; i++) {
        bool valide = false;
        int tentatives = 0;
        vector<Sommet> nouveau_polygone;
        
        while (!valide && tentatives < max_tentatives) {
            tentatives++;
            
            // Générer un nouveau polygone aléatoire
            double centre_x = ((double)rand() / RAND_MAX) * largeur_espace;
            double centre_y = ((double)rand() / RAND_MAX) * hauteur_espace;
            double rayon_moyen = rayon_moyen_min + ((double)rand() / RAND_MAX) * (rayon_moyen_max - rayon_moyen_min);
            
            int min_sommets = 3;
            int max_sommets = 15;  // Moins de sommets pour garder les obstacles simples
            int nombre_sommets = min_sommets + rand() % (max_sommets - min_sommets + 1);
            
            nouveau_polygone = generer_polygone(centre_x, centre_y, rayon_moyen, irregularite, pointes, nombre_sommets);
            
            // Vérifier s'il chevauche un obstacle existant
            valide = true;
            for (const auto& poly : polygones) {
                if (polygones_se_chevauchent(nouveau_polygone, poly)) {
                    valide = false;
                    break;
                }
            }
        }
        
        if (valide) {
            polygones.push_back(nouveau_polygone);
            obstacles.push_back(Obstacle(nouveau_polygone));
            cout << "Obstacle " << i + 1 << " créé avec " << nouveau_polygone.size() << " sommets" << endl;
        } else {
            cout << "Impossible de placer l'obstacle " << i + 1 << " après " << max_tentatives << " tentatives" << endl;
        }
    }
    
    // Création des Gobstacles
    vector<Gobstacle> gobstacles;
    for (size_t i = 0; i < obstacles.size(); i++) {
        gobstacles.push_back(Gobstacle(obstacles[i], i + 1));
    }
    

        // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    

    
    cout << "Pour intégrer ces obstacles à votre graphe et algorithme de chemin:" << endl;
    cout << "1. Adaptez votre fonction to_graph_Naive_3 pour accepter un vecteur de Gobstacles" << endl;
    cout << "2. Modifiez l'appel de Dijkstra selon sa signature dans votre code" << endl;
    cout << "====== Graphe non construit (à adapter) ======\n\n";
    
    // ========== Exportation des Obstacles ==========
   
    
    // Exporter les obstacles pour visualisation
    ofstream obstacles_file("obstacles_data.txt");
    if (obstacles_file.is_open()) {
        // Écrire les obstacles
        for (size_t i = 0; i < polygones.size(); i++) {
            obstacles_file << "# Obstacle " << i + 1 << endl;
            for (const auto& sommet : polygones[i]) {
                obstacles_file << sommet.x << " " << sommet.y << endl;
            }
            // Fermer le polygone en répétant le premier sommet
            if (!polygones[i].empty()) {
                obstacles_file << polygones[i][0].x << " " << polygones[i][0].y << endl;
            }
            obstacles_file << endl;
        }
        
        // Écrire le point de départ et d'arrivée
        obstacles_file << "# Points de départ et d'arrivée" << endl;
        obstacles_file << A.x << " " << A.y << endl;
        obstacles_file << B.x << " " << B.y << endl;
        
        obstacles_file.close();
        cout << "Données des obstacles exportées dans obstacles_data.txt" << endl;
    }

    // Visualisation avec gnuplot si disponible
    cout << "\n===== Tentative de visualisation avec gnuplot =====\n";
    FILE* gnuplot = popen("gnuplot -persist", "w");
    if (gnuplot) {
        fprintf(gnuplot, "set title 'Polygones d'obstacles non chevauchants'\n");
        fprintf(gnuplot, "set xlabel 'X'\n");
        fprintf(gnuplot, "set ylabel 'Y'\n");
        fprintf(gnuplot, "set size ratio -1\n");
        fprintf(gnuplot, "set grid\n");
        
        // Définir les limites pour voir tous les obstacles
        fprintf(gnuplot, "set xrange [0:%f]\n", largeur_espace * 1.1);
        fprintf(gnuplot, "set yrange [0:%f]\n", hauteur_espace * 1.1);
        
        // Tracer les obstacles en couleurs différentes
        for (size_t i = 0; i < polygones.size(); i++) {
            if (i == 0) {
                fprintf(gnuplot, "plot 'obstacles_data.txt' index %zu with filledcurves closed lt rgb '#%06X' title 'Obstacle %zu'", 
                        i, 0x800000 + i * 0x100000 / polygones.size(), i + 1);
            } else {
                fprintf(gnuplot, ", 'obstacles_data.txt' index %zu with filledcurves closed lt rgb '#%06X' title 'Obstacle %zu'", 
                        i, 0x800000 + i * 0x100000 / polygones.size(), i + 1);
            }
        }
        
        // Ajouter les points de départ et d'arrivée
        fprintf(gnuplot, ", 'obstacles_data.txt' index %zu using 1:2:(%f):(%f):(0x00FF00) with circles fill solid title 'Départ'", 
                polygones.size(), 2.0, 2.0);
        fprintf(gnuplot, ", 'obstacles_data.txt' index %zu using 1:2:(%f):(%f):(0xFF0000) with circles fill solid title 'Arrivée' skip 1", 
                polygones.size(), 2.0, 2.0);
        fprintf(gnuplot, "\n");
        
        pclose(gnuplot);
        cout << "Visualisation effectuée avec gnuplot" << endl;
    } else {
        cout << "Impossible d'ouvrir gnuplot pour la visualisation" << endl;
    }

    return 0;
}