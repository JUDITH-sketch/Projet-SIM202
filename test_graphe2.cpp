#include <iostream>
#include "arc-graph.hpp"

using namespace std;

int main() {
    cout << "==== TEST GRAPHE ====" << endl;

    // Création du graphe avec A, B et un obstacle carré
    Graph g;
    
    int A = g.ajouterSommet(Sommet(-1, 3.0/4.0), -1);
    int B = g.ajouterSommet(Sommet(2, 3.0/4.0), -1);

    g.ajouterObstacle(Obstacle({
        Sommet(0, 0), Sommet(1, 0), Sommet(1, 1), Sommet(0, 1)
    }));

    // Génération automatique des arcs
    g.genererArcs();

    // Affichage du nombre de sommets
    cout << "Nombre de sommets : " << g.nombreSommets << endl;

    // Affichage des arcs
    cout << "Liste des arcs :" << endl;
    for (const auto& arc : g.listeArcs) {
        cout << arc.pred() << " -> " << arc.succ() << " (Poids: " << arc.poids() << ")" << endl;
    }

    // Test des fonctions voisins, successeurs et prédécesseurs sur 4 et 2
    cout << "Voisins de 4 : " << g.voisins(0) << endl;
    cout << "Successeurs de 4 : " << g.successeurs(0) << endl;
    cout << "Prédécesseurs de 4 : " << g.predecesseurs(0) << endl;

    cout << "Voisins de 2 : " << g.voisins(1) << endl;
    cout << "Successeurs de 2 : " << g.successeurs(1) << endl;
    cout << "Prédécesseurs de 2 : " << g.predecesseurs(1) << endl;

    return 0;
}
