#include "arc_graph.hpp"
#include "obstacle.hpp"

typedef pair<Sommet, int> Node;
typedef pair<Obstacle, int> Gobstacle;

using namespace std;

// On assume qu'un obstacle ne possède pas plus de 100 points
Graph to_graph_Naive_2(const Sommet D, const Sommet A, const initializer_list<Gobstacle> list_gobs) {
    Graph G;

    // ----------- Initialisation des listes ---------------
    int n = 2;
    for (auto& obs : list_gobs) {
        n += obs.first.sommets.size();
    }
    
    int nb_sommet = n;  // Nombre total de sommets dans le graphe
    vector<Sommet> list_sommet(n + 1);
    vector<int> list_indice(n + 1);
    vector<int> list_ref(n + 1);

    int k = 1;
    for (auto& obst : list_gobs) {
        for (auto& S : obst.first.sommets) {
            list_sommet[k] = S;
            list_indice[k] = k;
            list_ref[k] = obst.second;
            k++;
        }
    }

    cout << nb_sommet;

    list_sommet[0] = D;
    list_indice[0] = 0;
    list_ref[0] = 0;

    list_sommet[n - 1] = A;
    list_indice[n - 1] = n - 1;
    list_ref[n - 1] = -1;

    cout << "\n----------------- Obstacle Interne -------------\n";

    // Ajoute obstacle_k -> obstacle_k
    int ref = 1;        // Référence de l'obstacle
    int ref_prem = 1;   // Référence du premier sommet de l'obstacle

    for (int k = 1; k < nb_sommet; k++) {
        if (list_ref[k + 1] == ref) {
            Segment iter_seg(list_sommet[k], list_sommet[k + 1]);
            Arc iter_arc(list_indice[k], list_indice[k + 1], iter_seg.longueur());
            G.add(iter_arc);
            G.add(inverse(iter_arc));

            cout << iter_arc << " bruh \n";
        } 
        else {
            if (ref_prem != nb_sommet - 1) { // N'envoie pas le dernier sommet sur lui-même
                Segment iter_seg(list_sommet[k], list_sommet[ref_prem]);
                Arc iter_arc(list_indice[k], list_indice[ref_prem], iter_seg.longueur());
                
                cout << iter_seg << '\n';
                G.add(iter_arc);
                G.add(inverse(iter_arc));
                cout << iter_arc << " exit \n";

                ref++;
                ref_prem = k + 1;
            }
        }
        cout << ref << " " << ref_prem;
    }

    // ----------------- Obstacle Externe -------------
    cout << "\n----------------- Obstacle Externe -------------\n";

    for (int i = 1; i < nb_sommet - 1; i++) { // Boucle sur tous les sommets
        cout << "\n----------------- Obstacle Externe Sommet -- " << i << " ----------\n";

        Segment DS(D, list_sommet[i]);
        Segment SA(list_sommet[i], A);

        bool inter_DS = false;
        bool inter_SA = false;

        for (auto& gobs : list_gobs) {
            if (gobs.first.intersection(DS)) inter_DS = true;
            if (gobs.first.intersection(SA)) inter_SA = true;
        }

        Arc DS_arc(list_indice[i], list_indice[0], DS.longueur());
        Arc SA_arc(list_indice[i], list_indice[nb_sommet - 1], SA.longueur());

        if (!inter_DS) {
            cout << DS << '\n';
            G.add(DS_arc);
            G.add(inverse(DS_arc));
            cout << DS_arc << " DS " << i << '\n';
        }

        if (!inter_SA) {
            cout << SA << '\n';
            G.add(SA_arc);
            G.add(inverse(SA_arc));
            cout << SA_arc << " SA " << i << '\n';
        }

        // ----------------- Obstacle Externe Obstacles -------------
        cout << "\n----------------- Obstacle Externe Obstacles -------------\n";

        for (int j = 1; j < nb_sommet - 1; j++) { // Boucle sur les sommets non extrêmes
            cout << j;
            if (list_ref[i] != list_ref[j]) { // Différents obstacles
                Segment iter_seg(list_sommet[i], list_sommet[j]);
                bool inter = false; // Innocent jusqu'à preuve du contraire

                for (auto& gobs : list_gobs) {
                    if (gobs.first.intersection(iter_seg)) inter = true;
                }

                if (!inter) {
                    Arc iter_arc(list_indice[i], list_indice[j], iter_seg.longueur());
                    cout << iter_seg << '\n';
                    G.add(iter_arc);
                    G.add(inverse(iter_arc));
                    cout << iter_arc << " " << i << "," << j << " bloub \n";
                }
            }
        }
    }

    return G;
}
