#include <iostream>
#include "obstacle.hpp"

int main() {
    // ==================== CAS 1 : Obstacles NON chevauchants ====================
    std::cout << "\n[TEST 1] Obstacles non chevauchants : Doit afficher FALSE\n";
    Obstacle O1({{0,0}, {0,2}, {2,2}, {2,0}});  // Carré
    Obstacle O2({{3,3}, {3,5}, {5,5}, {5,3}});  // Carré éloigné
    std::vector<std::pair<Obstacle, int>> obstacles1 = {{O1, 1}, {O2, 2}};
    std::cout << "Chevauchement détecté ? " 
              << (Obstacle :: obstacles_se_chevauchent(obstacles1) ? "TRUE" : "FALSE") 
              << "\n"; // Doit afficher FALSE

    // ==================== CAS 2 : Un obstacle contenu dans un autre ====================
    std::cout << "\n[TEST 2] Un obstacle est entièrement à l'intérieur d'un autre : Doit afficher TRUE\n";
    Obstacle O3({{0,0}, {0,4}, {4,4}, {4,0}});  // Grand carré
    Obstacle O4({{1,1}, {1,2}, {2,2}, {2,1}});  // Petit carré contenu
    std::vector<std::pair<Obstacle, int>> obstacles2 = {{O3, 1}, {O4, 2}};
    std::cout << "Chevauchement détecté ? " 
              << (Obstacle :: obstacles_se_chevauchent(obstacles2) ? "TRUE" : "FALSE") 
              << "\n"; // Doit afficher TRUE

    // ==================== CAS 3 : Obstacles partageant une arête ====================
    std::cout << "\n[TEST 3] Obstacles partageant une arête : Doit afficher FALSE (cas particulier)\n";
    Obstacle O5({{0,0}, {0,2}, {2,2}, {2,0}});
    Obstacle O6({{2,0}, {2,2}, {4,2}, {4,0}}); // Partage le bord droit de O5
    std::vector<std::pair<Obstacle, int>> obstacles3 = {{O5, 1}, {O6, 2}};
    std::cout << "Chevauchement détecté ? " 
              << (Obstacle :: obstacles_se_chevauchent(obstacles3) ? "TRUE" : "FALSE") 
              << "\n"; // Doit afficher FALSE selon l'implémentation

    // ==================== CAS 4 : Obstacles avec intersection ====================
    std::cout << "\n[TEST 4] Obstacles avec une intersection d'arêtes : Doit afficher TRUE\n";
    Obstacle O7({{0,0}, {0,2}, {2,2}, {2,0}});
    Obstacle O8({{1,1}, {1,3}, {3,3}, {3,1}}); // Se croise avec O7
    std::vector<std::pair<Obstacle, int>> obstacles4 = {{O7, 1}, {O8, 2}};
    std::cout << "Chevauchement détecté ? " 
              << (Obstacle :: obstacles_se_chevauchent(obstacles4) ? "TRUE" : "FALSE") 
              << "\n"; // Doit afficher TRUE

    // ==================== CAS 5 : Un sommet sur le bord de l'autre ====================
    std::cout << "\n[TEST 5] Un sommet d'un obstacle est sur un bord de l'autre : Doit afficher FALSE\n";
    Obstacle O9({{0,0}, {0,2}, {2,2}, {2,0}});
    Obstacle O10({{2,2}, {3,3}, {4,2}, {3,1}}); // Son sommet (2,2) touche le bord de O9
    std::vector<std::pair<Obstacle, int>> obstacles5 = {{O9, 1}, {O10, 2}};
    std::cout << "Chevauchement détecté ? " 
              << (Obstacle :: obstacles_se_chevauchent(obstacles5) ? "TRUE" : "FALSE") 
              << "\n"; // Doit afficher FALSE

    return 0;
}
