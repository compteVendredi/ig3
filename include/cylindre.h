#ifndef CYLINDRE_H
#define CYLINDRE_H

#include <vector>
#include <point.h>
#include <glad/glad.h>
#include <iostream>

class Cylindre{
    public:
        Cylindre(unsigned int subdivisionsH, unsigned int subdivisionsV);
        void afficher();
        void free();
        std::vector<Point>* getPoints();
    private:
        void genererCylindre(unsigned int subdivisionsH, unsigned int subdivisionsV);
        void actualiser();
        std::vector<Point> points;
        std::vector<unsigned int> indices;
        unsigned int VAO, VBO, EBO;
};

#endif
