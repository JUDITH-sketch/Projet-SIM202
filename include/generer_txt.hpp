#ifndef GENERER_TXT_HPP
#define GENERER_TXT_HPP

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "generer_graphe.hpp"
#include "dijkstra.hpp"

using namespace std;

// Fonction pour exporter les données du graphe dans un fichier
inline void exporter_graphe_vers_fichier(const string& filename, const GraphData& graphData, const Sommet& D, const Sommet& A) {
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

    // ========= Ajout du plus court chemin =========
    // Calcul du plus court chemin avec Dijkstra
    pair<vector<double>, vector<int>> dijkstra_result = dijkstra(G, 0);
    vector<int> predecessors = dijkstra_result.second;

    // Reconstruction du chemin
    vector<Sommet> chemin_plus_court;
    int current = list_indice.back(); // Indice du sommet d'arrivée
    while (current != -1) {
        chemin_plus_court.push_back(list_sommet[current]);
        current = predecessors[current];
    }
    reverse(chemin_plus_court.begin(), chemin_plus_court.end()); // Remettre le chemin dans l'ordre correct

    // Écriture du chemin dans le fichier
    file << "CHEMIN_PLUS_COURT\n";
    for (const auto& point : chemin_plus_court) {
        file << point.x << " " << point.y << "\n";
    }

    file.close();
    cout << "Données du graphe exportées avec succès dans " << filename << endl;
}

// Fonction pour afficher les trois listes
inline void afficher_listes(const GraphData& graphData) {
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

#endif // GENERER_TXT_HPP
