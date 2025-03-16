#include <iostream>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"
#include "generer_txt.hpp"

using namespace std;

int main() {
    // ========== Définition des Sommets de Départ et d'Arrivée ==========
    double xA, yA, xB, yB;

    cout << "Entrez les coordonnées du point de départ (x y) : ";
    while (!(cin >> xA >> yA)) {
        cout << "Entrée invalide ! Veuillez entrer deux nombres séparés par un espace : ";
        cin.clear(); // Réinitialise cin
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Ignore le reste de la ligne
    }

    cout << "Entrez les coordonnées du point d'arrivée (x y) : ";
    while (!(cin >> xB >> yB)) {
        cout << "Entrée invalide ! Veuillez entrer deux nombres séparés par un espace : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    Sommet A(xA, yA);
    Sommet B(xB, yB);

    // ========== Demande du Nombre d'Obstacles ==========
    int nbObstacles;
    cout << "Combien d'obstacles souhaitez-vous ajouter ? ";
    while (!(cin >> nbObstacles) || nbObstacles < 0) {
        cout << "Entrée invalide ! Veuillez entrer un nombre entier positif : ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    
    vector<pair<Obstacle, int>> obstacles;

    for (int i = 0; i < nbObstacles; i++) {
        int nbSommets;
        cout << "\nObstacle " << i+1 << " : combien de sommets ? ";
        while (!(cin >> nbSommets) || nbSommets <= 2) {
            cout << "Un obstacle doit avoir au moins 3 sommets ! Essayez encore : ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        
        vector<Sommet> sommets;
        cout << "Veuillez entrer les sommets sous la forme suivante : (x y)\n";
        for (int j = 0; j < nbSommets; j++) {
            double x, y;
            cout << "Sommet " << j+1 << " : ";
            while (!(cin >> x >> y)) {
                cout << "Entrée invalide ! Veuillez entrer deux nombres séparés par un espace : ";
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
            sommets.emplace_back(x, y);
        }
        
        Obstacle O(sommets);
        obstacles.push_back(make_pair(O, i+1));
    }
    
    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_3(A, B, obstacles);
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des Sommets ==========
    afficher_listes(graphData);

    // ========== Exportation ==========
    exporter_graphe_vers_fichier("graph_data.txt", graphData, A, B);

    return 0;
}
