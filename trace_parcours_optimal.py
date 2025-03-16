import matplotlib
#matplotlib.use('Agg') ajouter pour Judith parce que j'arrive pas à les afficher sur vs code
import matplotlib.pyplot as plt
from collections import defaultdict

def lire_graphe(fichier):
    """Lit un fichier et extrait les points de départ, d'arrivée, les obstacles et le plus court chemin."""
    
    # Initialisation des variables
    depart, arrivee = None, None
    sommets = []
    obstacles = defaultdict(list)  # Dictionnaire associant chaque obstacle à ses sommets
    chemin_plus_court = []  # Liste des points du chemin le plus court
    section = None  # Indique la section en cours de lecture

    # Ouverture du fichier en mode lecture
    with open(fichier, "r") as file:
        for ligne in file:
            elements = ligne.strip().split()  # Supprime les espaces superflus et divise la ligne en éléments
            
            if not elements:
                continue  # Ignore les lignes vides

            type_donnee = elements[0]  # Identifie le type de donnée

            # Détection des sections du fichier
            if type_donnee == "DEBUT":
                depart = tuple(map(float, elements[1:3]))  # Convertit en tuple de coordonnées (x, y)
            elif type_donnee == "FIN":
                arrivee = tuple(map(float, elements[1:3]))
            elif type_donnee == "SOMMETS":
                section = "sommets"
                continue  # Ignore l'en-tête
            elif type_donnee == "ARCS":
                section = "arcs"
                continue
            elif type_donnee == "CHEMIN_PLUS_COURT":
                section = "chemin_plus_court"
                continue

            # Lecture des données selon la section
            if section == "sommets":
                _, index, x, y, ref = elements  # Extraction des valeurs
                x, y, ref = float(x), float(y), int(ref)  # Conversion aux bons types
                sommets.append((x, y, ref))
                if ref >= 1:
                    obstacles[ref].append((x, y))  # Regroupement des sommets par obstacle

            elif section == "chemin_plus_court":
                x, y = map(float, elements)  # Conversion des coordonnées
                chemin_plus_court.append((x, y))

    return depart, arrivee, sommets, obstacles, chemin_plus_court


def tracer_graphe(fichier):
    """Trace un graphe avec obstacles, départ, arrivée et le plus court chemin."""
    
    # Lecture des données du fichier
    depart, arrivee, sommets, obstacles, chemin_plus_court = lire_graphe(fichier)

    plt.figure(figsize=(8, 6))

    # Tracé des obstacles sous forme de polygones remplis
    for points in obstacles.values():
        x_vals, y_vals = zip(*points)  # Séparation des coordonnées X et Y
        plt.fill(x_vals + (x_vals[0],), y_vals + (y_vals[0],), color="gray", alpha=0.5)  # Remplissage des obstacles

    # Affichage des points de départ et d'arrivée
    plt.scatter(*depart, color="green", s=100, label="Départ")  # Départ en vert
    plt.scatter(*arrivee, color="red", s=100, label="Arrivée")  # Arrivée en rouge

    # Affichage des sommets des obstacles en noir
    for x, y, ref in sommets:
        if ref >= 1:
            plt.scatter(x, y, color="black", s=50)

    # Tracé du chemin le plus court en rouge
    if chemin_plus_court:
        x_values, y_values = zip(*chemin_plus_court)
        plt.plot(x_values, y_values, "r-", linewidth=2, label="Chemin le plus court")

    # Personnalisation du graphique
    plt.legend()
    plt.xlabel("X")
    plt.ylabel("Y")
    plt.title("Visualisation du Graphe avec Chemin Optimal")
    plt.grid(True)
    #plt.show()
    plt.savefig('figure.png', dpi=300, bbox_inches='tight')



# Exécution de la fonction pour afficher le graphe
tracer_graphe("graph_data.txt")
