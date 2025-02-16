#include <iostream>
#include "sommet_graph_v1.hpp"
#include "arc_graph.hpp"
#include "obstacle.hpp"
#include "dijkstra.hpp"

int main(){

Sommet A(0,2);
Sommet B(9,2);

Node An (A,0);
Node Bn (B,1);

Sommet S11(1,0), S12(4,0), S13(4,3), S14(1,3);
Sommet S21(5,2), S22(8,2), S23(8,5), S24(5,5);

Obstacle O1({S11,S12,S13,S14});
Obstacle O2({S21,S22,S23,S24});

Gobstacle G01 (O1,1);
Gobstacle G02 (O2,2);
cout<<"=====construction du graph===="<<'\n';
Graph G=to_graph_Naive(An,Bn,{G01,G02});
cout<<"======graph fini ======"<<'\n';
// cout<<"on obtiens le graph suivant : "<<G;

cout<<"voisins du point de départ : "<<G.voisins(0)<<'\n';
cout<<"voisins du point d'arrivé : "<<G.voisins(1)<<'\n';

cout<<"voisins d'un point obstacle "<<G.voisins(101)<<'\n';
cout<<"voisins d'un point obstacle "<<G.voisins(203)<<'\n';

cout<<"====== test dijkstra ====="<<'\n';
cout<<"test 1";
auto [l, p] = dijkstra(G, 1);
cout<<"test 2";

// Affichage des distances minimales
cout << "Distances minimales (l) :\n";
for (size_t i = 1; i <= G.nombreSommets; i++) {
    std::cout << "l[" << i << "] = " << l[i] << "\n";
}

// Affichage des prédécesseurs
cout << "\nPrédécesseurs (p) :\n";
for (size_t i = 1; i <= G.nombreSommets; i++) {
    cout << "p[" << i << "] = " << p[i] << "\n";
}

cout<<G.listeArcs[1].Poids;

}