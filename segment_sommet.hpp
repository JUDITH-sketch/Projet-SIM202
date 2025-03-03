#ifndef SEGMENT_SOMMET_HPP
#define SEGMENT_SOMMET_HPP

#include <iostream>
#include <cmath>

class Sommet {
public:
    double x, y;

    // Constructeurs
    Sommet(double x = 0, double y = 0) : x(x), y(y) {}

    // Opérateurs mathématiques
    Sommet operator+(const Sommet& autre) const {
        return Sommet(x + autre.x, y + autre.y);
    }

    Sommet operator-(const Sommet& autre) const {
        return Sommet(x - autre.x, y - autre.y);
    }

    // Opérateur unaire pour inverser un Sommet (-s)
    Sommet operator-() const {
        return Sommet(-x, -y);
    }

    // Définition unique pour `Sommet * scalaire` et `scalaire * Sommet`
    friend Sommet operator*(const Sommet& s, double scalaire) {
        return Sommet(s.x * scalaire, s.y * scalaire);
    }
    
    friend Sommet operator*(double scalaire, const Sommet& s) {
        return s * scalaire; // Réutilisation de la première définition
    }

    // Norme du vecteur
    double norme() const {
        return std::sqrt(x * x + y * y);
    }

    // Affichage
    friend std::ostream& operator<<(std::ostream& os, const Sommet& s) {
        os << "(" << s.x << ", " << s.y << ")";
        return os;
    }

    bool operator==(const Sommet& other) const {
    return (x == other.x) && (y == other.y);
}

};

class Segment {
public:
    Sommet A, B;

    // Constructeur
    Segment(const Sommet& A, const Sommet& B) : A(A), B(B) {}

    // Longueur du segment
    double longueur() const {
        return (B - A).norme();
    }

    // Direction du segment
    Sommet direction() const {
        return B - A;
    }

    // Normale au segment
    Sommet normale() const {
        Sommet dir = direction();
        return Sommet(-dir.y, dir.x);  // Rotation de 90°
    }

    // // Test d'intersection avec un autre segment en utilisant les normales
    // bool intersection(const Segment& S) const {
    //     double a = B.x - A.x, b = S.A.x - S.B.x;
    //     double c = B.y - A.y, d = S.A.y - S.B.y;
    //     double det = a * d - b * c;

    //     if (det == 0) return false; // Segments parallèles ou colinéaires

    //     double k1 = S.A.x - A.x;
    //     double k2 = S.A.y - A.y;

    //     double t = (k1 * d - k2 * b) / det;
    //     double u = (k2 * a - k1 * c) / det;
        
    //     bool t1, t2;
    //     if(0<t && t<1){t1=true;}
    //     if(0<u && u<1){t2=true;}
    //     if(t1 && t2){return true;}
    //     return false;
    // }

    // bool intersection(const Segment& S) const {
    //     // Vérifier si les segments sont exactement les mêmes
    //     if ((A == S.A && B == S.B) || (A == S.B && B == S.A)) {
    //         return false;
    //     }
        
    //     // Vérifier si un sommet coïncide
    //     if (A == S.A || A == S.B || B == S.A || B == S.B) {
    //         return false;
    //     }
        
    //     double a = B.x - A.x, b = S.A.x - S.B.x;
    //     double c = B.y - A.y, d = S.A.y - S.B.y;
    //     double det = a * d - b * c;
    
    //     if (det == 0) return false; // Segments parallèles ou colinéaires
    
    //     double k1 = S.A.x - A.x;
    //     double k2 = S.A.y - A.y;
    
    //     double t = (k1 * d - k2 * b) / det;
    //     double u = (k2 * a - k1 * c) / det;
        
    //     // Vérification avec égalité non stricte (inclut les extrémités)
    //     bool t1 = (0 <= t && t <= 1);
    //     bool t2 = (0 <= u && u <= 1);
        
    //     return t1 && t2;
    // }
    

    // Affichage
    friend std::ostream& operator<<(std::ostream& os, const Segment& S) {
        os << "[" << S.A << " -> " << S.B << "]";
        return os;
    }

    bool operator==(const Segment& other) const {
    return (A == other.A && B == other.B) || (A == other.B && B == other.A);
}

};

#endif // SEGMENT_SOMMET_HPP
