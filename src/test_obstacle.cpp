#include "obstacle.hpp"

int main() {
    // Définition des points de base
    Sommet e1(1, 0), e2(0, 1);

    // Sommets de l'obstacle (ordre important)
    Sommet S1(0, 0), S2(0, 2), S3(2, 2), S4(2, 0);

    // Création de l'obstacle (carré de longueur 2)
    Obstacle O({S1, S2, S3, S4});
    std::cout << "Obstacle créé :\n";

    // Test d'intersection avec un segment qui traverse l'obstacle
    Segment S(e1 - e2, e1 + 3.0 * e2); // Segment (1,-1) -> (1,3)
    std::cout << "Segment testé : " << S << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(S) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    // Test avec un segment aligné sur un bord de l'obstacle
    Segment A(S1, S1 + 2.0 * e1); // Segment (0,0) -> (2,0)
    std::cout << "\nSegment testé : " << A << "\n";
    std::cout << "Intersection avec le premier segment ? " << (A.intersection(S) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE (intersection en (1,0))

    // Test avec segment passant par un sommet de l'obstacle. 
    Segment B(-1 * e1 + 3 * e2, 3 * e1 -1 * e2);
    std::cout << "\nSegment testé : " << B << "\n";
    std::cout << "Intersection avec le premier segment ? " << (A.intersection(B) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    return 0;
}
