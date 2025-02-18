#include <iostream>
#include "sommet_graph_N2.hpp"
#include "arc-graph.hpp"
#include "obstacle.hpp"
#include "dijkstra.hpp"

int main(){

Sommet A(1,4);
Sommet B(7,2);

Node An (A,0);
Node Bn (B,1);

Sommet S11(3,0), S12(6,0), S13(6,3), S14(3,3);

Obstacle O1({S11,S12,S13,S14});

Gobstacle G01 (O1,1);
cout<<"=====construction du graph===="<<'\n';
Graph G=to_graph_Naive_2(A,B,{G01});
cout<<"======graph fini ======"<<'\n';
// cout<<"on obtiens le graph suivant : "<<G;

cout<<"voisins du point de départ : "<<G.voisins(0)<<'\n';
cout<<"voisins du point d'arrivé : "<<G.voisins(G.nombreSommets-1)<<'\n';

cout<<"voisins d'un point obstacle "<<G.voisins(2)<<'\n';
cout<<"voisins d'un point obstacle "<<G.voisins(1)<<'\n';

cout<<G;

cout<<"====== test dijkstra ====="<<'\n';
cout<<"test 1";
auto [l, p] = dijkstra(G, 0);
cout<<"test 2";

// Affichage des distances minimales
cout << "Distances minimales (l) :\n";
for (size_t i = 0; i < G.nombreSommets; i++) {
    std::cout << "l[" << i << "] = " << l[i] << "\n";
}

// Affichage des prédécesseurs
cout << "\nPrédécesseurs (p) :\n";
for (size_t i = 0; i < G.nombreSommets; i++) {
    cout << "p[" << i << "] = " << p[i] << "\n";
}


}