#include <iostream>
#include <fstream>
#include "sommet_graph_v2.hpp"
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "dijkstra.hpp"

using namespace std;

// Fonction pour exporter les données du graphe dans un fichier
void export_graph_to_file(const string& filename, const GraphData& graphData, const Sommet& D, const Sommet& A) {
    ofstream file(filename);

    if (!file) {
        cerr << "Erreur : Impossible d'ouvrir le fichier " << filename << endl;
        return;
    }

    // Extraction des données du graphe
    const Graph& G = graphData.G;
    const vector<Sommet>& list_sommet = graphData.list_sommet;
    const vector<int>& list_indice = graphData.list_indice;
    const vector<int>& list_ref = graphData.list_ref;

    // Écriture du point de départ et d'arrivée
    file << "DEBUT " << D.x << " " << D.y << "\n";
    file << "FIN " << A.x << " " << A.y << "\n";

    // Écriture des sommets
    file << "SOMMETS\n";
    for (size_t i = 0; i < list_sommet.size(); i++) {
        file << "SOMMET " << list_indice[i] << " " << list_sommet[i].x << " " << list_sommet[i].y << " " << list_ref[i] << "\n";
    }

    // Écriture des arêtes
    file << "ARCS\n";
    for (const auto& arc : G.listeArcs) {
        file << "ARC " << arc.pred() << " " << arc.succ() << "\n";
    }

    file.close();
    cout << "Données du graphe exportées avec succès dans " << filename << endl;
}

// Fonction pour afficher les trois listes
void afficher_listes(const GraphData& graphData) {
    cout << "\n===== Liste des Indices =====\n";
    for (int i : graphData.list_indice) {
        cout << i << " ";
    }
    cout << "\n";

    cout << "\n===== Liste des Sommets =====\n";
    for (const Sommet& s : graphData.list_sommet) {
        cout << "(" << s.x << ", " << s.y << ") ";
    }
    cout << "\n";

    cout << "\n===== Liste des Références =====\n";
    for (int r : graphData.list_ref) {
        cout << r << " ";
    }
    cout << "\n";
}

int main() {
    // ========== Initialisation des Sommets ==========
    Sommet A(1, 4);
    Sommet B(7, 2);

    // ========== Définition de l'Obstacle ==========
    Sommet S11(3, 0), S12(6, 0), S13(6, 3), S14(3, 3);
    Obstacle O1({S11, S12, S13, S14});
    Gobstacle G01(O1, 1);

    // ========== Construction du Graphe ==========
    cout << "\n===== Construction du Graphe =====\n";
    GraphData graphData = to_graph_Naive_2(A, B, {G01});
    cout << "====== Graphe terminé ======\n\n";

    // ========== Affichage des trois listes ==========
    afficher_listes(graphData);

    // ========== Exportation du Graphe ==========
    export_graph_to_file("graph_data.txt", graphData, A, B);

    return 0;
}
