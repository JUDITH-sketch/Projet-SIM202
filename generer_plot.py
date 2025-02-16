import matplotlib.pyplot as plt
from collections import defaultdict

def lire_graphe(fichier):
    """Lit un fichier et extrait les points de départ, d'arrivée et les obstacles."""
    depart, arrivee = None, None
    sommets = []
    obstacles = defaultdict(list)  # Dictionnaire pour regrouper les sommets des obstacles par référence

    with open(fichier, "r") as file:
        for ligne in file:
            elements = ligne.strip().split() # Supprime les espaces en début/fin de ligne et divise le texte en une liste de mots
            if not elements:
                continue  # Ignore les lignes vides

            type_donnee = elements[0]

            if type_donnee == "DEBUT":
                depart = tuple(map(float, elements[1:3]))  # Convertit les coordonnées en tuple (x, y)
            elif type_donnee == "FIN":
                arrivee = tuple(map(float, elements[1:3]))  
            elif type_donnee == "SOMMET":
                _, x, y, ref = map(float, elements[1:])  # Extrait les coordonnées et la référence
                sommets.append((x, y, int(ref)))  # Stocke les sommets avec leur référence
                if ref >= 1:
                    obstacles[int(ref)].append((x, y))  # Regroupe les sommets des obstacles par référence

    return depart, arrivee, sommets, obstacles

def tracer_graphe(fichier):
    """Trace un graphe avec obstacles, départ et arrivée."""
    depart, arrivee, sommets, obstacles = lire_graphe(fichier)

    plt.figure(figsize=(8, 6))

    # Trace les obstacles sous forme de polygones remplis
    for points in obstacles.values():
        x_vals, y_vals = zip(*points)  # Sépare les coordonnées X et Y
        plt.fill(x_vals + (x_vals[0],), y_vals + (y_vals[0],), color="gray", alpha=0.5)  # Remplit l'obstacle

    # Affichage des points de départ et d'arrivée avec une légende
    plt.scatter(*depart, color="green", s=100, label="Départ")  # Départ en vert
    plt.scatter(*arrivee, color="red", s=100, label="Arrivée")  # Arrivée en rouge

    # Affichage des sommets des obstacles (en noir)
    for x, y, ref in sommets:
        if ref >= 1:
            plt.scatter(x, y, color="black", s=50)  # Points des obstacles en noir

    # Personnalisation du graphique
    plt.legend()  
    plt.xlabel("X")  
    plt.ylabel("Y")  
    plt.title("Visualisation du Graphe")  
    plt.grid(True)  
    plt.show()

tracer_graphe("graph_data.txt")
