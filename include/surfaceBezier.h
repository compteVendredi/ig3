#ifndef SURFACEBEZIER_H
#define SURFACEBEZIER_H


#include <vector>
#include <glm/glm.hpp>
#include <courbeBezier.h>
#include <point.h>
#include <math.h>


class SurfaceBezier {
    public:
        SurfaceBezier(const std::vector<std::vector<glm::vec3>>& pointsControles, float pasU, float pasV);
        Point evaluer(float u, float v) const;
        void charger(unsigned int *VBO, unsigned int *VAO, unsigned int *EBO);
        void afficher() const;
        void afficherPolygoneControle() const;
        

    private:
        std::pair<int,int> generer(float pasU, float pasV);
        std::vector<glm::vec3> pointsControles;
        std::vector<Point> points;
        std::vector<unsigned int> indicesPointsControles, indices;
        unsigned int *VAO, taillePointsControlesLigne, taillepointsControlesColonne;
};


#endif
