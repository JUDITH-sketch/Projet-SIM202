# Projet-SIM202
                                                  Planification de trajectoire   
Bienvenue dans le READ ME de notre projet de C++ pour le cours de SIM202.

Ce Readme fera office de documentation pour l'ensemble du code que nous vous présentons dans ce dossier. 

Nous pouvons diviser le dossier de notre projet en trois catégories et ce Readme est organisé selon ces trois catégories. Nous avons dans un premier temps les fichiers .hpp qui concernent toutes les fonctions de notre cod ainsi que les différentes classes. Ils sont organisé de manière linéaire selon l'ordre logique dans lequel ils ont été crée. Nous avons ensuite tous les fichiers test_XX_.cpp qui sont des fichiers permettant de tester de manière indépendante la compilation ainsi que l'éxécution de chaque fonctions ou groupe de fonctions de manière indépendante, sans se soucier du résultat en lien avec notre programme. Enfin nous avons les fichiers exemple_X.cpp qui sont des fichiers permettant de valider l'entierté du projet et de notre code et de visualiser les différents résultats. 

Enfin en plus de ces trois catégories de fichier nous avons également une routine python (sur le folder deux sont proposées la première est simplement une première version) 

Les fichiers .cpp génèrent des fichiers .txt qui sont ensuite lu par la routine python trace_parcours_optimal.py. Mais vous n'avez pas besoin de vous soucier du fonctionnement de la compilation et de l'éxécution des fichiers exemple_X.cpp, en effet nous avons rédiger un make file qui vous permet de simplement après la commande make donner le numéro de l'exemple que vous souhaitez tester et la visualisation de ces différents exemple. Ainsi dans ce fichier nous détaillerons simplement quelle situation/cas chaque numéro de fichier exemple_x.cpp permet de tester. 

Voilà finalement pour conclure le plan de ce Readme : 

I° Les fichiers .hpp
II° Les fichiers test_X.cpp : tests indépendants des fonctions et des classes des fichiers .hpp
III° Routines python
III° Les fichiers exemple_X.cpp : les différents résultats.
IV° Makefile 


I° Les fichiers .hpp 

// segment_sommet.hpp 

Ce fichier contient la définition des classes Sommet et Segment et de leurs différentes fonctions élémentaires : opérateurs simples, norme, test d'égalité, direction du segment,normale, milieu. Pour la classe segment elle contient notamment la fonction intersection verifiant si deux segments sont en intersection et la fonction distance à un point utile ensuite pour créer le graphe. 

// obstacle.hpp 

Ce fichier contient l'ensemble des fonctions de la classe obstacle permettant de la définir. Ils sont construits à partir d'une liste de sommets qui définissent les différents sommets d'un obstacle donnée. Ce fichier contient notamment les fonctions calcul des normales, slide, grow, inversion (qui inverse l'ordre des sommets qui sont numérotés), les fonctions qui vérifient si un point est exactement sur l'arrête d'une polygone, vérifient si un point est à l'intérieur d'un polygone qui sont utiles pour la méthode ray tracing ( qui est notre première méthode pour vérifier si il y a une intersection). Elle contient une dernière fonction intersection ainsi que toutes les fonctions relatives à l'implémentation des obstacles avec la méthode de Padding. 

// arc_graph.hpp 

Ce fichier contient l'implémentation des classes arcs et graphe qui permettent de gérer ces objets de manière indépendante du problème rencontré. Un arc est défini commme deux numéros de sommets et un poids. 
La classe arc contient les fonctions suivantes : constructeurs, et autre fonction banale : affichage du sommet de départ, du sommet d'arrivé et les opérateurs d'affichage. 
La classe graphe quant à elle contient tous les outils qui pourraient être attendus dans l'implémentation d'un graph : constructeurs, liste de voisins, ajout d'un arc au graphe, et différentes fonctions d'affichage. 

// generer_graph_naif.hpp
Ce fichier contient une version simplifiée et exhaustive de la génération du graphe sans optimisation. Il contient la fonction to_graph_Naive_3 (génération d’un graphe en testant toutes les connexions possibles entre sommets).
// generer_graph.hpp
Ce fichier génère le graphe en tenant compte des obstacles en connectant les sommets valides. Il contient les fonctions suivantes : to_graph (création du graphe en appliquant les méthodes d’intersection), ajouter_arcs (ajout des arcs valides), et des fonctions d'affichage
// dijkstra.hpp 
Ce fichier implémente l'algorithme de Dijkstra pour trouver le plus court chemin dans un graphe. Il contient les fonctions suivantes : dijkstra (calcul des distances minimales), reconstruct_path (reconstruction du chemin optimal), et des fonctions d'affichage des résultats.
// generer_txt.hpp
Ce fichier exporte les données du graphe vers un fichier texte pour être exploité par le programme Python. Il contient la fonction exporter_graphe_vers_fichier (écriture des sommets, des arcs et du chemin optimal dans un fichier texte).
II° Les fichiers test_X.cpp
Ces fichiers test permettent de tester les fonctions de manière individuelles. Pour les tester il suffit de les compiler individuellement et de se référer au rapport pour savoir ce qui est tester dans ce fichier. La compilation de ces fichiers n'est pas géré par le makefile. 

III° Routines Python
Ces fichiers est compilé dans le makefile il n'est pas nécessaire de les compiler. Ils servent à faire la visualisation des exemples. 
IV° Les fichiers exemple_X.cpp
Ces différents fichiers permettent finalement d'appliquer notre programme à plusieurs cas. A chaque fois le cas testé est précisé en commentaire en haut du fichier d'exemple. 
Finalement pour éxécuter notre programme vous n'avez qu'a faire make puis préciser le numéro de l'exemple que vous voulez tester. Une fichier "figure.png" se créera et vous permettra de visualiser l'exemple que vous venez de tester. 
Petit rappel des exemples testés : 

- Exemple 1 : un carré simple c'est l'exemple de base de l'énnoncé
- Exemple 2 :  Deux exemples dont un pentagone (utile pour exemple d'alignement des points)
- Exemple 3 : Exemple complexe de l'ennoncé
- Exemple 4 : Exemple Haie 
- Exemple 5 : Obstacle carré avec trois points alignés 
- Exemple 6 : Obstacle généré de manière aléatoire
- Exemple 7 : Configuration entièrement choisie par l'utilisateur

Dernière remarque pour la compilation : 

- il existe trois méthode pour l'intersection elles ont des numéros  1(Ray-Tracing), 2(Segments_ouverts_fermés), 3(Normales). On a la possibilité de run le code avec chacune des méthodes en allant modifier dans to_graph_naive_3  présent dans le fichier generer_graph. le numéro passé en argument.
- Il existe une option padding que l'on peut activer en mettant true de même dans to_graph_naive_3 également
V° Makefile


- faire make pour éxécuter les exemples
- faire make clean pour se débarasser des fichier .x et du fichier texte intermédiaire
