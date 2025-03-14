#include "arc_graph.hpp"
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
            //on suit le contour prédéfinit de l'obstacle
            //une approche plus poussé pourrait faire des raccourcis
            //mais cela demanderais des données sur les autres obstacles 
            //l'algorithme serait donc plus couteux
            
            if(k==0){ // cas particulier du 1er sommet
                Segment int_seg(S,gobs.first.sommets[gobs.first.sommets.size()]);
                Arc int_arc(ns,gobs.second*100+gobs.first.sommets.size()-1,int_seg.longueur());
                G.add(int_arc);
            }
            else{
                Segment int_seg(S,gobs.first.sommets[k-1]);
                Arc int_arc(ns,ns-1,int_seg.longueur());
                G.add(int_arc);

            }
            if(k==gobs.first.sommets.size()){ // cas particulier du dernier sommet
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

            //Il est encore à déterminer pourquoi ces lignes de codes sont nécessaire au bon fonctionnement de l'algo
                
                
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
                //kgobs l'obstacle d'itération
                
                int i=0;
                
                if(kgobs.second != gobs.second){ 
                //vérification que l'on ne traite pas du même obstacle (déjà fait dans l'étape 1)
                    
                // std::cout<<"---obstacle iteration :"<<kgobs.second<<'\n';
                    
                for(auto& Si : kgobs.first.sommets){
                    //prends un sommet de l'obstacle k 
                    
                    // std::cout<<i<<"e iteration pour le sommet "<<ns<<','<<'\n';
                    
                    int ni = kgobs.second * 100 +i; 
                    //indice du sommet S
                    
                    Segment SSi(S,Si); 
                    bool ST = true; //est-ce que le segment est possible
                    
                    if(ni!=ns){ //evite les arcs de poids 0
                        
                    for(auto& Kgobs : list_gobs){
                    if(Kgobs.first.intersection(SSi)){ ST =false; }
                    } // check l'intersection avec tout les obstacles disponibles
                    // pensé : essayer de voir si il est possible d'enlever kgobs et gobs du check sans bug
                        
                    Arc SiA(ns,ni,SSi.longueur());

                    if(SSi.A==SSi.B && ni!=ns ){//check si 2 indices différents renvoie le même points
                                                //bug patched
                    number_error +=1;
                    std::cout<<SiA<<"error point overlap : "<<number_error<<'\n';
                    std::cout<<SSi.A<<','<<SSi.B<<'\n';
                    }

                    if(ST){G.add(SiA);} //si l'arc est possible on l'ajoute au graph
                    }
                    //sinon on passe à la suite
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



