#include "arc-graph.hpp"
#include "obstacle.hpp"

typedef pair<Sommet,int> Node ;
typedef pair<Obstacle,int> Gobstacle;

//on assume qu'un obstacle ne possède pas plus de 100 points

Graph to_graph_Naive(Node D,Node A, initializer_list<Gobstacle> list_gobs){
    Graph G;

    int number_error=0;

    //ajouter une verification d'obstacle overlap
    // est-ce que 2 obstacles s'intersecte ??

    for(auto& gobs : list_gobs){
        int k=0;
        // std::cout<<" ====obstacle :"<<gobs.second<<'\n';

        for(auto& S : gobs.first.sommets){ // prend un sommet de l'obstacle observé

            int ns = gobs.second*100 +k; //ref du sommet S
            
            //ETAPE 1: ajouter les arcs liant l'obstacle à lui même

            if(k==0){
                Segment int_seg(S,gobs.first.sommets[gobs.first.sommets.size()]);
                Arc int_arc(ns,gobs.second*100+gobs.first.sommets.size()-1,int_seg.longueur());
                G.add(int_arc);
            }
            else{
                Segment int_seg(S,gobs.first.sommets[k-1]);
                Arc int_arc(ns,ns-1,int_seg.longueur());
                G.add(int_arc);

            }
            if(k==gobs.first.sommets.size()){
                Segment int_seg(S,gobs.first.sommets[0]);
                Arc int_arc(gobs.second*100,ns,int_seg.longueur());
                G.add(int_arc);
            }
            else{
                Segment int_seg(gobs.first.sommets[k+1],ns);
                Arc int_arc(ns+1,ns,int_seg.longueur());
                G.add(int_arc);
            }

            // ETAPE 2 : Ajouter les arcs [D->S] et [S->A] si ils existent
            Segment DS(D.first,S); Segment SA(S,A.first);
            bool DST =true, SAT = true; //est-ce que le segment est possible
            // std::cout<<"-------"<<S<<"------------"<<'\n';

            for(auto& Kgobs : list_gobs){ //check pour chaque obstacles
                if(Kgobs.first.intersection(DS)){ DST =false;} // il existe un obstacle qui coupe le segment [DS]
                std::cout<<' '; //ne pas supprimer !!!!!!!!!!!
                
                
                if(Kgobs.first.intersection(SA)){ SAT =false;} // il existe un obstacle qui coupe le segment [SA]
                std::cout<<' '; //ne pas supprimer !!!!!!!!!!!
                
                
            }
            // std::cout<<DST<<SAT;
            Arc DSA(0,ns,DS.longueur()); 
            Arc SAA(ns,1,SA.longueur());
            if(DST==true){G.add(DSA);}
            // std::cout<<DSA<<"S"<<'\n'; 
            //ajoute l'arc [D->S] si il ne coupe aucun obstacle
            
            if(SAT==true){G.add(SAA);}
            // std::cout<<SAA<<"S"<<'\n'; 
            //ajoute l'arc [S->A] si il ne coupe aucun obstacle
            // std::cout<<DST<<SAT<<'\n';

            //ETAPE 3: check les obstacles que l'on peut connecter à S
            for(auto& kgobs : list_gobs){ 
                int i=0;
                if(kgobs.second != gobs.second){
                // std::cout<<"---obstacle iteration :"<<kgobs.second<<'\n';
                for(auto& Si : kgobs.first.sommets){
                    // std::cout<<i<<"e iteration pour le sommet "<<ns<<','<<'\n';
                    int ni = kgobs.second * 100 +i; //indice du sommet S
                    Segment SSi(S,Si); 
                    bool ST = true; //est-ce que le segment est possible
                    if(ni!=ns){
                    for(auto& Kgobs : list_gobs){
                    if(Kgobs.first.intersection(SSi)){ ST =false; }
                    }
                    Arc SiA(ns,ni,SSi.longueur());

                    if(SSi.A==SSi.B && ni!=ns ){
                    number_error +=1;
                    std::cout<<SiA<<"error point overlap : "<<number_error<<'\n';
                    std::cout<<SSi.A<<','<<SSi.B<<'\n';
                    }

                    if(ST){G.add(SiA);} 
                    }
                    
                    i+=1;
                }
                }
            }
            k+=1;
        }
    }
    
    std::cout<<'\n';
    std::cout<<"il y a "<<number_error<< " error dans la construction"<<'\n';
    return G;
}



