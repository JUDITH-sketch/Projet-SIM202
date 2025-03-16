#include "obstacle.hpp"

int main() {

    // methode testé 
    int methode =1;

    // Définition des points de base
    Sommet e1(1, 0), e2(0, 1);

    // Sommets du carré (ordre important)
    Sommet S1(0, 0), S2(0, 2), S3(2, 2), S4(2, 0);

    // Sommets du L 
    Sommet S5(-1.5, 2), S6(-1, 2), S7(-1, 0.32), S8(0.99, 0.3), S9(0.99, -0.1), S10(-1.51, -0.09);
    

    // Création de l'obstacle (carré de longueur 2)
    Obstacle O({S1, S2, S3, S4});
    Obstacle O1({S5, S6, S7, S8, S9, S10});
    std::cout << "Obstacles créé :\n";

    // Test d'intersection avec un segment qui traverse l'obstacle
    Segment S(e1 - e2, e1 + 3.0 * e2); // Segment (1,-1) -> (1,3)
    std::cout << "Segment testé : " << S << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(S, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    // Test avec un segment aligné sur un bord de l'obstacle
    Segment A(S1, S2); // Segment (0,0) -> (0,2)
    std::cout << "\nSegment testé : " << A << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(A, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher FALSE (propre segment)

    // Test avec segment passant par un sommet de l'obstacle. (diagonale)
    Segment B(-1 * e1 + 3 * e2, 3 * e1 -1 * e2);
    std::cout << "\nSegment testé : " << B << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(B, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    // Test d'intersection avec un segment qui ne traverse pas l'obstacle
    Segment C(3.0 * e1, 4.0 * e1); 
    std::cout << "\nSegment testé : " << C << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(C, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher FALSE

    // Test d'intersection avec un segment qui traverse l'obstacle (diagonale)
    Segment D(S1, S3); 
    std::cout << "\nSegment testé : " << D << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(D, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    // Test d'intersection avec un segment qui entre dans l'obstacle mais qui n'en sort pas
    Segment E(S1, e1 + e2); 
    std::cout << "\nSegment testé : " << E << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(E, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE

    // Test d'intersection avec un segment contenu entièrement dans l'obstacle
    Segment F(0.5 * e1 + e2, 1.5 * e1 + e2);
    std::cout << "\nSegment testé : " << F << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O.intersection(F, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher TRUE
    
    // Test d'intersection avec le L 
    Segment G(S6, S8);
    std::cout << "\nSegment testé : " << G << "\n";
    std::cout << "Intersection avec l'obstacle ? " << (O1.intersection(F, methode) ? "TRUE" : "FALSE") << "\n"; // Doit afficher FALSE
}
