import matplotlib.pyplot as plt
from collections import defaultdict

def lire_graphe(fichier):
    """
    Lit les données du fichier `graph_data.txt` et extrait :
    - Le point de départ et d'arrivée
    - Les sommets des obstacles (classés par référence)
    """
    depart, arrivee = None, None
    sommets = []
    obstacles_groupes = defaultdict(list)  # Dictionnaire pour stocker les obstacles par référence

    with open(fichier, "r") as file:
        for ligne in file:
            elements = ligne.strip().split()
            if not elements:
                continue  # Ignore les lignes vides

            type_donnee = elements[0]

            # Lecture du point de départ
            if type_donnee == "DEBUT":
                depart = (float(elements[1]), float(elements[2]))

            # Lecture du point d'arrivée
            elif type_donnee == "FIN":
                arrivee = (float(elements[1]), float(elements[2]))

            # Ignore l'en-tête "SOMMETS"
            elif type_donnee == "SOMMETS":
                continue  

            # Lecture des sommets (points du graphe)
            elif type_donnee == "SOMMET":
                idx, x, y, ref = int(elements[1]), float(elements[2]), float(elements[3]), int(elements[4])
                sommets.append((x, y, ref))
                
                # Stocke les points d'obstacles selon leur référence
                if ref >= 1:
                    obstacles_groupes[ref].append((x, y))

    return depart, arrivee, sommets, obstacles_groupes

def tracer_graphe(fichier):
    """
    Trace le graphe à partir des données lues dans `graph_data.txt`
    - Affiche les points de départ (vert) et d'arrivée (rouge)
    - Relie les sommets des obstacles pour former des formes fermées
    - Remplit les zones des obstacles en gris
    """
    depart, arrivee, sommets, obstacles_groupes = lire_graphe(fichier)

    plt.figure(figsize=(8, 6))

    # Trace et remplit chaque obstacle séparément
    for ref, points in obstacles_groupes.items():
        x_vals, y_vals = zip(*points)  # Sépare les coordonnées X et Y

        # Remplissage de la zone de l'obstacle en gris clair
        plt.fill(x_vals + (x_vals[0],), y_vals + (y_vals[0],), color="gray", alpha=0.5)

        # Tracé du contour de l'obstacle en noir
        #plt.plot(x_vals + (x_vals[0],), y_vals + (y_vals[0],), "black", linewidth=1.5)  

    # Affichage des points du graphe
    for x, y, ref in sommets:
        if ref == 0:  # Point de départ
            plt.scatter(x, y, color="green", s=100, label="Départ" if "Départ" not in plt.gca().get_legend_handles_labels()[1] else "")
        elif ref == -1:  # Point d'arrivée
            plt.scatter(x, y, color="red", s=100, label="Arrivée" if "Arrivée" not in plt.gca().get_legend_handles_labels()[1] else "")
        elif ref >= 1:  # Points des obstacles
            plt.scatter(x, y, color="black", s=50)

    # Personnalisation du tracé
    plt.legend()
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Visualisation du Graphe - Départ, Arrivée et Obstacles")
    plt.grid(True)
    plt.show()

# Exécuter la visualisation
tracer_graphe("graph_data.txt")
