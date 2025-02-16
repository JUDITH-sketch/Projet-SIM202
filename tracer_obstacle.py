import matplotlib.pyplot as plt
import matplotlib.pyplot as plt

def tracer_polygones(graphe):
    sommets = {s[0]: (s[1], s[2]) for s in graphe["sommets"]} #dictionnaire des sommets
    arcs = graphe["arcs"]

    fig, ax = plt.subplots()

    
    for id1, id2 in arcs:
        x = [sommets[id1][0], sommets[id2][0]]
        y = [sommets[id1][1], sommets[id2][1]]
        ax.plot(x, y, 'k-', linewidth=2) #on trace chaque portion de segments

    
    ax.set_aspect('equal') #affichage cohérent sinon ça dépasse du quadrillage
    plt.axis('off')  # Supprimer les axes
    plt.show()

# Définition des sommets et des arcs pour la forme en L et les deux polygones
graphe_polygones = {
    "sommets": [
        # Forme en L chelou
        (1, 0, 0), (2, 0, 5), (3, 2, 5), (4, 2, 2), (5, 5, 2), (6, 5, 0),
        
        # Premier pentagone flottant dans le vide du haut
        (7, 3, 3), (8, 3.5, 4.5), (9, 4.5, 4.5), (10, 5, 3), (11, 4, 2.5),

        # Deuxième pentagone flottant  dans le vide du bas
        (12, 2, 1), (13, 2.5, 2), (14, 3.5, 2), (15, 3, 0.5), (16, 1.5, 0.5)
    ],
    "arcs": [
        # Forme en L chelou
        (1, 2), (2, 3), (3, 4), (4, 5), (5, 6), (6, 1),

        # Premier pentagone 
        (7, 8), (8, 9), (9, 10), (10, 11), (11, 7),

        # Deuxième pentagone 
        (12, 13), (13, 14), (14, 15), (15, 16), (16, 12)
    ]
}


tracer_polygones(graphe_polygones) #test