#include "arc-graph.hpp"
#include "obstacle.hpp"

typedef pair<Sommet,int> Node ;
typedef pair<Obstacle,int> Gobstacle;

using namespace std;

//on assume qu'un obstacle ne possède pas plus de 100 points

Graph to_graph_Naive_2(const Sommet D,const Sommet A,const  initializer_list<Gobstacle> list_gobs){

    Graph G;

    // cout<<'\n'<<"-----------generation liste---------------"<<'\n';
    //INIT liste
    int n=2;
    for(auto& obs:list_gobs){
        n+=obs.first.sommets.size();
    }
    int nb_sommet = n; //nombre de sommet total dans le graph
    vector<Sommet> list_sommet;     list_sommet.reserve(n+1);        
    vector<int> list_indice;        list_indice.reserve(n+1);
    vector<int> list_ref;           list_ref.reserve(n+1);
    int k =1;

    for(auto& obst:list_gobs){
        for(auto& S : obst.first.sommets){
        list_sommet[k]  = S;     
        list_indice[k]  = k;
        list_ref[k]     = obst.second;
        k+=1;
        }
    }
    cout<<nb_sommet;
    list_sommet[0]=D; list_indice[0]=0; list_ref[0]=0; 
    list_sommet[n-1]=A; list_indice[n-1]=n-1; list_ref[n-1]=-1;

    // for(int k=0;k<n;k++){
    //     cout<<list_sommet[k]<<" , "<<list_indice[k]<<" , "<<list_ref[k]<<'\n';
    // }

    cout<<'\n'<<"-----------------obstacle interne-------------"<<'\n';
    //Ajoute obstacle_k -> obstacle_k
    int ref=1;          //ref de l'obstacle
    int ref_prem=1;     //ref du premier sommet de l'obstacle
    for(int k=1;k<nb_sommet;k++){
        if(list_ref[k+1]==ref){

        Segment iter_seg(list_sommet[k],list_sommet[k+1]);
        Arc iter_arc(list_indice[k],list_indice[k+1],iter_seg.longueur());
        G.add(iter_arc); 
        G.add(inverse(iter_arc));

        cout<<iter_arc<<" bruh "<<'\n';

        }
        else{
        if(ref_prem !=nb_sommet-1){ // n'envoie pas le dernier sommet sur lui même
        Segment iter_seg(list_sommet[k],list_sommet[ref_prem]);
        Arc iter_arc(list_indice[k],list_indice[ref_prem],iter_seg.longueur());
        cout<<iter_seg<<'\n';
        G.add(iter_arc);
        G.add(inverse(iter_arc));

        cout<<iter_arc<<" exit "<<'\n';

        ref +=1;
        ref_prem = k+1;
        }
        }
        cout<<ref<<" "<<ref_prem;
    }

    //Ajoute obstacle_i -> obstacle_j
    cout<<'\n'<<"-----------------obstacle externe-------------"<<'\n';
    for(int i=1;i<nb_sommet-1;i++){ //boucle sur tout les sommets
        cout<<'\n'<<"-----------------obstacle externe sommets--"<<i<<"----------"<<'\n';
        Segment DS (D,list_sommet[i]);        Segment SA (list_sommet[i],A);

        bool inter_DS =false ; bool inter_SA =false;

        for(auto& gobs: list_gobs){
            if(gobs.first.intersection(DS)==true){inter_DS =true; std::cout<<" ";}
            if(gobs.first.intersection(SA)==true){inter_SA =true; std::cout<<" "; } // ne pas enlever les Cout !!!
        }
        
        Arc DS_arc(list_indice[i],list_indice[0],DS.longueur());
        Arc SA_arc(list_indice[i],list_indice[nb_sommet-1],DS.longueur());

        if(inter_DS==false){
            cout<<DS<<'\n';
            G.add(DS_arc); 
            G.add(inverse(DS_arc));
            cout<<DS_arc<<" DS "<<i<<'\n';
        }

        if(inter_SA==false){
            cout<<SA<<'\n';
            G.add(SA_arc); 
            G.add(inverse(SA_arc));
            cout<<SA_arc<<" SA "<<i<<'\n';
        }


        cout<<'\n'<<"-----------------obstacle externe obstacles-------------"<<'\n';

        for(int j=1;j<nb_sommet-1;j++){ //boucle sur les sommets non extremales
            cout<<j;
            if(list_ref[i]!=list_ref[j]) // diff obstacle
            {
                Segment iter_seg(list_sommet[i],list_sommet[j]);
                bool inter=false; //innocent jusqu'à preuve du contraire

                for(auto& gobs: list_gobs){
                    if(gobs.first.intersection(iter_seg)==true){inter=true;}
                }

                if(inter==false){
                    Arc iter_arc (list_indice[i],list_indice[j],iter_seg.longueur());
                    cout<<iter_seg<<'\n';
                    G.add(iter_arc);
                    G.add(inverse(iter_arc));
                    cout<<iter_arc<<" "<<i<<","<<j<<" bloub "<<'\n';
                }

            }
        }
    }

    return G;

}


