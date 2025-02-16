#include "arc_graph.hpp"
using namespace std;
int main() {
    cout << "==== TEST GRAPHE ====" << std::endl;
    Graph g = {
        {1, 2, 15}, {1, 5, 4}, {3, 2, 3}, {3, 4, 2}, {4, 1, 10}, {4, 2, 3}, {5, 3, 7}, {5, 4, 5}
    };
    cout << "Nombre de sommets : " << g.nombreSommets << endl;
    //cout << "Arcs : " << g.listeArcs << endl; pas de méthode implémentée pour afficher liste d'arcs pour l'instantgit
    cout << "Voisins de 4 : " << g.voisins(4) << endl;
    cout << "Successeurs de 4 : " << g.successeurs(4) << endl;
    cout << "Prédécesseurs de 4 : " << g.predecesseurs(4) << endl;
    
    cout << "Voisins de 2 : " << g.voisins(2) << endl;
    cout << "Successeurs de 2 : " << g.successeurs(2) << endl;
    cout << "Prédécesseurs de 2 : " << g.predecesseurs(2) << endl;

    return 0;
}

