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

Ce fichier contient la définition des classes Sommet et Segment et de leurs différentes fonctions élémentaires. Pour la classe segment elle contient notamment la fonction intersection verifiant si deux segments sont en intersection et la fonction distance à un point utile ensuite pour créer le graphe. 

// obstacle.hpp 

Ce fichier contient l'ensemble des fonctions de la classe obstacle permettant de la définir. Ils sont construits à partir d'une liste de sommets qui définissent les différents sommets d'un obstacle donnée. Ce fichier contient notamment les fonctions calcul des normales, slide, grow, inversion (qui inverse l'ordre des sommets qui sont numérotés), les fonctions qui vérifient si un point est exactement sur l'arrête d'une polygone, vérifient si un point est à l'intérieur d'un polygone qui sont utiles pour la méthode ray tracing ( qui est notre première méthode pour vérifier si il y a une intersection). Elle contient une dernière fonction intersection ainsi que toutes les fonctions relatives à l'implémentation des obstacles avec la méthode de Padding. 

// arc_graph.hpp 

Ce fichier contient l'implémentation des classes arcs et graphe qui permettent de gérer ces objets de manière indépendante du problème rencontré. Un arc est défini commme deux numéros de sommets et un poids. 
La classe arc contient les fonctions suivantes : constructeurs, et autre fonction banale : affichage du sommet de départ, du sommet d'arrivé et les opérateurs d'affichage. 
La classe graphe quant à elle contient tous les outils qui pourraient être attendus dans l'implémentation d'un graph : constructeurs, liste de voisins, ajout d'un arc au graphe, et différentes fonctions d'affichage. 

// generer_graph_naif.hpp

// generer_graph.hpp

// dijkstra.hpp 

// generer_txt.hpp

II° Les fichiers test_X.cpp

III° Routines Python

IV° Les fichiers exemple_X.cpp

V° Makefile


